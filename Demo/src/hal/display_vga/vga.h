/**
*******************************************************************************
**
**  @file               vga.h
**  @brief              Vga module definition for vga controller management
**  @par				Detail description
**  					...
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


#ifndef VGA_H_
#define VGA_H_

/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "conf.h"
#include "color.h"
#include "new_types.h"

#include <stdint.h>

/******************************************************************************
**                     	DEFINITIONS AND MACROS                           	 **
******************************************************************************/
#define DISPLAY_NUM_FRAMES 		3

#define DISPLAY_MAX_FRAME 		(1200*1200)//(DISPLAY_W*DISPLAY_H)

#define VGA_BASEADDR 			XPAR_AXI_DISPCTRL_0_S_AXI_BASEADDR
#define HDMI_BASEADDR 			XPAR_AXI_DISPCTRL_1_S_AXI_BASEADDR

#define VGA_VDMA_ID 			XPAR_AXIVDMA_0_DEVICE_ID
#define HDMI_VDMA_ID 			XPAR_AXIVDMA_1_DEVICE_ID
#define DISPLAYDEMO_STRIDE 		(DISPLAY_WIDTH * 4)
#define UART_BASEADDR 			XPAR_PS7_UART_1_BASEADDR


/******************************************************************************
**             			TYPEDEFS AND STRUCTURES                         	 **
******************************************************************************/


/******************************************************************************
**                   	PUBLIC FUNCTIONS                               	     **
******************************************************************************/

int VGA_displayInit();
void VGA_stop(void);
void VGA_updateFrame();
void VGA_copyFrameBuffer();
void VGA_clearFrameBuffer();
void VGA_displayChar(int x0 , int y0 , char kar, color_t* color);
void VGA_displayRect(int x0, int y0 , int width , int height, color_t* color, bool_t fill);
void VGA_lineP2P(int x0, int y0 , int x1, int y1, color_t* color);


#endif /* _VGA_H_ */

/******************************************************************************
**                  	EOF                                      	         **
******************************************************************************/
