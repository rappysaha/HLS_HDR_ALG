#include "core.h"

//float a, float Lwhite
void test_HDR_IP1(AXI_STREAM& image_in, AXI_STREAM& image_out, uint_9 rows, uint_9 cols,ap_uint<8> AvgLhf) {

#pragma HLS INTERFACE s_axilite port=return bundle=CNTRL_BUS
#pragma HLS INTERFACE s_axilite port=cols bundle=CNTRL_BUS
#pragma HLS INTERFACE s_axilite port=rows bundle=CNTRL_BUS
#pragma HLS INTERFACE s_axilite port=AvgLhf bundle=CNTRL_BUS
//#pragma HLS INTERFACE s_axilite port=a bundle=CNTRL_BUS
//#pragma HLS INTERFACE s_axilite port=Lwhite bundle=CNTRL_BUS
#pragma HLS INTERFACE axis port = image_in
#pragma HLS INTERFACE axis port = image_out


float a=0.04f, Lwhite = 0.3f;
floatC1 Lhf=0,  L=0,delta = 0.0039, Con1 = 0.27, Con2 = 0.67, Con3 = 0.06;


	loop: for (int idxPixel = 0; idxPixel < (rows*cols); idxPixel++)
	{
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=100 max=200000

		stream_24  pixel_in;
		pixel_in = image_in.read();

		ap_uint<8> rp = pixel_in.data>>16;
		ap_uint<8> gp = pixel_in.data>>8;
		ap_uint<8> bp = pixel_in.data;

		float Lhf1 = (delta +Con1*rp + Con2*gp + Con3*bp);

		float L = (a/(float)AvgLhf)*Lhf1;
		float n = (Lwhite*Lwhite);
		float d = L/n;
		float Ld = (L*(1+d))/(1+L);

		rp = (rp*Lhf1)/(255*Ld);
		gp = (gp*Lhf1)/(255*Ld);
		bp = (bp*Lhf1)/(255*Ld);

		ap_uint<24> pixelout = rp;
		pixelout = pixelout<<16;
		ap_uint<24> pixelout1 = gp;
		pixelout1 = pixelout1<<8;
		ap_uint<24> pixelout2 = bp;
		pixelout = pixelout|pixelout1|pixelout2;

		stream_24  pixel_out;

		pixel_out.data = pixelout;
		pixel_out.keep = pixel_in.keep;
		pixel_out.strb = pixel_in.strb;
		pixel_out.user = pixel_in.user;
		pixel_out.last = pixel_in.last;
		pixel_out.id = pixel_in.id;
		pixel_out.dest = pixel_in.dest;

		image_out.write(pixel_out);
	//		Lhf1 -= Lhf1;

	}
}


