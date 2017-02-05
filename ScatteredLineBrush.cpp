//
// ScatteredLineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"
#include <math.h>
extern float frand();
static Point prev(-1, -1);
static Point current(-1, -1);
ScatteredLineBrush::ScatteredLineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredLineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int width = pDoc->getLineWidth();



	glLineWidth((float)width);


	BrushMove( source, target );
}

void ScatteredLineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	int size = pDoc->getSize();
	double Pi = 3.14159265;
	int angle = pDoc->getLineAngle();
	
	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove  document is NULL\n" );
		return;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glBegin( GL_LINES );
	
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			// srand((unsigned int)(time(NULL)));
			int index=rand()%(size*size);
			if (index == 1 || index == 2)
			{
				switch (pDoc->getDirectionType()){

					case 0:	
						angle = pDoc->getLineAngle();
						break;

					case 1: 
						double Gx;
						double Gy;
						GLubyte color[3][3][3];
						double intensity[3][3];
						for (int p = -1; p < 2; p++){
							for (int q = -1; q < 2; q++){
								memcpy(color[p+1][q+1], pDoc->GetOriginalPixel(Point(source.x - size/2 + i + p, source.y - size/2 + j + q)), 3);
								intensity[p + 1][q + 1] = 0.299*color[p + 1][q + 1][0] + 0.587*color[p + 1][q + 1][1] + 0.144*color[p + 1][q + 1][2];
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
				SetColor( Point(source.x - size/2 + i, source.y - size/2+j));

				glVertex2d( target.x - size/2 + i + cos(angle * Pi / 180) * size/2.0, target.y - size/2 + j + sin(angle * Pi / 180) * size/2.0);
				glVertex2d( target.x - size/2 + i - cos(angle * Pi / 180) * size/2.0, target.y - size/2 + j - sin(angle * Pi / 180) * size/2.0);
			}
			
		}
	}

	glEnd();
}

void ScatteredLineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

