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
#include <vector>
#include <wx\wx.h>
#include <algorithm>

class RawImage;

class LookUpTable {

	std::vector<unsigned char> table;

	void reset();


public:
	LookUpTable();								//Identidad
	LookUpTable(const LookUpTable& t);			//Constructor copia
	LookUpTable(double a, double b);			//Valores A y B para el ajuste lineal del brillo
	LookUpTable(long* original, long* target);	//Especificación del histograma
	LookUpTable(std::vector<wxPoint> points);		//Ajuste lineal por tramos
	LookUpTable(long* acc, int size);			//Ecualizar
	LookUpTable(long* hist, double gamma);		//Corrección gamma
	LookUpTable(unsigned char t);				//Umbralizado
	~LookUpTable();
	unsigned char get(unsigned char v) const;	
};

enum {
	ID_ECUALIZAR
};