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

using namespace std;

class HistogramPanel : public wxPanel{

public:
	HistogramPanel(wxFrame* parent);
	~HistogramPanel();
	void setData(long * abs, long* acc);
	void changeHistogram();

	wxSize GetChartSize();

private:

	bool acc;
	long* data_abs;
	long* data_acc;
	long dataMax;
	long dataMin;
	long dataHighest_abs;
	long dataHighest_acc;

	int width;
	int height;
	double columnWidth;

	wxFrame* parent;

	void GatherData();
	void updateStatusText(int mousex = 0);

	void OnPaint(wxPaintEvent& event);
	void OnResize(wxSizeEvent& event);
	void OnMouseMoved(wxMouseEvent& event);

	DECLARE_EVENT_TABLE()
};

