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
#include "MainWindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_MENU(ID_M_ARCHIVO_ABRIR_IMAGEN, MainWindow::OnMenuArchivoAbrir)
	EVT_MENU(ID_M_ARCHIVO_GUARDAR_IMAGEN, MainWindow::OnMenuArchivoGuardar)
	EVT_MENU(ID_M_ARCHIVO_CERRAR_IMAGEN, MainWindow::OnMenuArchivoCerrar)
	EVT_MENU(ID_M_IMAGEN_AJUSTAR_UMBRALIZADO, MainWindow::OnMenuImagenAjustarUmbralizado)
	EVT_MENU(ID_M_IMAGEN_AJUSTAR_TAMANO, MainWindow::OnMenuImagenAjustarTamano)
	EVT_MENU(ID_M_IMAGEN_INFO, MainWindow::OnMenuImagenInfo)
	EVT_MENU(ID_M_IMAGEN_DUPLICAR, MainWindow::OnMenuImagenDuplicar)
	EVT_MENU(ID_M_IMAGEN_ESCALADO, MainWindow::OnMenuImagenEscalado)
	EVT_MENU(ID_M_IMAGEN_CONVERTIR_NTSC, MainWindow::OnMenuImagenConvertirNTSC)
	EVT_MENU(ID_M_IMAGEN_CONVERTIR_PAL, MainWindow::OnMenuImagenConvertirPAL)
	EVT_MENU(ID_M_IMAGEN_TRANSFORMAR_ESPEJO_HORIZONTAL, MainWindow::OnMenuImagenTransformarEspejoHorizontal)
	EVT_MENU(ID_M_IMAGEN_TRANSFORMAR_ESPEJO_VERTICAL, MainWindow::OnMenuImagenTransformarEspejoVertical)
	EVT_MENU(ID_M_IMAGEN_TRANSFORMAR_ROTAR_90_DERECHA, MainWindow::OnMenuImagenTransformarRotarDerecha)
	EVT_MENU(ID_M_IMAGEN_TRANSFORMAR_ROTAR_90_IZQUIERDA, MainWindow::OnMenuImagenTransformarRotarIzquierda)
	EVT_MENU(ID_M_IMAGEN_TRANSFORMAR_ROTACION, MainWindow::OnMenuImagenTransformarRotacion)
	EVT_MENU(ID_M_IMAGEN_TRANSFORMAR_TRASPUESTA, MainWindow::OnMenuImagenTransformarTraspuesta)
	EVT_MENU(ID_M_PROCESAR_TRANSFORMACION_LINEAL, MainWindow::OnMenuProcesarTLineal)
	EVT_MENU(ID_M_PROCESAR_BRILLO_CONTRASTE, MainWindow::OnMenuProcesarBrilloContraste)
	EVT_MENU(ID_M_PROCESAR_ECUALIZAR, MainWindow::OnMenuProcesarEcualizar)
	EVT_MENU(ID_M_PROCESAR_ESPECIFICACION_HISTOGRAMA, MainWindow::OnMenuProcesarEspecificacionH)
	EVT_MENU(ID_M_PROCESAR_CORRECCION_GAMMA, MainWindow::OnMenuProcesarCorreccionGamma)
	EVT_MENU(ID_M_PROCESAR_DIFERENCIA, MainWindow::OnMenuProcesarDiferencia)
	EVT_MENU(ID_M_PROCESAR_FILTROS_CONVOLUCION, MainWindow::OnMenuProcesarFiltrosConvolucion)
	EVT_MENU(ID_M_ANALIZAR_HISTOGRAMA, MainWindow::OnMenuAnalizarHistograma)
	EVT_MENU(wxID_EXIT, MainWindow::OnQuit)
	EVT_CLOSE(MainWindow::OnExit)
END_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title) {

	lastFocus = NULL;
	
	SetIcon(wxICON(sample));
	wxMenu *archivo_M = new wxMenu;
	wxMenu *editar_M = new wxMenu;
	wxMenu *imagen_M = new wxMenu;
	wxMenu *procesar_M = new wxMenu;
	wxMenu *analizar_M = new wxMenu;
	wxMenu *ayuda_M = new wxMenu;

	//ARCHIVO
	archivo_M->Append(ID_M_ARCHIVO_ABRIR_IMAGEN, "&Abrir...",
		"Importar imagen para trabajar sobre ella.");
	
	archivo_M->Append(ID_M_ARCHIVO_GUARDAR_IMAGEN, "&Guardar...",
		"Guardar imagen.");

	archivo_M->Append(ID_M_ARCHIVO_CERRAR_IMAGEN, "&Cerrar",
		"Cerrar imagen.");

	archivo_M->AppendSeparator();
	archivo_M->Append(wxID_ABOUT);
	archivo_M->Append(wxID_EXIT, "&Salir",
		"Cerrar el programa.");
	//EDITAR
	//IMAGEN
	wxMenu *imagen_ajustar_M = new wxMenu;

	imagen_ajustar_M->Append(ID_M_IMAGEN_AJUSTAR_UMBRALIZADO, "&Umbralizado",
		"Crear imagen a partir de valor umbral.");

	imagen_ajustar_M->Append(ID_M_IMAGEN_AJUSTAR_TAMANO, "&Tamaño",
		"Cambiar el tamaño de la imagen.");

	imagen_M->AppendSubMenu(imagen_ajustar_M, _T("&Ajuste"));

	imagen_M->Append(ID_M_IMAGEN_INFO, "&Información de la imagen",
		"Mostrar información detallada de la imagen.");

	wxMenu *imagen_convertir_M = new wxMenu;
	
	imagen_convertir_M->Append(ID_M_IMAGEN_CONVERTIR_NTSC, "&NTSC",
		"Escala de grises modo NTSC.");
	imagen_convertir_M->Append(ID_M_IMAGEN_CONVERTIR_PAL, "&PAL",
		"Escala de grises modo PAL.");

	imagen_M->AppendSubMenu(imagen_convertir_M, _T("&Convertir a escala de grises"));

	imagen_M->AppendSeparator();

	imagen_M->Append(ID_M_IMAGEN_DUPLICAR, "&Duplicar",
		"Duplicar imagen.");

	imagen_M->Append(ID_M_IMAGEN_ESCALADO, "&Escalado...",
		"Escalar la imagen e interpolación VMP o Bilineal.");

	wxMenu *imagen_transformar_M = new wxMenu;

	imagen_transformar_M->Append(ID_M_IMAGEN_TRANSFORMAR_ESPEJO_HORIZONTAL, "&Espejo horizontal",
		"Invertir la imagen horizontalmente, pixel a pixel.");

	imagen_transformar_M->Append(ID_M_IMAGEN_TRANSFORMAR_ESPEJO_VERTICAL, "&Espejo vertical",
	"Invertir la imagen verticalmente, pixel a pixel.");

	imagen_transformar_M->Append(ID_M_IMAGEN_TRANSFORMAR_ROTAR_90_DERECHA, "&Rotar 90º Derecha",
		"Rotar la imagen en sentido antihorario 90º.");

	imagen_transformar_M->Append(ID_M_IMAGEN_TRANSFORMAR_ROTAR_90_IZQUIERDA, "&Rotar 90º Izquierda",
		"Rotar la imagen en sentido horario 90º.");

	imagen_transformar_M->Append(ID_M_IMAGEN_TRANSFORMAR_ROTACION, "&Rotación...",
		"Rotar la imagen según ángulo y sentido.")->Enable(false);	//Remove "->Enable(false)" when ready

	imagen_transformar_M->Append(ID_M_IMAGEN_TRANSFORMAR_TRASPUESTA, "&Imagen traspuesta",
		"Intercambiar filas por columnas en la imagen.");

	imagen_M->AppendSubMenu(imagen_transformar_M, _T("&Transformar"));

	//PROCESAR
	procesar_M->Append(ID_M_PROCESAR_TRANSFORMACION_LINEAL, "&Transformación lineal",
		"Realizar tranformación lineal.");

	procesar_M->Append(ID_M_PROCESAR_BRILLO_CONTRASTE, "&Brillo y Contraste",
		"Cambiar el brillo y contraste linealmente.");

	procesar_M->AppendSeparator();

	procesar_M->Append(ID_M_PROCESAR_ECUALIZAR, "&Ecualizar",
		"Ecualizar el histograma de la imagen.");

	procesar_M->Append(ID_M_PROCESAR_ESPECIFICACION_HISTOGRAMA, "&Especificación del histograma",
		"Especificar histograma.");

	procesar_M->Append(ID_M_PROCESAR_CORRECCION_GAMMA, "&Corrección Gamma",
		"Corrección Gamma.");

	procesar_M->Append(ID_M_PROCESAR_DIFERENCIA, "&Diferencia de imágenes",
		"Diferencia de imágenes.");

	wxMenu *procesar_filtros_M = new wxMenu;

	procesar_filtros_M->Append(ID_M_PROCESAR_FILTROS_CONVOLUCION, "&Convolución...",
		"Convoluciona una imagen utilizando un kernel.")->Enable(false);	//Remove "->Enable(false)" when ready

	procesar_M->AppendSubMenu(procesar_filtros_M, _T("&Filtros"));

	//ANALIZAR
	analizar_M->Append(ID_M_ANALIZAR_HISTOGRAMA, "&Histograma",
		"Mostrar histograma de la imagen.");
	//AYUDA

	//MENU
	wxMenuBar *menuBar = new wxMenuBar();

	menuBar->Append(archivo_M, _T("&Archivo"));
	menuBar->Append(editar_M, _T("&Editar"));
	menuBar->Append(imagen_M, _T("&Imagen"));
	menuBar->Append(procesar_M, _T("&Procesar"));
	menuBar->Append(analizar_M, _T("&Analizar"));
	menuBar->Append(ayuda_M, _T("&Ayuda"));
	SetMenuBar(menuBar);
	CreateStatusBar(1);

}

void MainWindow::buildAndShowHistogram(ImageFrame* target) {

	long* data_abs = target->computeHistogram(H_ABSOLUTE);
	long* data_acc = target->computeHistogram(H_ACCUMULATIVE);

	HistogramFrame* frame = new HistogramFrame(this, data_abs, data_acc, target->GetName());	//UNDONE: Close pointer
	frame->Show();
	frame->Raise();
}

bool MainWindow::updateLastFocus(){
	int index = -1;
	wxDateTime max = wxDateTime((time_t) 1);
	for (int i = 0; i < images.size(); i++) {
		if (images[i] == NULL || images[i]->isClosed()) {
			images.erase(images.begin() + i);
			i--;
			continue;
		}
		if (max < images[i]->getLastFocus() ){
			index = i;
			max = images[i]->getLastFocus();
		}
	}

	if (index == -1) {	//No image
		lastFocus = NULL;
		return false;
	}

	lastFocus = images[index];
	return true;
}

bool MainWindow::saveAndCloseAllImages() {
	updateLastFocus();

	bool successful = true;

	for (int i = 0; i < images.size(); i++) {
		int result = askUserForSave();
		if (result == USER_YES) {
			guardarImagen(images[i]);
			cerrarImagen(images[i]);
			i--;
		} else if (result == USER_NO) {
			//BUG: A veces falla, errores con los punteros.
			cerrarImagen(images[i]);
			i--;
		} else	//USER_CANCEL
			return false;
	}
	return successful;

}

int MainWindow::askUserForSave(ImageFrame* target) {

	ImageFrame* t;
	if (target == NULL && updateLastFocus()) {
		t = lastFocus;
	} else
		t = target;

	int save = USER_CANCEL;

	if (t->isModified()) {
		wxString message = "Hay cambios no guardados.\n¿Desea guardar?";
		wxString title = "Cerrando... ¿Está seguro?";
		long style = wxYES_NO | wxCANCEL | wxCENTRE | wxSTAY_ON_TOP;
		wxMessageDialog dialog(this, message, title, style);
		int response = dialog.ShowModal();

		switch (response) {
		case wxID_YES: {//Guardamos
						//BUG: Si le damos que queremos guardar y cancelamos en el dialogo, no guardamos y perdemos la imagen
			save = USER_YES;
			break;
		}
		case wxID_NO: {	//Cerramos
			save = USER_NO;
			break;
		}
		case wxID_CANCEL: {
			save = USER_CANCEL;
			break;
		}
		default: {}		//No hacemos nada
		}

	} else {
		save = USER_NO;
	}

	return save;
}

ImageFrame* MainWindow::duplicate(ImageFrame* frame){
	wxString newName = getNewImageName(frame->GetName());
	ImageFrame* image = new ImageFrame(*frame);
	image->SetName(newName);
	image->SetTitle(newName);
	images.push_back(image);
	image->Show();
	return image;
}

wxArrayString MainWindow::getImagesName(){
	updateLastFocus();
	wxArrayString result;

	for (int i = 0; i < images.size(); i++) {
		result.Add(images[i]->GetName());	//BUG: A veces cuando se cierra la ventana no podemos quitarla
	}

	return result;
}

wxString MainWindow::getNewImageName(wxString oldName){
	wxString name, version, ext, result;
	int v = 0;

	wxRegEx expresion(string("(.*?)([-](\\d+))?[.](.*)$"), wxRE_ICASE | wxRE_ADVANCED);	//0: todo, 1: nombre, 3: versión, 4: extensión
	if (expresion.IsValid() && expresion.Matches(oldName)) {
		name = expresion.GetMatch(oldName, 1);
		version = expresion.GetMatch(oldName, 3);
		ext = expresion.GetMatch(oldName, 4);

		if (version.IsNull()) {
			v = 0;
		}
		else {
			v = stoi(version.ToStdString());
		}
		v++;

		result = name + "-" + to_string(v) + "." + ext;

		return result;
	}

	return oldName;
}

bool MainWindow::guardarImagen(ImageFrame* target){
	
	wxString wildcard = " Imagen jpg (*.jpg)|*.jpg| Imagen png (*.png)|*.png| Mapa de bits (*.bmp)|*.bmp| Imagen tiff (*.tiff)|*.tiff| Todos los archivos (*.*)|*.*";
	wxString title = "Guardar fichero...";

	wxFileDialog saveFileDialog(this, title, "", "", wildcard, wxFD_SAVE);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return false;

	wxBitmapType type = target->getType(saveFileDialog.GetPath());

	if (type == wxBITMAP_TYPE_INVALID) {
		wxString message = "Formato de imagen inválido.\nOperación cancelada.";
		wxString title = "Advertencia";
		long style = wxOK | wxICON_EXCLAMATION | wxCENTRE | wxSTAY_ON_TOP;
		wxMessageDialog dialog(this, message, title, style);
		dialog.ShowModal();
		return false;
	}
	else {
		target->saveToFile(saveFileDialog.GetPath());
		return true;
	}
}

void MainWindow::cerrarImagen(ImageFrame* target){

	for (std::vector<ImageFrame*>::iterator i = images.begin(); i != images.end(); ++i) {
		if (*i == target) {
			(*i)->Close(true);
			images.erase(i, ++i);
			break;
		}
	}
	updateLastFocus();
}

MainWindow::~MainWindow() {

}

void MainWindow::OnQuit(wxCommandEvent& event){
	bool result = saveAndCloseAllImages();
	if (result) {
		lastFocus = NULL;
		Destroy();
		event.Skip();
	}
}

void MainWindow::OnExit(wxCloseEvent& event) {
	bool result = saveAndCloseAllImages();
	if (result) {
		lastFocus = NULL;
		Destroy();
		event.Skip();
	}
}

void MainWindow::OnAbout(wxCommandEvent& WXUNUSED(event)){
	wxString msg;
	msg.Printf(_T("About.\n")
		_T("Welcome to %s"), wxVERSION_STRING);

	wxMessageBox(msg, _T("About My Program"),
		wxOK | wxICON_INFORMATION, this);
}

void MainWindow::OnMenuArchivoAbrir(wxCommandEvent& WXUNUSED(event)){
	
	wxString wildcard = " Imagen jpg (*.jpg)|*.jpg| Imagen png (*.png)|*.png| Mapa de bits (*.bmp)|*.bmp| Imagen tiff (*.tiff)|*.tiff| Todos los archivos (*.*)|*.*";

	wxFileDialog openFileDialog(this, _("Abrir imagen..."), "", "", wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxFileInputStream input_stream(openFileDialog.GetPath());
	if (!input_stream.IsOk()){
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
		return;
	}

	ImageFrame* image = new ImageFrame(this, openFileDialog.GetPath(), openFileDialog.GetFilename());
	images.push_back(image);
	image->Show();
	image->Raise();
}

void MainWindow::OnMenuArchivoGuardar(wxCommandEvent & event) {
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	guardarImagen(lastFocus);
}

void MainWindow::OnMenuArchivoCerrar(wxCommandEvent& WXUNUSED(event)) {
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	int result = askUserForSave();
	switch (result) {
	case USER_YES: {//Guardamos
		if (!guardarImagen(lastFocus)) {
			break;	//Si no hemos guardado, no cerramos la imagen.
		}
	}
	case USER_NO: {	//Cerramos
		cerrarImagen(lastFocus);
		break;
	}
	case USER_CANCEL: {
		break;
	}
	default: {}		//No hacemos nada
	}
}

void MainWindow::OnMenuImagenAjustarUmbralizado(wxCommandEvent & event) {
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	int umbral = 0;
	wxTextEntryDialog segmentDialog(lastFocus, "Introduce el umbral", "Umbralizado.");
	segmentDialog.SetMaxLength(3);
	int userAction = segmentDialog.ShowModal();
	if (userAction == wxID_OK) {
		umbral = stoi(segmentDialog.GetValue().ToStdString());
		lastFocus = duplicate(lastFocus);
		lastFocus->computeThreshold(umbral);
		lastFocus->Raise();
	}
	else {
		//Nothing
	}
}

void MainWindow::OnMenuImagenAjustarTamano(wxCommandEvent & event){
	//UNDONE: Que ajuste el tamaño
}

void MainWindow::OnMenuImagenInfo(wxCommandEvent & event) {
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	ImageInfoFrame* frame = new ImageInfoFrame(lastFocus);
	frame->Show();
	frame->Raise();
}

void MainWindow::OnMenuImagenConvertirNTSC(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	lastFocus = duplicate(lastFocus);
	lastFocus->convertToGrayScale(NTSC);
	lastFocus->Raise();
}

void MainWindow::OnMenuImagenConvertirPAL(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	lastFocus = duplicate(lastFocus);
	lastFocus->convertToGrayScale(PAL);
	lastFocus->Raise();
}

void MainWindow::OnMenuImagenDuplicar(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	lastFocus = duplicate(lastFocus);
	lastFocus->Raise();
}

void MainWindow::OnMenuImagenEscalado(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	ScaleDialog dialog;

	if (dialog.ShowModal()) {
		double p = double(dialog.getProportion()) / double(100);
		int m = dialog.getInterpolationMethod();
		lastFocus = duplicate(lastFocus);
		lastFocus->computeScaling(p, m);
		lastFocus->Raise();
	}
	else {
		//nothing
	}
}

void MainWindow::OnMenuImagenTransformarEspejoHorizontal(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	lastFocus = duplicate(lastFocus);
	lastFocus->computeFlip(HORIZONTAL);
	lastFocus->Raise();
}

void MainWindow::OnMenuImagenTransformarEspejoVertical(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	lastFocus = duplicate(lastFocus);
	lastFocus->computeFlip(VERTICAL);
	lastFocus->Raise();
}

void MainWindow::OnMenuImagenTransformarRotarDerecha(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	lastFocus = duplicate(lastFocus);
	lastFocus->compute90Rotation(RIGHT);
	lastFocus->Raise();
}

void MainWindow::OnMenuImagenTransformarRotarIzquierda(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	lastFocus = duplicate(lastFocus);
	lastFocus->compute90Rotation(LEFT);
	lastFocus->Raise();
}

void MainWindow::OnMenuImagenTransformarRotacion(wxCommandEvent & event){

}

void MainWindow::OnMenuImagenTransformarTraspuesta(wxCommandEvent & event){
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	lastFocus = duplicate(lastFocus);
	lastFocus->computeTranspose();
	lastFocus->Raise();
}

void MainWindow::OnMenuProcesarTLineal(wxCommandEvent & event) {
	//TODO: Esto es lo ultimo, el else externo no funciona del todo
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	int segments = 0;
	wxTextEntryDialog segmentDialog(lastFocus, "Introduce el número de segmentos", "Transformación lineal.");
	segmentDialog.SetMaxLength(3);
	if (segmentDialog.ShowModal() == wxID_OK) {
		lastFocus = duplicate(lastFocus);
		segments = stoi(segmentDialog.GetValue().ToStdString());

		TLinealDialog pointsDialog(lastFocus, segments);
		if (pointsDialog.ShowModal() == wxID_OK) {
			vector<wxPoint> points = pointsDialog.getPoints();
			lastFocus->computeLinealTranformation(points);
			lastFocus->Raise();
		}
		else {
			//cerrarImagen(lastFocus);	//User-cancelled
		}
	}
	else {
		//cerrarImagen(lastFocus);	//User-cancelled
	}
}

void MainWindow::OnMenuProcesarBrilloContraste(wxCommandEvent & event) {
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	BCLinealDialog dialog(lastFocus);
	if (dialog.ShowModal()) {
		unsigned char b = dialog.getNewBrightness();
		unsigned char c = dialog.getNewContrast();
		lastFocus = duplicate(lastFocus);
		lastFocus->computeNewBrightnessAndContrast(b, c);
		lastFocus->Raise();
	}
	else {
		//nothing
	}
	
}

void MainWindow::OnMenuProcesarEcualizar(wxCommandEvent & event) {
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	wxString message = "¿Quiere visualizar los histogramas de la imagen original y de la resultante?";
	wxString title = "¿Quiere los histogramas?";
	long style = wxYES_NO | wxCANCEL | wxCENTRE | wxSTAY_ON_TOP;
	wxMessageDialog dialog(this, message, title, style);
	int response = dialog.ShowModal();

	switch (response) {
	case wxID_YES: {//Mostramos los histogramas y hacemos el calculo
		buildAndShowHistogram(lastFocus);	//Histograma imagen original
		lastFocus = duplicate(lastFocus);	//Hacemos el calculo
		lastFocus->computeEqualization();
		lastFocus->Raise();
		buildAndShowHistogram(lastFocus);	//Histograma imagen nueva
		break;
	}
	case wxID_NO: {	//Hacemos el calculo
		lastFocus = duplicate(lastFocus);
		lastFocus->computeEqualization();
		lastFocus->Raise();
		break;
	}
	//case wxID_CANCEL: {}	//No hacemos nada
	default: {}		//No hacemos nada
	}

}

void MainWindow::OnMenuProcesarEspecificacionH(wxCommandEvent & event) {

	HEspecificationDialog dialog(this->getImagesName());
	if (dialog.ShowModal()) {
		int original = dialog.getOriginalIndex();
		int target = dialog.getTargetIndex();
		if (original != -1 && target != -1) {
			lastFocus = duplicate(images[original]);
			lastFocus->computeHistogramEspecification(images[original], images[target]);
			lastFocus->Raise();
		}
		else {
			wxString message = "Imágenes inválidas.\nOperación cancelada.";
			wxString title = "Advertencia";
			long style = wxOK | wxICON_EXCLAMATION | wxCENTRE | wxSTAY_ON_TOP;
			wxMessageDialog dialog(this, message, title, style);
			dialog.ShowModal();
		}
	}
}

void MainWindow::OnMenuProcesarCorreccionGamma(wxCommandEvent & event) {
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;
	
	double gamma = 0;
	wxTextEntryDialog segmentDialog(lastFocus, "Introduce gamma.", "Corrección gamma.");
	segmentDialog.SetMaxLength(3);
	if (segmentDialog.ShowModal()) {
		gamma = stod(segmentDialog.GetValue().ToStdString());

		lastFocus = duplicate(lastFocus);
		lastFocus->computeGammaCorrection(gamma);
		lastFocus->Raise();
	}
	else {
		//Nothing
	}	
}

void MainWindow::OnMenuProcesarDiferencia(wxCommandEvent & event) {

	HEspecificationDialog dialog(this->getImagesName());
	if (dialog.ShowModal()) {
		int original = dialog.getOriginalIndex();
		int target = dialog.getTargetIndex();
		if (original != -1 && target != -1) {
			lastFocus = duplicate(images[original]);
			lastFocus->computeDiference(images[original], images[target]);
			lastFocus->Raise();
		}
		else {
			wxString message = "Imágenes inválidas.\nOperación cancelada.";
			wxString title = "Advertencia";
			long style = wxOK | wxICON_EXCLAMATION | wxCENTRE | wxSTAY_ON_TOP;
			wxMessageDialog dialog(this, message, title, style);
			dialog.ShowModal();
		}
	}
}

void MainWindow::OnMenuProcesarFiltrosConvolucion(wxCommandEvent & event){

}


void MainWindow::OnMenuAnalizarHistograma(wxCommandEvent & event) {
	bool status = updateLastFocus();

	if (!status) //if status == false then lastFocus == NULL
		return;

	buildAndShowHistogram(lastFocus);
}

