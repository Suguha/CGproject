#ifndef _MODEL_H
#define _MODEL_H

#include <opencv2/opencv.hpp>
#include "sweepPoint.h"
using namespace cv;

class model
{
public:
	model();

	//先放弃
	//model(sweepPoint* sp);

	void drawBy2Points();
	void drawBy3Points(IplImage* src);
	void drawBy4Points(IplImage* src);
	
	void savePoint(CvPoint point);
	void saveTempPoint(CvPoint point);
	void run(IplImage* src);

	int getNumber();

private:
	//先放弃
	//sweepPoint* point;
	CvPoint points[4];
	CvPoint center;
	int longAxe, shortAxe;
	int count;
	bool tempRun;
	bool twoPointsCompute, threePointsDraw;
	CvScalar color;
};

#endif