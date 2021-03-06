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
	int 	loadEdgeImage(char *iname);
	int 	loadMuralImage(char *iname);
	int 	loadAlphaMap(char *iname);
	void 	generateRGB();


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	void 	setPaintlyStrokeType(int type);
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
	void 	saveDim();
	void 	undo();
	void 	swapViews();

	int 	changeThreshold();

	void 	applyUserFilter();
	void 	changeDimmedValue();
	void 	swap(GLubyte* &a, GLubyte* &b);
	void 	generateBlur();


// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Alpha brush image info
	int 			m_nAlphaBrushWidth,
					m_nAlphaBrushHeight;
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucAnotherBitmap;
	unsigned char* 	m_ucDissolveBitmap;
	unsigned char*	m_ucEdgeBitmap;
	unsigned char* 	m_ucUserEdgeBitmap;
	unsigned char*	m_ucPainting;
	unsigned char* 	m_ucDisplayBitmap;
	unsigned char* 	m_ucPrePainting;
	unsigned char* 	m_ucMuralBitmap;
	unsigned char* 	m_ucAlphaBrushBitmap;
	unsigned char* 	m_ucBitmapR;
	unsigned char* 	m_ucBitmapG;
	unsigned char* 	m_ucBitmapB;
	int* 			m_nGradientxy;
	int* 			m_nGradientValue;
	int* 			m_nAnotherGradientxy;
	int* 			m_nAnotherGradientValue;

	// The current active brush.
	int 			m_nPaintlyStrokeType;
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
	Filter<double>* f_blur;


// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  

	// Get the color of the painting picture at the specified coord
	GLubyte* GetPaintingPixel( int x, int y );   
	// Get the color of the painting picture at the specified point	
	GLubyte* GetPaintingPixel( const Point p );  

	// Get the color of the painting picture at the specified coord double
	GLubyte* GetPaintingPixel( double x, double y );   
	// Get the color of the painting picture at the specified point	double
	GLubyte* GetPaintingPixel( const Pointd p );  

	// Get the color of the another picture at the specified coord
	GLubyte* GetAnotherPixel( int x, int y );   
	// Get the color of the another picture at the specified point	
	GLubyte* GetAnotherPixel( const Point p );  

	// Set the color of the another picture at the specified coord
	void SetPaintingPixel(int x, int y, const GLubyte* color) ; 
	// Set the color of the another picture at the specified point	
	void SetPaintingPixel( const Point p, const GLubyte* color);

	// calculate gradient
	void calculateGradient(unsigned char* source, int* gradientxy, int* value );
	// Calculate edge image
	GLubyte* ImpressionistDoc::calculateEdgeMap(int threshold = 100);

	static GLubyte grayPixel(double r, double g, double b);
	static GLubyte grayPixel( GLubyte*  pixel);

private:
	char			m_imageName[256];
	void 			setPaintingDone();
	bool 			firstTime;
	double 			lastDimmedValue;

};

extern void MessageBox(char *message);

#endif
