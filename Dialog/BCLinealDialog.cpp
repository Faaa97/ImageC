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
#include "BCLinealDialog.h"

BEGIN_EVENT_TABLE(BCLinealDialog, wxDialog)
	EVT_BUTTON(ID_B_ACEPTAR, BCLinealDialog::onBAceptar)
	EVT_BUTTON(ID_B_CANCELAR, BCLinealDialog::onBCancelar)
END_EVENT_TABLE()

//UNDONE: Mejorar UX del diálogo
BCLinealDialog::BCLinealDialog(ImageFrame* t)
	: wxDialog(NULL, wxID_ANY, "Brillo y contraste") {

	target = t;

	wxBoxSizer* actual = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* nuevo = new wxBoxSizer(wxVERTICAL);

	actual->Add(new wxStaticText(this, wxID_ANY, "Actual:"), 0, wxLEFT, 0);
	nuevo->Add(new wxStaticText(this, wxID_ANY, "Nuevo:"), 0, wxLEFT, 0);

	wxString b = to_string(target->getBrightness());	//Brillo
	wxString c = to_string(target->getContrast());	//Contraste

	wxTextCtrl* brilloCtrl = new wxTextCtrl(this, wxID_ANY, b, wxDefaultPosition);
	wxTextCtrl* contrasteCtrl = new wxTextCtrl(this, wxID_ANY, c, wxDefaultPosition);
	brilloCtrl->SetMaxLength(3);
	contrasteCtrl->SetMaxLength(3);
	brilloCtrl->Disable();
	contrasteCtrl->Disable();

	brilloNuevo = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);
	contrasteNuevo = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);
	brilloNuevo->SetMaxLength(3);
	contrasteNuevo->SetMaxLength(3);

	wxBoxSizer* brillo = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* contraste = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* brillo2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* contraste2 = new wxBoxSizer(wxHORIZONTAL);

	brillo->Add(new wxStaticText(this, wxID_ANY, "Brillo:"), 0, 0, 0);
	brillo->Add(brilloCtrl, 0, 0, 0);
	contraste->Add(new wxStaticText(this, wxID_ANY, "Contraste:"), 0, 0, 0);
	contraste->Add(contrasteCtrl, 0, 0, 0);

	brillo2->Add(new wxStaticText(this, wxID_ANY, "Brillo:"), 0, 0, 0);
	brillo2->Add(brilloNuevo, 0, 0, 0);
	contraste2->Add(new wxStaticText(this, wxID_ANY, "Contraste:"), 0, 0, 0);
	contraste2->Add(contrasteNuevo, 0, 0, 0);

	actual->Add(brillo, 0, 0, 0);
	actual->Add(contraste, 0, 0, 0);

	nuevo->Add(brillo2, 0, 0, 0);
	nuevo->Add(contraste2, 0, 0, 0);

	wxBoxSizer* buttons = new wxBoxSizer(wxHORIZONTAL);

	wxButton *aceptarButton = new wxButton(this, ID_B_ACEPTAR, wxT("Aceptar"),
		wxDefaultPosition);
	wxButton *cancelButton = new wxButton(this, ID_B_CANCELAR, wxT("Cancelar"),
		wxDefaultPosition);

	buttons->Add(aceptarButton, 0);
	buttons->Add(cancelButton, 0);

	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

	dialogSizer->Add(actual, 0, 0, 0);
	dialogSizer->Add(nuevo, 0, 0, 0);
	dialogSizer->Add(buttons, 0, 0, 0);
	SetSizerAndFit(dialogSizer);
}


BCLinealDialog::~BCLinealDialog(){

}

unsigned char BCLinealDialog::getNewBrightness(){
	return stoi(brilloNuevo->GetValue().ToStdString());
}

unsigned char BCLinealDialog::getNewContrast(){
	return stoi(contrasteNuevo->GetValue().ToStdString());
}

void BCLinealDialog::onBAceptar(wxCommandEvent & event){
	this->EndModal(1);
}

void BCLinealDialog::onBCancelar(wxCommandEvent & event){
	if (IsModal())
		this->EndModal(0);
	else
		this->Destroy();
}
