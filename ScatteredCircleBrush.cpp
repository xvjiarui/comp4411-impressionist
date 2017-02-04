//
// ScatteredCircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"
#include <math.h>
extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	// int size = pDoc->getSize();



	// glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredCircleBrush::BrushMove  document is NULL\n" );
		return;
	}
	int size = pDoc->getSize();
	double radius = pDoc->getSize()/2.0;
	double twicePi = 2.0 * 3.142;
	
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				// srand((unsigned int)(time(NULL)));
				int index=rand()%(size*size);
				if (index == 1 || index == 2)
				{
					glBegin( GL_TRIANGLE_FAN );
					SetColor( Point(source.x - size/2 + i, source.y - size/2+j));

					glVertex2d( target.x - size/2 + i, target.y - size/2 + j);

					for (int k = 0; k <= 50; k++)   
					{
			        	glVertex2d ((target.x - size/2 + i + (radius * cos(k * twicePi / 50))), (target.y - size/2 + j+ (radius * sin(k * twicePi / 50))));
			    	}
			    	glEnd();
				}
			}
		}

	


}

void ScatteredCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

