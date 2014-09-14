#ifndef DISPMANYIMGS_H
#define DISPMANYIMGS_H

#include <iostream>
#include <highgui.h>
#include <imgproc\imgproc.hpp>
#include <cstring>
#include <stdarg.h>
#include <Windows.h>
#include "showmnImage.h"

using namespace std;
using namespace cv;

void dispManyimgs(char* title, int nArgs, ...);

#endif