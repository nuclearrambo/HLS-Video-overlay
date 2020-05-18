/******************** Include files **********************************/

/*****************************************************************************
*
* run_triple_frame_buffer API
*
* This API is the interface between application and other API. When application will call
* this API with right argument, This API will call rest of the API to configure the read
* and write path of VDMA,based on ID. After that it will start both the read and write path
* of VDMA
*
* @return
*		- XST_SUCCESS if example finishes successfully
*		- XST_FAILURE if example fails.
*
* @Argument
* 		- InstancePtr:		The handle to XAxiVdma data structure.
* 		- DeviceId:			The device ID of current VDMA
* 		- hsize:			The horizontal size of the frame. It will be in Pixels.
* 							The actual size of frame will be calculated by multiplying this
* 							with tdata width.
* 		-vsize:				Vertical size of the frame.
* 		-buf_base_addr:		The buffer address where frames will be written and read by VDMA
* 		-number_frame_count:If application needs interrupt on frame processing, this variable
* 							will tell after how many frames interrupt should come.
* 		-enable_frm_cnt_intr: Enable frame count interrupt.
*
******************************************************************************/

int run_triple_frame_buffer(XAxiVdma* InstancePtr, int DeviceId, int hsize,\
		int vsize, int buf_base_addr, int number_frame_count, int enable_frm_cnt_intr);
