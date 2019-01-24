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
#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include "../Tools/Image.h"

class ImagePanel : public wxPanel{
	Image* image;

	wxFrame* parent;

	void paintEvent(wxPaintEvent & evt);
	void OnMouseMoved(wxMouseEvent & event);
	void paintNow();
	void render(wxDC& dc);

public:
	ImagePanel(wxFrame* parent, wxString file);
	ImagePanel(wxFrame* parent, const ImagePanel& p);
	~ImagePanel();

	void saveToFile(wxString file, wxBitmapType format);


	wxSize getImageSize();

	
	//RawImage
	void convertToGrayScale(unsigned type);
	long* computeHistogram(unsigned type);
	void computeLinealTranformation(vector<wxPoint> points);
	void computeNewBrightnessAndContrast(unsigned newBrightness, unsigned contrast);
	void computeHistogramEspecification(ImagePanel* original, ImagePanel* target);
	void computeEqualization();
	void computeGammaCorrection(double gamma);
	void computeDiference(ImagePanel* original, ImagePanel* target);
	void computeThreshold(unsigned char t);

	void compute90Rotation(int direction);
	void computeFlip(int direction);
	void computeTranspose();
	void computeScaling(double proportion, int interpolation);
	void computeRotation(double angle, int rotMethod, int interMethod);
	void computeConvolution(vector<vector<long>> kernel);

	unsigned char getBrightness();
	unsigned char getContrast();
	// some useful events
	/*
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
	*/

	DECLARE_EVENT_TABLE()
};