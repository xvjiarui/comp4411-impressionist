//
// HeartBrush.cpp
//
// The implementation of Triangle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "HeartBrush.h"
#include <math.h>

extern float frand();

HeartBrush::HeartBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void HeartBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	//int size = pDoc->getSize();



	// glPointSize( (float)size );

	BrushMove(source, target);
}

void HeartBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("HeartBrush::BrushMove  document is NULL\n");
		return;
	}
	double size = pDoc->getSize() / 2.0;
	double twicePi = 2.0 * 3.142;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_TRIANGLE_FAN);
	SetColor(source);

	//glVertex2d(target.x, target.y);

	for (int i = 0; i <= 50; i++)
	{
		glVertex2d((target.x + size * (2*cos(i * twicePi / 50)-cos(2*i*twicePi/50))), (target.y + size * (2 * sin(i * twicePi / 50) - sin(2*i*twicePi / 50))));
	}
	

	glEnd();
}

void HeartBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}