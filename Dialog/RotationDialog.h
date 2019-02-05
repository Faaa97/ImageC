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
#include "../Tools/RawImage.h"

//UNDONE: Mejorar UX 
class RotationDialog : public wxDialog {

	wxChoice* interChoice;
	wxChoice* methodChoice;
	wxTextCtrl* angleCtrl;

public:
	RotationDialog();
	~RotationDialog();

	double getAngle();
	int getInterpolationMethod();
	int getRotationMethod();

private:

	enum {
		ID_B_ACEPTAR,
		ID_B_CANCELAR,
		ID_METODO
	};

	void onBAceptar(wxCommandEvent & event);
	void onBCancelar(wxCommandEvent & event);
	void onMethodUpdate(wxCommandEvent& event);

public:

	DECLARE_EVENT_TABLE()
};

