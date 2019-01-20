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
#include <wx/wxprec.h>
#include <vector>
#include "ImageFrame.h"
#include "HistogramFrame.h"
#include "ImageInfoFrame.h"

#include "../Dialog/TLinealDialog.h"
#include "../Dialog/BCLinealDialog.h"
#include "../Dialog/HEspecificationDialog.h"
#include "../Dialog/ScaleDialog.h"
//#include <wx/frame.h>

// For compilers that support precompilation, includes "wx/wx.h".
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
class MainWindow : public wxFrame {
private:
	std::vector<ImageFrame*> images;
	ImageFrame* lastFocus;

	void buildAndShowHistogram(ImageFrame* target);
	bool updateLastFocus();			//Returns true if there is lastFocus (i.e. one image open)
	bool saveAndCloseAllImages();	//Returns true if all images were closed
	int askUserForSave(ImageFrame* target = NULL);
	// TODO: Hacer función para que guarde al cerrar el programa si se han hecho cambios sin guardar 
	ImageFrame* duplicate(ImageFrame* frame);
	wxArrayString getImagesName();
	wxString getNewImageName(wxString oldName);

	bool guardarImagen(ImageFrame* target = NULL);	//Returns true if saved correctly
	void cerrarImagen(ImageFrame* target = NULL);

public:
	MainWindow(const wxString& title);
	~MainWindow();
	
private:
	//Handlers
	void OnMenuArchivoAbrir(wxCommandEvent &event);
	void OnMenuArchivoGuardar(wxCommandEvent &event);
	void OnMenuArchivoCerrar(wxCommandEvent &event);
	void OnMenuImagenAjustarUmbralizado(wxCommandEvent & event);
	void OnMenuImagenAjustarTamano(wxCommandEvent & event);
	void OnMenuImagenInfo(wxCommandEvent & event);
	void OnMenuImagenConvertirNTSC(wxCommandEvent &event);
	void OnMenuImagenConvertirPAL(wxCommandEvent &event);
	void OnMenuImagenDuplicar(wxCommandEvent & event);
	void OnMenuImagenEscalado(wxCommandEvent & event);
	void OnMenuImagenTransformarEspejoHorizontal(wxCommandEvent & event);
	void OnMenuImagenTransformarEspejoVertical(wxCommandEvent & event);
	void OnMenuImagenTransformarRotarDerecha(wxCommandEvent & event);
	void OnMenuImagenTransformarRotarIzquierda(wxCommandEvent & event);
	void OnMenuImagenTransformarRotacion(wxCommandEvent & event);
	void OnMenuImagenTransformarTraspuesta(wxCommandEvent & event);
	void OnMenuProcesarTLineal(wxCommandEvent & event);
	void OnMenuProcesarBrilloContraste(wxCommandEvent & event);
	void OnMenuProcesarEcualizar(wxCommandEvent & event);
	void OnMenuProcesarEspecificacionH(wxCommandEvent & event);
	void OnMenuProcesarCorreccionGamma(wxCommandEvent & event);
	void OnMenuProcesarDiferencia(wxCommandEvent & event);
	void OnMenuProcesarFiltrosConvolucion(wxCommandEvent & event);
	void OnMenuAnalizarHistograma(wxCommandEvent & event);
	void OnQuit(wxCommandEvent& event);
	void OnExit(wxCloseEvent& event);
	void OnAbout(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

enum {
	ID_M_ARCHIVO,
	ID_M_ARCHIVO_ABRIR_IMAGEN,
	ID_M_ARCHIVO_CERRAR_IMAGEN,
	ID_M_ARCHIVO_GUARDAR_IMAGEN,
	ID_M_EDITAR,
	ID_M_IMAGEN,
	ID_M_IMAGEN_AJUSTAR_UMBRALIZADO,
	ID_M_IMAGEN_AJUSTAR_TAMANO,
	ID_M_IMAGEN_INFO,
	ID_M_IMAGEN_CONVERTIR_NTSC,
	ID_M_IMAGEN_CONVERTIR_PAL,
	ID_M_IMAGEN_DUPLICAR,
	ID_M_IMAGEN_ESCALADO,
	ID_M_IMAGEN_TRANSFORMAR_ESPEJO_HORIZONTAL,
	ID_M_IMAGEN_TRANSFORMAR_ESPEJO_VERTICAL,
	ID_M_IMAGEN_TRANSFORMAR_ROTAR_90_DERECHA,
	ID_M_IMAGEN_TRANSFORMAR_ROTAR_90_IZQUIERDA,
	ID_M_IMAGEN_TRANSFORMAR_ROTACION,
	ID_M_IMAGEN_TRANSFORMAR_TRASPUESTA,
	ID_M_PROCESAR,
	ID_M_PROCESAR_TRANSFORMACION_LINEAL,
	ID_M_PROCESAR_BRILLO_CONTRASTE,
	ID_M_PROCESAR_ECUALIZAR,
	ID_M_PROCESAR_ESPECIFICACION_HISTOGRAMA,
	ID_M_PROCESAR_CORRECCION_GAMMA,
	ID_M_PROCESAR_DIFERENCIA,
	ID_M_PROCESAR_FILTROS_CONVOLUCION,
	ID_M_ANALIZAR,
	ID_M_ANALIZAR_HISTOGRAMA,
	ID_M_AYUDA,
	ID_CERRAR,
	USER_YES,
	USER_CANCEL,
	USER_NO,
};


