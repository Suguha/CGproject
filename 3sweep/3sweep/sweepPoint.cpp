#include "sweepPoint.h"

sweepPoint::sweepPoint()
{
	for (int i = 0; i < 4; i++)
	{
		points[i] = { -1, -1 };
	}
	pointsNumber = 0;
}

int sweepPoint::getNumber()
{
	return pointsNumber;
}

void sweepPoint::savePoint(CvPoint currentPoint)
{
	points[pointsNumber++] = currentPoint;
}

CvPoint sweepPoint::getPrePoint()
{
	return points[pointsNumber - 1];
}

void sweepPoint::drawLine()
{

}