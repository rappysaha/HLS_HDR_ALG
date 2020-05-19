#include <stdio.h>
#include <iostream>
#include "core.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <hls_opencv.h>
#include <math.h>

using namespace std;




int main()
{
	int row, col;
	ap_uint<8> avg =30;
//	float a=0.04f, Sq_Lwhite = 0.3f;
//	float tHD,tMSF;
//	float avgLhf;
	AXI_STREAM inputStream, outputStream;

	IplImage* imageSrc = cvLoadImage(INPUT_IMAGE);
	IplImage* imgdst = cvCreateImage(cvGetSize(imageSrc), imageSrc->depth, imageSrc->nChannels);
	printf("Image row:%d Cols:%d\n", imageSrc->height, imageSrc->width);
	row = imageSrc->height;
	col = imageSrc->width;

	IplImage2AXIvideo(imageSrc, inputStream);
	test_HDR_IP1(inputStream, outputStream, row, col, avg);//,a,Sq_Lwhite
//	printf("Average:%f", std);
//	printf("THD:%f", tHD);
//	printf("TMSF:%f", tMSF);
//	printf("Average LHF: %f", avgLhf);
	AXIvideo2IplImage(outputStream, imgdst);
	cvSaveImage(OUTPUT_IMAGE,imgdst);
	return 0;
}
