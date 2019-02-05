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
#include "../Frame/ImageFrame.h"
#include <vector>

class TLinealDialog : public wxDialog {

	std::vector<wxTextCtrl*> segmentsX;
	std::vector<wxTextCtrl*> segmentsY;
	ImageFrame* target;

	int pointsNo;

public:
	TLinealDialog(ImageFrame* t, int s);
	~TLinealDialog();

	std::vector<wxPoint> getPoints();

private:

	enum {
		ID_B_ACEPTAR,
		ID_B_CANCELAR
	};

	void onBAceptar(wxCommandEvent& event);
	void onBCancelar(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

