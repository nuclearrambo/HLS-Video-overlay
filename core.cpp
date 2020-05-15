#include <hls_video.h>
#include "core.hpp"

void painter(AXI_STREAM_RGB &tpgStream, AXI_STREAM_RGB &maskStream, AXI_STREAM_RGB &paintedStream){
#pragma HLS INTERFACE axis port=paintedStream bundle=OUT_STREAM
#pragma HLS INTERFACE axis port=maskStream bundle=MASK_STREAM
#pragma HLS INTERFACE axis port=tpgStream bundle=TPG_STREAM
#pragma HLS INTERFACE s_axilite port=return bundle=CONTORL_BUS


	RGB_IMAGE video_in(MAX_HEIGHT, MAX_WIDTH), mask_in(MAX_HEIGHT, MAX_WIDTH), painted_out(MAX_HEIGHT, MAX_WIDTH);
#pragma HLS dataflow

	hls::AXIvideo2Mat(tpgStream, video_in);
	hls::AXIvideo2Mat(maskStream, mask_in);
	hls::Mul(mask_in, video_in, painted_out);
	hls::Mat2AXIvideo(painted_out, paintedStream);
}
