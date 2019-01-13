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
#include "HistogramFrame.h"

BEGIN_EVENT_TABLE(HistogramFrame, wxFrame)
	EVT_MENU(ID_M_AJUSTES_CAMBIAR, HistogramFrame::OnMenuAjustesCambiar)
END_EVENT_TABLE()

HistogramFrame::HistogramFrame(wxFrame* parent, long* data_abs, long* data_acc, const wxString& imageName):
	wxFrame(parent, wxID_ANY, wxEmptyString){
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	SetWindowStyle(wxDEFAULT_FRAME_STYLE);

	SetTitle("Histograma de " + imageName);

	panel = new HistogramPanel(this);
	panel->setData(data_abs, data_acc);

	sizer->Add(panel, 1, wxEXPAND);
	SetSizer(sizer);

	wxStatusBar status = CreateStatusBar(4);

	wxSize panelSize = panel->GetChartSize();
	panelSize.SetHeight(status.GetBorders().GetHeight() + panelSize.GetHeight());
	SetClientSize(panelSize);

	wxMenu *ajustes_M = new wxMenu;
	ajustes_M->Append(ID_M_AJUSTES_CAMBIAR, "&Cambiar tipo");
	wxMenuBar *menuBar = new wxMenuBar();

	menuBar->Append(ajustes_M, _T("&Ajustes"));
	SetMenuBar(menuBar);
}


HistogramFrame::~HistogramFrame(){

}

void HistogramFrame::OnMenuAjustesCambiar(wxCommandEvent & event) {
	panel->changeHistogram();
}