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
#include "LookUpTable.h"

void LookUpTable::reset(){
	for (int i = 0; i < 256; i++)
		table.push_back(i);
}

LookUpTable::LookUpTable() {
	reset();
}

LookUpTable::LookUpTable(const LookUpTable & t){
	this->table = t.table;
}

LookUpTable::LookUpTable(double a, double b){
	reset();

	for (int i = 0; i < table.size(); i++) {

		long value = round(a * double(i) + b);
		
		if (value > 255)
			value = 255;
		else if (value < 0)
			value = 0;

		table[i] = value;
	}
}

LookUpTable::LookUpTable(long* original, long* target){
	reset();
	//Normalizar los histogramas
	double* o = new double[256];
	double* t = new double[256];
	for (int i = 0; i < 256; i++) {
		o[i] = double(original[i]) / double(original[255]);
		t[i] = double(target[i]) / double(target[255]);
	}
	
	for (int i = 0; i < 256; i++) {
		int j = 255;
		do {
			table[i] = j;
			j--;
		} while (j >= 0 && o[i] <= t[j]);
	}
}

LookUpTable::LookUpTable(std::vector<wxPoint> points){

	reset();

	for (int i = 0; i < points.size() - 1; i++) {
		unsigned char Xi = points[i].x;
		unsigned char Yi = points[i].y;

		unsigned char Xf = points[i + 1].x;
		unsigned char Yf = points[i + 1].y;

		double m = double(Yf - Yi) / double(Xf - Xi);

		double n = Yi - m * Xi;

		for (int j = Xi; j <= Xf; j++) {
			table[j] = round(m * double(j) + n);
		}
	}
}

LookUpTable::LookUpTable(long* acc, int size){
	reset();

	for (int i = 0; i < 256; i++) {
		table[i] = std::max(double(0), round(double(256) / double(size) * double(acc[i])) - 1);
	}
}

LookUpTable::LookUpTable(long* hist, double gamma){
	reset();

	for (int i = 0; i < 256; i++) {
		//table[i] = 255 / log(256) * log(hist[i] + 1);
		double a = double(i) / double(255);
		double b = pow(a, gamma);
		table[i] = round(b * 255);	
	}
}

LookUpTable::LookUpTable(unsigned char t){
	reset();

	for (int i = 0; i < 256; i++) {
		table[i] = (table[i] > t) ? 255 : 0;
	}
}


LookUpTable::~LookUpTable(){
	table.clear();
}

unsigned char LookUpTable::get(unsigned char v) const{

	return table[v];
}
