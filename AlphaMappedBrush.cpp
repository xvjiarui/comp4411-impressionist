#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "AlphaMappedBrush.h"

extern float frand();

AlphaMappedBrush::AlphaMappedBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void AlphaMappedBrush::BrushBegin(const Point source, const Point target)
{
	glPointSize(2);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	BrushMove(source, target);
}

void AlphaMappedBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* p_UI = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}
	glBegin(GL_POINTS);
	GLubyte alpha = pDoc->m_ucAlphaBrushBitmap[ target.y * pDoc->m_nWidth + target.x];
	SetColor(source, alpha);
	glVertex2d(target.x, target.y);
	glEnd();
	glFlush();
}

void AlphaMappedBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}