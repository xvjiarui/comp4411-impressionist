//
// TriangleBrush.cpp
//
// The implementation of Triangle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "TriangleBrush.h"
#include <math.h>

extern float frand();

TriangleBrush::TriangleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void TriangleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	//int size = pDoc->getSize();



	// glPointSize( (float)size );

	BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("TriangleBrush::BrushMove  document is NULL\n");
		return;
	}
	double size = pDoc->getSize() / 2.0;
	//double twicePi = 2.0 * 3.142;
	double ro3 = 1.732;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_TRIANGLE_FAN);
	SetColor(source);

	glVertex2d(target.x, target.y+size);

	//for (int i = 0; i <= 50; i++)
	//{
	//	glVertex2d((target.x + (radius * cos(i * twicePi / 50))), (target.y + (radius * sin(i * twicePi / 50))));
	//}
	glVertex2d(target.x + ro3*size / 2, target.y - size*(1 / 2));
	glVertex2d(target.x - ro3*size / 2, target.y - size*(1 / 2));

	glEnd();
}

void TriangleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}