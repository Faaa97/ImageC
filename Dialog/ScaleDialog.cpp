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
#include "ScaleDialog.h"

BEGIN_EVENT_TABLE(ScaleDialog, wxDialog)
EVT_BUTTON(ID_B_ACEPTAR, ScaleDialog::onBAceptar)
EVT_BUTTON(ID_B_CANCELAR, ScaleDialog::onBCancelar)
END_EVENT_TABLE()

ScaleDialog::ScaleDialog() 
	: wxDialog(NULL, wxID_ANY, "Escalado") {

	wxArrayString interStrings;

	interStrings.Add("Vecino Más Próximo (VMP)");
	interStrings.Add("Bilineal");

	interChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, interStrings);

	scaleCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);

	wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);
	rowSizer->Add(new wxStaticText(this, wxID_ANY, "Escala:"), 0, 0, 0);
	rowSizer->Add(scaleCtrl, 0, 0, 0);
	rowSizer->Add(new wxStaticText(this, wxID_ANY, "%:"), 0, 0, 0);

	wxBoxSizer* rowsSizer = new wxBoxSizer(wxVERTICAL);
	rowsSizer->Add(rowSizer);
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


ScaleDialog::~ScaleDialog(){

}

int ScaleDialog::getProportion(){
	return stoi(scaleCtrl->GetLineText(0).ToStdString());
}

int ScaleDialog::getInterpolationMethod(){
	int selection = interChoice->GetSelection();

	if (selection == 0) {
		return VMP;
	}
	else {
		return BILINEAL;
	}
}

void ScaleDialog::onBAceptar(wxCommandEvent & event) {
	this->EndModal(1);
}

void ScaleDialog::onBCancelar(wxCommandEvent & event) {
	if (IsModal())
		this->EndModal(0);
	else
		this->Destroy();
}
