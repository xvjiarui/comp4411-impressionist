//
// CircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	//int size = pDoc->getSize();



	// glPointSize( (float)size );

	BrushMove( source, target );
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "CircleBrush::BrushMove  document is NULL\n" );
		return;
	}
	double radius = pDoc->getSize()/2.0;
	double twicePi = 2.0 * 3.142;
	glBegin( GL_TRIANGLE_FAN );
		SetColor( source );

		glVertex2d( target.x, target.y );
		
		for (int i = 0; i <= 50; i++)   
		{
        	glVertex2d ((target.x + (radius * cos(i * twicePi / 50))), (target.y + (radius * sin(i * twicePi / 50))));
    	}

	glEnd();
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

