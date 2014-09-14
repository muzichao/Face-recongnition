/**
 *@brief 计算协方差矩阵，并除以（M*N）
 *@param[in] Mat& _matX：行向量矩阵 
 *@param[out]
 *@return    _matX Mat型  CV_32F
 *@pre       输入的Mat型数据必须是单通道CV_32F型的
 *@post      输出的Mat型数据是单通道CV_32F型的
 *@code
   Mat _matX(25, 1000, CV_32F, Scalar(0.0));
   int _M = 5;
   int _N = 5;

   Mat out;
   out=matCov(Mat& _matX, int _M, int _N);
 *@endcode

 *@since 2013.10.20
 *@author lichao
*/
#include "matCov.h"

Mat matCov(Mat _matX, int _M, int _N)
{
	return _matX * _matX.t() / (_M * _N);

}
