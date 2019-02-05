/* ImageC - An Image Manipulation Program based on ImageJ
*	Copyright(C) 2018 Felipe Álvarez Avaria <faaa97@protonmail.com>
*
*	This program is free software : you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.If not, see <https://www.gnu.org/licenses/>.
*/
#include "RawImage.h"



RawImage::RawImage(){
}

RawImage::RawImage(unsigned char* raw, wxSize size, unsigned t){
	rawImg = raw;
	imgSize = size;
	type = t;

	resetHistogram();
}


RawImage::~RawImage(){
	delete[] histogram;
}

unsigned char RawImage::getBrightness(){
	if (!valid_histogram)
		computeHistogram();
	return brightness;
}

unsigned char RawImage::getContrast(){

	if (!valid_histogram)
		computeHistogram();
	return contrast;
}

void RawImage::computeWithLUT(const LookUpTable& table){

	unsigned char* datap = rawImg;

	for (int i = 0; i < imgSize.GetX(); i++) {
		for (int j = 0; j < imgSize.GetY(); j++) {
			unsigned char value = table.get(*datap);
			*datap = value;
			*++datap = value;
			*++datap = value;
			datap++;
		}
	}
}

void RawImage::resetHistogram() {

	histogram = new long[256];
	histogram_acc = new long[256];

	for (int i = 0; i < 256; i++) {
		histogram[i] = 0;
		histogram_acc[i] = 0;
	}
	histogram[0] = -1;
	histogram_acc[0] = -1;

	valid_histogram = false;
}

void RawImage::setPixel(wxPoint position, unsigned char value){
	int x = imgSize.GetX();
	int y = imgSize.GetY();
	int index = 0;

	if (x < position.x || y < position.y) {
		//error
	}
	else {
		index = position.x + position.y * x;
		*(rawImg + (index * 3)) = value;
		*(rawImg + (index * 3 + 1)) = value;
		*(rawImg + (index * 3 + 2)) = value;
	}

}

std::vector<std::vector<unsigned char>> RawImage::getImageCopy(){

	int x = imgSize.GetX();
	int y = imgSize.GetY();

	std::vector<std::vector<unsigned char>> matrix;

	matrix.resize(x);

	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].resize(y);

		for (int j = 0; j < matrix[i].size(); j++)
			matrix[i][j] = getPixel(wxPoint(i, j));

	}

	return matrix;
}

wxRealPoint RawImage::maxPoint(const std::vector<wxRealPoint>& points){
	double maxX = points[0].x;
	double maxY = points[0].y;

	for (int i = 1; i < points.size(); i++) {
		if (points[i].x > maxX) {
			maxX = points[i].x;
		}
		if (points[i].y > maxY) {
			maxY = points[i].y;
		}
	}
	return wxRealPoint(maxX, maxY);
}

wxRealPoint RawImage::minPoint(const std::vector<wxRealPoint>& points){
	double minX = points[0].x;
	double minY = points[0].y;

	for (int i = 1; i < points.size(); i++) {
		if (points[i].x < minX) {
			minX = points[i].x;
		}
		if (points[i].y < minY) {
			minY = points[i].y;
		}
	}
	return wxRealPoint(minX, minY);
}


wxRealPoint RawImage::rotatePointFromAxis(wxPoint p, double angle){
	double x = double(p.x) * cos(angle) - double(p.y) * sin(angle);
	double y = double(p.x) * sin(angle) + double(p.y) * cos(angle);

	return wxRealPoint(x, y);
}

wxRealPoint RawImage::rotatePointIT(wxPoint p, double angle){
	double x = double(p.x) * cos(angle) + double(p.y) * sin(angle);
	double y = double(-p.x) * sin(angle) + double(p.y) * cos(angle);

	return wxRealPoint(x, y);
}

wxRealPoint RawImage::translatePoint(wxRealPoint main, wxRealPoint vector){
	double x = main.x + vector.x;
	double y = main.y + vector.y;

	return wxRealPoint(x, y);
}

void RawImage::convertToGrayScale(unsigned type){
	//Exploración de arriba a abajo, de izquierda a derecha.

	unsigned char* datap = rawImg;

	for (int i = 0; i < imgSize.GetY(); i++) {
		for (int j = 0; j < imgSize.GetX(); j++) {
			unsigned char* r = datap;
			unsigned char* g = ++datap;
			unsigned char* b = ++datap;

			unsigned char value = 0;

			if (type == NTSC) {
				value = round(double(*r) * 0.299 + double(*g) * 0.587 + double(*b) * 0.114);
			}
			else if (type == PAL) {
				value = round(double(*r) * 0.222 + double(*g) * 0.707 + double(*b) * 0.071);
			}
			*r = value;
			*g = value;
			*b = value;

			datap++;
		}
	}

	resetHistogram();
}

long* RawImage::computeHistogram(unsigned t){

	if (histogram[0] == -1) {

		histogram[0] = 0;

		for (int i = 0; i < imgSize.GetY(); i++) {
			for (int j = 0; j < imgSize.GetX(); j++) {
				wxPoint p(j, i);
				unsigned char index = getPixel(p);

				histogram[index]++;

			}
		}
		valid_histogram = true;
		//BRILLO
		double sum = 0;

		for (int i = 0; i < 256; i++)
			sum += double(histogram[i]) * double(i);

		double factor = 1.0 / (double(imgSize.GetX()) * double(imgSize.GetY()));

		brightness = floor(factor * sum);	// 0 - 255
		//CONTRASTE
		sum = 0;

		for (int i = 0; i < 256; i++)
			sum += double(histogram[i]) * pow(double(i - brightness),2);

		contrast = floor(sqrt(factor * sum));	// 0 - 127
	}

	if (histogram_acc[0] == -1) {

		histogram_acc[0] = histogram[0];

		for (int i = 1; i < 256; i++) {
			histogram_acc[i] = histogram_acc[i - 1] + histogram[i];
		}
	}

	if (t == H_ABSOLUTE) {
		return histogram;
	}
	else if (t == H_ACCUMULATIVE) {
		return histogram_acc;
	}
}

void RawImage::computeLinealTranformation(std::vector<wxPoint> points){

	LookUpTable table(points);

	computeWithLUT(table);

	resetHistogram();
}

void RawImage::computeNewBrightnessAndContrast(unsigned newBrightness, unsigned newContrast){
	
	double A = double(newContrast) / double(this->contrast);
	double B = double(newBrightness) - A * double(this->brightness);

	LookUpTable table(A, B);

	computeWithLUT(table);

	resetHistogram();
}

void RawImage::computeHistogramEspecification(RawImage * original, RawImage * target){

	long* originalH = original->computeHistogram(H_ACCUMULATIVE);
	long* targetH = target->computeHistogram(H_ACCUMULATIVE);

	LookUpTable table(originalH, targetH);

	computeWithLUT(table);

	resetHistogram();
}

void RawImage::computeEqualization(){

	LookUpTable table(this->computeHistogram(H_ACCUMULATIVE), imgSize.GetX() * imgSize.GetY());

	computeWithLUT(table);

	resetHistogram();
}

void RawImage::computeGammaCorrection(double gamma){

	LookUpTable table(this->computeHistogram(H_ACCUMULATIVE), gamma);

	computeWithLUT(table);

	resetHistogram();
}

void RawImage::computeDiference(RawImage * original, RawImage* target){
	
	int size = imgSize.GetX() * imgSize.GetY();

	for (int i = 0; i < size; i++) {
		unsigned char value = abs(original->rawImg[i * 3] - target->rawImg[i * 3]);
		this->rawImg[i * 3] = value;
		this->rawImg[i * 3 + 1] = value;
		this->rawImg[i * 3 + 2] = value;
	}

	resetHistogram();
}

void RawImage::computeThreshold(unsigned char t){
	LookUpTable table(t);

	computeWithLUT(table);

	resetHistogram();
}

void RawImage::compute90Rotation(int direction){
	
	computeTranspose();
	if (direction == RIGHT)
		computeFlip(VERTICAL);
	else if(direction == LEFT)
		computeFlip(HORIZONTAL);
}

void RawImage::computeFlip(int direction){

	std::vector<std::vector<unsigned char>> matrix = getImageCopy();

	if (direction == VERTICAL) {
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				wxPoint p(i, j);
				setPixel(p, matrix[imgSize.GetX() - 1 - i][j]);
			}
		}
	}
	else if (direction == HORIZONTAL) {
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				wxPoint p(i, j);
				setPixel(p, matrix[i][imgSize.GetY() - 1 - j]);
			}
		}
	}

	resetHistogram();
}

void RawImage::computeTranspose(){

	std::vector<std::vector<unsigned char>> matrix = getImageCopy();

	imgSize.Set(imgSize.GetY(), imgSize.GetX());

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			wxPoint p(j, i);
			setPixel(p, matrix[i][j]);
		}
	}

	resetHistogram();
}

void RawImage::computeScaling(double proportion, int interpolation){

	int x = imgSize.GetX();
	int y = imgSize.GetY();

	int newX = floor(x * proportion);
	int newY = floor(y * proportion);

	std::vector<std::vector<unsigned char>> matrix = getImageCopy();

	imgSize.Set(newX, newY);
	int dataSize = newX * newY * 3;
	rawImg = (unsigned char*)malloc(dataSize);	//No need to close as wxImage will close it when needed

	if (interpolation == VMP) {
		for (int i = 0; i < newX; i++) {
			for (int j = 0; j < newY; j++) {
				double indiceX = i / proportion;
				double indiceY = j / proportion;

				int sourceX = floor(indiceX);
				int sourceY = floor(indiceY);



				unsigned char value = matrix[sourceX][sourceY];

				wxPoint p(i, j);
				setPixel(p, value);

				}

			}
		}
	else if (interpolation == BILINEAL) {
		for (int i = 0; i < newX; i++) {
			for (int j = 0; j < newY; j++) {
				double indiceX = i / proportion;
				double indiceY = j / proportion;

				int t = floor(indiceX);
				int v = floor(indiceY);

				int t2 = std::min(t + 1, x - 1);
				int v2 = std::min(v + 1, y - 1);

				int A = matrix[t][v2];
				int B = matrix[t2][v2];
				int C = matrix[t][v];
				int D = matrix[t2][v];

				double p = indiceX - t;
				double q = indiceY - v;

				double term1 = (D - C) * p;
				double term2 = (A - C) * q;
				double term3 = (B + C - A - D) * p * q;

				unsigned char value = floor(C + term1 + term2 + term3);

				wxPoint point(i, j);
				setPixel(point, value);
			}
		}
	}


	resetHistogram();
}

void RawImage::computeRotation(double angle, int rotMethod, int interMethod){
	
	int x = imgSize.GetX();	//Tamaño x de la imagen original
	int y = imgSize.GetY();	//Tamaño y de la imagen original

	std::vector<std::vector<unsigned char>> matrix = getImageCopy();

	/*		A - - - - - - - B -> Each point is a corner
	 *		|	  Image		|
	 *		C -	- - - - - - D	*/

	std::vector<wxPoint> points;	//Los puntos que conforman las 4 esquinas de la imagen original.
	points.push_back(wxPoint(0, 0));		//A
	points.push_back(wxPoint(x - 1, 0));	//B
	points.push_back(wxPoint(0, y - 1));	//C
	points.push_back(wxPoint(x - 1, y - 1));//D

	std::vector<wxRealPoint> rotatedPoints;	//points, rotados angle grados (imagen original)

	for (int i = 0; i < points.size(); i++) {
		wxRealPoint rotated = rotatePointFromAxis(points[i], angle);
		rotatedPoints.push_back(rotated);
	}
	
	wxRealPoint maxp = maxPoint(rotatedPoints);	//Coordenadas máximas en x e y
	wxRealPoint minp = minPoint(rotatedPoints);	//Coordenadas mínimas en x e y

	int newX = abs(maxp.x - minp.x);	//Nuevo tamaño de imagen (X)
	int newY = abs(maxp.y - minp.y);	//Nuevo tamaño de imagen (Y)

	imgSize.Set(newX, newY);
	int dataSize = newX * newY * 3;
	rawImg = (unsigned char*)malloc(dataSize);	//No need to close as wxImage will close it when needed

	if (rotMethod == METODO_ROTACION_ROTAR_PINTAR) {
		for (int i = 0; i < newX * newY * 3; i++) {
			rawImg[i] = 0;
		}

		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				wxRealPoint rotated = rotatePointFromAxis(wxPoint(i, j), angle);
				wxRealPoint rotatedAndTranslated = translatePoint(rotated, wxRealPoint(-minp.x, -minp.y));
				wxPoint dummy(floor(rotatedAndTranslated.x), floor(rotatedAndTranslated.y));
				setPixel(dummy, matrix[i][j]);
			}
		}
	}
	else if (rotMethod == METODO_ROTACION_MEJORADO) {
		if (interMethod == VMP) {
			for (int i = 0; i < newX; i++) {
				for (int j = 0; j < newY; j++) {
					
					wxRealPoint translated = translatePoint(wxPoint(i, j), wxRealPoint(minp.x, minp.y));
					wxRealPoint rotated = rotatePointIT(translated, angle);

					wxPoint point(i, j);
					if (rotated.x < 0 || round(rotated.x) >= x || rotated.y < 0 || round(rotated.y) >= y) {
						setPixel(point, 0);
					}
					else {
						

						int indiceX = std::min((int)round(rotated.x), x - 1);// -minp.x;
						int indiceY = std::min((int)round(rotated.y), y - 1);// -minp.y;

						setPixel(point, matrix[indiceX][indiceY]);

					}

				}
			}
		}
		else if (interMethod == BILINEAL) {
			for (int i = 0; i < newX; i++) {
				for (int j = 0; j < newY; j++) {
					wxRealPoint translated = translatePoint(wxPoint(i, j), wxRealPoint(minp.x, minp.y));
					wxRealPoint rotated = rotatePointIT(translated, angle);
					
					wxPoint point(i, j);
					if (rotated.x < 0 || rotated.x >= x || rotated.y < 0 || rotated.y >= y) {
						setPixel(point, 0);
					}
					else {

						int t = floor(rotated.x);
						int v = floor(rotated.y);

						int t2 = std::min(t + 1, x - 1);
						int v2 = std::min(v + 1, y - 1);

						int A = matrix[t][v2];
						int B = matrix[t2][v2];
						int C = matrix[t][v];
						int D = matrix[t2][v];

						double p = rotated.x - t;
						double q = rotated.y - v;

						double term1 = (D - C) * p;
						double term2 = (A - C) * q;
						double term3 = (B + C - A - D) * p * q;

						unsigned char value = floor(C + term1 + term2 + term3);
						wxPoint point(i, j);
						setPixel(point, value);
					}

				}
			}
		}
	}

	resetHistogram();
}

void RawImage::computeConvolution(std::vector<std::vector<long>> kernel){
	int x = imgSize.GetX();	//Tamaño x de la imagen original
	int y = imgSize.GetY();	//Tamaño y de la imagen original

	int kSum = 0;

	for (int i = 0; i < kernel.size(); i++) {
		for (int j = 0; j < kernel[i].size(); j++) {
			kSum += kernel[i][j];
		}
	}

	double s = double(1) / double(kSum);

	std::vector<std::vector<unsigned char>> matrix = getImageCopy();

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			int value = 0;
			int center = (kernel.size() - 1) / 2;

			for (int r = 0; r < kernel.size(); r++) {
				int indiceX = i - center + r;
				if (indiceX < 0 || indiceX >= matrix.size())
					continue;
				for (int s = 0; s < kernel[r].size(); s++) {
					int indiceY = j - center + s;
					if (indiceY < 0 || indiceY >= matrix[i].size())
						continue;
					value += kernel[r][s] * matrix[indiceX][indiceY];
				}
			}
			
			if (kSum != 0) {
				value = round(s * value);
			}
			else {
				//UNDONE: Preguntar al usuario si quiere reescalar el resultado o truncar en 0-255
				value = (value + 255) / 2;	//In case of edge detectors, range is [-255, 255] ----shift + shortening---> [0, 255] 
			}
			
			if (value < 0) {
				value = 0;
			}
			else if (value >= 255) {
				value = 255;
			}
			setPixel(wxPoint(i, j), value);
		}

	}

	resetHistogram();
}

wxSize RawImage::getSize() {
	return imgSize;
}

unsigned char * RawImage::getData(){
	return rawImg;
}

unsigned char RawImage::getPixel(wxPoint p){
	//Las imágenes en grayscale en wxwidgets son del formato RGBRGBRGB... donde R = G = B -> nivel de gris (0-255)
	unsigned char red = getPixelR(p);
	//unsigned char green = getPixelG(p);
	//unsigned char blue = getPixelB(p);
	return red;
}

unsigned char RawImage::getPixelR(wxPoint p) {

	int x = imgSize.GetWidth();
	int y = imgSize.GetHeight();
	int index = 0;

	if (x < p.x || y < p.y) {
		//error
	}
	else {
		index = p.x + p.y * x;
	}

	unsigned char value = *(rawImg + (index * 3));

	return value;

}
unsigned char RawImage::getPixelG(wxPoint p) {

	int x = imgSize.GetWidth();
	int y = imgSize.GetHeight();
	int index = 0;

	if (x < p.x || y < p.y) {
		//error
	}
	else {
		index = p.x + p.y * x;
	}

	return *(rawImg + (index * 3 + 1));
}
unsigned char RawImage::getPixelB(wxPoint p) {

	int x = imgSize.GetWidth();
	int y = imgSize.GetHeight();
	int index = 0;

	if (x < p.x || y < p.y) {
		//error
	}
	else {
		index = p.x + p.y * x;
	}

	return *(rawImg + (index * 3 + 2));
}