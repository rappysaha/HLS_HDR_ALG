#include "definition.h"
#include <hls_opencv.h>
//#include <opencv2/opencv.hpp>

//float doavg (AXI_STREAM input,AXI_STREAM output, int height, int width, float avg);
//float dostd (stream_24 input, float avg, float std);
//void IplImage2hlsMat( IplImage* img, hls::Mat<ROWS, COLS, T>& mat );
//void hls::Split( hls::Mat<ROWS, COLS, SRC_T>& src,
//                 hls::Mat<ROWS, COLS, DST_T>& dst0,
//                 hls::Mat<ROWS, COLS, DST_T>& dst1,
//                 hls::Mat<ROWS, COLS, DST_T>& dst2 );
int main()
{
	AXI_STREAM inputStream, outputStream;
	ap_uint<8> avg =30, std = 22;

	IplImage* imageSrc = cvLoadImage(INPUT_IMAGE);
	IplImage* imgdst = cvCreateImage(cvGetSize(imageSrc), imageSrc->depth, imageSrc->nChannels);
	printf("Image row:%d Cols:%d\n", imageSrc->height, imageSrc->width);

	uint_9 rows = imageSrc->height;
	uint_9 cols = imageSrc->width;

	IplImage2AXIvideo(imageSrc,inputStream);
//	stream_24  pixel_in;
//	pixel_in = inputStream.read();

//	doavg (inputStream, outputStream1, imageSrc->height, imageSrc->width, average);
//	printf("average:%f\n", average);

	test_HF(inputStream, outputStream,avg,std,rows,cols);
	AXIvideo2IplImage(outputStream, imgdst);
	cvSaveImage(OUTPUT_IMAGE,imgdst);

	return 0;
}


//float doavg (AXI_STREAM input,AXI_STREAM output, int height, int width, float avg){
//	ap_uint<8> min_pix = 255;
//	float sum = 0;
//	stream_24  pixel_in;
//	stream_24  pixel_out;
//	pixel_in = input.read();
//	for (int idxPixel = 0; idxPixel < (height*width); idxPixel++){
//		ap_uint<8> rp = pixel_in.data>>16;
//		ap_uint<8> gp = pixel_in.data>>8;
//		ap_uint<8> bp = pixel_in.data;
//
//		if(rp < min_pix) min_pix = rp;
//		if(bp < min_pix) min_pix = bp;
//		if(gp < min_pix) min_pix = gp;
//
//		sum += min_pix;
//		if (idxPixel==(height*width)-1) avg = sum /(height*width);
//		min_pix = 255;
//
//		pixel_out.data = pixel_in.data;
//		pixel_out.keep = pixel_in.keep;
//		pixel_out.strb = pixel_in.strb;
//		pixel_out.user = pixel_in.user;
//		pixel_out.last = pixel_in.last;
//		pixel_out.id = pixel_in.id;
//		pixel_out.dest = pixel_in.dest;
//
//		output.write(pixel_out);
//	}
//
//}
