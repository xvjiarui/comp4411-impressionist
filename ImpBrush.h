#ifndef IMPBRUSH_H
#define IMPBRUSH_H

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>

// Each brush type has an associated constant.
enum
{
	BRUSH_POINTS = 0,
	BRUSH_LINES,
	BRUSH_CIRCLES,
	BRUSH_SCATTERED_POINTS,
	BRUSH_SCATTERED_LINES,
	BRUSH_SCATTERED_CIRCLES,
	BRUSH_TRIANGLES,
	BRUSH_HEARTS,
	BRUSH_BLUR,
	BRUSH_SHARPEN,
	BRUSH_WARP,
	BRUSH_ALPHA_MAPPED,
	BRUSH_GRAY,
	NUM_BRUSH_TYPE // Make sure this stays at the end!
};

// Each brush direction has an associated constant.
enum
{
	DIRECTION_SLIDER = 0,
	DIRECTION_GRADIENT,
	DIRECTION_CURSOR,
	NUM_BRUSH_DIRECTION // Make sure this stays at the end!
};



class ImpressionistDoc; // Pre-declaring class

class Point 
{
public:
	Point() {};
	Point(int xx, int yy) { x = xx; y = yy; };
	Point operator-(const Point another) const 
	{ 
		return Point(x - another.x, y - another.y); 
	}
	int x, y;
};

class Pointd 
{
public:
	Pointd() {};
	Pointd(double xx, double yy) { x = xx; y = yy; };
	Pointd operator-(const Pointd another) const 
	{ 
		return Pointd(x - another.x, y - another.y); 
	}
	double x, y;
};

class ImpBrush 
{
protected:
	ImpBrush::ImpBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

public:
	// The implementation of your brush should realize these virtual functions
	virtual void BrushBegin( const Point source, const Point target ) = 0;
	virtual void BrushMove( const Point source, const Point target ) = 0;
	virtual void BrushEnd( const Point source, const Point target ) = 0;

	// according to the source image and the position, determine the draw color
	void SetColor( const Point source );
	void SetColor( const Point source, GLubyte alpha);
	void SetGray( const Point source );

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the brush (not used in this version).
	char* BrushName( void );
	
	static int			c_nBrushCount;	// How many brushes we have,
	static ImpBrush**	c_pBrushes;		// and what they are.

private:
	ImpressionistDoc*	m_pDoc;

	// Brush's name (not used in this version).
	char*				m_pBrushName;
};

#endif