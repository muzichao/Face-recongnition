/**
 *@brief 计算协方差矩阵的特征向量
		 C = A*A'/(m*n);
		 [S, U, VT]=svd(C);
		 S:特征值的开平方
		 特征向量=1/Si*A*Vi
 *@param[in] Mat& _A_mat：A矩阵  Mat& _VT_mat：V矩阵的转置 
			 Mat& _eignValues：特征值的开根号  int _nums：要取的特征向量的个数
 *@param[out]
 *@return    eignVector_mat Mat型  CV_32F  特征向量矩阵
 *@pre       输入的Mat型数据必须是单通道CV_32F型的
 *@post      输出的Mat型数据是单通道CV_32F型的
 *@code
	int _nums=10;
	A = ...;
	C_mat = matCov(A, M, N); // 计算协方差矩阵
	SVDecomp(C, S, U, VT,SVD::FULL_UV);  //SVD分解 ，后面的FULL_UV表示把U和VT补充称单位正交方阵;
	Mat out;
	out = pickUpeignvectorn(Mat& A, Mat& VT, Mat& S, int _nums);
 *@endcode

 *@since 2013.10.21
 *@author lichao
*/
#include "pickUpeignvectorn.h"

Mat pickUpeignvectorn(Mat _A_mat, Mat _VT_mat, Mat _eignValues, int _nums)
{
	Mat eignVector_mat(_A_mat.cols, _nums, CV_32F, Scalar(0.0));
	Mat eignVectorRoi;
	Mat vtRoi;
	for (int i = 0; i < _nums; i++)
	{
		eignVectorRoi = eignVector_mat(Rect(i, 0, 1, _A_mat.cols)); // 输出的第i列，第i个特征向量
		vtRoi =_VT_mat.t()(Rect(i, 0, 1, _VT_mat.cols)); // VT_mat的第i列，第i个特征向量
		//cout << _eignValues.at<float>(i,0) << endl;
		eignVectorRoi = (1/sqrt(_eignValues.at<float>(i,0))) * _A_mat.t() * vtRoi;
	}
	return eignVector_mat;
}
