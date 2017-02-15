//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Color_Chooser.H>
#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"
#include <sstream>
#include <iostream>

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//-------------------------------------------------------------
// Brings up the dimmed dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_dimmed_view(Fl_Menu_* o, void* v) 
{
	// printf("show\n");
	// ImpressionistDoc *pDoc=whoami(o)->getDocument();
	whoami(o)->m_dimmedDialog->show();
}

// void ImpressionistUI::cb_restore_painting(Fl_Widget* o, void* v)
// {
// 	printf("callback\n");
// 	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
// 	ImpressionistDoc* pDoc=pUI->getDocument();
// 	pDoc->m_ucPainting=pDoc->m_ucDisplayBitmap;
// 	if (pDoc->m_ucDisplayBitmap)
// 	{
// 		delete []  pDoc->m_ucDisplayBitmap;
// 	}
// 	pDoc->m_ucDisplayBitmap = NULL;
// }

//-------------------------------------------------------------
// Brings up the filter dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_filter(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_filterSizeDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Colors function
// Called by the UI when the colors menu item is chosen
//------------------------------------------------------------

void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v){
	int y = fl_color_chooser("Color",m_nR,m_nG,m_nB);
}

//------------------------------------------------------------
// Paintly function
// Called by the UI when the paintly menu item is chosen
//------------------------------------------------------------

void ImpressionistUI::cb_paintly(Fl_Menu_* o, void* v){
	whoami(o)->m_paintlyDialog->show();
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_dissolve_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Dissolve File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->dissolveImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load mural image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_mural_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Mural File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadMuralImage(newfile);
	}
}

//------------------------------------------------------------
// Load Edge Image function
// Called by the UI when the load_edge_image menu item is chosen
//------------------------------------------------------------

void ImpressionistUI::cb_load_edge_image(Fl_Menu_* o, void* v){
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Load Edge File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadEdgeImage(newfile);
	}
}

//------------------------------------------------------------
// Load Another Image function
// Called by the UI when the load_edge_image menu item is chosen
//------------------------------------------------------------

void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v){
	ImpressionistDoc* pDoc=whoami(o)->getDocument();
	char* newfile = fl_file_chooser("Open Another File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadAnotherImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load alpha brush menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_alpha_brush(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAlphaMap(newfile);
	}
	brushTypeMenu[BRUSH_ALPHA_MAPPED].activate();
}


//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();
	whoami(o)->m_filterSizeDialog->hide();

}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the original_image menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_original_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();
	pDoc->m_pUI->m_origView->imageIndex = 0;
	pDoc->m_pUI->m_origView->refresh();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the edge_image menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_edge_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();
	pDoc->m_pUI->m_origView->imageIndex = 1;
	pDoc->m_pUI->m_origView->refresh();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the edge_image menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_user_edge_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();
	pDoc->m_pUI->m_origView->imageIndex = 3;
	pDoc->m_pUI->m_origView->refresh();
}

//------------------------------------------------------------
// Called by the UI when the another_image menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_another_image(Fl_Menu_* o, void* v) 
{	
	ImpressionistDoc* pDoc=whoami(o)->getDocument();
	pDoc->m_pUI->m_origView->imageIndex = 2;
	pDoc->m_pUI->m_origView->refresh();
}

//------------------------------------------------------------
// Called by the UI when the swap_views menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_swap_views(Fl_Menu_* o, void* v){
	ImpressionistDoc* pDoc=whoami(o)->getDocument();
	pDoc->swapViews();
}

//------------------------------------------------------------
// Called by the UI when the faster menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_faster(Fl_Menu_* o, void* v) 
{
	fl_message("Faster todo");
}

//------------------------------------------------------------
// Called by the UI when the safer menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_safer(Fl_Menu_* o, void* v) 
{	
	fl_message("Safer todo");
}

//------------------------------------------------------------
// Called by the UI when the undo menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v) 
{	
	ImpressionistDoc* pDoc=whoami(o)->getDocument();
	pDoc->undo();
}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;
	pDoc->setBrushType(type);
}

//-------------------------------------------------------------
// Sets the direction of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_directionChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;
	pDoc->setBrushDirection(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the line width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the line angle slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the opacity to use from the value of the size
// slider
// Called by the UI when the line angle slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_opacitySlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dOpacity=double( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the spacing to use from the value of the size
// slider
// Called by the UI when the spacing slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_spacing_slide(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSpacing=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the threshold to use from the value of the size
// slider
// Called by the UI when the threshold slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_threshold_slide(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nThreshold=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the dimmed value to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_dimmed_value_slide(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dDimmedValue=double( ((Fl_Slider *)o)->value() ) ;
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->changeDimmedValue();
}

void ImpressionistUI::cb_edge_clipping_lbutton(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	if (pDoc->m_ucUserEdgeBitmap)
	{
		if (pUI->m_bEdgeClipping==TRUE)
		{
			pUI->m_bEdgeClipping=FALSE;
			pUI->m_EdgeClippingButton->value(0);
		} 
		else {
			pUI->m_bEdgeClipping=TRUE;
			pUI->m_EdgeClippingButton->value(1);
		}
	}
	else pUI->m_EdgeClippingButton->value(0);
	
}

void ImpressionistUI::cb_another_gradient_lbutton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	if (pDoc->m_ucAnotherBitmap)
	{	

		if (pUI->m_bAnotherGradient==TRUE) 
		{
			pUI->m_bAnotherGradient=FALSE;
			pUI->m_AnotherGradientButton->value(0);
		}
		else 
		{
			pUI->m_bAnotherGradient=TRUE;
			pUI->m_AnotherGradientButton->value(1);
		}
	}
	else pUI->m_AnotherGradientButton->value(0);
	
}

void ImpressionistUI::cb_size_random_lbutton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

	if (pUI->m_bSizeRandom==TRUE) pUI->m_bSizeRandom=FALSE;
	else pUI->m_bSizeRandom=TRUE;
}

//------------------------------------------------------------
// Auto painting
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_auto_paint_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->m_pUI->m_paintView->triggerAutoPaint();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_threshold_change_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->changeThreshold();
	pDoc->m_pUI->m_origView->imageIndex = 1;
	pDoc->m_pUI->m_origView->refresh();
}

void ImpressionistUI::cb_filter_size_submit(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)o->user_data();
	int width = atoi(pUI->m_filterWidthInput->value());
	int height = atoi(pUI->m_filterHeightInput->value());
	width = width > 1 ? width : 1;
	height = height > 1 ? height : 1;
	pUI->showKernel(width, height);
	pUI->m_filterSizeDialog->hide();
}

void ImpressionistUI::showKernel(int width, int height)
{
	int dialogWidth = width * 30 + (width + 1) * 10 + 20;
	int dialogHeight = height * 20 + (height + 1) * 10 + 80;
	m_filterInputDialog = new Fl_Window(dialogWidth, dialogHeight, "Filter Kernel Input");
		m_filterInputDialog->user_data((void*)(this));
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				Fl_Float_Input *input = new Fl_Float_Input((i +1) * 10 + i * 30, (j + 1) * 10 + j * 20, 30, 20, "");
				input->value("1.0");
				m_FilterInputs.push_back(input);
			}
		}
		

		m_filterInputApplyButton = new Fl_Button(dialogWidth / 2 - 40, dialogHeight - 30, 80, 20, "Apply");
		m_filterInputApplyButton->user_data((void*)(this));
		m_filterInputApplyButton->callback(cb_filter_input_apply);
		m_filterInputNormalButton = new Fl_Light_Button (dialogWidth / 2 - 40, dialogHeight - 60, 80, 20, "Normalize");
		m_filterInputNormalButton->user_data((void*)(this));
		m_filterInputNormalButton->callback(cb_filter_input_normalize_lbutton);
	m_filterInputDialog->end();

	m_filterInputDialog->show();
	m_nKernelHeight = height;
	m_nKernelWidth = width;
}

void ImpressionistUI::cb_filter_input_normalize_lbutton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

	if (pUI->m_bNormalize==TRUE) pUI->m_bNormalize=FALSE;
	else pUI->m_bNormalize=TRUE;
}

void ImpressionistUI::cb_filter_input_apply(Fl_Widget* o, void* v){
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->applyUserFilter();
}


void ImpressionistUI::cb_paintlyStyleChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	int type = (int)v;
	if (type != STYLE_CUSTOMIZE)
	{
		pUI->m_paintlyStrokeChoice->deactivate();
		pUI->m_paintlyGridSlider->deactivate();
		pUI->m_paintlyThresholdSlider->deactivate();
		pUI->m_paintlyMaxBrushSizeSlider->deactivate();
		pUI->m_paintlyMinBrushSizeSlider->deactivate();
		pUI->m_paintlyMaxStrokeLengthSlider->deactivate();
		pUI->m_paintlyMinStrokeLengthSlider->deactivate();
		pUI->m_paintlyCurvatureSlider->deactivate();
		pUI->m_paintlyBlurSlider->deactivate();
		pUI->m_paintlyAlphaSlider->deactivate();
		pUI->m_paintlyLayersSlider->deactivate();
		pUI->m_paintlyStrokeChoice->value(1);
		pDoc->setPaintlyStrokeType(STROKE_CURVEDBRUSH);
		if (type == STYLE_IMPRESSIONIST)
		{	
			
			pUI->m_nPaintlyThreshold = 100;
			pUI->m_nPaintlyMaxBrush = 8;
			pUI->m_nPaintlyMinBrush = 2;
			pUI->m_dPaintlyGrid = 1.0;
			pUI->m_dPaintlyCurvature = 1.0;
			pUI->m_dPaintlyBlur = 0.8;
			pUI->m_nPaintlyMaxStroke = 16;
			pUI->m_nPaintlyMinStroke = 4;
			pUI->m_dOpacity = 1;
			pUI->m_nPaintlyLayers = 3;
		}
		else if (type == STYLE_EXPRESSIONIST)
		{
			pUI->m_paintlyStrokeChoice->value(0);
			pUI->m_nPaintlyThreshold = 50;
			pUI->m_nPaintlyMaxBrush = 8;
			pUI->m_nPaintlyMinBrush = 2;
			pUI->m_dPaintlyGrid = 1.0;
			pUI->m_dPaintlyCurvature = 0.25;
			pUI->m_dPaintlyBlur = 0.5;
			pUI->m_nPaintlyMaxStroke = 16;
			pUI->m_nPaintlyMinStroke = 10;
			pUI->m_dOpacity = 0.7;
			pUI->m_nPaintlyLayers = 3;
		}
	}
	else
	{	
		pUI->m_paintlyStrokeChoice->activate();
		pUI->m_paintlyGridSlider->activate();
		pUI->m_paintlyThresholdSlider->activate();
		pUI->m_paintlyMaxBrushSizeSlider->activate();
		pUI->m_paintlyMinBrushSizeSlider->activate();
		pUI->m_paintlyMaxStrokeLengthSlider->activate();
		pUI->m_paintlyMinStrokeLengthSlider->activate();
		pUI->m_paintlyCurvatureSlider->activate();
		pUI->m_paintlyBlurSlider->activate();
		pUI->m_paintlyAlphaSlider->activate();
		pUI->m_paintlyLayersSlider->activate();
	}
}

void ImpressionistUI::cb_paintlyStrokeChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	int type = (int)v;
	switch (type)
	{
	case STROKE_CIRCLEBRUSH:
		pDoc->setPaintlyStrokeType(type);
		pDoc->setBrushType(BRUSH_CIRCLES); 
		break;
	case STROKE_CURVEDBRUSH:
		pDoc->setPaintlyStrokeType(type);
		break;
	}
}

void ImpressionistUI::cb_paintly_apply_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->m_pUI->m_paintView->triggerPaintly();
}

void ImpressionistUI::cb_paintlyThresholdSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nPaintlyThreshold=int( ((Fl_Slider *)o)->value() ) ;
	printf("%d\n", ((ImpressionistUI*)(o->user_data()))->m_nPaintlyThreshold );
}


void ImpressionistUI::cb_paintlyMaxBrushSizeSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nPaintlyMaxBrush=int( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyMinBrushSizeSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nPaintlyMinBrush=int( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyGridSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyGrid=double( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyCurvatureSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyCurvature=double( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyBlurSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyBlur=double( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyMaxStrokeLengthSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nPaintlyMaxStroke=int( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyMinStrokeLengthSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nPaintlyMinStroke=int( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyAlphaSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyAlpha=double( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyLayersSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nPaintlyLayers=int( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyJrSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyJr=double( ((Fl_Slider *)o)->value() ) ;
	m_nR = double( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyJgSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyJg=double( ((Fl_Slider *)o)->value() ) ;
	m_nG = double( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyJbSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyJb=double( ((Fl_Slider *)o)->value() ) ;
	m_nB = double( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyJhSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyJh=double( ((Fl_Slider *)o)->value() ) ;
}
void ImpressionistUI::cb_paintlyJsSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyJs=double( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_paintlyJvSlider(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_dPaintlyJv=double( ((Fl_Slider *)o)->value() ) ;
}
//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//------------------------------------------------
// Return the line width size
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}

//------------------------------------------------
// Return the line angle size
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;
}

//------------------------------------------------
// Return the opacity
//------------------------------------------------
double ImpressionistUI::getOpacity()
{
	return m_dOpacity;
}

//------------------------------------------------
// Return the dimmed
//------------------------------------------------
double ImpressionistUI::getDimmedValue()
{
	return m_dDimmedValue;
}

//------------------------------------------------
// Return the R
//------------------------------------------------
double ImpressionistUI::getR()
{
	return m_nR;
}

//------------------------------------------------
// Return the G
//------------------------------------------------
double ImpressionistUI::getG()
{
	return m_nG;
}

//------------------------------------------------
// Return the B
//------------------------------------------------
double ImpressionistUI::getB()
{
	return m_nB;
}

//------------------------------------------------
// Return the threshold
//------------------------------------------------
int ImpressionistUI::getThreshold()
{
	return m_nThreshold;
}

//------------------------------------------------
// Return the threshold
//------------------------------------------------
int ImpressionistUI::getSpacing()
{
	return m_nSpacing;
}

//------------------------------------------------
// Return the sizeRandom
//------------------------------------------------
bool ImpressionistUI::getSizeRandom()
{
	return m_bSizeRandom;
}

//------------------------------------------------
// Return the another gradient
//------------------------------------------------
bool ImpressionistUI::getAnotherGradient()
{
	return m_bAnotherGradient;
}

bool ImpressionistUI::getNormalize()
{
	return m_bNormalize;
}

//------------------------------------------------
// Return the edge clipping
//------------------------------------------------
bool ImpressionistUI::getEdgeClipping()
{
	return m_bEdgeClipping;
}

int ImpressionistUI::getKernelWidth()
{
	return m_nKernelWidth;
}

int ImpressionistUI::getKernelHeight(){
	return m_nKernelHeight;
}
//------------------------------------------------
// Reset RGB default 1 1 1
//------------------------------------------------
void ImpressionistUI::resetRGB(double r, double g, double b)
{
	m_nR = r;
	m_nG = g;
	m_nB = b;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

//-------------------------------------------------
// Set the line width size
//-------------------------------------------------
void ImpressionistUI::setLineWidth( int width )
{
	m_nLineWidth=width;

	if (width<=40) 
		m_BrushLineWidthSlider->value(m_nLineWidth);
}

//-------------------------------------------------
// Set the line angle size
//-------------------------------------------------
void ImpressionistUI::setLineAngle( int angle )
{
	m_nLineAngle=angle;

	if (angle<=359) 
		m_BrushLineAngleSlider->value(m_nLineAngle);
}

//-------------------------------------------------
// Set the opacity
//-------------------------------------------------
void ImpressionistUI::setOpacity( double opacity )
{
	m_dOpacity=opacity;

	if (opacity<=40) 
		m_OpacitySlider->value(m_dOpacity);
}

// Control value of paintly dialog
int ImpressionistUI:: getPaintlyThreshold()
{
	return m_nPaintlyThreshold;
}
int ImpressionistUI:: getPaintlyMaxBrush()
{
	return m_nPaintlyMaxBrush;
}
int ImpressionistUI:: getPaintlyMinBrush()
{
	return m_nPaintlyMinBrush;
}
int ImpressionistUI:: getPaintlyMaxStroke()
{
	return m_nPaintlyMaxStroke;
}
int ImpressionistUI:: getPaintlyMinStroke()
{
	return m_nPaintlyMinStroke;
}
int ImpressionistUI:: getPaintlyLayers()
{
	return m_nPaintlyLayers;
}
double ImpressionistUI:: getPaintlyGrid()
{
	return m_dPaintlyGrid;
}
double ImpressionistUI:: getPaintlyCurvature()
{
	return m_dPaintlyCurvature;
}
double ImpressionistUI:: getPaintlyBlur()
{
	return m_dPaintlyBlur;
}
double ImpressionistUI:: getPaintlyAlpha()
{
	return m_dPaintlyAlpha;
}
double ImpressionistUI:: getPaintlyJr()
{
	return m_dPaintlyJr;
}
double ImpressionistUI:: getPaintlyJg()
{
	return m_dPaintlyJg;
}
double ImpressionistUI:: getPaintlyJb()
{
	return m_dPaintlyJb;
}
double ImpressionistUI:: getPaintlyJh()
{
	return m_dPaintlyJh;
}
double ImpressionistUI:: getPaintlyJs()
{
	return m_dPaintlyJs;
}
double ImpressionistUI:: getPaintlyJv()
{
	return m_dPaintlyJv;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		{ "&Colors", FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_colors },
		{ "&Filters", FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_filter},
		{ "&Paintly", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_paintly, 0, FL_MENU_DIVIDER},
		{ "&Dissolve Image", FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_load_dissolve_image},
		{ "&Load Edge Image", FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_load_edge_image},
		{ "&Load Another Image", FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_another_image},
		{ "&Load Mural Image", FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_load_mural_image, 0, FL_MENU_DIVIDER},
		{ "Load Alpha Brush", FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_alpha_brush, 0, FL_MENU_DIVIDER },
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Display",		0, 0, 0, FL_SUBMENU },
		{ "&Original Image",	FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_original_image },
		{ "&Edge Image",	FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_edge_image },
		{ "&User Edge Image",	FL_ALT + 'u', (Fl_Callback *)ImpressionistUI::cb_user_edge_image },
		{ "&Another Image",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_another_image }, 
		{ "&Swap views", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_swap_views},
		{ "&Dimmed view", FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_dimmed_view},
		{ 0 },

	{ "&Options",		0, 0, 0, FL_SUBMENU },
		{ "&Faster",	FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_faster },
		{ "&Sager",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_safer },
		{ "&Undo", FL_ALT + 'u', (Fl_Callback *)ImpressionistUI::cb_undo },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Blur",				FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_BLUR},
  {"Sharpen",			FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SHARPEN},
  {"Warp",			FL_ALT+'w', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_WARP},
  { "Alpha Mapped", 	FL_ALT+'a', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_ALPHA_MAPPED, FL_MENU_INACTIVE},
  {0}
};

// Direction choice menu definition
Fl_Menu_Item ImpressionistUI::brushDirectionMenu[NUM_BRUSH_DIRECTION+1] = {
  {"SLider/Right Mouse",			FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_SLIDER},
  {"Gradient",				FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_GRADIENT},
  {"Brush Direction",			FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_CURSOR},
  {0}
};

// Paintly Dialog
Fl_Menu_Item ImpressionistUI::paintlyStyleMenu[NUM_PAINTLYSTYLE + 1] = {
		{ "Impressionist", FL_ALT + 'i', (Fl_Callback *)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_IMPRESSIONIST},
		{ "Expressionist", FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_EXPRESSIONIST},
		//{ "Colorist Wash", FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_COLORISTWASH},
		//{ "Pointillist", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_POINTILLIST},
		{ "Customized", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_CUSTOMIZE},
		{0}
};

Fl_Menu_Item ImpressionistUI::paintlyStrokeMenu[NUM_PAINTLYSTROKE + 1] = {
		{"Circle Brush", FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_paintlyStrokeChoice, (void*)STROKE_CIRCLEBRUSH},
		{"Curved Brush", FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_paintlyStrokeChoice, (void*)STROKE_CURVEDBRUSH},
		{0}
};
double ImpressionistUI:: m_nR(1.0);
double ImpressionistUI:: m_nG(1.0);
double ImpressionistUI:: m_nB(1.0);

//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_dOpacity = 1.0;
	m_dDimmedValue = 0.0;
	m_nSpacing = 4;
	m_nThreshold = 200;
	m_bEdgeClipping = FALSE;
	m_bAnotherGradient = FALSE;
	m_bSizeRandom = FALSE;
	m_bNormalize = FALSE;
	m_nPaintlyThreshold = 100;
	m_nPaintlyMaxBrush = 8;
	m_nPaintlyMinBrush = 2;
	m_nPaintlyMaxStroke = 16;
	m_nPaintlyMinStroke = 4;
	m_nPaintlyLayers = 3;

	m_dPaintlyGrid = 1.0;
	m_dPaintlyCurvature = 1.0;
	m_dPaintlyBlur = 0.8;
	m_dPaintlyAlpha = 1;
	m_dPaintlyJr = 1.0;
	m_dPaintlyJg = 1.0;
	m_dPaintlyJb = 1.0;
	m_dPaintlyJh = 1.0;
	m_dPaintlyJs = 1.0;
	m_dPaintlyJv = 1.0;

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add a brush direction choice to the dialog
		m_BrushDirectionChoice = new Fl_Choice(60,50,150,25,"&Stroke Direction");
		m_BrushDirectionChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushDirectionChoice->menu(brushDirectionMenu);
		m_BrushDirectionChoice->callback(cb_directionChoice);
		m_BrushDirectionChoice->deactivate();

		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 90, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add brush line width slider to the dialog 
		m_BrushLineWidthSlider = new Fl_Value_Slider(10, 120, 300, 20, "Line Width");
		m_BrushLineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushLineWidthSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushLineWidthSlider->labelfont(FL_COURIER);
        m_BrushLineWidthSlider->labelsize(12);
		m_BrushLineWidthSlider->minimum(1);
		m_BrushLineWidthSlider->maximum(40);
		m_BrushLineWidthSlider->step(1);
		m_BrushLineWidthSlider->value(m_nLineWidth);
		m_BrushLineWidthSlider->align(FL_ALIGN_RIGHT);
		m_BrushLineWidthSlider->callback(cb_lineWidthSlides);
		m_BrushLineWidthSlider->deactivate();

		// Add brush line angle slider to the dialog 
		m_BrushLineAngleSlider = new Fl_Value_Slider(10, 150, 300, 20, "Line Angle");
		m_BrushLineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushLineAngleSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushLineAngleSlider->labelfont(FL_COURIER);
        m_BrushLineAngleSlider->labelsize(12);
		m_BrushLineAngleSlider->minimum(0);
		m_BrushLineAngleSlider->maximum(359);
		m_BrushLineAngleSlider->step(1);
		m_BrushLineAngleSlider->value(m_nLineAngle);
		m_BrushLineAngleSlider->align(FL_ALIGN_RIGHT);
		m_BrushLineAngleSlider->callback(cb_lineAngleSlides);
		m_BrushLineAngleSlider->deactivate();

		// Add opacity slider to the dialog 
		m_OpacitySlider = new Fl_Value_Slider(10, 180, 300, 20, "Alpha");
		m_OpacitySlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_OpacitySlider->type(FL_HOR_NICE_SLIDER);
        m_OpacitySlider->labelfont(FL_COURIER);
        m_OpacitySlider->labelsize(12);
		m_OpacitySlider->minimum(0.00);
		m_OpacitySlider->maximum(1.00);
		m_OpacitySlider->step(0.01);
		m_OpacitySlider->value(m_dOpacity);
		m_OpacitySlider->align(FL_ALIGN_RIGHT);
		m_OpacitySlider->callback(cb_opacitySlides);

		// Add Edge Clipping light button
		m_EdgeClippingButton = new Fl_Light_Button(10,210,150,25,"&Edge_Clipping");
		m_EdgeClippingButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_EdgeClippingButton->callback(cb_edge_clipping_lbutton);

		// Add Edge Clipping light button
		m_AnotherGradientButton = new Fl_Light_Button(240,210,150,25,"&Another Gradient");
		m_AnotherGradientButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_AnotherGradientButton->callback(cb_another_gradient_lbutton);
		m_AnotherGradientButton->deactivate();

		// Add spacing slider to the dialog 
		m_SpacingSlider = new Fl_Value_Slider(10, 240, 120, 20, "&Spacing");
		m_SpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_SpacingSlider->type(FL_HOR_NICE_SLIDER);
        m_SpacingSlider->labelfont(FL_COURIER);
        m_SpacingSlider->labelsize(12);
		m_SpacingSlider->minimum(1);
		m_SpacingSlider->maximum(16);
		m_SpacingSlider->step(1);
		m_SpacingSlider->value(m_nSpacing);
		m_SpacingSlider->align(FL_ALIGN_RIGHT);
		m_SpacingSlider->callback(cb_spacing_slide);

		// Add Size Random light button
		m_SizeRandomButton = new Fl_Light_Button(210,240,100,25,"&Size Rand");
		m_SizeRandomButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_SizeRandomButton->callback(cb_size_random_lbutton);

		m_AutoPaintButton = new Fl_Button(320,240,70,25,"&Paint");
		m_AutoPaintButton->user_data((void*)(this));
		m_AutoPaintButton->callback(cb_auto_paint_button);

		// Add spacing slider to the dialog 
		m_ThresholdSlider = new Fl_Value_Slider(10, 270, 200, 20, "&Threshold");
		m_ThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_ThresholdSlider->type(FL_HOR_NICE_SLIDER);
        m_ThresholdSlider->labelfont(FL_COURIER);
        m_ThresholdSlider->labelsize(12);
		m_ThresholdSlider->minimum(0);
		m_ThresholdSlider->maximum(500);
		m_ThresholdSlider->step(1);
		m_ThresholdSlider->value(m_nThreshold);
		m_ThresholdSlider->align(FL_ALIGN_RIGHT);
		m_ThresholdSlider->callback(cb_threshold_slide);

		m_ThresholdChangeButton = new Fl_Button(320,270,70,25,"&Set");
		m_ThresholdChangeButton->user_data((void*)(this));
		m_ThresholdChangeButton->callback(cb_threshold_change_button);


    m_brushDialog->end();	


    m_filterSizeDialog = new Fl_Window(250, 250, "Filter Size");

		m_filterWidthInput = new Fl_Int_Input(40, 50, 60, 20, "Width");
			m_filterWidthInput->labelfont(FL_COURIER);
			m_filterWidthInput->labelsize(12);
			m_filterWidthInput->value("1");
		m_filterHeightInput = new Fl_Int_Input(180, 50, 60, 20, "Height");
			m_filterHeightInput->labelfont(FL_COURIER);
			m_filterHeightInput->labelsize(12);
			m_filterHeightInput->value("1");
		m_filterSizeSubmitButton = new Fl_Button(80, 150, 80, 20, "&OK");
			m_filterSizeSubmitButton->user_data((void*)(this));
			m_filterSizeSubmitButton->callback(cb_filter_size_submit);

	m_filterSizeDialog->end();


	m_dimmedDialog = new Fl_Window(300,100, "Dimmed Value");

		// / Add dimmed value slider to the dialog 
		m_DimmedValueSlider = new Fl_Value_Slider(10, 20, 150, 20, "&Dimmed value");
		m_DimmedValueSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_DimmedValueSlider->type(FL_HOR_NICE_SLIDER);
        m_DimmedValueSlider->labelfont(FL_COURIER);
        m_DimmedValueSlider->labelsize(12);
		m_DimmedValueSlider->minimum(0);
		m_DimmedValueSlider->maximum(1);
		m_DimmedValueSlider->step(0.01);
		m_DimmedValueSlider->value(m_dDimmedValue);
		m_DimmedValueSlider->align(FL_ALIGN_RIGHT);
		m_DimmedValueSlider->callback(cb_dimmed_value_slide);

	m_dimmedDialog->end();
	// m_dimmedDialog->callback(cb_restore_painting);

	m_paintlyDialog = new Fl_Window(500, 400, "Paintly");
		m_PaintlyStyleChoice = new Fl_Choice(50, 15, 140, 25, "&Style");
		m_PaintlyStyleChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_PaintlyStyleChoice->menu(paintlyStyleMenu);
		m_PaintlyStyleChoice->callback(cb_paintlyStyleChoice);

		m_paintlyStrokeChoice = new Fl_Choice(250, 15, 110, 25, "&Stroke");
		m_paintlyStrokeChoice->user_data((void*)(this));
		m_paintlyStrokeChoice->menu(paintlyStrokeMenu);
		m_paintlyStrokeChoice->callback(cb_paintlyStrokeChoice);
		m_paintlyStrokeChoice->value(1);
		m_paintlyStrokeChoice->deactivate();

		m_paintlyApplyButton = new Fl_Button(400, 15, 60, 25, "&Paint");
		m_paintlyApplyButton->user_data((void*)(this));
		m_paintlyApplyButton->callback(cb_paintly_apply_button);

		m_paintlyThresholdSlider = new Fl_Value_Slider(15, 60, 200, 20, "Threshold");
		m_paintlyThresholdSlider->user_data((void*)(this));
		m_paintlyThresholdSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyThresholdSlider->labelfont(FL_COURIER);
		m_paintlyThresholdSlider->labelsize(12);
		m_paintlyThresholdSlider->minimum(0);
		m_paintlyThresholdSlider->maximum(250);
		m_paintlyThresholdSlider->step(1);
		m_paintlyThresholdSlider->value(m_nPaintlyThreshold);
		m_paintlyThresholdSlider->align(FL_ALIGN_RIGHT);
		m_paintlyThresholdSlider->callback(cb_paintlyThresholdSlider);
		m_paintlyThresholdSlider->deactivate();

		m_paintlyMaxBrushSizeSlider = new Fl_Value_Slider(15, 90, 200, 20, "Max Brush");
		m_paintlyMaxBrushSizeSlider->user_data((void*)(this));
		m_paintlyMaxBrushSizeSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyMaxBrushSizeSlider->labelfont(FL_COURIER);
		m_paintlyMaxBrushSizeSlider->labelsize(12);
		m_paintlyMaxBrushSizeSlider->minimum(1);
		m_paintlyMaxBrushSizeSlider->maximum(15);
		m_paintlyMaxBrushSizeSlider->step(1);
		m_paintlyMaxBrushSizeSlider->value(m_nPaintlyMaxBrush);
		m_paintlyMaxBrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_paintlyMaxBrushSizeSlider->callback(cb_paintlyMaxBrushSizeSlider);
		m_paintlyMaxBrushSizeSlider->deactivate();

		m_paintlyMinBrushSizeSlider = new Fl_Value_Slider(15, 120, 200, 20, "Min Brush");
		m_paintlyMinBrushSizeSlider->user_data((void*)(this));
		m_paintlyMinBrushSizeSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyMinBrushSizeSlider->labelfont(FL_COURIER);
		m_paintlyMinBrushSizeSlider->labelsize(12);
		m_paintlyMinBrushSizeSlider->minimum(1);
		m_paintlyMinBrushSizeSlider->maximum(15);
		m_paintlyMinBrushSizeSlider->step(1);
		m_paintlyMinBrushSizeSlider->value(m_nPaintlyMinBrush);
		m_paintlyMinBrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_paintlyMinBrushSizeSlider->callback(cb_paintlyMinBrushSizeSlider);
		m_paintlyMinBrushSizeSlider->deactivate();

		m_paintlyGridSlider = new Fl_Value_Slider(15, 150, 200, 20, "Grid Size");
		m_paintlyGridSlider->user_data((void*)(this));
		m_paintlyGridSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyGridSlider->labelfont(FL_COURIER);
		m_paintlyGridSlider->labelsize(12);
		m_paintlyGridSlider->minimum(0);
		m_paintlyGridSlider->maximum(1);
		m_paintlyGridSlider->step(0.01);
		m_paintlyGridSlider->value(m_dPaintlyGrid);
		m_paintlyGridSlider->align(FL_ALIGN_RIGHT);
		m_paintlyGridSlider->callback(cb_paintlyGridSlider);
		m_paintlyGridSlider->deactivate();

		m_paintlyCurvatureSlider = new Fl_Value_Slider(15, 180, 200, 20, "Curvature");
		m_paintlyCurvatureSlider->user_data((void*)(this));
		m_paintlyCurvatureSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyCurvatureSlider->labelfont(FL_COURIER);
		m_paintlyCurvatureSlider->labelsize(12);
		m_paintlyCurvatureSlider->minimum(0);
		m_paintlyCurvatureSlider->maximum(1);
		m_paintlyCurvatureSlider->step(0.01);
		m_paintlyCurvatureSlider->value(m_dPaintlyCurvature);
		m_paintlyCurvatureSlider->align(FL_ALIGN_RIGHT);
		m_paintlyCurvatureSlider->callback(cb_paintlyCurvatureSlider);
		m_paintlyCurvatureSlider->deactivate();

		m_paintlyBlurSlider = new Fl_Value_Slider(15, 210, 200, 20, "Blur");
		m_paintlyBlurSlider->user_data((void*)(this));
		m_paintlyBlurSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyBlurSlider->labelfont(FL_COURIER);
		m_paintlyBlurSlider->labelsize(12);
		m_paintlyBlurSlider->minimum(0);
		m_paintlyBlurSlider->maximum(1);
		m_paintlyBlurSlider->step(0.01);
		m_paintlyBlurSlider->value(m_dPaintlyBlur);
		m_paintlyBlurSlider->align(FL_ALIGN_RIGHT);
		m_paintlyBlurSlider->callback(cb_paintlyBlurSlider);
		m_paintlyBlurSlider->deactivate();

		m_paintlyMaxStrokeLengthSlider = new Fl_Value_Slider(15, 240, 200, 20, "Max Stroke");
		m_paintlyMaxStrokeLengthSlider->user_data((void*)(this));
		m_paintlyMaxStrokeLengthSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyMaxStrokeLengthSlider->labelfont(FL_COURIER);
		m_paintlyMaxStrokeLengthSlider->labelsize(12);
		m_paintlyMaxStrokeLengthSlider->minimum(0);
		m_paintlyMaxStrokeLengthSlider->maximum(30);
		m_paintlyMaxStrokeLengthSlider->step(1);
		m_paintlyMaxStrokeLengthSlider->value(m_nPaintlyMaxStroke);
		m_paintlyMaxStrokeLengthSlider->align(FL_ALIGN_RIGHT);
		m_paintlyMaxStrokeLengthSlider->callback(cb_paintlyMaxStrokeLengthSlider);
		m_paintlyMaxStrokeLengthSlider->deactivate();
	
		m_paintlyMinStrokeLengthSlider = new Fl_Value_Slider(15, 270, 200, 20, "Min Stroke");
		m_paintlyMinStrokeLengthSlider->user_data((void*)(this));
		m_paintlyMinStrokeLengthSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyMinStrokeLengthSlider->labelfont(FL_COURIER);
		m_paintlyMinStrokeLengthSlider->labelsize(12);
		m_paintlyMinStrokeLengthSlider->minimum(0);
		m_paintlyMinStrokeLengthSlider->maximum(30);
		m_paintlyMinStrokeLengthSlider->step(1);
		m_paintlyMinStrokeLengthSlider->value(m_nPaintlyMinStroke);
		m_paintlyMinStrokeLengthSlider->align(FL_ALIGN_RIGHT);
		m_paintlyMinStrokeLengthSlider->callback(cb_paintlyMinStrokeLengthSlider);
		m_paintlyMinStrokeLengthSlider->deactivate();

		m_paintlyAlphaSlider = new Fl_Value_Slider(15, 300, 200, 20, "Alpha");
		m_paintlyAlphaSlider->user_data((void*)(this));
		m_paintlyAlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyAlphaSlider->labelfont(FL_COURIER);
		m_paintlyAlphaSlider->labelsize(12);
		m_paintlyAlphaSlider->minimum(0);
		m_paintlyAlphaSlider->maximum(1);
		m_paintlyAlphaSlider->step(0.01);
		m_paintlyAlphaSlider->value(m_dOpacity);
		m_paintlyAlphaSlider->align(FL_ALIGN_RIGHT);
		m_paintlyAlphaSlider->callback(cb_paintlyAlphaSlider);
		m_paintlyAlphaSlider->deactivate();

		m_paintlyLayersSlider = new Fl_Value_Slider(15, 330, 200, 20, "Layers");
		m_paintlyLayersSlider->user_data((void*)(this));
		m_paintlyLayersSlider->type(FL_HOR_NICE_SLIDER);
		m_paintlyLayersSlider->labelfont(FL_COURIER);
		m_paintlyLayersSlider->labelsize(12);
		m_paintlyLayersSlider->minimum(1);
		m_paintlyLayersSlider->maximum(5);
		m_paintlyLayersSlider->step(1);
		m_paintlyLayersSlider->value(m_nPaintlyLayers);
		m_paintlyLayersSlider->align(FL_ALIGN_RIGHT);
		m_paintlyLayersSlider->callback(cb_paintlyLayersSlider);
		m_paintlyLayersSlider->deactivate();

		m_paintlyJrSlider = new Fl_Value_Slider(330, 60, 25, 110, "Jr");
		m_paintlyJrSlider->user_data((void*)(this));
		m_paintlyJrSlider->type(FL_VERT_NICE_SLIDER);
		m_paintlyJrSlider->labelfont(FL_COURIER);
		m_paintlyJrSlider->labelsize(12);
		m_paintlyJrSlider->minimum(1);
		m_paintlyJrSlider->maximum(0);
		m_paintlyJrSlider->step(0.01);
		m_paintlyJrSlider->value(m_dPaintlyJr);
		m_paintlyJrSlider->align(FL_ALIGN_BOTTOM);
		m_paintlyJrSlider->callback(cb_paintlyJrSlider);

		m_paintlyJgSlider = new Fl_Value_Slider(375, 60, 25, 110, "Jg");
		m_paintlyJgSlider->user_data((void*)(this));
		m_paintlyJgSlider->type(FL_VERT_NICE_SLIDER);
		m_paintlyJgSlider->labelfont(FL_COURIER);
		m_paintlyJgSlider->labelsize(12);
		m_paintlyJgSlider->minimum(1);
		m_paintlyJgSlider->maximum(0);
		m_paintlyJgSlider->step(0.01);
		m_paintlyJgSlider->value(m_dPaintlyJg);
		m_paintlyJgSlider->align(FL_ALIGN_BOTTOM);
		m_paintlyJgSlider->callback(cb_paintlyJgSlider);

		m_paintlyJbSlider = new Fl_Value_Slider(420, 60, 25, 110, "Jb");
		m_paintlyJbSlider->user_data((void*)(this));
		m_paintlyJbSlider->type(FL_VERT_NICE_SLIDER);
		m_paintlyJbSlider->labelfont(FL_COURIER);
		m_paintlyJbSlider->labelsize(12);
		m_paintlyJbSlider->minimum(1);
		m_paintlyJbSlider->maximum(0);
		m_paintlyJbSlider->step(0.01);
		m_paintlyJbSlider->value(m_dPaintlyJb);
		m_paintlyJbSlider->align(FL_ALIGN_BOTTOM);
		m_paintlyJbSlider->callback(cb_paintlyJbSlider);

		m_paintlyJhSlider = new Fl_Value_Slider(330, 200, 25, 110, "Jh");
		m_paintlyJhSlider->user_data((void*)(this));
		m_paintlyJhSlider->type(FL_VERT_NICE_SLIDER);
		m_paintlyJhSlider->labelfont(FL_COURIER);
		m_paintlyJhSlider->labelsize(12);
		m_paintlyJhSlider->minimum(1);
		m_paintlyJhSlider->maximum(0);
		m_paintlyJhSlider->step(0.01);
		m_paintlyJhSlider->value(m_dPaintlyJh);
		m_paintlyJhSlider->align(FL_ALIGN_BOTTOM);
		m_paintlyJhSlider->callback(cb_paintlyJhSlider);

		m_paintlyJsSlider = new Fl_Value_Slider(375, 200, 25, 110, "Js");
		m_paintlyJsSlider->user_data((void*)(this));
		m_paintlyJsSlider->type(FL_VERT_NICE_SLIDER);
		m_paintlyJsSlider->labelfont(FL_COURIER);
		m_paintlyJsSlider->labelsize(12);
		m_paintlyJsSlider->minimum(1);
		m_paintlyJsSlider->maximum(0);
		m_paintlyJsSlider->step(0.01);
		m_paintlyJsSlider->value(m_dPaintlyJs);
		m_paintlyJsSlider->align(FL_ALIGN_BOTTOM);
		m_paintlyJsSlider->callback(cb_paintlyJsSlider);

		m_paintlyJvSlider = new Fl_Value_Slider(420, 200, 25, 110, "Jv");
		m_paintlyJvSlider->user_data((void*)(this));
		m_paintlyJvSlider->type(FL_VERT_NICE_SLIDER);
		m_paintlyJvSlider->labelfont(FL_COURIER);
		m_paintlyJvSlider->labelsize(12);
		m_paintlyJvSlider->minimum(1);
		m_paintlyJvSlider->maximum(0);
		m_paintlyJvSlider->step(0.01);
		m_paintlyJvSlider->value(m_dPaintlyJv);
		m_paintlyJvSlider->align(FL_ALIGN_BOTTOM);
		m_paintlyJvSlider->callback(cb_paintlyJvSlider);

	m_paintlyDialog->end();

}
