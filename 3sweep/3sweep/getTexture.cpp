#include "getTexture.h"
#include <iostream>
using namespace std;

getTexture::getTexture()
{
	src = 0;
	modelImage = 0;
	result = 0;
}

getTexture::~getTexture()
{
	cvReleaseImage(&src);
	cvReleaseImage(&modelImage);
	cvReleaseImage(&result);
}

void getTexture::init(IplImage* s)
{
	src = s;
	modelImage = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 4);
	result = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 4);
}

IplImage* getTexture::drawModel()
{
	return modelImage;
}

void getTexture::showModel()
{
	namedWindow("model", 1);
	cvShowImage("model", modelImage);
}

void getTexture::drawResult()
{
	uchar* srcData = (uchar*)src->imageData;
	uchar* modelData = (uchar*)modelImage->imageData;
	uchar* resultData = (uchar*)result->imageData;
	/*
	for (int i = 0; i < result->height; i++)
	{
		for (int j = 0; j < result->width; j++)
		{
			cout << modelData[i * modelImage->width + j * 3] << endl;
			//if (modelData[i * modelImage->width + j * 3] == )
		}
	}*/
}

void getTexture::showResult()
{
	namedWindow("Result", 1);
	cvShowImage("Result", result);
}