#ifndef _GETTEXTURE_H
#define _GETTEXTURE_H
#include <opencv2\opencv.hpp>
using namespace cv;

class getTexture
{
public:
	getTexture();
	~getTexture();

	void init(IplImage* s);
	IplImage* drawModel();
	void showModel();
	void showResult();
	void drawResult();

private:
	IplImage* src;
	IplImage* modelImage;
	IplImage* result;
};

#endif
