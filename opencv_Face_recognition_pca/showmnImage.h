#ifndef _SHOWMNIMAGE_H
#define _SHOWMNIMAGE_H

#include <iostream>
#include <highgui.h>

using namespace std;
using namespace cv;

Mat showmnImage(int _m,int _n,Mat& _Image, Mat& DispImage); //在DispImage的（m,n）位置开始显示Image

#endif