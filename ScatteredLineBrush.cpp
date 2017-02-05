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
	int angle = pDoc->getLineAngle();
	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove  document is NULL\n" );
		return;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glBegin( GL_LINES );
	double Pi = 3.14159265;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			// srand((unsigned int)(time(NULL)));
			int index=rand()%3;
			if (index == 1)
			{
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

