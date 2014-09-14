/**
 *@brief 计算一个列向量矩阵中最大的若干个数，注意列向量已经按从大到小排列
 *@param[in] Mat& _eignValues：输入的列向量矩阵 float _percent：最大的几个数的百分比
 *@param[out]
 *@return    _eignValues Mat型  CV_32F
 *@pre       输入的Mat型数据必须是单通道CV_32F型的
 *@post      输出的int型，个数
 *@code
   Mat X_img(100, 1, CV_32F, Scalar(0.0));
   X_img = 。。。;
   int out;
   out=findMaxnums(Mat& _eignValues, float _percent);
 *@endcode

 *@since 2013.10.20
 *@author lichao
*/
#include "findMaxnums.h"

int findMaxnums(Mat _eignValues, float _percent)
{
	if(_eignValues.depth() != 5)
	{
		cout << "请输入正确的Mat数值类型！" << endl;
		Sleep(2000);
		exit(-1);
	}

	Mat sumEignvalueall; // 所有特征值的和
	Mat _eignValues_mid; // 中间变量
	float sumEignvaluen = 0; // 前若干个特征值的和
	int maxNumsn = 0; // 最大的_percent个特征值的个数

	// _eignValues_mid = _eignValues.mul(_eignValues); // _eignValues中是特征值开根号后的值，此处点乘
	reduce(_eignValues, sumEignvalueall, 0, CV_REDUCE_SUM); // 按列求和
	for (int i=0; i<_eignValues.rows; i++)
	{
		maxNumsn += 1;
		sumEignvaluen += _eignValues.at<float>(i);
		if(sumEignvaluen >= sumEignvalueall.at<float>(0) * _percent)
		{
			i = _eignValues.rows;
		}
	}
	//cout << sumEignvalueall << endl;
	//cout << sumEignvaluen << endl;
	return maxNumsn;
}
