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
#include "RotationDialog.h"

BEGIN_EVENT_TABLE(RotationDialog, wxDialog)
EVT_BUTTON(ID_B_ACEPTAR, RotationDialog::onBAceptar)
EVT_BUTTON(ID_B_CANCELAR, RotationDialog::onBCancelar)
EVT_CHOICE(ID_METODO, RotationDialog::onMethodUpdate)
END_EVENT_TABLE()

RotationDialog::RotationDialog()
	: wxDialog(NULL, wxID_ANY, "Rotación") {

	angleCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);

	wxBoxSizer* angleSizer = new wxBoxSizer(wxHORIZONTAL);
	angleSizer->Add(new wxStaticText(this, wxID_ANY, "Ángulo:"), 0, 0, 0);
	angleSizer->Add(angleCtrl, 0, 0, 0);
	angleSizer->Add(new wxStaticText(this, wxID_ANY, "º"), 0, 0, 0);

	wxArrayString methodStrings;

	methodStrings.Add("Rotar + Pintar (TD)");
	methodStrings.Add("Mejorado (TI)");

	methodChoice = new wxChoice(this, ID_METODO, wxDefaultPosition, wxDefaultSize, methodStrings);

	wxArrayString interStrings;

	interStrings.Add("Vecino Más Próximo (VMP)");
	interStrings.Add("Bilineal");

	interChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, interStrings);

	wxBoxSizer* rowsSizer = new wxBoxSizer(wxVERTICAL);
	rowsSizer->Add(angleSizer);
	rowsSizer->Add(new wxStaticText(this, wxID_ANY, "Método:"), 0, 0, 0);
	rowsSizer->Add(methodChoice);
	rowsSizer->Add(new wxStaticText(this, wxID_ANY, "Interpolación:"), 0, 0, 0);
	rowsSizer->Add(interChoice);

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

RotationDialog::~RotationDialog(){

}

double RotationDialog::getAngle(){
	return stod(angleCtrl->GetLineText(0).ToStdString())* M_PI / 180;
}

int RotationDialog::getInterpolationMethod(){
	int selection = interChoice->GetSelection();

	switch (selection) {
		case 0: return VMP;
		case 1: return BILINEAL;
		default: return BILINEAL;
	}
}

int RotationDialog::getRotationMethod(){
	int selection = methodChoice->GetSelection();

	switch (selection) {
		case 0:	return METODO_ROTACION_ROTAR_PINTAR;
		case 1: return METODO_ROTACION_MEJORADO;
		default: return METODO_ROTACION_ROTAR_PINTAR;
	}
}

void RotationDialog::onBAceptar(wxCommandEvent & event) {
	this->EndModal(1);
}

void RotationDialog::onBCancelar(wxCommandEvent & event) {
	if (IsModal())
		this->EndModal(0);
	else
		this->Destroy();
}

void RotationDialog::onMethodUpdate(wxCommandEvent& event){
	int selection = methodChoice->GetSelection();
	if (selection == 0) {
		interChoice->Disable();
	}
	else if (selection == 1) {
		interChoice->Enable();
	}
}
