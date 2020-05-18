/*****************************************************************************/
/**
 *
 * @file vdma.c
 * Author: Salil Tembe
 * This file comprises sample application to  usage of VDMA APi's in vdma_api.c.
 *  .
 *
 * ***************************************************************************/

/*** Include file ***/
#include "vdma.h"
#include "vdma_api.h"
#include "xv_tpg.h"
#include <stdlib.h>
#include "xpainter.h"
//#include "ximage_filter.h"

#define VDMA0_BASE XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x1000000
#define VDMA1_BASE VDMA0_BASE+0x1000000
#define FRAME_HEIGHT 720
#define FRAME_WIDTH 1280
#define PIXEL_DEPTH 8
#define COLOUR_CHANNELS 3
#define FRAME_SIZE FRAME_HEIGHT * FRAME_WIDTH * COLOUR_CHANNELS

/* TPG Instance */
XV_tpg TPG;

/* TPG Config */
XV_tpg_Config *tpgConfig;

/* Painter */
XPainter_Config *painterConfig;
XPainter Painter;


extern unsigned char rawData[2764800];
int main(){
	int i;
	Xil_DCacheDisable();
	xil_printf("\n--- Entering main() --- \r\n");
	int Status;
	XAxiVdma InstancePtr,InstancePtr_1;

	xil_printf("Starting the first VDMA and TPG \n\r");

	tpgConfig = XV_tpg_LookupConfig(XPAR_V_TPG_0_DEVICE_ID);
	XV_tpg_CfgInitialize(&TPG, tpgConfig, tpgConfig->BaseAddress);
	XV_tpg_Set_height(&TPG, FRAME_HEIGHT);
	XV_tpg_Set_width(&TPG, FRAME_WIDTH);
	XV_tpg_Set_bckgndId(&TPG, XTPG_BKGND_RAINBOW_COLOR);
	XV_tpg_EnableAutoRestart(&TPG);
	XV_tpg_Start(&TPG);

	XPainter_Initialize(&Painter, XPAR_XPAINTER_0_DEVICE_ID);
	XPainter_EnableAutoRestart(&Painter);
	XPainter_Start(&Painter);

	for(i = 0; i < 3; i++){
		memcpy((void*)(VDMA1_BASE+i*FRAME_SIZE), rawData, FRAME_SIZE);
	}

	Status = run_triple_frame_buffer(&InstancePtr,0,FRAME_WIDTH,FRAME_HEIGHT,VDMA0_BASE,100,0);
	if (Status != XST_SUCCESS){
		xil_printf("Transfer of frames failed with error = %d\r\n",Status);
		return XST_FAILURE;
	}
	else
	{
		xil_printf("Transfer of frames started \r\n");
	}
	xil_printf("Starting the second VDMA \r\n");

	Status = run_triple_frame_buffer(&InstancePtr_1,1,FRAME_WIDTH,FRAME_HEIGHT,VDMA1_BASE,100,0);
	if (Status != XST_SUCCESS){
		xil_printf("Transfer of frames failed with error = %d\r\n",Status);
		return XST_FAILURE;
	}
	else
	{
		xil_printf("Transfer of frames started \r\n");
	}


	/* Infinite while loop to let it run */
	while(1){

	}
}
