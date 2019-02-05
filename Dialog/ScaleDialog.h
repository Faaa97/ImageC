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
class ScaleDialog : public wxDialog {

	wxChoice* interChoice;
	wxTextCtrl* scaleCtrl;

public:
	ScaleDialog();
	~ScaleDialog();

	int getProportion();
	int getInterpolationMethod();

private:

	enum {
		ID_B_ACEPTAR,
		ID_B_CANCELAR
	};

	void onBAceptar(wxCommandEvent & event);
	void onBCancelar(wxCommandEvent & event);

public:

	DECLARE_EVENT_TABLE()
};

