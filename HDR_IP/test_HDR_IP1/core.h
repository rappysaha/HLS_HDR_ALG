#ifndef _CORE_H_
#define _CORE_H_

#include "hls_video.h"
#include "ap_int.h"
#include <ap_fixed.h>



// maximum image size
#define MAX_WIDTH  500
#define MAX_HEIGHT 400

// I/O Image Settings
#define INPUT_IMAGE           "trial12_idol_0808.png"
#define OUTPUT_IMAGE          "result_trial12_idol_0808.png"

// typedef video library core structures
typedef ap_axiu<24,1,1,1>	   stream_24;
typedef hls::stream<stream_24> AXI_STREAM;
typedef ap_uint<24> 		   uint_24;
typedef ap_uint<9>             uint_9;
typedef ap_ufixed <14,8> 	   floatC1;
typedef ap_ufixed <7,1> 	   floatC2;
typedef ap_ufixed <25,23> 	   floatC3;

//typedef ap_uint<10>            uint_20; //for rows*cols type

// top level function for HW synthesis
void test_HDR_IP1(AXI_STREAM& src_axi, AXI_STREAM& dst_axi, uint_9 rows, uint_9 cols, ap_uint<8> AvgLhf);
//,float a, float Lwhite



#endif
