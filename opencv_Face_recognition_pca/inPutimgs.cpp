/**
*@brief 读入若干幅RGB图像，然后转换为灰度图像，并保存，每幅图像保存为一行
*@param[in] int N， int M：确定读入图像个数， int rows，int cols：确定读入图像大小
*@param[out]
*@return    float_img Mat型  CV_32FC3
*@pre       输入的Mat型数据必须是三通道CV_8U型的
*@post      输出的Mat型数据是单通道CV_32F型的
*@code
Mat test_img(25, 10000, CV_8U, Scalar(0));
test_img=inPutimgs(5, 5, 100, 100);
*@endcode

*@since 2013.10.20
*@author lichao
*/
#include "inPutimgs.h"

Mat inPutimgs(int _N, int _M, int _rows, int _cols)
{
	char pathNames[100]; // 保存读入图像的路径
	Mat imagergb(_rows, _cols, CV_8U, Scalar(0, 0, 0)); // 读入的RGB图
	Mat imagegray(_rows, _cols, CV_8U, Scalar(0)); // 读入的RGB图转换为灰度图
	Mat imagegrayt(_rows, _cols, CV_8U, Scalar(0)); // 图像反转，是为了读入数据是与matlab保持一致，可删去
	Mat imagegray_f(_rows, _cols, CV_32F, Scalar(0.0)); // uchar图保存为float图，保持计算精度
	Mat outImg(_N * _M, _rows * _cols, CV_32F, Scalar(0.0)); // 输出的图像矩阵
	Mat imgROI; // 输出图像的感兴趣区域

	for (int i = 1; i <= _N; i++)
	{
		for (int j = 1; j <= _M; j++)
		{
			sprintf_s(pathNames, "D:\\Document\\vidpic\\人脸图像\\训练\\orl_%d_%d.bmp", i, j);
			imagergb = imread(pathNames); // 读入rgb图像
			if(!imagergb.data)
			{
				cout << "未找到指定的图像！" << endl;
				Sleep(2000);
				exit(0);
			}
			cvtColor(imagergb, imagegray, CV_BGR2GRAY); //rgb2gray
			imagegrayt = imagegray.t(); // 图像反转，是为了读入数据是与matlab保持一致，可删去
			imagegrayt.convertTo(imagegray_f, CV_32F, 1.0, 0.0); // uchar to float
			normalize(imagegray_f, imagegray_f, 1.0, 0.0, NORM_INF); // 用最大值归一化

			//将每一幅图像拉成一行，依次存储在outImg中
			imgROI = outImg(Rect(0, (i - 1) * _M + j - 1, _rows * _cols, 1)); // 选择感兴趣区域
			imagegray_f.reshape(1, 1).copyTo(imgROI); // 图像拉成一行，并保存在感兴趣区域

			//cout << i << "_" << j << endl;
			//namedWindow("test");
			//imshow("test",imagegray);
			//waitKey(10);
		}
	}
	return outImg;
}
