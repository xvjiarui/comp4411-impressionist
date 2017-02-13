//
// WarpBrush.cpp
//
// The implementation of Rubber Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "WarpBrush.h"

extern float frand();

WarpBrush::WarpBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name), size(0)
{
}

void WarpBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	size = pDoc->getSize();
	prePoint = target;
	BrushMove(source, target);
}

void WarpBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* pUI = pDoc->m_pUI;
	if (pDoc == NULL) {
		printf("WarpBrush::BrushMove  document is NULL\n");
		return;
	}
	
	//calculate the displacement
	Point displacement = target - prePoint;
	//do nothing if displacement is zero
	if (displacement.x == 0 && displacement.y == 0) return;
	//calculate the color of every point
	GLubyte* warpPainting = new GLubyte[size*size * 4 * 3];
	int startX = target.x - size;
	int startY = target.y - size;
	//calculate color and store in a temporary array
	for (int j = 0; j < size * 2; ++j)
		for (int i = 0; i < size * 2; ++i)
		{
			memcpy(warpPainting + 3 * (i + j * 2 * size), pDoc->GetPaintingPixel(warppedSourcePoint(target, startX + i, startY + j, displacement, size)), 3);
		}
	//copy this temporary to the paint image
	for (int j = 0; j < size * 2; ++j)
		for (int i = 0; i < size * 2; ++i)
		{
			pDoc->SetPaintingPixel(startX + i, startY + j, warpPainting + 3 * (j * 2 * size + i));
		}
	//printf("warpped! displacement: %d %d center: %d %d radius: %d\n", displacement.x, displacement.y, target.x, target.y, size);
	delete[] warpPainting;
	prePoint = target;
	// pUI->m_paintView->SaveCurrentContent();
	pUI->m_paintView->RestoreContent();
}

void WarpBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}
/**
* \brief Calculate the original point given the target point, the displacement of the brush, and
* radius of the rubber brush
*/
Pointd WarpBrush::warppedSourcePoint(const Point center, int targetX, int targetY, const Point displacement, int radius)
{
	//this determines how much the center is moved relative to brush movement
	const double ratio = size;
	const int diffX = targetX - center.x;
	const int diffY = targetY - center.y;
	//distance of givent point from the center of brush
	const double distance = sqrt(diffX*diffX + diffY*diffY);
	if (distance >= radius) return Pointd(targetX, targetY);
	//this is the displacementMagnitude of the brush relative to last position
	const double displacementMagnitude = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	//the offset of desired point should be the minimum of two values:
	//1. center equal displacementMagnitude, decrease linearly by slope with distance
	//2. edge equal 0, increase linearly by slope with (radius - distance)
	double offset = ratio * displacementMagnitude * (1 - pow(distance / radius, 2));
	//with the given offset and the direction of displacement, calculate the point to which target should be mapped
	Pointd warped = Pointd(targetX - (offset / displacementMagnitude) * displacement.x, targetY -(offset/displacementMagnitude) * displacement.y);
	//printf("disMag: %f diff: %d %d target: %d %d orig: %d %d\n", displacementMagnitude, diffX, diffY,targetX, targetY, warped.x, warped.y);
	return warped;
}
Pointd WarpBrush::warppedSourcePoint(const Point center, const Point target, const Point displacement, int radius)
{
	return warppedSourcePoint(center, target.x, target.y, displacement, radius);
}