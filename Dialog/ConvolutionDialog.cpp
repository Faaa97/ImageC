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
#include "ConvolutionDialog.h"

BEGIN_EVENT_TABLE(ConvolutionDialog, wxDialog)
	EVT_BUTTON(ID_B_ACEPTAR, ConvolutionDialog::onBAceptar)
	EVT_BUTTON(ID_B_CANCELAR, ConvolutionDialog::onBCancelar)
END_EVENT_TABLE()

ConvolutionDialog::ConvolutionDialog()
	: wxDialog(NULL, wxID_ANY, "Convolución") {

	computed = false;

	wxString placeholder = "1 1 1\n1 1 1\n1 1 1";

	input = new wxTextCtrl(this, wxID_ANY, placeholder, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

	wxBoxSizer* buttons = new wxBoxSizer(wxHORIZONTAL);

	wxButton *aceptarButton = new wxButton(this, ID_B_ACEPTAR, wxT("Aceptar"),
		wxDefaultPosition);
	wxButton *cancelButton = new wxButton(this, ID_B_CANCELAR, wxT("Cancelar"),
		wxDefaultPosition);

	buttons->Add(aceptarButton, 0);
	buttons->Add(cancelButton, 0, 0, 0);

	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

	dialogSizer->Add(input, 0, 0, 0);
	dialogSizer->Add(buttons, 0, 0, 0);
	SetSizerAndFit(dialogSizer);

}

void ConvolutionDialog::onBAceptar(wxCommandEvent & event){
	this->EndModal(1);
}

void ConvolutionDialog::onBCancelar(wxCommandEvent & event){
	if (IsModal())
		this->EndModal(0);
	else
		this->Destroy();
}

ConvolutionDialog::~ConvolutionDialog(){

}

std::vector<std::vector<long>> ConvolutionDialog::getKernel(){

	if (!computed) {

		int lines = input->GetNumberOfLines();

		kernel.resize(lines);

		for (int i = 0; i < kernel.size(); i++) {
			wxString text = input->GetLineText(i);

			std::stringstream ss(text.ToStdString());

			std::vector<long> kernelRow;

			while (ss.good()) {
				long number = 0;

				ss >> (long)number;

				kernelRow.push_back(number);
			}

			kernel[i].resize(kernelRow.size());
			for (int j = 0; j < kernel[i].size(); j++)
				kernel[i][j] = kernelRow[j];

		}
	}

	return kernel;
}
