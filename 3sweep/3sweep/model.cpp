#include "model.h"
#include <math.h>
#include <iostream>
using namespace std;

model::model()
{
	for (int i = 0; i < 4; i++)
	{
		points[i] = { -1, -1 };
	}
	//point = new sweepPoint();
	count = longAxe = shortAxe = 0;
	center = { -1, -1 };
	tempRun = false;
	twoPointsCompute = false;
	threePointsDraw = false;
	color = cvScalar(0, 0, 255, 0);
}
/*
model::model(sweepPoint* sp)
{
	point = sp;
	count = sp->getNumber();
	longAxe = shortAxe = 0;
	center = { -1, -1 };
	tempRun = false;
	twoPointsCompute = false;
	threePointsDraw = false;
	color = cvScalar(0, 0, 255, 0);
}
*/
void model::drawBy2Points()
{
	center = { (points[0].x + points[1].x) / 2, (points[0].y + points[1].y) / 2 };
	int temp = pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2);
	longAxe = sqrt(temp) / 2;
	//cout << "long: " <<longAxe << endl;
}

void model::drawBy3Points(IplImage* src)
{
	double temp = 1 - (double)(pow(points[2].x - center.x, 2) / (longAxe * longAxe));
	shortAxe = sqrt(pow(points[2].y - center.y, 2) / temp);
	//cout << "short: " <<shortAxe << endl;
	if (shortAxe > 0)
	{
		cvEllipse(src, center, cvSize(longAxe, shortAxe), 0, 0, 360, color, 1);
	}
}

void model::drawBy4Points(IplImage* src)
{
	if (abs(points[3].y - points[2].y) < abs(points[3].x - points[2].x))
	{
		//cout << "y" << endl;
		double k = (double)(points[3].y - points[2].y) / (points[3].x - points[2].x);
		int min, max;
		if (points[2].x <= points[3].x)
		{
			min = points[2].x;
			max = points[3].x;
		}
		else
		{
			min = points[3].x;
			max = points[2].x;
		}
		for (int i = min; i <= max; i++)
		{
			CvPoint tempCenter = cvPoint(center.x + (i - points[2].x), center.y + (i - points[2].x) * k);
			cvEllipse(src, tempCenter, cvSize(longAxe, shortAxe), 0, 0, 360, color, -1);
		}
	}
	else
	{
		//cout << "x" << endl;
		double k = (double)(points[3].x - points[2].x) / (points[3].y - points[2].y);
		int min, max;
		if (points[2].y <= points[3].y)
		{
			min = points[2].y;
			max = points[3].y;
		}
		else
		{
			min = points[3].y;
			max = points[2].y;
		}
		for (int i = min; i <= max; i++)
		{
			CvPoint tempCenter = cvPoint(center.x + (i - points[2].y) * k, center.y + (i - points[2].y));
			cvEllipse(src, tempCenter, cvSize(longAxe, shortAxe), 0, 0, 360, color, -1);
		}
	}
}

void model::savePoint(CvPoint point)
{
	points[count++] = point;
	tempRun = false;
}

void model::saveTempPoint(CvPoint point)
{
	points[count] = point;
	tempRun = true;
}

int model::getNumber()
{
	return count;
}

void model::run(IplImage* src)
{
	if (count == 2 && !twoPointsCompute)
	{
		drawBy2Points();
		twoPointsCompute = true;
		//cout << 2 << endl;
	}
	if ((count == 3 && !threePointsDraw) || (tempRun && count == 2))
	{
		drawBy3Points(src);
		if (tempRun == false)
		{
			threePointsDraw = true;
			//cout << 3 << endl;
		}
	}
	if (count == 4 || (tempRun && count == 3))
	{
		drawBy4Points(src);
	}
}