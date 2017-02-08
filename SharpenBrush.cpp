//
// SharpenBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SharpenBrush.h"
#include "Filter.h"

extern float frand();

SharpenBrush::SharpenBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void SharpenBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( 1.0 );

	BrushMove( source, target );
}

void SharpenBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "SharpenBrush::BrushMove  document is NULL\n" );
		return;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin( GL_POINTS );
		SetFilterColor( source );

		glVertex2d( target.x, target.y );

	glEnd();
}

void SharpenBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

void SharpenBrush::SetFilterColor ( const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[4];
	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
	double r = pDoc->m_pUI->getR();
	double g = pDoc->m_pUI->getG();
	double b = pDoc->m_pUI->getB();
	Filter<int>* filter = pDoc->f_Sharpen;
	color[0] = filter->applyToPixel(pDoc->m_ucBitmapR, pDoc->m_nWidth, pDoc->m_nWidth, source.x, source.y);
	color[1] = filter->applyToPixel(pDoc->m_ucBitmapG, pDoc->m_nWidth, pDoc->m_nWidth, source.x, source.y);
	color[2] = filter->applyToPixel(pDoc->m_ucBitmapB, pDoc->m_nWidth, pDoc->m_nWidth, source.x, source.y);

	color[0] *= r;
	color[1] *= g;
	color[2] *= b;
 	color[3] = 255 * pDoc->getOpacity();
	glColor4ubv( color );

}
