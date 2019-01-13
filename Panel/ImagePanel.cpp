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
#include "ImagePanel.h"

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
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

// catch paint events
EVT_PAINT(ImagePanel::paintEvent)
EVT_MOTION(ImagePanel::OnMouseMoved)
END_EVENT_TABLE()

// some useful events
/*
void ImagePanel::mouseMoved(wxMouseEvent& event) {}
void ImagePanel::mouseDown(wxMouseEvent& event) {}
void ImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
void ImagePanel::mouseReleased(wxMouseEvent& event) {}
void ImagePanel::rightClick(wxMouseEvent& event) {}
void ImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
void ImagePanel::keyPressed(wxKeyEvent& event) {}
void ImagePanel::keyReleased(wxKeyEvent& event) {}
*/

ImagePanel::ImagePanel(wxFrame* parent, wxString file, wxBitmapType format):
	wxPanel(parent){
	//UNDONE: Verificar que encuentra el fichero
	image = new Image(file, format);
	this->SetClientSize(image->GetSize());
	this->parent = parent;
}

/*
* Called by the system of by wxWidgets when the panel needs
* to be redrawn. You can also trigger this call by
* calling Refresh()/Update().
*/

ImagePanel::ImagePanel(wxFrame* parent, const ImagePanel & p):
	wxPanel(parent) {
	this->image = new Image(*p.image);
	this->SetClientSize(image->GetSize());
	this->parent = parent;
}

ImagePanel::~ImagePanel(){
	delete image;
}

void ImagePanel::saveToFile(wxString file, wxBitmapType format){
	image->saveToFile(file, format);
}

void ImagePanel::paintEvent(wxPaintEvent & evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

void ImagePanel::OnMouseMoved(wxMouseEvent & event) {

	int mouseX = event.GetX();
	int mouseY = event.GetY();
	wxPoint p = wxPoint(mouseX, mouseY);

	wxString pos = "Position: (";
	wxString value = "Value: ";

	parent->SetStatusText(pos + to_string(mouseX) + ", " + to_string(mouseY) + ")", 1);
	parent->SetStatusText(value + to_string(image->getPixel(p)), 2);
}

/*
* Alternatively, you can use a clientDC to paint on the panel
* at any time. Using this generally does not free you from
* catching paint events, since it is possible that e.g. the window
* manager throws away your drawing when the window comes to the
* background, and expects you will redraw it when the window comes
* back (by sending a paint event).
*/
void ImagePanel::paintNow()
{
	// depending on your system you may need to look at double-buffered dcs
	wxClientDC dc(this);
	render(dc);
}

wxSize ImagePanel::getImageSize()
{
	return image->GetSize();
}

/*
* Here we do the actual rendering. I put it in a separate
* method so that it can work no matter what type of DC
* (e.g. wxPaintDC or wxClientDC) is used.
*/
void ImagePanel::render(wxDC&  dc){
	image->render(dc);
}

void ImagePanel::convertToGrayScale(unsigned type){
	image->convertToGrayScale(type);
}

long* ImagePanel::computeHistogram(unsigned type){
	return image->computeHistogram(type);
}

void ImagePanel::computeLinealTranformation(vector<wxPoint> points){
	image->computeLinealTranformation(points);
}

void ImagePanel::computeNewBrightnessAndContrast(unsigned newBrightness, unsigned contrast){
	image->computeNewBrightnessAndContrast(newBrightness, contrast);
}

void ImagePanel::computeHistogramEspecification(ImagePanel * original, ImagePanel * target){
	image->computeHistogramEspecification(original->image, target->image);
}

void ImagePanel::computeEqualization(){
	image->computeEqualization();
}

void ImagePanel::computeGammaCorrection(double gamma){
	image->computeGammaCorrection(gamma);
}

void ImagePanel::computeDiference(ImagePanel * original, ImagePanel * target){
	image->computeDiference(original->image, target->image);
}

void ImagePanel::computeThreshold(unsigned char t){
	image->computeThreshold(t);
}

void ImagePanel::compute90Rotation(int direction){
	image->compute90Rotation(direction);
}

void ImagePanel::computeFlip(int direction){
	image->computeFlip(direction);
}

unsigned char ImagePanel::getBrightness(){
	return image->getBrightness();
}

unsigned char ImagePanel::getContrast(){
	return image->getContrast();
}
