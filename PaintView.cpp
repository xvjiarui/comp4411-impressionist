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


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6
#define AUTO_PAINT			7


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
