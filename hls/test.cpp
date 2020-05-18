#include <hls_stream.h>
#include <hls_video.h>
#include "core.hpp"
#include <hls_opencv.h>

int main(){
	AXI_STREAM_RGB tpgStream, maskStream, paintedStream;


	IplImage* testImage = cvLoadImage(INPUT_IMAGE);
	IplImage* maskImage = cvLoadImage(MASK_IMAGE);
	IplImage* paintedImage = cvCreateImage(cvGetSize(testImage), testImage->depth, testImage->nChannels);

	IplImage2AXIvideo(testImage, tpgStream);
	IplImage2AXIvideo(maskImage, maskStream);
	painter(tpgStream, maskStream, paintedStream);

	AXIvideo2IplImage(paintedStream, paintedImage);

	cvSaveImage(OUTPUT_IMAGE, paintedImage);
	cvReleaseImage(&testImage);
	cvReleaseImage(&maskImage);
	cvReleaseImage(&paintedImage);

	return 0;
}
