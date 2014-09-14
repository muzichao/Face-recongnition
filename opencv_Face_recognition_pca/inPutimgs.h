#ifndef INPUTIMGS_H
#define INPUTIMGS_H

#include <iostream>
#include <highgui.h>
#include <imgproc\imgproc.hpp>
#include <cstring>
#include <Windows.h>

using namespace std;
using namespace cv;

Mat inPutimgs(int _N, int _M, int _rows, int _cols);

#endif