#ifndef _3DMODEL_H_
#define _3DMODEL_H_
#include <stdlib.h>
#include <list>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

struct Data
{
	Data()
	{
		shortAxe = 0;
		angle = 0;
	}
	list<CvPoint> center;
	list<int> longAxe;
	int shortAxe;
	double angle;
};

class threeDModel
{
public:
	static threeDModel* getInstance()
	{
		if (instance == NULL)
			instance = new threeDModel();
		return instance;
	};
	
	Data* getData();
	void run();

	void setParam(int argc, char** argv);
	int getWidth();
	void setWidth(int w);
	int getHeight();
	void setHeight(int h);

private:
	threeDModel();
    ~threeDModel();
	static threeDModel* instance;
	int width;
	int height;
	Data* data;

	int argc;
	char** argv;
};


#endif