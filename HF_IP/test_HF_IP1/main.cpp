#include "definition.h"

void test_HF(AXI_STREAM& image_in, AXI_STREAM& image_out,ap_uint<8> minPixAvg,ap_uint<8> minPixStd,uint_9 rows, uint_9 cols) //,int minAvg,int minStd
{
#pragma HLS INTERFACE axis port=image_in
#pragma HLS INTERFACE axis port=image_out
#pragma HLS INTERFACE s_axilite port=minPixAvg bundle=CNTRL_BUS
#pragma HLS INTERFACE s_axilite port=minPixStd bundle=CNTRL_BUS
#pragma HLS INTERFACE s_axilite port=cols bundle=CNTRL_BUS
#pragma HLS INTERFACE s_axilite port=rows bundle=CNTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CNTRL_BUS

	ap_uint<8> min_pix = 255;
	floatC1 LMSF = 0, etaMSF=1.6, V = 0.975, etaHD=2.5, Con1 = 0.27, Con2 = 0.67, Con3 = 0.06,tHD, tMSF,offsetHD,offsetMSF;
	float phiz;

//	tHD = (floatC1)minAvg + etaHD*(floatC1)minStd;
//	tMSF = (floatC1)minAvg + etaMSF*(floatC1)minStd;
	tHD = minPixAvg + etaHD*minPixStd;
	tMSF = minPixAvg + etaMSF*minPixStd;
	// Iterate on a stream of (320*240)
	loop: for (int idxPixel = 0; idxPixel < (rows*cols); idxPixel++)
	{
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=100 max=200000
		stream_24  pixel_in;
		pixel_in = image_in.read();
		ap_uint<8> rp = pixel_in.data>>16;
		ap_uint<8> gp = pixel_in.data>>8;
		ap_uint<8> bp = pixel_in.data;

		if(rp < min_pix) min_pix = rp;
		if(bp < min_pix) min_pix = bp;
		if(gp < min_pix) min_pix = gp;

		if (min_pix>tHD) offsetHD = tHD;
		else offsetHD = min_pix;

		if (offsetHD > 2*minPixAvg)
		{
			if (min_pix> tMSF) offsetMSF = tMSF;
			else offsetMSF = min_pix;

			rp -=  min_pix;
			rp += offsetMSF;///IMSF_red
			gp -=  min_pix;
			gp += offsetMSF;///IMSF_green
			bp -=  min_pix;
			bp += offsetMSF;///IMSF_blue

			LMSF += (Con1*rp + Con2*gp + Con3*bp);
			floatC1 Con4= 1, Con5 =14, Con6 =1.6, Con7 =255;
			phiz = (float)Con4 + expf(-(float)Con5*expf((float)Con6*logf((float)LMSF/(float)Con7)));//phi

			rp = rp*phiz*(float)V;/// V= 1.025f
			gp = gp*phiz*(float)V;/// V= 1.025f
			bp = bp*phiz*(float)V;/// V= 1.025f
		}
		ap_uint<24> pixelout = rp;
		pixelout = pixelout<<16;
		ap_uint<24> pixelout1 = gp;
		pixelout1 = pixelout1<<8;
		ap_uint<24> pixelout2 = bp;
		pixelout = pixelout|pixelout1|pixelout2;


		min_pix = 255;
		LMSF -= LMSF;
		stream_24  pixel_out;

		// Put data on output stream (side-channel(tlast) way...)
		pixel_out.data = pixelout;
//		pixel_out.data = pixel_in.data;
		pixel_out.keep = pixel_in.keep;
		pixel_out.strb = pixel_in.strb;
		pixel_out.user = pixel_in.user;
		pixel_out.last = pixel_in.last;
		pixel_out.id = pixel_in.id;
		pixel_out.dest = pixel_in.dest;

		image_out.write(pixel_out);

	}

}
