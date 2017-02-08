// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include "Filter.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image
	int		dissolveImage(char *iname);			// called by the UI to dissolve image
	int		loadAnotherImage(char *iname);			// called by the UI to load another image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	void	setBrushDirection(int direction);			// called by the UI to set the brushDirection
	int		getSize();						// get the UI size
	double 	getOpacity();
	int 	getLineWidth();
	int 	getLineAngle();
	int 	getBrushType();
	int 	getDirectionType();
	void	setSize(int size);				// set the UI size
	void	setLineAngle(int angle);				// set the UI lineAngle
	char*	getImageName();					// get the current image name

	void 	setStartPoint(Point start);
	void 	setEndPoint(Point start);
	int 	rightMouseAngle();
	int 	rightMouseSize();
	void 	saveTemp();
	void 	undo();
	void 	swapViews();
	


// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucAnotherBitmap;
	unsigned char* 	m_ucDissolveBitmap;
	unsigned char*	m_ucEdgeBitmap;
	unsigned char*	m_ucPainting;
	unsigned char* 	m_ucPrePainting;
	int* 			m_nGradientxy;
	int* 			m_nGradientValue;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	// Size of the brush.
	int m_nSize;
	int m_nType;
	int m_nDirection;

	// Opacity
	double m_dOpacity;							

	ImpressionistUI*	m_pUI;

	// Right mouse control
	Point startPoint;
	Point endPoint;

	// filters
	Filter<int>* f_SobelX;
	Filter<int>* f_SobelY;
	Filter<double>* f_Gaussian;
	Filter<int>* f_Sharpen;


// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  
	// calculate gradient
	void calculateGradient(unsigned char* source, int* gradientxy, int* value );
	// Calculate edge image
	GLubyte* ImpressionistDoc::calculateEdgeMap(int threshold = 100);

	static GLubyte grayPixel(double r, double g, double b);
	static GLubyte grayPixel( GLubyte*  pixel);

private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
