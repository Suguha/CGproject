#include "sweepCanny.h"
#include <iostream>
using namespace std;

sweepCanny::sweepCanny()
{
	hold = 0.2;
}

sweepCanny::~sweepCanny()
{

}

void sweepCanny::init(Mat src, int a, int b)
{
	cvtColor(src, src, CV_RGB2GRAY);
	Canny(src, edge, a, b);   ///125    400
	threshold(edge, edge, 128, 255, THRESH_BINARY);
	row = edge.rows;
	col = edge.cols;
	if (edge.isContinuous())
	{
		row *= col;
		col = 1;
	}
}

void sweepCanny::show()
{
	namedWindow("canny", 1);
	imshow("canny", edge);
}

int sweepCanny::nextLongAxe(CvPoint center, int pre)
{
	int min = pre * (1 - hold);
	int max = pre * (1 + hold);

	for (int i = pre; i < max; i++)
	{
		CvPoint point1 = cvPoint(center.x - i, center.y);
		CvPoint point2 = cvPoint(center.x + i, center.y);
		if (isMatch(point1) || isMatch(point2))
		{
			return i;
		}
	}

	for (int i = pre; i > min; i--)
	{
		CvPoint point1 = cvPoint(center.x - i, center.y);
		CvPoint point2 = cvPoint(center.x + i, center.y);
		if (isMatch(point1) || isMatch(point2))
		{
			return i;
		}
	}

	return pre;
}

bool sweepCanny::isMatch(CvPoint p)
{
	uchar* pt;
	pt = edge.ptr<uchar>(p.y);
	if (pt[p.x] == 255)
	{
		return true;
	}
	return false;
}