/**
 *@brief 新建一个title窗口，显示 nArgs个图像
 *@param[in] char* title：窗口名称  nArgs：待显示图像个数
			 ...：nArgs个Mat图像
 *@param[out]
 *@return    
 *@pre       输入的Mat型图像个数必须=nArgs
 *@post      
 *@code
   Mat _Image(100, 100, CV_8UC3, Scalar(0, 255, 0));
   Mat _Image1(100, 100, CV_8UC3, Scalar(255, 0, 0));
   dispManyimgs("test", 2, _Image, _Image1);
 *@endcode

 *@since 2013.10.22
 *@author lichao
*/
#include "dispmanyimgs.h"

void dispManyimgs(char* title, int nArgs, ...) 
{
	
	Mat img; // img 用来读取输入的图像参数
	Mat DispImage; // 整体显示图像区域

	int size = 0;
	int x = 0;
	int y = 0;
	int i = 0;
	int m = 0;
	int n = 0;
	// w - Maximum number of images in a row 
	// h - Maximum number of images in a column 
	int w = 0;
	int h = 0;

	// scale - How much we have to resize the image
	float scale = 0.0;
	int max = 0;

	// If the number of arguments is lesser than 0 or greater than 12
	// return without displaying 
	if(nArgs <= 0) 
	{
		cout << "Number of arguments too small...." << endl;
		return;
	}
	else if(nArgs > 12) 
	{
		cout << "Number of arguments too large...." <<endl;
		return;
	}
	// Determine the size of the image, 
	// and the number of rows/cols 
	// from number of arguments 
	else if (nArgs == 1) 
	{
		w = h = 1;
		size = 150;
	}
	else if (nArgs == 2) 
	{
		w = 2; 
		h = 1;
		size = 150;
	}
	else if (nArgs == 3 || nArgs == 4)
	{
		w = 2; 
		h = 2;
		size = 150;
	}
	else if (nArgs == 5 || nArgs == 6) 
	{
		w = 3; 
		h = 2;
		size = 150;
	}
	else if (nArgs == 7 || nArgs == 8) 
	{
		w = 4; 
		h = 2;
		size = 150;
	}
	else 
	{
		w = 4; 
		h = 3;
		size = 150;
	}
	// Create a new 3 channel image
	DispImage.create( 60 + size*h, 100 + size*w, CV_8UC3);
	// Used to get the arguments passed
	va_list args;
	va_start(args, nArgs);
	// Loop for nArgs number of arguments
	for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) 
	{
		// Get the Pointer to the Mat
		img = va_arg(args, Mat);
		// Find the width and height of the image
		x = img.cols;
		y = img.rows;
		// Find whether height or width is greater in order to resize the image
		max = (x > y)? x: y;
		// Find the scaling factor to resize the image
		scale = (float) ( (float) max / size );
		// Used to Align the images
		if( i % w == 0 && m!= 20) 
		{
			m = 20;
			n+= 20 + size;
		}
		DispImage = showmnImage(m, n, img, DispImage); ////在DispImage的（m,n）位置开始显示Image
	}
	// End the number of arguments
	va_end(args);

	namedWindow(title);
	imshow(title, DispImage);
	waitKey(10);
}