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
// For compilers that support precompilation, includes "wx/wx.h".
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "Frame/MainWindow.h"

class ImageC : public wxApp {
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(ImageC);

bool ImageC::OnInit() {
	MainWindow *frame = new MainWindow(_T("ImageC"));
	frame->Show(true);
	return true;
}
