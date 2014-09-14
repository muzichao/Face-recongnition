/**
 *@brief 在_DispImage的（_m, _n）位置开始显示_Image
 *@param[in] int _m,int _n：开始坐标  Mat _Image：待显示图像
			 Mat& _DispImage 整体图像区域
 *@param[out]
 *@return    _DispImage 修改过的整体图像
 *@pre       输入的Mat型数据
 *@post      输出的Mat型数据
 *@code
   Mat _DispImage(500, 500, CV_8UC3, Scalar(0, 0, 0));
   Mat _Image(100, 100, CV_8UC3, Scalar(255, 0, 0));
   int _m = 100;
   int _n = 100;
   _DispImage = showmnImage(int _m,int _n,Mat& _Image, Mat& _DispImage) ;

 *@endcode

 *@since 2013.10.21
 *@author lichao
*/
#include "showmnImage.h"

Mat showmnImage(int _m,int _n,Mat& _Image, Mat& _DispImage) 
{
	Mat imageROI;
	if((_m < 0) || (_m > _DispImage.cols - _Image.cols) || (_n < 0) || (_n > _DispImage.rows - _Image.rows))
	{
		cout << "参数输入错误！" << endl;
		_m = 0;
		_n = 0;
	}
	imageROI=_DispImage(Rect(_m,_n,_Image.cols,_Image.rows));
	_Image.copyTo(imageROI,_Image);
	return _DispImage;
}