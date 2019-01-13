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
#pragma once
#include <wx/wx.h>
#include <wx/wfstream.h>
#include <wx/regex.h>
#include "../Panel/ImagePanel.h"
#include "../Tools/LookUpTable.h"
//TODO: Notificar al padre de que se ha cerrado, para quitarlo de la lista
class ImageFrame : public wxFrame{

	ImagePanel* imgPanel;
	
	wxDateTime lastFocus;

	wxString ext;	//Extension file
	
	bool destroyed;
	bool modified;
	wxWindow* parent;
	void onSetFocus(wxFocusEvent& event);
	//void OnMouseMoved(wxMouseEvent & event);

	wxString getExt(wxString filename);
	wxString getExpresion(wxString & texto, wxString exp);

	void OnQuit(wxCloseEvent & WXUNUSED);

public:
	

	ImageFrame();
	ImageFrame(const ImageFrame& frame);
	ImageFrame(wxFrame* parent, wxString filepath, wxString filename);
	~ImageFrame();

	void saveToFile(wxString file);
	wxDateTime getLastFocus();
	bool isModified();
	bool isClosed();
	

	//RawImage
	void convertToGrayScale(unsigned type);
	long* computeHistogram(unsigned type);
	void computeLinealTranformation(vector<wxPoint> points);
	void computeNewBrightnessAndContrast(unsigned newBrightness, unsigned contrast);
	void computeHistogramEspecification(ImageFrame* original, ImageFrame* target);
	void computeEqualization();
	void computeGammaCorrection(double gamma);
	void computeDiference(ImageFrame* original, ImageFrame* target);
	void computeThreshold(unsigned char t);

	void compute90Rotation(int direction);

	unsigned char getBrightness();
	unsigned char getContrast();

	wxBitmapType getType(wxString filename);
	wxString getExt();
	wxSize getImageSize();

	DECLARE_EVENT_TABLE()

};

