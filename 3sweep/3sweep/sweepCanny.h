#ifndef _SWEEPCANNY_H
#define _SWEEPCANNY_H

#include <opencv2\opencv.hpp>
using namespace cv;

class sweepCanny
{
public:
	sweepCanny();
	void init(Mat src);
	void show();
	bool isMatch(CvPoint p);
	int nextLongAxe(CvPoint center, int preLongAxe);
	~sweepCanny();

private:
	Mat edge;
	int row, col;
	float hold;
};

#endif