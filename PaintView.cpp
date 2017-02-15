//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//
#include <algorithm>
#include <vector>;
#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include "CircleBrush.h"


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6
#define AUTO_PAINT			7
#define PAINTLY 			8


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	if(!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{
		RestoreContent();

	}

	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{

		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		// printf("x:%d y:%d\n", coord.x,coord.y);
		// printf("x:%d y:%d\n", coord.x+m_nStartCol,m_nEndRow - coord.y);
		// printf("x:%d y:%d\n", coord.x,m_nWindowHeight - coord.y);
		// This is the event handler

		m_pDoc->saveTemp();
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
			// printf("s x:%d y:%d\n",source.x,source.y );
			// printf("t x:%d y:%d\n",target.x,target.y );
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			m_pDoc->m_pUI->m_origView->cursor(coord);
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );

			SaveCurrentContent();
			RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
			m_pDoc->setStartPoint(target);
			break;
		case RIGHT_MOUSE_DRAG:
			RestoreContent();
			m_pDoc->setEndPoint(target);
			glLineWidth(0.5);
			glEnable(GL_LINE_SMOOTH);
			glBegin( GL_LINE );
				glColor3f(1, 0, 0);
				glVertex2d(m_pDoc->startPoint.x , m_pDoc->startPoint.y);
				glVertex2d(m_pDoc->endPoint.x , m_pDoc->endPoint.y);
			glEnd();
			
			break;
		case RIGHT_MOUSE_UP:
			m_pDoc->setEndPoint(target);
			if (m_pDoc->getBrushType() == 1 || m_pDoc->getBrushType() == 4)
			{
				m_pDoc->setLineAngle(m_pDoc->rightMouseAngle());
				m_pDoc->setSize(m_pDoc->rightMouseSize());
			}
			RestoreContent();
			break;
		case AUTO_PAINT:
			autoPaint();
			SaveCurrentContent();
			RestoreContent();
			break;
		case PAINTLY:
			paintly();
			SaveCurrentContent();
			RestoreContent();
			break;
		default:
			printf("Unknown event!!\n");		
			break;
		}
		// m_pDoc->saveDim();
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		m_pDoc->m_pUI->m_origView->cursor(coord);
		break;
	default:
		return 0;
		break;

	}



	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::autoPaint(){
	if ( m_pDoc->m_ucPainting) 
	{
		int spacing = m_pDoc->m_pUI->getSpacing();
		// int temp_size = m_pDoc->getSize();
		int width = m_pDoc->m_nWidth;
		int height = m_pDoc->m_nHeight;
		// printf("w%d\n", width);
		// printf("h%d\n", height);
		// printf("spacing:%d\n", spacing);
		m_pDoc->saveTemp();
		if (m_pDoc->m_pUI->getSizeRandom())
		{
			std::vector<Point> order;
			int range = (int)((m_pDoc->m_pUI->getSize()));
			for (int j = 0; j < m_pDoc->m_nHeight; j += spacing)
			{
				for (int i = 0; i < m_pDoc->m_nWidth; i += spacing)
				{
					int randomPosx = rand() % range - range / 2;
					int randomPosy = rand() % range - range / 2;
					Point p(i+randomPosx, j+randomPosy);
					order.push_back(p);
				}
			}
			std::random_shuffle(order.begin(), order.end());

			for (int i = 0; i < order.size(); ++i)
			{
				m_pDoc->m_pCurrentBrush->BrushBegin(order[i],order[i]);
				m_pDoc->m_pCurrentBrush->BrushEnd(order[i],order[i]);
			}
		}
		else {
			for (int i = 0; i < width; i+=spacing)
			{
				for (int j = 0; j < height; j+=spacing)
				{	
					m_pDoc->m_pCurrentBrush->BrushBegin( Point(i,j), Point(i,j) );
					m_pDoc->m_pCurrentBrush->BrushEnd( Point(i,j), Point(i,j));
				}
			}
		}
		if (m_pDoc->m_pUI->getEdgeClipping())
		{
			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					if (m_pDoc->m_ucUserEdgeBitmap[3 * (j * width +i)])
					{
						m_pDoc->m_pCurrentBrush->BrushBegin( Point(i,j), Point(i,j) );
						m_pDoc->m_pCurrentBrush->BrushEnd( Point(i,j), Point(i,j));
					}
				}
			}
		}	
		// m_pDoc->setSize(temp_size);	
	}
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::triggerAutoPaint()
{
	isAnEvent = 1;
	eventToDo = AUTO_PAINT;
	redraw();
}

void PaintView::triggerPaintly()
{
	// printf("%d\n", m_pDoc->m_nPaintlyStrokeType);
	isAnEvent = 1;
	eventToDo = PAINTLY;
	m_pDoc->generateBlur();
	redraw();
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT_AND_BACK);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}

void PaintView::paintly()
{
	int width = m_pDoc->m_nWidth;
	int height = m_pDoc->m_nHeight;
	
	unsigned char* canvas = m_pDoc->m_ucPainting;
	unsigned char* reference = new unsigned char[width*height*3];
	unsigned char* diff = new unsigned char[width*height];
	memset(canvas, 0, width*height*3);

	int maxBrushSize = m_pDoc->m_pUI->getPaintlyMaxBrush();
	int minBrushSize = m_pDoc->m_pUI->getPaintlyMinBrush();
	double gridRatio = m_pDoc->m_pUI->getPaintlyGrid();
	int threshold = m_pDoc->m_pUI->getPaintlyThreshold();
	int layers = m_pDoc->m_pUI->getPaintlyLayers();
	int brushSizeStep = (maxBrushSize - minBrushSize) / layers;

	brushSizeStep = brushSizeStep > 1 ? brushSizeStep : 1;

	for (int i = maxBrushSize; i >= minBrushSize; i-=brushSizeStep) {
		paintlyBlur(m_pDoc->m_ucBitmap, reference, i);
		paintlyDifferenceCalculate(canvas, reference, diff);
		paintlyLayer(canvas, diff, reference, gridRatio, i, threshold);
	}
	// m_pDoc->m_pUI->m_paintView->refresh();//????
	//glFlush();
	//m_pDoc->m_pUI->m_paintView->refresh();
}

void PaintView::paintlyBlur(unsigned char* source, unsigned char* reference, int brushSize)
{
	int width = m_pDoc->m_nWidth;
	int height = m_pDoc->m_nHeight;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			// double result =  m_pDoc->f_Gaussian->applyToPixel(source, width, height, i, j );
			double result = m_pDoc->f_blur->applyToPixel(source,width,height,i,j);
			if (result < 0 )
			{
				result = 0;
			}
			if (result > 255)
			{
				result = 255;
			}
			reference[ i* height + j] = (unsigned char) result;
		}
	}
}

void PaintView::paintlyDifferenceCalculate(unsigned char* canvas, unsigned char* reference, unsigned char* diff)
{
	int width = m_pDoc->m_nWidth;
	int height = m_pDoc->m_nHeight;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int pos = i * width + j;
			diff[pos] = (reference[pos * 3] - canvas[pos * 3]) * (reference[pos * 3] - canvas[pos * 3])
				+ (reference[pos * 3 + 1] - canvas[pos * 3 + 1]) * (reference[pos * 3 + 1] - canvas[pos * 3 + 1])
				+ (reference[pos * 3 + 2] - canvas[pos * 3 + 2]) * (reference[pos * 3 + 2] - canvas[pos * 3 + 2]);
			diff[pos] = (unsigned char)(sqrt((double)diff[pos])/3);
			
		}
	}
}

void PaintView::makeCurved(const Point& start, unsigned char* reference, int brushSize, unsigned char* canvas, std::vector<Point>& vP)
{
	int startX = start.x;
	int startY = start.y;
	unsigned char strokeColorR = reference[(startY*m_nDrawWidth + startX) * 3];
	unsigned char strokeColorG = reference[(startY*m_nDrawWidth + startX) * 3 + 1];
	unsigned char strokeColorB = reference[(startY*m_nDrawWidth + startX) * 3 + 2];
	vP.push_back(Point(startX, startY));
	int x = startX, y = startY;
	int lastDx = 0, lastDy = 0;

	for (int i = 1; i <= m_pDoc->m_pUI->getPaintlyMaxStroke(); i++)
	{
		if (i > m_pDoc->m_pUI->getPaintlyMinStroke())
		{
			int diff1 = reference[(y*m_nDrawWidth + x) * 3] - canvas[(y*m_nDrawWidth + x) * 3]
				+ reference[(y*m_nDrawWidth + x) * 3 + 1] - canvas[(y*m_nDrawWidth + x) * 3 + 1]
				+ reference[(y*m_nDrawWidth + x) * 3 + 2] - canvas[(y*m_nDrawWidth + x) * 3 + 2];
			int diff2 = reference[(y*m_nDrawWidth + x) * 3] - strokeColorR
				+ reference[(y*m_nDrawWidth + x) * 3 + 1] - strokeColorG
				+ reference[(y*m_nDrawWidth + x) * 3 + 2] - strokeColorB;
			if (abs(diff1) < abs(diff2)) return;
		}

		int gradientX = (int)m_pDoc->m_nGradientxy[2 * (y * m_pDoc->m_nWidth + x)];
		int gradientY = (int)m_pDoc->m_nGradientxy[2 * (y * m_pDoc->m_nWidth + x) + 1];

		int dx = -gradientY;
		int dy = gradientX;

		if (lastDx * dx + lastDy * dy < 0)
		{
			dx = -dx;
			dy = -dy;
		}
		if (dx == 0 && dy == 0) return;

		dx = m_pDoc->m_pUI->getPaintlyCurvature()*dx + lastDx*(1 - m_pDoc->m_pUI->getPaintlyCurvature());
		dy = m_pDoc->m_pUI->getPaintlyCurvature()*dy + lastDy*(1 - m_pDoc->m_pUI->getPaintlyCurvature());
		double tempX = (dx) / (sqrt((double)(dx*dx + dy*dy)));
		double tempY = (dy) / (sqrt((double)(dx*dx + dy*dy)));
		x = x + brushSize*tempX;
		y = y + brushSize*tempY;
		lastDx = dx;
		lastDy = dy;
		if (x < 0 || y < 0 || x > m_nDrawWidth-1 || y > m_nDrawHeight-1) return;
 		vP.push_back(Point(x, y));
	}
}

void PaintView::paintlyLayer(unsigned char* canvas, unsigned char* diff,  unsigned char* reference, double gridRatio, int brushSize, int threshold)
{
	int width = m_pDoc->m_nWidth;
	int height = m_pDoc->m_nHeight;

	int gridSize = (int)(gridRatio * brushSize);
	std::vector<Point> vec;
	for (int i = 0; i < height; i += gridSize)
	{
		for (int j = 0; j < width; j += gridSize)
		{
			double sumError = 0;
			double maxError = -10.0;
			int maxErrorIndX = 0;
			int maxErrorIndY = 0;

			for (int ni = -gridSize / 2; ni < gridSize / 2; ni++)
			{
				for (int nj = -gridSize / 2; nj < gridSize / 2; nj++)
				{
					int curY = i + ni, curX = j + nj;
					
					if (curX < 0 || curY < 0 || curY > height - 1 || curX > width - 1) continue;
					
					sumError += ((double)diff[curY * width + curX]);// / (gridSize*gridSize);
					
					if (diff[curY * width + curX] > maxError)
					{
						maxError = diff[curY * width + curX];
						maxErrorIndX = curX; maxErrorIndY = curY;
					}
				}
			}

			if (sumError > threshold)
			{
				vec.push_back(Point(maxErrorIndX, maxErrorIndY));
			}
		}
	}
	std::random_shuffle(vec.begin(), vec.end());
	m_pDoc->m_pUI->setSize(brushSize);
	
	for (int i = 0; i < vec.size(); ++i)
	{
		if (m_pDoc->m_nPaintlyStrokeType == STROKE_CURVEDBRUSH)
		{
			std:: vector<Point> vp;
			makeCurved(vec[i], reference, brushSize, canvas, vp);
			for (int j = 0; j < vp.size(); j++) 
			{
				// CircleBrush* a = (CircleBrush*)m_pDoc->m_pCurrentBrush;
				// a->DrawCircle(vp[0], vp[j], (((float)(brushSize*2))/3.0));
				// m_pDoc->setBrushType(BRUSH_CIRCLES);
				// m_pDoc->setSize(1.5 * brushSize);
				m_pDoc->setBrushType(BRUSH_CIRCLES);
				m_pDoc->setSize(1.6 * brushSize);
				m_pDoc->m_pCurrentBrush->BrushBegin(vp[0], vp[j]);
				m_pDoc->m_pCurrentBrush->BrushEnd(vp[0], vp[j]);
			}
		}
		else
		{
			m_pDoc->setBrushType(BRUSH_CIRCLES);
			m_pDoc->m_pCurrentBrush->BrushBegin(vec[i], vec[i]);
			m_pDoc->m_pCurrentBrush->BrushEnd(vec[i], vec[i]);
		}
	}
}