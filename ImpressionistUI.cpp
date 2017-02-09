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
	fl_message("Paintly todo");
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


//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

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

//------------------------------------------------
// Return the edge clipping
//------------------------------------------------
bool ImpressionistUI::getEdgeClipping()
{
	return m_bEdgeClipping;
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

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		{ "&Colors", FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_colors },
		{ "&Paintly", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_paintly, 0, FL_MENU_DIVIDER},
		{ "&Dissolve Image", FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_load_dissolve_image},
		{ "&Load Edge Image", FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_load_edge_image},
		{ "&Load Another Image", FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_another_image, 0, FL_MENU_DIVIDER},

		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Display",		0, 0, 0, FL_SUBMENU },
		{ "&Original Image",	FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_original_image },
		{ "&Edge Image",	FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_edge_image },
		{ "&User Edge Image",	FL_ALT + 'u', (Fl_Callback *)ImpressionistUI::cb_user_edge_image },
		{ "&Another Image",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_another_image }, 
		{ "&Swap views", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_swap_views},
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
  {0}
};

// Direction choice menu definition
Fl_Menu_Item ImpressionistUI::brushDirectionMenu[NUM_BRUSH_DIRECTION+1] = {
  {"SLider/Right Mouse",			FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_SLIDER},
  {"Gradient",				FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_GRADIENT},
  {"Brush Direction",			FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_directionChoice, (void *)DIRECTION_CURSOR},
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
	m_nSpacing = 4;
	m_nThreshold = 200;
	m_bEdgeClipping = FALSE;
	m_bAnotherGradient = FALSE;
	m_bSizeRandom = FALSE;

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

}
