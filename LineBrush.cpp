//
// LineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include <math.h>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"

extern float frand();
static Point prev(-1, -1);
static Point current(-1, -1);
LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int width = pDoc->getLineWidth();



	glLineWidth((float)width);

	BrushMove( source, target );
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	double size = pDoc->getSize()/2;
	double Pi=3.14159265;
	int angle = pDoc->getLineAngle();
	switch (pDoc->getDirectionType()){

		case 0:	
			angle = pDoc->getLineAngle();
			break;

		case 1: 
			double Gx;
			double Gy;
			GLubyte color[3][3][3];
			double intensity[3][3];
			for (int i = -1; i < 2; i++){
				for (int j = -1; j < 2; j++){
					memcpy(color[i+1][j+1], pDoc->GetOriginalPixel(Point(source.x + i, source.y + j)), 3);
					intensity[i + 1][j + 1] = 0.299*color[i + 1][j + 1][0] + 0.587*color[i + 1][j + 1][1] + 0.144*color[i + 1][j + 1][2];
				}
			}
			Gx = intensity[0][0] * (-1) + intensity[0][1] * (-2) + intensity[0][2] * (-1)\
					  + intensity[2][0] * (1) + intensity[2][1] * (2) + intensity[2][2] * (1);
			Gy = intensity[0][0] * (-1) + intensity[1][0] * (-2) + intensity[2][0] * (-1)\
				+ intensity[0][2] * (1) + intensity[1][2] * (2) + intensity[2][2] * (1);
			angle = -(int)(atan2(Gy, Gx)*180/Pi) % 360;
			break;

		case 2:
			current.x = target.x;
			current.y = target.y;
			if (prev.x!=-1&&current.x!=-1&&(current.x != prev.x || current.y != prev.y)){
				int dx = current.x - prev.x;
				int dy = current.y - prev.y;
				angle = (int)(atan2(dy, dx)*180/Pi) % 360;
			}
			prev.x = current.x;
			prev.y = current.y;
			break;
	}
	
	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove  document is NULL\n" );
		return;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glBegin( GL_LINES );
		SetColor( source );
		glVertex2d( target.x + (cos(angle * Pi / 180) * size), target.y + (sin(angle * Pi / 180) * size));
		glVertex2d( target.x - (cos(angle * Pi / 180) * size), target.y - (sin(angle * Pi / 180) * size));
	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

