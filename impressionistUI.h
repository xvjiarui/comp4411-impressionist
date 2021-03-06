//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Float_Input.H>
#include <vector>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

enum {
	STYLE_IMPRESSIONIST = 0,
	STYLE_EXPRESSIONIST,
	//STYLE_COLORISTWASH,
	//STYLE_POINTILLIST,
	STYLE_CUSTOMIZE,
	NUM_PAINTLYSTYLE
};

enum {
	STROKE_CIRCLEBRUSH = 0,
	STROKE_CURVEDBRUSH,
	NUM_PAINTLYSTROKE
};

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Window* 			m_filterSizeDialog;
	Fl_Window* 			m_filterInputDialog;
	Fl_Window*			m_dimmedDialog;
	Fl_Window* 			m_paintlyDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_BrushDirectionChoice;
	Fl_Choice*			m_PaintlyStyleChoice;
	Fl_Choice*			m_paintlyStrokeChoice;

	Fl_Int_Input*		m_filterWidthInput;
	Fl_Int_Input*		m_filterHeightInput;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_BrushLineWidthSlider;
	Fl_Slider*			m_BrushLineAngleSlider;
	Fl_Slider* 			m_OpacitySlider;
	Fl_Slider* 			m_SpacingSlider;
	Fl_Slider* 			m_ThresholdSlider;
	Fl_Slider*			m_DimmedValueSlider;
	Fl_Slider*			m_paintlyThresholdSlider;
	Fl_Slider*			m_paintlyMaxBrushSizeSlider;
	Fl_Slider*			m_paintlyMinBrushSizeSlider;
	Fl_Slider*			m_paintlyGridSlider;
	Fl_Slider*			m_paintlyCurvatureSlider;
	Fl_Slider*			m_paintlyBlurSlider;
	Fl_Slider*			m_paintlyMaxStrokeLengthSlider;
	Fl_Slider*			m_paintlyMinStrokeLengthSlider;
	Fl_Slider*			m_paintlyAlphaSlider;
	Fl_Slider*			m_paintlyLayersSlider;
	Fl_Slider*			m_paintlyJrSlider;
	Fl_Slider*			m_paintlyJgSlider;
	Fl_Slider*			m_paintlyJbSlider;
	Fl_Slider*			m_paintlyJhSlider;
	Fl_Slider*			m_paintlyJsSlider;
	Fl_Slider*			m_paintlyJvSlider;
	
	Fl_Button*          m_ClearCanvasButton;
	Fl_Button* 			m_AutoPaintButton;
	Fl_Button*			m_ThresholdChangeButton;
	Fl_Button*			m_filterSizeSubmitButton;
	Fl_Button*			m_filterInputApplyButton;
	Fl_Button* 			m_filterInputNormalButton;
	Fl_Button*			m_paintlyApplyButton;


	Fl_Light_Button* 	m_EdgeClippingButton;
	Fl_Light_Button*	m_AnotherGradientButton;
	Fl_Light_Button*	m_SizeRandomButton;
	Fl_Light_Button* 	m_DimmedViewButton;

	std::vector<Fl_Float_Input*> m_FilterInputs;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	int 				getLineWidth();
	int 				getLineAngle();
	int 				getThreshold();
	int 				getSpacing();
	bool 				getSizeRandom();
	bool 				getAnotherGradient();
	bool 				getEdgeClipping();
	bool 				getNormalize();
	double				getOpacity();
	double 				getDimmedValue();
	bool  				getDimmedChoice();
	double				getR();
	double				getG();
	double				getB();
	int 				getKernelWidth();
	int 				getKernelHeight();
	int 				getPaintlyThreshold();
	int 				getPaintlyMaxBrush();
	int 				getPaintlyMinBrush();
	int 				getPaintlyMaxStroke();
	int 				getPaintlyMinStroke();
	int 				getPaintlyLayers();
	double 				getPaintlyGrid();
	double 				getPaintlyCurvature();
	double				getPaintlyBlur();
	double				getPaintlyAlpha();
	double				getPaintlyJr();
	double				getPaintlyJg();
	double				getPaintlyJb();
	double				getPaintlyJh();
	double				getPaintlyJs();
	double				getPaintlyJv();
	void 				resetRGB(double r = 1, double g = 1, double b = 1);
	void				setSize(int size);
	void 				setLineWidth(int width);
	void 				setLineAngle(int angle);
	void 				setOpacity(double opacity);

	void 				showKernel(int weight, int height);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int 	m_nLineWidth;
	int 	m_nLineAngle;
	int 	m_nSpacing;
	int 	m_nThreshold;
	int 	m_nKernelWidth;
	int 	m_nKernelHeight;
	int		m_nPaintlyThreshold;
	int 	m_nPaintlyMaxBrush;
	int 	m_nPaintlyMinBrush;
	int		m_nPaintlyMaxStroke;
	int		m_nPaintlyMinStroke;
	int		m_nPaintlyLayers;
	double 	m_dPaintlyGrid;
	double 	m_dPaintlyCurvature;
	double 	m_dPaintlyBlur;
	double 	m_dPaintlyAlpha;
	double 	m_dPaintlyJr;
	double 	m_dPaintlyJg;
	double 	m_dPaintlyJb;
	double 	m_dPaintlyJh;
	double 	m_dPaintlyJs;
	double 	m_dPaintlyJv;
	double 	m_dOpacity;
	bool 	m_bEdgeClipping;
	bool	m_bAnotherGradient;
	bool	m_bSizeRandom;
	bool 	m_bNormalize;
	bool 	m_bDimmed;
	double m_dDimmedValue;
	static double	m_nR;
	static double	m_nG;
	static double	m_nB;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		brushDirectionMenu[NUM_BRUSH_DIRECTION+1];
	static Fl_Menu_Item		paintlyStyleMenu[NUM_PAINTLYSTYLE + 1];
	static Fl_Menu_Item		paintlyStrokeMenu[NUM_PAINTLYSTROKE + 1];


	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_filter(Fl_Menu_* o, void* v);
	static void cb_colors(Fl_Menu_* o, void* v);
	static void cb_paintly(Fl_Menu_* o, void* v);
	static void cb_load_dissolve_image(Fl_Menu_* o, void* v);
	static void cb_load_edge_image(Fl_Menu_* o, void* v);
	static void cb_user_edge_image(Fl_Menu_* o, void* v);
	static void cb_load_another_image(Fl_Menu_* o, void* v);
	static void cb_load_mural_image(Fl_Menu_* o, void* v) ;
	static void cb_load_alpha_brush(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void cb_original_image(Fl_Menu_* o, void* v);
	static void cb_edge_image(Fl_Menu_* o, void* v);
	static void cb_another_image(Fl_Menu_* o, void* v);
	static void cb_dimmed_view(Fl_Menu_* o, void* v);
	static void cb_swap_views(Fl_Menu_* o, void* v);
	static void cb_faster(Fl_Menu_* o, void* v);
	static void cb_safer(Fl_Menu_* o, void* v);
	static void cb_undo(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_directionChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_lineWidthSlides(Fl_Widget* o, void* v);
	static void cb_lineAngleSlides(Fl_Widget* o, void* v);
	static void cb_opacitySlides(Fl_Widget* o, void* v);
	static void cb_dimmed_value_slide(Fl_Widget* o, void* v);
	static void cb_dimmed_lbutton(Fl_Widget* o, void* v);
	static void cb_edge_clipping_lbutton(Fl_Widget* o, void* v);
	static void cb_another_gradient_lbutton(Fl_Widget* o, void* v);
	static void cb_size_random_lbutton(Fl_Widget* o, void* v);
	static void cb_auto_paint_button(Fl_Widget* o, void* v);
	static void cb_threshold_change_button(Fl_Widget* o, void* v);
	static void cb_spacing_slide(Fl_Widget* o, void* v);
	static void cb_threshold_slide(Fl_Widget * o, void* v);
	static void cb_filter_size_submit(Fl_Widget* o, void* v);
	static void cb_filter_input_apply(Fl_Widget* o, void* v);
	static void cb_filter_input_normalize_lbutton(Fl_Widget* o, void* v);
	static void cb_restore_painting(Fl_Widget* o, void* v);
	static void cb_paintly_window(Fl_Menu_* o, void* v);
	static void cb_paintlyStyleChoice(Fl_Widget* o, void* v);
	static void cb_paintlyStrokeChoice(Fl_Widget* o, void* v);
	static void cb_paintly_apply_button(Fl_Widget* o, void* v);
	static void cb_paintlyThresholdSlider(Fl_Widget* o, void* v);
	static void cb_paintlyMaxBrushSizeSlider(Fl_Widget* o, void* v);
	static void cb_paintlyMinBrushSizeSlider(Fl_Widget* o, void* v);
	static void cb_paintlyGridSlider(Fl_Widget* o, void* v);
	static void cb_paintlyCurvatureSlider(Fl_Widget* o, void* v);
	static void cb_paintlyBlurSlider(Fl_Widget* o, void* v);
	static void cb_paintlyMaxStrokeLengthSlider(Fl_Widget* o, void* v);
	static void cb_paintlyMinStrokeLengthSlider(Fl_Widget* o, void* v);
	static void cb_paintlyAlphaSlider(Fl_Widget* o, void* v);
	static void cb_paintlyLayersSlider(Fl_Widget* o, void* v);
	static void	cb_paintlyJrSlider(Fl_Widget* o, void* v);
	static void	cb_paintlyJgSlider(Fl_Widget* o, void* v);
	static void	cb_paintlyJbSlider(Fl_Widget* o, void* v);
	static void	cb_paintlyJhSlider(Fl_Widget* o, void* v);
	static void	cb_paintlyJsSlider(Fl_Widget* o, void* v);
	static void	cb_paintlyJvSlider(Fl_Widget* o, void* v);


};

#endif
