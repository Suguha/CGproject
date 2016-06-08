#ifndef _SWEEPPOINT_H
#define _SWEEPPOINT_H

#include <opencv2/opencv.hpp>
using namespace cv;

class sweepPoint {
public:
	sweepPoint();
	int getNumber();
	void savePoint(CvPoint currentPoint);
	CvPoint getPrePoint();
	void drawLine();//delete

private:
	CvPoint points[4];
	int pointsNumber;
};

#endif