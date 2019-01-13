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

	for (int i = 0; i < imgSize.GetY(); i++) {
		for (int j = 0; j < imgSize.GetX(); j++) {
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
	int x = imgSize.GetWidth();
	int y = imgSize.GetHeight();
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
//TODO: El histograma no se está computando correctamente para algunas imágenes
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

void RawImage::computeLinealTranformation(vector<wxPoint> points){

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
	
	vector<vector<unsigned char>> matrix;

	matrix.resize(imgSize.GetX());

	for (int i = 0; i < matrix.size(); i++)
		matrix[i].resize(imgSize.GetY());

	for (int i = 0; i < imgSize.GetX(); i++) {
		for (int j = 0; j < imgSize.GetY(); j++) {
			matrix[i][j] = getPixel(wxPoint(i, j));
		}
	}
	if (direction == RIGHT) {
		for (int i = 0; i < imgSize.GetX(); i++) {
			for (int j = 0; j < imgSize.GetY(); j++) {
				wxPoint p(i, j);
				setPixel(p, matrix[imgSize.GetY() - 1 - j][i]);
			}
		}
	}
	else if (direction == LEFT) {
		for (int i = 0; i < imgSize.GetX(); i++) {
			for (int j = 0; j < imgSize.GetY(); j++) {
				wxPoint p(i, j);
				setPixel(p, matrix[j][imgSize.GetY() - 1 - i]);
			}
		}
	}

	resetHistogram();
}

void RawImage::computeFlip(int direction){

	vector<vector<unsigned char>> matrix;

	matrix.resize(imgSize.GetX());

	for (int i = 0; i < matrix.size(); i++)
		matrix[i].resize(imgSize.GetY());

	for (int i = 0; i < imgSize.GetX(); i++) {
		for (int j = 0; j < imgSize.GetY(); j++) {
			matrix[i][j] = getPixel(wxPoint(i, j));
		}
	}
	if (direction == VERTICAL) {
		for (int i = 0; i < imgSize.GetX(); i++) {
			for (int j = 0; j < imgSize.GetY(); j++) {
				wxPoint p(i, j);
				setPixel(p, matrix[imgSize.GetX() - 1 - i][j]);
			}
		}
	}
	else if (direction == HORIZONTAL) {
		for (int i = 0; i < imgSize.GetX(); i++) {
			for (int j = 0; j < imgSize.GetY(); j++) {
				wxPoint p(i, j);
				setPixel(p, matrix[i][imgSize.GetY() - 1 - j]);
			}
		}
	}

	resetHistogram();
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