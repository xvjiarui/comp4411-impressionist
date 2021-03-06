//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"


// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();
	GLubyte color[4];
	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
	double r = pDoc->m_pUI->getR();
	double g = pDoc->m_pUI->getG();
	double b = pDoc->m_pUI->getB();
	color[0] *= r;
	color[1] *= g;
	color[2] *= b;
 	color[3] = 255 * pDoc->getOpacity();
	glColor4ubv( color );

}

void ImpBrush::SetColor (const Point source, GLubyte alpha)
{
	ImpressionistDoc* pDoc = GetDocument();
	GLubyte color[4];
	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
	double r = pDoc->m_pUI->getR();
	double g = pDoc->m_pUI->getG();
	double b = pDoc->m_pUI->getB();
	color[0] *= r;
	color[1] *= g;
	color[2] *= b;
 	color[3] = alpha;
	glColor4ubv( color );

}

void ImpBrush::SetGray (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();
	GLubyte color[4];
	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
	GLubyte gray = pDoc->grayPixel(color);
	color[0] = gray;
	color[1] = gray;
	color[2] = gray;
	color[3] = 255 * pDoc->getOpacity();
	glColor4ubv( color );
}


