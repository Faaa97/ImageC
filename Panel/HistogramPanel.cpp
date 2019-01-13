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
#include "HistogramPanel.h"

BEGIN_EVENT_TABLE(HistogramPanel, wxPanel)

EVT_PAINT(HistogramPanel::OnPaint)
EVT_SIZE(HistogramPanel::OnResize)
EVT_MOTION(HistogramPanel::OnMouseMoved)
END_EVENT_TABLE()

HistogramPanel::HistogramPanel(wxFrame* parent): 
	wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER){
	
	acc = false;

	this->parent = parent;

	width = 512;
	height = 256;

	this->SetSize(width, height);
}

HistogramPanel::~HistogramPanel(){

}

void HistogramPanel::setData(long * abs, long* acc) {
	data_abs = abs;
	data_acc = acc;

	dataHighest_abs = 0;

	for (int i = 0; i < 256; i++) {
		if(dataHighest_abs < data_abs[i])
			dataHighest_abs = data_abs[i];
	}
	
	dataHighest_acc = 0;

	for (int i = 0; i < 256; i++) {
		if (dataHighest_acc < data_acc[i])
			dataHighest_acc = data_acc[i];
	}

	GatherData();
}

void HistogramPanel::changeHistogram(){
	acc = !acc;
	Refresh();
}

wxSize HistogramPanel::GetChartSize(){
	return wxSize(width, height);
}

void HistogramPanel::GatherData() {
	dataMax = 255;
	dataMin = 0;

	for (int i = 0; i < 256; i++) {
		if (data_abs[i] != 0) {
			dataMin = i;
			break;
		}
	}
	for (int i = 255; i >= 0; i--) {
		if (data_abs[i] != 0) {
			dataMax = i;
			break;
		}
	}
}

void HistogramPanel::updateStatusText(int mousex) {

	int mouseX = mousex;
	int v = mouseX / columnWidth;

	wxString min = "Min: ";
	wxString max = "Max: ";
	wxString value = "Value: ";
	wxString count = "Count: ";

	parent->SetStatusText(min + to_string(dataMin), 0);
	parent->SetStatusText(max + to_string(dataMax), 1);
	parent->SetStatusText(value + to_string(v), 2);
	if (!acc) {
		parent->SetStatusText(count + to_string(data_abs[v]), 3);
	} else {
		parent->SetStatusText(count + to_string(data_acc[v]), 3);
	}
}

void HistogramPanel::OnPaint(wxPaintEvent& event){

	wxPaintDC dc(this);
	//auto_ptr<wxGraphicsContext> dc(wxGraphicsContext::Create(pdc));

	dc.SetBrush(*wxBLACK_BRUSH);
	
	
	//wxSize panelSize(width, height);
	

	columnWidth = double(width) / double(256);

	double itemX, itemY, itemRatio, itemHeight;


	if (acc) {
		for (int i = 0; i < 256; i++) {
			itemX = i * columnWidth;
			itemRatio = double(data_acc[i]) / double(dataHighest_acc);
			itemHeight = round(itemRatio * double(height));
			itemY = height - itemHeight;
			dc.DrawRectangle(itemX, itemY, columnWidth, itemHeight);
		}
	}
	else {
		for (int i = 0; i < 256; i++) {
			itemX = i * columnWidth;
			itemRatio = double(data_abs[i]) / double(dataHighest_abs);
			itemHeight = round(itemRatio * double(height));
			itemY = height - itemHeight;
			dc.DrawRectangle(itemX, itemY, columnWidth, itemHeight);
		}
	}

	updateStatusText();
}

void HistogramPanel::OnResize(wxSizeEvent& event){

	width = this->GetClientSize().GetWidth();
	height = this->GetClientSize().GetHeight();
	Refresh();
	event.Skip();
}

void HistogramPanel::OnMouseMoved(wxMouseEvent & event){
	updateStatusText(event.GetX());
}
