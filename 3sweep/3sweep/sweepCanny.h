#ifndef _SWEEPCANNY_H_
#define _SWEEPCANNY_H_

#include <opencv2\opencv.hpp>
using namespace cv;

class sweepCanny
{
public:
	sweepCanny();
	void init(Mat src, int a, int b);
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