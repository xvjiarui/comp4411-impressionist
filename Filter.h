#ifndef FILTER_H
#define FILTER_H

//
// Filter.h
//
// The header file of filters. 
//
#include <cmath>
#include <iostream>
#include "FL/gl.h"
#include "ImpressionistDoc.h"

template<typename filterType>
class Filter 
{
public:
	Filter(filterType* arr, int w, int h){
		kernel = new filterType [w*h];
		for (int i = 0; i < w * h; ++i)
		{
			kernel[i]=arr[i];
		}
		filterWidth = w;
		filterHeight = h;
		// for (int i = 0; i < w *h; ++i)
		// {
		// 	printf("f%f\n", kernel[i]);
		// 	printf("d%d\n", kernel[i]);
		// }
	}
	double applyToPixel(const GLubyte* source, int sourceWidth, int sourceHeight, int x, int y){
		
		int alignX = x - (filterWidth / 2);
		int alignY = y - (filterHeight / 2);

		double result = 0;

		for (int j = 0; j < filterHeight; ++j)
		{
			for (int i = 0; i < filterWidth; ++i)
			{
				int x = (i + alignX < sourceWidth) ? abs(i + alignX) : 2 * (sourceWidth - 1) - (i + alignX);
				int y = (j + alignY < sourceHeight) ? abs(j + alignY) : 2 * (sourceHeight - 1) - (j + alignY);

				//convert coordinate to index in 1D
				int filterPos = j * filterWidth + i; //According to blue book, pixels are stored row-first
				int sourcePos = y * sourceWidth + x;
				result += (double) (kernel[filterPos] * source[sourcePos]);
				// printf("%d, %d:%f\n",j,i,result );
			}
		}
		// printf("final:%f\n", result);
		return result;
	}

private:
	filterType* kernel;
	int filterWidth;
	int filterHeight;
};

#endif