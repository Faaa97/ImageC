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
#include <wx/wx.h>
#include <wx/sizer.h>
#include "RawImage.h"

class Image{

	wxBitmap* image;	//Image to print on screen
	wxImage* img;	//Image to work with
	RawImage* rawImg;	//Raw info of img

	void refreshBitmap();

public:
	Image(wxString file, wxBitmapType format);
	Image(const Image& i);
	~Image();

	void saveToFile(wxString file, wxBitmapType format);

	unsigned char getBrightness();
	unsigned char getContrast();
	wxSize GetSize();
	unsigned char getPixel(wxPoint p);
	void render(wxDC&  dc);

	//RawImage
	void convertToGrayScale(unsigned type);
	long* computeHistogram(unsigned type);
	void computeLinealTranformation(vector<wxPoint> points);
	void computeNewBrightnessAndContrast(unsigned newBrightness, unsigned contrast);
	void computeHistogramEspecification(Image* original, Image* target);
	void computeEqualization();
	void computeGammaCorrection(double gamma);
	void computeDiference(Image* original, Image* target);
	void computeThreshold(unsigned char t);

	void compute90Rotation(int direction);
	void computeFlip(int direction);
};

