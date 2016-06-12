#ifndef _MODEL_H
#define _MODEL_H

#include <opencv2/opencv.hpp>
#include "sweepPoint.h"
#include "sweepCanny.h"
#include "getTexture.h"
using namespace cv;

class model
{
public:
	model();

	//先放弃
	//model(sweepPoint* sp);

	void drawBy2Points();
	void drawBy3Points(IplImage* src);
	void drawBy4Points(IplImage* src, sweepCanny edge, getTexture& t);
	
	void savePoint(CvPoint point);
	void saveTempPoint(CvPoint point);
	void run(IplImage* src, sweepCanny edge, getTexture& t);

	int getNumber();

private:
	//先放弃
	//sweepPoint* point;
	CvPoint points[4];
	CvPoint center;
	int baseLongAxe, baseShortAxe;
	int count;
	int preLongAxe;
	bool tempRun;
	bool twoPointsCompute, threePointsDraw;
	CvScalar color;
};

#endif