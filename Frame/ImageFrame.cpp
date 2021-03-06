/* ImageC - An Image Manipulation Program based on ImageJ
*	Copyright(C) 2018 Felipe �lvarez Avaria <faaa97@protonmail.com>
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
#include "ImageFrame.h"

BEGIN_EVENT_TABLE(ImageFrame, wxPanel)
// some useful events
/*
EVT_LEFT_DOWN(wxImagePanel::mouseDown)
EVT_LEFT_UP(wxImagePanel::mouseReleased)
EVT_RIGHT_DOWN(wxImagePanel::rightClick)
EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
EVT_KEY_DOWN(wxImagePanel::keyPressed)
EVT_KEY_UP(wxImagePanel::keyReleased)
EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
*/
//EVT_MOTION(ImageFrame::OnMouseMoved)
EVT_SET_FOCUS(ImageFrame::onSetFocus)
EVT_CLOSE(ImageFrame::OnQuit)
END_EVENT_TABLE()

//TODO: Regi�n de inter�s. El usuario puede hacer una selecci�n y todas las operaciones se aplican en ese trozo solo
ImageFrame::ImageFrame(wxFrame* parent, wxString filepath, wxString filename):
	wxFrame(parent, wxID_ANY, filename, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, filename) {
	this->parent = parent;
	lastFocus = wxDateTime::Now();
	modified = false;
	destroyed = false;
	ext = getExt(filename);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	imgPanel = new ImagePanel(this, filepath);
	sizer->Add(imgPanel, 1, wxEXPAND);
	
	SetSizer(sizer);
	
	SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));

	statusBar = CreateStatusBar(3);

	updateFrame();
	updateStatusText();
}


ImageFrame::ImageFrame(){
	//Does nothing
}

ImageFrame::ImageFrame(const ImageFrame & frame):
	wxFrame(frame.GetParent(), wxID_ANY, frame.GetTitle(), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, frame.GetName()) {
	this->parent = frame.GetParent();
	modified = false;
	destroyed = frame.destroyed;
	ext = frame.ext;

	lastFocus = wxDateTime::Now();

	wxInitAllImageHandlers();

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	imgPanel = new ImagePanel(this, *frame.imgPanel);
	sizer->Add(imgPanel, 1, wxEXPAND);
	
	SetSizer(sizer);

	SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));

	wxStatusBar status = CreateStatusBar(3);

	updateFrame();
	updateStatusText();
}

ImageFrame::~ImageFrame(){
	
}

void ImageFrame::saveToFile(wxString file){

	wxBitmapType format = getType(file);

	imgPanel->saveToFile(file, format);
}

wxDateTime ImageFrame::getLastFocus(){
	return lastFocus;
}

bool ImageFrame::isModified(){
	return modified;
}

bool ImageFrame::isClosed(){
	return destroyed;
}

void ImageFrame::convertToGrayScale(unsigned type){
	imgPanel->convertToGrayScale(type);
	modified = true;
	this->Refresh();
}

long* ImageFrame::computeHistogram(unsigned type){
	return imgPanel->computeHistogram(type);
}

void ImageFrame::computeLinealTranformation(std::vector<wxPoint> points){
	imgPanel->computeLinealTranformation(points);
	modified = true;
	this->Refresh();
}

void ImageFrame::computeNewBrightnessAndContrast(unsigned newBrightness, unsigned contrast){
	imgPanel->computeNewBrightnessAndContrast(newBrightness, contrast);
	modified = true;
	this->Refresh();
}

void ImageFrame::computeHistogramEspecification(ImageFrame * original, ImageFrame * target){
	imgPanel->computeHistogramEspecification(original->imgPanel, target->imgPanel);
	modified = true;
	this->Refresh();
}

void ImageFrame::computeEqualization(){
	imgPanel->computeEqualization();
	modified = true;
	this->Refresh();
}

void ImageFrame::computeGammaCorrection(double gamma){
	imgPanel->computeGammaCorrection(gamma);
	modified = true;
	this->Refresh();
}

void ImageFrame::computeDiference(ImageFrame * original, ImageFrame * target){
	imgPanel->computeDiference(original->imgPanel, target->imgPanel);
	modified = true;
	this->Refresh();
}

void ImageFrame::computeThreshold(unsigned char t){
	imgPanel->computeThreshold(t);
	modified = true;
	this->Refresh();
}

void ImageFrame::compute90Rotation(int direction){
	imgPanel->compute90Rotation(direction);
	modified = true;
	updateFrame();
	updateStatusText();
	this->Refresh();
}

void ImageFrame::computeFlip(int direction){
	imgPanel->computeFlip(direction);
	modified = true;
	this->Refresh();
}

void ImageFrame::computeTranspose(){
	imgPanel->computeTranspose();
	modified = true;
	updateFrame();
	updateStatusText();
	this->Refresh();
}

void ImageFrame::computeScaling(double proportion, int interpolation){
	imgPanel->computeScaling(proportion, interpolation);
	modified = true;
	updateFrame();
	updateStatusText();
	this->Refresh();
}

void ImageFrame::computeRotation(double angle, int rotMethod, int interMethod){
	imgPanel->computeRotation(angle, rotMethod, interMethod);
	modified = true;
	updateFrame();
	updateStatusText();
	this->Refresh();
}

void ImageFrame::computeConvolution(std::vector<std::vector<long>> kernel){
	imgPanel->computeConvolution(kernel);
	modified = true;
	this->Refresh();
}

unsigned char ImageFrame::getBrightness(){
	return imgPanel->getBrightness();
}

unsigned char ImageFrame::getContrast(){
	return imgPanel->getContrast();
}

void ImageFrame::updateFrame() {
	SetClientSize(imgPanel->getImageSize());
}

void ImageFrame::updateStatusText(){
	wxString res = std::to_string(imgPanel->getImageSize().GetWidth()) + "x" + std::to_string(imgPanel->getImageSize().GetHeight());

	SetStatusText(res, 0);	//0: Tama�o total de la imagen
}

wxString ImageFrame::getExt(wxString filename) {
	wxString extension = getExpresion(filename, std::string(".*[.](.*)"));
	return extension;
}

wxString ImageFrame::getExt(){
	return ext;
}

wxSize ImageFrame::getImageSize(){
	return imgPanel->getImageSize();
}

void ImageFrame::OnQuit(wxCloseEvent& event) {

	this->parent = NULL;
	destroyed = true;
	this->Destroy();
	event.Skip();
}

void ImageFrame::onSetFocus(wxFocusEvent & event){
	lastFocus = wxDateTime::Now();
}

wxBitmapType ImageFrame::getType(wxString filename){
	
	wxString ext = getExpresion(filename, std::string(".*[.](.*)"));

	if (ext == "tiff") {
		return wxBITMAP_TYPE_TIFF;
	}
	else if (ext == "jpg") {
		return wxBITMAP_TYPE_JPEG;
	}
	else if (ext == "png") {
		return wxBITMAP_TYPE_PNG;
	}
	else if (ext == "bmp") {
		return wxBITMAP_TYPE_BMP;
	}

	return wxBITMAP_TYPE_INVALID;
}

wxString ImageFrame::getExpresion(wxString &texto, wxString exp){
	wxString result;
	wxRegEx expresion(exp, wxRE_ICASE | wxRE_DEFAULT);

	if (expresion.IsValid() && expresion.Matches(texto)){
		result = expresion.GetMatch(texto, 1);
	}

	return result;
}