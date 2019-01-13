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
#include "../Panel/HistogramPanel.h"
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/wxprec.h>
class HistogramFrame : public wxFrame{

	HistogramPanel* panel;
public:
	HistogramFrame(wxFrame* parent, long* data_abs, long* data_acc, const wxString& imageName);
	~HistogramFrame();

private:
	void OnMenuAjustesCambiar(wxCommandEvent & event);

	DECLARE_EVENT_TABLE()
};

enum {
	ID_M_AJUSTES_CAMBIAR
};