#pragma once
#include <GL/GL.h>
#include <GL/GLU.h>
#include "C:/Libs/freeglut/include/GL/glut.h"

#include<opencv2/core.hpp>

#define width 640
#define height 480
// OpenGL Variables
static GLuint textureId;               // ID of the texture to contain Kinect RGB Data
//static GLubyte data[width*height * 4];  // BGRA array containing the texture data
void myDraw();

class mygl_ShowImage
{
public:
	mygl_ShowImage();
	~mygl_ShowImage();
	void init();
	char* WidnowName;
	static void upDate(cv::Mat inputMat);
 
};

