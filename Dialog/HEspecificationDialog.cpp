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
#include "HEspecificationDialog.h"

BEGIN_EVENT_TABLE(HEspecificationDialog, wxDialog)
	EVT_BUTTON(ID_B_ACEPTAR, HEspecificationDialog::onBAceptar)
	EVT_BUTTON(ID_B_CANCELAR, HEspecificationDialog::onBCancelar)
END_EVENT_TABLE()

//UNDONE: Mejorar UX 
HEspecificationDialog::HEspecificationDialog(const wxArrayString& images)
	: wxDialog(NULL, wxID_ANY, "Especificación del histograma") {

	original = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, images);
	target = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, images);

	wxBoxSizer* rowsSizer = new wxBoxSizer(wxVERTICAL);
	rowsSizer->Add(new wxStaticText(this, wxID_ANY, "Original:"), 0, 0, 0);
	rowsSizer->Add(original);
	rowsSizer->Add(new wxStaticText(this, wxID_ANY, "Copiar de:"), 0, 0, 0);
	rowsSizer->Add(target);

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


HEspecificationDialog::~HEspecificationDialog(){

}

int HEspecificationDialog::getOriginalIndex(){
	return original->GetSelection();
}

int HEspecificationDialog::getTargetIndex(){
	return target->GetSelection();
}

void HEspecificationDialog::onBAceptar(wxCommandEvent & event) {
	this->EndModal(1);
}

void HEspecificationDialog::onBCancelar(wxCommandEvent & event) {
	if (IsModal())
		this->EndModal(0);
	else
		this->Destroy();
}

