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
#include "Image.h"
void Image::refreshBitmap(){
	
	delete image;
	image = new wxBitmap(*img);
}

//Code taken from https://wiki.wxwidgets.org/WxImage
void Image::refreshImage(){
	

	int dataSize = img->GetWidth() * img->GetHeight() * 3;
	unsigned char* NewImgData = (unsigned char*)malloc(dataSize);
	unsigned char* OldImgData = img->GetData();

	memcpy(NewImgData, OldImgData, dataSize);

	wxSize rawImgSize = rawImg->getSize();

	img = new wxImage(rawImgSize.GetWidth(), rawImgSize.GetHeight(), NewImgData);
}

//UNDONE: Usar wxImage::GetType para simplificar el control de las extensiones
Image::Image(wxString file, wxBitmapType format){
	
	wxInitAllImageHandlers();

	img = new wxImage();
	img->LoadFile(file);
	if (img->IsOk()) {
		image = new wxBitmap(*img);
	}
	else {
		//error
	}
	if (image->IsOk()) {
		rawImg = new RawImage(img->GetData(), img->GetSize(), RGB);	//No hay soporte de 8bit greyscale en wxwidgets
	}
	else {
		//error
	}

}

Image::Image(const Image & i){

	wxInitAllImageHandlers();

	image = new wxBitmap();
	img = new wxImage();
	*image = i.image->GetSubBitmap(wxRect(0, 0, i.image->GetWidth(), i.image->GetHeight()));//Mejor manera de duplicar imagen
	*img = image->ConvertToImage();
	rawImg = new RawImage(img->GetData(), img->GetSize(), RGB);	//No hay soporte de 8bit greyscale en wxwidgets
}

Image::~Image(){
	delete image;
	delete img;
	delete rawImg;
}

void Image::saveToFile(wxString file, wxBitmapType format){
	image->SaveFile(file, format);
}

unsigned char Image::getBrightness(){
	return rawImg->getBrightness();
}

unsigned char Image::getContrast(){
	return rawImg->getContrast();
}

wxSize Image::GetSize(){
	return image->GetSize();
}

unsigned char Image::getPixel(wxPoint p) {
	return rawImg->getPixel(p);
}

void Image::render(wxDC&  dc){

	dc.DrawBitmap(*image, 0, 0, false);
}

//TODO:  wxDC::GetAsBitmap puede funcionar para el area de trabajo (ROI)

void Image::convertToGrayScale(unsigned type){
	rawImg->convertToGrayScale(type);

	refreshBitmap();
}

long* Image::computeHistogram(unsigned type){
	return rawImg->computeHistogram(type);
}

void Image::computeLinealTranformation(vector<wxPoint> points){
	rawImg->computeLinealTranformation(points);

	refreshBitmap();
}

void Image::computeNewBrightnessAndContrast(unsigned newBrightness, unsigned contrast){
	rawImg->computeNewBrightnessAndContrast(newBrightness, contrast);

	refreshBitmap();
}

void Image::computeHistogramEspecification(Image * original, Image * target){
	rawImg->computeHistogramEspecification(original->rawImg, target->rawImg);

	refreshBitmap();
}

void Image::computeEqualization(){
	rawImg->computeEqualization();

	refreshBitmap();
}

void Image::computeGammaCorrection(double gamma){
	rawImg->computeGammaCorrection(gamma);

	refreshBitmap();
}

void Image::computeDiference(Image * original, Image * target){
	rawImg->computeDiference(original->rawImg, target->rawImg);

	refreshBitmap();
}

void Image::computeThreshold(unsigned char t){
	rawImg->computeThreshold(t);

	refreshBitmap();
}

void Image::compute90Rotation(int direction){

	rawImg->compute90Rotation(direction);
	
	refreshImage();
	refreshBitmap();
}

void Image::computeFlip(int direction){
	rawImg->computeFlip(direction);

	refreshBitmap();
}

void Image::computeTranspose(){
	rawImg->computeTranspose();
	
	refreshImage();
	refreshBitmap();
}
