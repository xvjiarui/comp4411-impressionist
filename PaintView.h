//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <vector>

class ImpressionistDoc;

class PaintView : public Fl_Gl_Window
{
public:
	PaintView(int x, int y, int w, int h, const char* l);
	void draw();
	int handle(int event);

	void refresh();
	
	void resizeWindow(int width, int height);

	void SaveCurrentContent();

	void RestoreContent();

	void autoPaint();

	void triggerAutoPaint();

	void paintly();

	void triggerPaintly();

	void paintlyBlur(unsigned char* source, unsigned char* reference, int brushSize);

	void paintlyDifferenceCalculate(unsigned char* canvas, unsigned char* reference, unsigned char* diff);

	void paintlyLayer(unsigned char* canvas, unsigned char* diff,  unsigned char* reference, double gridRate, int brushSize, int threshold);

	void PaintView::makeCurved(const Point& start, unsigned char* reference, int brushSize, unsigned char* canvas, std::vector<Point>& vP);

	ImpressionistDoc *m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nStartRow, 
			m_nEndRow,
			m_nStartCol, 
			m_nEndCol,
			m_nWindowWidth, 
			m_nWindowHeight;

};

#endif