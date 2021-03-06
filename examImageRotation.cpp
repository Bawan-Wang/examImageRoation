#include <opencv2\opencv.hpp>
#include <time.h>
#include "rotate_image.h"

using namespace cv;
using namespace std;

int main()
{
	Mat matSrcImgCh3, matSplitCh3[3], matInputImg, matOutputImg;
	//matSrcImgCh3 = imread("Forest_gray.jpg");
	matSrcImgCh3 = imread("Lenna_gray.jpg");
	if (matSrcImgCh3.empty()) {
		return -1;
	}
	split(matSrcImgCh3, matSplitCh3);
	matInputImg = matSplitCh3[0].clone();
	
	BYTE *srcImg = NULL, *dstImg = NULL;
	int iSrcWidth, iSrcHeight, iDstWidth, iDstHeight;

	srcImg = matInputImg.data;
	iSrcWidth  = matInputImg.cols;
	iSrcHeight = matInputImg.rows;
	printf("Original size : %d x %d\n", iSrcWidth, iSrcHeight);

	for(int i = 0; i<360;i++){
//		double start, end, cost;
//		start = clock();
		dstImg = rotate_image(srcImg, iSrcWidth, iSrcHeight, i, &iDstWidth, &iDstHeight);
//		end = clock();
//		cost = end - start;
//		printf("%f\n", cost);
		if (NULL == dstImg) {
			return -1;
		}
		printf("New size : %d x %d\n", iDstWidth, iDstHeight);

		matOutputImg = Mat(iDstHeight, iDstWidth, CV_8UC1, dstImg);

		char tmpString[80];
		sprintf(tmpString, "./result/rotate_image%d.jpg", i);
		imwrite(tmpString, matOutputImg);
		matOutputImg.release();
		rotate_image_release(&dstImg);
	}
	matInputImg.release();

	system("PAUSE");
    return 0;
}