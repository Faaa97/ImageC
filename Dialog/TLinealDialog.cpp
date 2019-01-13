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
#include "TLinealDialog.h"

BEGIN_EVENT_TABLE(TLinealDialog, wxDialog)
	EVT_BUTTON(ID_B_ACEPTAR, TLinealDialog::onBAceptar)
	EVT_BUTTON(ID_B_CANCELAR, TLinealDialog::onBCancelar)
END_EVENT_TABLE()

//UNDONE: Mejorar parte visual del diálogo
//UNDONE: mostrar grafica correspondiente a los segmentos
TLinealDialog::TLinealDialog(ImageFrame* t, int s)
	: wxDialog(NULL, wxID_ANY, "Transformación lineal") {

	pointsNo = s + 1;
	target = t;

	wxBoxSizer* row1points = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* row2points = new wxBoxSizer(wxVERTICAL);

	for (int i = 0; i < pointsNo; i++) {
		//TODO: Crear variable de cad textCtrl para poder llamar GetLineText(line) (GetNumberOfLines()) y obtener los puntos
		//TODO: Como alternativa a lo anterior, investigar el row1points->GetItem(index) para obtener los datos
		row1points->Add(new wxStaticText(this, wxID_ANY, "x :"), 0, 0, 0);

		wxString placeholder = wxEmptyString;
		if (i == 0)
			placeholder = "0";
		if (i == pointsNo - 1)
			placeholder = "255";

		wxTextCtrl* dummy = new wxTextCtrl(this, wxID_ANY, placeholder, wxDefaultPosition);
		row1points->Add(dummy, 0, 0, 0);
		segmentsX.push_back(dummy);
	}

	for (int i = 0; i < pointsNo; i++) {
		row2points->Add(new wxStaticText(this, wxID_ANY, "y :"), 0, 0, 0);

		wxTextCtrl* dummy = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);
		row2points->Add(dummy, 0, 0, 0);
		segmentsY.push_back(dummy);
	}

	wxBoxSizer* rowsSizer = new wxBoxSizer(wxHORIZONTAL);

	rowsSizer->Add(row1points, 1, 0, 0);
	rowsSizer->Add(row2points, 1, 0, 0);

	wxBoxSizer* buttons = new wxBoxSizer(wxHORIZONTAL);

	wxButton *aceptarButton = new wxButton(this, ID_B_ACEPTAR, wxT("Aceptar"),
		wxDefaultPosition);
	wxButton *cancelButton = new wxButton(this, ID_B_CANCELAR, wxT("Cancelar"),
		wxDefaultPosition);

	buttons->Add(aceptarButton, 0);
	buttons->Add(cancelButton, 0, 0, 0);

	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

	dialogSizer->Add(rowsSizer, 0, 0, 0);
	dialogSizer->Add(buttons, 0, 0, 0);
	SetSizerAndFit(dialogSizer);

}

void TLinealDialog::onBAceptar(wxCommandEvent & event){
	this->EndModal(1);
}

void TLinealDialog::onBCancelar(wxCommandEvent & event){
	if (IsModal())
		this->EndModal(0);
	else
		this->Destroy();
}

TLinealDialog::~TLinealDialog(){

}

vector<wxPoint> TLinealDialog::getPoints(){

	vector<wxPoint> result;

	for (int i = 0; i < pointsNo; i++) {
		wxString x;
		wxString y;

		if (segmentsX[i]->GetNumberOfLines() != 0)
			x = segmentsX[i]->GetLineText(0);

		if (segmentsY[i]->GetNumberOfLines() != 0)
			y = segmentsY[i]->GetLineText(0);

		wxPoint p(stoi(x.ToStdString()), stoi(y.ToStdString()));
		
		result.push_back(p);
	}

	return result;
}