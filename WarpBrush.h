#ifndef WARPBRUSH_H
#define WARPBRUSH_H	

#include "ImpBrush.h"
#include <cmath>

class WarpBrush : public ImpBrush
{
public:
	WarpBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
private:
	int size;
	Point prePoint;
	Pointd warppedSourcePoint(const Point center, int targetX, int targetY, const Point displacement, int radius);
	Pointd warppedSourcePoint(const Point center, const Point target, const Point displacement, int radius);
};

#endif