#ifndef _CORE_H_
#define _CORE_H_

#include "hls_video.h"

#define MAX_WIDTH  1280
#define MAX_HEIGHT 720

#define INPUT_IMAGE           "J:\\XilinxProjects\\VitisWorkspace3\\stream_mul\\test.bmp"
#define MASK_IMAGE            "J:\\XilinxProjects\\VitisWorkspace3\\stream_mul\\mask.bmp"
#define OUTPUT_IMAGE		  "J:\\XilinxProjects\\VitisWorkspace3\\stream_mul\\output.bmp"

typedef hls::stream<ap_axiu<24,1,1,1> >               AXI_STREAM_RGB;

typedef hls::Scalar<3, unsigned char>                 RGB_PIXEL;

typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3>     RGB_IMAGE;

void painter(AXI_STREAM_RGB &tpg, AXI_STREAM_RGB &mask, AXI_STREAM_RGB &painted);


#endif
