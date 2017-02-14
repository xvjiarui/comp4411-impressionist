//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef CIRCLEBRUSH_H
#define CIRCLEBRUSH_H

#include "ImpBrush.h"

class CircleBrush : public ImpBrush
{
public:
	CircleBrush ( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	void DrawCircle(Point source, Point target ,float r);
	char* BrushName( void );
};

#endif