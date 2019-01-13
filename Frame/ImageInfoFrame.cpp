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
#include "ImageInfoFrame.h"

//UNDONE: Mostrar entropía
ImageInfoFrame::ImageInfoFrame(ImageFrame* parent) :
	wxFrame(parent, wxID_ANY, wxEmptyString){
	SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));

	wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
	sizer1->Add(new wxStaticText(this, wxID_ANY, "Tipo de fichero:"), 0, wxALL, 10);
	sizer1->Add(new wxStaticText(this, wxID_ANY, "Tamaño:"), 0, wxALL, 10);
	sizer1->Add(new wxStaticText(this, wxID_ANY, "Brillo:"), 0, wxALL, 10);
	sizer1->Add(new wxStaticText(this, wxID_ANY, "Contraste:"), 0, wxALL, 10);
	//sizer1->Add(new wxStaticText(this, wxID_ANY, "Entropía:"), 0, wxALL, 10);

	wxString file = parent->getExt();
	wxSize s = parent->getImageSize();
	wxString size = to_string(s.GetX()) + "x" + to_string(s.GetY());
	wxString brightness = to_string(parent->getBrightness());
	wxString contrast = to_string(parent->getContrast());
	//wxString entropy = "4";

	wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);
	sizer2->Add(new wxStaticText(this, wxID_ANY, file), 0, wxALL, 10);
	sizer2->Add(new wxStaticText(this, wxID_ANY, size), 0, wxALL, 10);
	sizer2->Add(new wxStaticText(this, wxID_ANY, brightness), 0, wxALL, 10);
	sizer2->Add(new wxStaticText(this, wxID_ANY, contrast), 0, wxALL, 10);
	//sizer2->Add(new wxStaticText(this, wxID_ANY, entropy), 0, wxALL, 10);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(sizer1, 1, 0, 0);
	sizer->Add(sizer2, 1, 0, 0);
	sizer->SetSizeHints(this);
	SetSizer(sizer);
	SetTitle("Información de " + parent->GetName());
}


ImageInfoFrame::~ImageInfoFrame(){

}
