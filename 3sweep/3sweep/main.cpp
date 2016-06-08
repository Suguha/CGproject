#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "sweepPoint.h"
#include "model.h"

using namespace std;
using namespace cv;

IplImage* src = 0;
IplImage* dst = 0;
sweepPoint points;
model m;

void mouseEvent(int event, int x, int y, int flags, void* ustc)
{
	static CvPoint pre_pt = { -1, -1 };
	static CvPoint cur_pt = { -1, -1 };

	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);
	char temp[16];

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cvCopy(dst, src);
		sprintf_s(temp, "(%d,%d)", x, y);
		cur_pt = cvPoint(x, y);
		
		if (points.getNumber() != 0 && points.getNumber() < 4)
		{
			pre_pt = points.getPrePoint();
			cvLine(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, 8, 0);
		}
		if (points.getNumber() < 4)
		{
			//保存点
			points.savePoint(cur_pt);
			m.savePoint(cur_pt);

			m.run(src);
			cvPutText(src, temp, cur_pt, &font, cvScalar(0, 0, 0, 255));
			cvCircle(src, cur_pt, 3, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		}
		cvShowImage("src", src);
		cvCopy(src, dst);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))
	{
		cvCopy(dst, src);
		sprintf_s(temp, "(%d,%d)", x, y);
		cur_pt = cvPoint(x, y);
		cvPutText(src, temp, cur_pt, &font, cvScalar(0, 0, 0, 255));
		if (points.getNumber() != 0 && points.getNumber() < 4)
		{
			pre_pt = points.getPrePoint();
			cvLine(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, 8, 0);
		}
		if (m.getNumber() > 1 && m.getNumber() < 4)
		{
			m.saveTempPoint(cur_pt);

			m.run(src);
		}
		cvShowImage("src", src);
	}
	/*
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		cvCopy(dst, src);
		sprintf_s(temp, "(%d,%d)", x, y);
		cur_pt = cvPoint(x, y);
		cvPutText(src, temp, cur_pt, &font, cvScalar(0, 0, 0, 255));
		cvLine(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, 8, 0);
		cvShowImage("src", src);
	}
	
	else if (event == CV_EVENT_LBUTTONUP)
	{
		sprintf_s(temp, "(%d,%d)", x, y);
		cur_pt = cvPoint(x, y);
		cvPutText(src, temp, cur_pt, &font, cvScalar(0, 0, 0, 255));
		cvCircle(src, cur_pt, 3, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		//cvRectangle(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, 8, 0);
		cvShowImage("src", src);
		cvCopy(src, dst);
	}*/
}

int main(int argc, char* argv[])
{
	const char* imagename = "1.png";

	//从文件中读入图像
	Mat img = imread(imagename, -1);
	
	//如果读入图像失败
	if (img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}

	
	src = cvLoadImage(imagename, 1);
	dst = cvCloneImage(src);
	cvNamedWindow("src", 1);
	cvShowImage("src", src);
	cvSetMouseCallback("src", mouseEvent, 0);
	//显示图像
	//imshow("image", img);

	//此函数等待按键，按键盘任意键就返回
	waitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	
	return 0;
}