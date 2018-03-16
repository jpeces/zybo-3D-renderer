/**
*******************************************************************************
**
**  @file               vga.c
**  @brief              Vga module implementation for vga controller management
**  @par				Detail description
**						...
**
**  @version            0.1.0
**  @date               2017-11-15
**
*******************************************************************************
**
**  @author				Javier Peces
**  @copyright
**
*******************************************************************************
**
**  @par VERSION HISTORY
**  @par
**  Version  | Date        | Revised by        | Description
**  -------- | ----------- | ----------------- | ----------------------------
**  0.1.0    | 2017-11-15  | Javier Peces      | File creation
**
*******************************************************************************
**/

#define VGA_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "vga.h"
#include "font8x8.h"
#include "display_ctrl.h"
#include "xil_cache.h"

#include <math.h>


/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/


/******************************************************************************
**                      PROTOTYPES OF LOCAL FUNCTIONS                        **
******************************************************************************/


/******************************************************************************
**                      GLOBAL VARIABLES                                 	 **
******************************************************************************/
DisplayCtrl vgaCtrl;

u32 vgaBuf[DISPLAY_NUM_FRAMES][DISPLAY_MAX_FRAME];
u32 frameBuffer[DISPLAY_MAX_FRAME];

/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/

/**
*******************************************************************************
* @brief   VGA_displayInit
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      int		'0' if the initialization was success or '1' if it's not.
*******************************************************************************
**/
int VGA_displayInit(){
	int status = 0;

	#if(DISPLAY_MODE == 0)
		status = DisplayInitialize(&vgaCtrl, HDMI_VDMA_ID, HDMI_BASEADDR, DISPLAY_HDMI, vgaBuf[0], DISPLAYDEMO_STRIDE);
	#endif

	#if(DISPLAY_MODE == 1)
		status = DisplayInitialize(&vgaCtrl, VGA_VDMA_ID, VGA_BASEADDR, DISPLAY_NOT_HDMI, vgaBuf[0], DISPLAYDEMO_STRIDE);
	#endif

	if (status != XST_SUCCESS)
	{
		xil_printf("Display Ctrl initialization failed during demo initialization%d\r\n", status);
		return XST_FAILURE;
	}

	status = DisplayStart(&vgaCtrl);
	if (status != XST_SUCCESS)
	{
		xil_printf("Couldn't start display during demo initialization%d\r\n", status);
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

/**
*******************************************************************************
* @brief   VGA_Stop
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void VGA_stop(void) {
	DisplayStop(&vgaCtrl);
}

/**
*******************************************************************************
* @brief   VGA_updateFrame
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void VGA_updateFrame(void){
	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAY_MAX_FRAME * 4);
}

/**
*******************************************************************************
* @brief   VGA_clearFrameBuffer
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void VGA_clearFrameBuffer(void) {
	memset(&frameBuffer, 0, sizeof(frameBuffer));
}

/**
*******************************************************************************
* @brief   VGA_copyFrameBuffer
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void VGA_copyFrameBuffer(void){
	int height_limit = vgaCtrl.vMode.height;
	int width_limit = vgaCtrl.vMode.width;

	memcpy(vgaBuf[0], frameBuffer, sizeof(u32) * height_limit * width_limit);
}

/**
*******************************************************************************
* @brief   VGA_displayChar
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void VGA_displayChar(int x0 , int y0 , char kar, color_t* color){
	u32 iPixelAddr;
	u32 x;
	int i = 0;
	char line = 0;
	char auxByte = 0;

	u32 wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
	u32 wColor = ((u32) color->red << BIT_DISPLAY_RED) | ((u32) color->blue << BIT_DISPLAY_BLUE) | ((u32) color->green << BIT_DISPLAY_GREEN);

	for (i = 0 ; i < 8 ; i++){
		line = font8x8_basic[(int)kar][i];
		for(x = 0 ; x <8; x++){
			auxByte = line & (0x01<<x);
			if ( auxByte > 0){
				iPixelAddr = (x0+x) +  (  (y0 + i ) * wStride ) ;
				frameBuffer[iPixelAddr] = wColor;
			}
		}
	}
}

/**
*******************************************************************************
* @brief   VGA_displayRect
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void VGA_displayRect(int x0, int y0 , int width , int height, color_t* color, bool_t fill) {
	u32 iPixelAddr;
	u32 x, y;

	u32 wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
	u32 wColor = ((u32) color->red << BIT_DISPLAY_RED) | ((u32) color->blue << BIT_DISPLAY_BLUE) | ( (u32) color->green << BIT_DISPLAY_GREEN);

	if(fill){
		for(y = y0; y < y0+height; y++){
			for(x = x0; x < x0+width ; x++){
				iPixelAddr = x + (y*wStride);
				frameBuffer[iPixelAddr] = wColor;
			}
		}
	}else{
		VGA_lineP2P(x0, y0, x0+width, y0, color);
		VGA_lineP2P(x0, y0, x0, y0+height, color);
		VGA_lineP2P(x0, y0+height, x0+width, y0+height, color);
		VGA_lineP2P(x0+width, y0, x0+width, y0+height, color);
	}
}

/**
*******************************************************************************
* @brief   VGA_lineP2P
* @par 	   Detail description
*              ...
*
* @param
* @return
*******************************************************************************
**/
void VGA_lineP2P(int x0, int y0 , int x1, int y1, color_t* color ){
	u32 iPixelAddr;
	u32 x, y;
	float malda=0;
	int aux = 0;

	u32 wStride = vgaCtrl.stride / 4; 	/* Find the stride in 32-bit words */
	u32 wColor = ((u32) color->red << BIT_DISPLAY_RED) | ((u32) color->blue << BIT_DISPLAY_BLUE) | ( (u32) color->green << BIT_DISPLAY_GREEN);

	if (x1 < x0){
		aux = x0;
		x0=x1;
		x1=aux;
		aux = y0;
		y0=y1;
		y1=aux;
	}

	if(x1 != x0){
		malda= (float)(y1-y0)/(float)(x1-x0);
		for(x = x0 ; x < x1; x++){
			iPixelAddr = x +  (  (y0 +  (int)( (x-x0) * malda ) ) * wStride ) ;
			frameBuffer[iPixelAddr] = wColor;
		}
	}else{
		for(x = x0; x <= x1; x++){
			iPixelAddr = x + (y0*wStride);
			for(y = y0; y < y1; y++) {
				frameBuffer[iPixelAddr] = wColor;
				iPixelAddr += wStride;
			}
		}
	}
}

/******************************************************************************
**                      LOCAL FUNCTIONS                                  	 **
******************************************************************************/


/******************************************************************************
**                      EOF				                                     **
******************************************************************************/




