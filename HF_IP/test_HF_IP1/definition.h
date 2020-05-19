#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#include "hls_video.h"
#include <ap_int.h>
#include <ap_fixed.h>

// I/O Image Settings
#define INPUT_IMAGE  "test_200_272p.jpg"
#define OUTPUT_IMAGE "result_test_200_272p.jpg"

typedef ap_axiu<24,1,1,1>	   stream_24;
typedef hls::stream<stream_24> AXI_STREAM;
typedef ap_ufixed <14,8> 	   floatC1;
typedef ap_uint<9> 		       uint_9;

void test_HF(AXI_STREAM& image_in, AXI_STREAM& image_out, ap_uint<8> minPixAvg,ap_uint<8> minPixStd,uint_9 rows, uint_9 cols);//,int minAvg,int minStd

#endif
