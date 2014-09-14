/**
 *@brief 计算每一行与行平均值的差值
 *@param[in] Mat& _X_img：行向量矩阵 Mat& _X_img_mean：所有行求平均
 *@param[out]
 *@return    avgMat Mat型  CV_32F
 *@pre       输入的Mat型数据必须是单通道CV_32F型的
 *@post      输出的Mat型数据是单通道CV_32F型的
 *@code
   Mat X_img(25, 1000, CV_32F, Scalar(0.0));
   Mat X_img_mean;
   randu(X_img, Scalar::all(0.0), Scalar::all(1.0));
   reduce(X_img, X_img_mean, 0, CV_REDUCE_AVG); // 按列平均，缩减为一行
   Mat out;
   out=avgFacemat(X_img, X_img_mean);
 *@endcode

 *@since 2013.10.20
 *@author lichao
*/
#include "avgFacemat.h"

Mat avgFacemat(Mat _X_img, Mat _X_img_mean)
{
	// _X_img 每一行对应一个人脸
	Mat avgMat(_X_img.rows, _X_img.cols, CV_32F, Scalar(0.0));
	Mat imgRoi;
	Mat midMat;
	for (int i=0; i<_X_img.rows; i++)
	{
		imgRoi = _X_img(Rect(0, i, _X_img.cols, 1)); // 提取一行
		avgMat(Rect(0, i, _X_img.cols, 1)) = imgRoi - _X_img_mean;// 每一行减去行平均值
		//cout<<imgRoi.at<float>(i,0)<<endl;
		//cout<<imgRoi.at<float>(i,1)<<endl;
	}
	return avgMat;
}
