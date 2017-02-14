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
	int size = pDoc->getSize()>1? pDoc->getSize():1;
	double radius = size/2.0;
	double twicePi = 2.0 * 3.142;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void CircleBrush::DrawCircle(Point source, Point target, float r) {
	//The brush is moved to a new place. I need to draw a filled circle there
	int num_segments = (int)(10 * sqrtf(r));//change the 10 to a smaller/bigger number as needed

	float theta = (float)(2 * 3.1415926) / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

	//set the initial point coordinate
	float x = r;//we start at angle = 0
	float y = 0;

	glBegin(GL_TRIANGLE_FAN);
	//set color
	SetColor(source);
	//first point is the center point
	glVertex2f((GLfloat)target.x, (GLfloat)target.y);
	//then loop to add the bounding points to the vertex map
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + target.x, y + target.y);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -y;
		float ty = x;

		//add the tangential vector

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor

		x *= radial_factor;
		y *= radial_factor;
	}
	//last point should return to the first bounding point,
	//for GL_TRIANGLE_FAN doesn't close the loop altomatically
	glVertex2f((GLfloat)(target.x + r), (GLfloat)target.y);
	glEnd();
}

