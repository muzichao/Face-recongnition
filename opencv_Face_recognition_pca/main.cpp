#include <iostream>
#include <highgui.h>
#include <algorithm>
#include "inPutimgs.h"
#include "matCov.h"
#include "avgFacemat.h"
#include "findMaxnums.h"
#include "pickUpeignvectorn.h"
#include "computeThreshold.h"
#include "distinguishFaces.h"

using namespace std;
using namespace cv;
// 注意matlab中矩阵是按列优先存储，而c中矩阵按行优先存储
// 因此matlab和opencv的reshape会不相同
int main()
{
	int N = 40; // 40个人
	int M = 8; // 每个人对应8幅图
	int rows = 112; // 图像的行
	int cols = 92; // 图像的列
	int numRight = 0; // 准确识别数
	int numWrong = 0; // 错误识别数
	Mat X_img(N*M, rows*cols, CV_32F, Scalar(0.0));
	Mat X_img_mean(1, rows*cols, CV_32F, Scalar(0.0));
	Mat A_mat; // 差值脸
	Mat C_mat; // 协方差矩阵
	Mat S; // 特征值25*1 U*S*VT=
	Mat U; //svd分解的U
	Mat VT; //svd分解的v的转置
	int maxeignValuenums = 0; // 最大的x%个特征值的个数
	float eignValuepercent = 0.99f; // 最大的几个特征值的百分比
	Mat eignVectorn; // 存放最大的若干个特征向量
	Mat omiga_mat; // 将训练的人脸与平均脸的差值投影到特征空间
	float threshold_omiga = 0.0f;
	int flag_Y_N = 0; // 标记检测的相似人脸的个数

	double duration;
	duration = static_cast<double>(getTickCount());

	X_img = inPutimgs(N, M, rows, cols); //每一行对应一个人的一幅图
	reduce(X_img, X_img_mean, 0, CV_REDUCE_AVG); // 按列平均，缩减为一行
	A_mat = avgFacemat(X_img, X_img_mean); // 求差值脸 
	C_mat = matCov(A_mat, M, N); // 计算协方差矩阵
	SVDecomp(C_mat, S, U, VT,SVD::FULL_UV);  //SVD分解 ，后面的FULL_UV表示把U和VT补充称单位正交方阵;

	maxeignValuenums = findMaxnums(S, eignValuepercent); // 求最大的若干个特征值的个数
	cout << "maxeignValuenums=" << maxeignValuenums << endl;

	eignVectorn = pickUpeignvectorn(A_mat, VT, S, maxeignValuenums); // 保存最大的几个特征值对应的特征向量

	omiga_mat = eignVectorn.t() * A_mat.t(); // 将训练的人脸与平均脸的差值投影到特征空间

	threshold_omiga = computeThreshold(omiga_mat); // 计算阈值
	// cout << "threshold_omiga=" << threshold_omiga << endl;

	for (int i = 9; i <= 10; i++)
	{
		for (int j = 1; j <= 40; j++)
		{
			flag_Y_N=distinguishfaces(X_img_mean, eignVectorn, omiga_mat, threshold_omiga, rows, cols, j, i); // 识别函数
			if (1 == flag_Y_N)
			{
				numRight++;
			}
			else if (2 == flag_Y_N)
			{
				numWrong++;
			}

		}
	}
	cout << "准确识别效率为：" << numRight / 80.0 << endl;
	cout << "错误识别效率为：" << numWrong / 80.0 << endl;

	duration = static_cast<double>(getTickCount())-duration;
	duration = duration / getTickFrequency();
	cout << "运行时间为：" << duration << "s" <<endl;

	Sleep(20000);
	waitKey(0);
}