/**
 *@brief 计算矩阵的任意两列的差值的二范数，并返回最大值
 *@param[in] Mat& _Omiga 列向量矩阵
 *@param[out]
 *@return    float threshold_omiga 
 *@pre       输入的Mat型数据必须是单通道CV_32F型的
 *@post      输出的float
 *@code
   Mat X_img(25, 30, CV_32F, Scalar(0.0));
   randu(X_img, Scalar::all(0.0), Scalar::all(1.0));
   float out;
   out=computeThreshold(Mat& _Omiga);
 *@endcode

 *@since 2013.10.21
 *@author lichao
*/
#include "computeThreshold.h"

float computeThreshold(Mat _Omiga)
{
	float threshold_omiga = 0;
	float mid_par = 0;
	Mat colRoi1; // 矩阵的第i列
	Mat colRoi2; // 矩阵的第j列
	Mat colRoi;  // 矩阵的第j列-第i列

	for (int i = 0; i < _Omiga.cols; i ++)
	{
		colRoi1 = _Omiga(Rect(i, 0, 1, _Omiga.rows)); // 取第i列
		for (int j = 0; j < _Omiga.cols; j++)
		{
			colRoi2 = _Omiga(Rect(j, 0, 1, _Omiga.rows)); // 取第j列
			colRoi = colRoi2 - colRoi1; // i列-j列
			mid_par = norm(colRoi, NORM_L2)/2; //求2范数并除以2
			if(mid_par > threshold_omiga)
			{
				threshold_omiga = mid_par; // 找到最大值
			}
		}
	}	
	return threshold_omiga;
}
