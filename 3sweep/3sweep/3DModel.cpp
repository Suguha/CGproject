#include "3DModel.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <math.h>
using namespace std;
#define PI 3.1415
#define N 40

threeDModel* threeDModel::instance = NULL;
threeDModel::threeDModel()
{
	width = 400;
	height = 400;
	data = new Data();
}

threeDModel::~threeDModel()
{
	if (instance != NULL)
		delete instance;
}

Data* threeDModel::getData()
{
	return data;
}
int threeDModel::getWidth()
{
	return width;
}
void threeDModel::setWidth(int w)
{
	width = w;
}
int threeDModel::getHeight()
{
	return height;
}
void threeDModel::setHeight(int h)
{
	height = h;
}
void threeDModel::setParam(int c, char** v)
{
	argc = c;
	argv = v;
}

GLfloat ang_x = 0;
GLfloat ang_y = 0;
GLfloat scar = 1;
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display()
{
	threeDModel* data = threeDModel::getInstance();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(ang_x, 1, 0, 0);
	glRotatef(ang_y, 0, 1, 0);
	glScalef(scar, scar, scar);
	glBegin(GL_TRIANGLE_FAN);//LINE_LOOP STRIP
	glColor3f(1.0, 1.0, 1.0);
	CvPoint first = *data->getData()->center.begin();
	list<CvPoint>::iterator centerIter = data->getData()->center.begin();
	for (list<int>::iterator i = data->getData()->longAxe.begin(); i != data->getData()->longAxe.end(); i++)
	{
		for (int j = 0; j < N; j++)
		{
			glVertex3f(((GLfloat)*i * cos(2 * j * PI / N) + abs(centerIter->x - first.x)) / data->getWidth() * 2, (GLfloat)abs((centerIter->y - first.y)) / data->getHeight() * 2, (GLfloat)(data->getData()->shortAxe) / data->getWidth() * sin(2 * j * PI / N) * 2);
		}
		centerIter++;
	}
	glEnd();
	glFlush();
}

void key(unsigned char key, int x, int y)
{
	if (key == 'w') {
		ang_x += 10;
	}
	if (key == 's') {
		ang_x -= 10;
	}
	if (key == 'a') {
		ang_y += 10;
	}
	if (key == 'd') {
		ang_y -= 10;
	}
	if (key == 'q') {
		scar += 0.01;
	}
	if (key == 'e') {
		scar -= 0.01;
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glutReshapeWindow(threeDModel::getInstance()->getWidth(), threeDModel::getInstance()->getHeight());
}

void threeDModel::run()
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("3D Model");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMainLoop();
	return;
}
