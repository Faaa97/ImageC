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
#include <wx/gdicmn.h>	//wxPoint
#include <stack>
#include <cmath>
#include <vector>
#include "LookUpTable.h"

enum {
	GREY_SCALE,
	RGB,
	NTSC,
	PAL,
	H_ABSOLUTE,
	H_ACCUMULATIVE,
	LEFT,
	RIGHT,
	VERTICAL,
	HORIZONTAL,
};

using namespace std;

class RawImage{

	wxSize imgSize;
	unsigned char* rawImg;
	unsigned type;

	long* histogram;
	long* histogram_acc;

	unsigned char brightness;
	unsigned char contrast;

	bool valid_histogram;
	void computeWithLUT(const LookUpTable& table);
	void resetHistogram();
	void setPixel(wxPoint position, unsigned char value);
public:
	RawImage();
	RawImage(unsigned char* raw, wxSize size, unsigned type);
	~RawImage();

	unsigned char getBrightness();
	unsigned char getContrast();

	void convertToGrayScale(unsigned type);
	long* computeHistogram(unsigned type = H_ABSOLUTE);
	void computeLinealTranformation(vector<wxPoint> points);
	void computeNewBrightnessAndContrast(unsigned newBrightness, unsigned newContrast);
	void computeHistogramEspecification(RawImage* original, RawImage* target);
	void computeEqualization();
	void computeGammaCorrection(double gamma);
	void computeDiference(RawImage* original, RawImage* target);
	void computeThreshold(unsigned char t);
	void compute90Rotation(int direction);
	void computeFlip(int direction);
	void computeTranspose();

	wxSize getSize();

	unsigned char getPixel(wxPoint p);
	unsigned char getPixelR(wxPoint p);
	unsigned char getPixelG(wxPoint p);
	unsigned char getPixelB(wxPoint p);
};

