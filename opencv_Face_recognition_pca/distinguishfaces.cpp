/**
 *@brief 根据参数读入图像，并根据训练所得的数据进行识别
 *@param[in] 
 *@param[out]
 *@return    
 *@pre       
 *@post      
 *@code

 *@endcode

 *@since 2013.10.22
 *@author lichao
*/
#include "distinguishFaces.h"
int distinguishfaces(Mat _X_img_mean, Mat _eignVectorn, Mat _omiga_mat, float _threshold_omiga, int rows, int cols, int i, int j)
{
	char pathNames[100]; // 要识别的图像的路径名
	char windowsName[50]; // 显示图像的窗口名字
	Mat imagergb(rows, cols, CV_8U, Scalar(0,0,0)); // 读入的RGB图像
	Mat imagergb_dis(rows, cols, CV_8U, Scalar(0,0,0)); // 识别出的图像

	Mat imagegray(rows, cols, CV_8U, Scalar(0)); // 读入的RGB图像转灰度图
	Mat imagegrayt(rows, cols, CV_8U, Scalar(0)); // 图像转置，是为了读入数据是与matlab保持一致，可删去
	Mat imagegray_f(rows, cols, CV_32F, Scalar(0.0));// uchar to float
	Mat omiga_matx; // 投影到特征空间所对应的特征向量
	Mat omiga_matx_mid; // 中间变量
	Mat _omigaRoi;
	float sigma_x; // 待识别的人脸与训练集中人脸在特征空间的欧式距离
	int ix = 1;
	int iy = 1;
	int flag_Y_N = 0; // 标记检测到图像的个数
	int mark_k = 0;       // 标记检测到哪个人脸


	sprintf_s(pathNames, "D:\\Document\\vidpic\\人脸图像\\测试\\orl_%d_%d.bmp", i, j);

	imagergb = imread(pathNames); // 读入rgb图像
	if(!imagergb.data)
	{
		cout << "未找到指定的图像！" << endl;
		Sleep(2000);
		exit(0);
	}

	cvtColor(imagergb, imagegray, CV_BGR2GRAY); // rgb2gray
	imagegrayt = imagegray.t(); // 图像转置
	imagegrayt.convertTo(imagegray_f, CV_32F, 1.0, 0.0); // uchar to float
	normalize(imagegray_f, imagegray_f, 1.0, 0.0, NORM_INF); // 归一化
	imagegray_f = imagegray_f.reshape(1,1); // 将每一幅图像拉成一行
	// 待识别的人脸与平均脸的差值投影到特征空间所对应的特征向量
	omiga_matx = _eignVectorn.t() * (imagegray_f - _X_img_mean).t(); 

	for (int k = 0; k < _eignVectorn.cols; k++)
	{
		_omigaRoi = _omiga_mat(Rect(k, 0, 1, _omiga_mat.rows));
		omiga_matx_mid = omiga_matx - _omigaRoi;
		sigma_x = norm(omiga_matx_mid, NORM_L2); // 待识别的人脸与训练集中人脸在特征空间的欧式距离
		if (sigma_x < _threshold_omiga)
		{
			_threshold_omiga = sigma_x;
			mark_k = k + 1;
		}

	}
	if (mark_k != 0)
	{
		ix = int((mark_k - 0.5) / 8); // 找到在训练集中对应的人脸
		iy = mark_k - ix * 8;
		sprintf_s(pathNames, "D:\\Document\\vidpic\\人脸图像\\训练\\orl_%d_%d.bmp", ix + 1, iy);
		imagergb_dis = imread(pathNames);

		cout <<"待识别图像:\t" << i << "_" << j << endl;
		cout <<"检测到的图像:\t" << ix + 1 << "_" << iy << endl;
		if(i == (ix+1))
		{
			cout << "检测正确！\n"<<endl;
			flag_Y_N = 1;
		}
		else
		{
			cout << "检测不正确！\n"<<endl;
			flag_Y_N = 2;
		}

		//sprintf_s(windowsName, "图%d_%d的检测结果！", i, j);
		//dispManyimgs(windowsName, 2, imagergb, imagergb_dis); // 在一个窗口中显示图像
	}
	return flag_Y_N;
}
