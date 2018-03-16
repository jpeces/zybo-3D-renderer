/**
*******************************************************************************
**
**  @file               display.c
**  @brief              Display module implementation for rendering proposes
**  @par				Detail description
**						...
**
**  @version            0.1.0
**  @date               2017-11-21
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
**  0.1.0    | 2017-11-21  | Javier Peces      | File creation
**
*******************************************************************************
**/


#define DISPLAY_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "conf.h"
#include "display.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "vga.h"

#include <stdio.h>
#include <math.h>

/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/
#define ROT_INC				0.00003f

/******************************************************************************
**                   	GLOBAL VARIABLES                                 	 **
******************************************************************************/
/* hand reference position in the screen */
vec2_t pRef = { (float)DISPLAY_WIDTH/2, (float)DISPLAY_HEIGHT/2 };
vec3_t rotateVec = { 0.0f, 0.0f, 0.0f };

/******************************************************************************
**               		PROTOTYPES OF LOCAL FUNCTIONS                   	 **
******************************************************************************/
void DISPLAY_rotate3D(TRIANGLE3D_T* triangle);
void DISPLAY_triangle2D(TRIANGLE2D_T* triangle, color_t* color);

/******************************************************************************
**                  	PUBLIC FUNCTIONS                                  	 **
******************************************************************************/

/**
*******************************************************************************
* @brief   DISPLAY_init
* @par 	   Detail description
*              ...
*
* @param       mode(int)	initialization mode: HDMI or VGA
* @return      None
*******************************************************************************
**/
void DISPLAY_init() {
	VGA_displayInit();
}

void DISPLAY_stop(void) {
	VGA_stop();
}

/**
*******************************************************************************
* @brief   DISPLAY_clearFrame
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void DISPLAY_clearFrame(void) {
	VGA_clearFrameBuffer();
}

/**
*******************************************************************************
* @brief   DISPLAY_updateFrame
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void DISPLAY_updateFrame(void) {
	VGA_copyFrameBuffer();
	VGA_updateFrame();
}

/**
*******************************************************************************
* @brief   DISPLAY_printString
* @par 	   Detail description
*              ...
*
* @param       str(char*)		Pointer to the string we want to display
* @param       pos(vec2_t*)		vector with x and y position of the string
* @param       color(color_t*)	string color
*
* @return      None
*******************************************************************************
**/
void DISPLAY_printString(char* str, vec2_t* pos, color_t* color ) {
	int  i=0;

	while ((i < strlen(str)) && (str[i]!= '\0')){
		VGA_displayChar((int)pos->x +(i*8), (int)pos->y , str[i], color);
		i++;
	}
}
/**
*******************************************************************************
* @brief   DISPLAY_drawDataBox
* @par 	   Detail description
*              ...
*
* @param       pos(vec2_t*)		vector with x and y position of the DataBox
* @param       width(int)		DataBox width
* @param       height(int)		DataBox height
* @param       color(color_t*)	DataBox color
*
* @return      None
*******************************************************************************
**/
void DISPLAY_drawDataBox(vec2_t* pos, int width , int height, color_t* color) {
	VGA_displayRect((int)pos->x, (int)pos->y ,width ,height, color, FALSE);
}

/**
*******************************************************************************
* @brief   DISPLAY_drawStatusBar
* @par 	   Detail description
*              ...
*
* @param       pos(vec2_t*)		vector with x and y position of the StatusBar
* @param       width(int)		StatusBar width
* @param       height(int)		StatusBar height
* @param       color(color_t)	StatusBar color
*
* @return      None
*******************************************************************************
**/
void DISPLAY_drawStatusBar(vec2_t* pos, int width , int height, color_t* color) {

}

/**
*******************************************************************************
* @brief   DISPLAY_drawApplied
* @par 	   Detail description
*              ...
*
* @param       pos(vec2_t*)		vector with x and y position of the rectangle
* @param       width(int)		rectangle width
* @param       height(int)		rectangle height
* @param       color(color_t*)	rectangle color
*
* @return      None
*******************************************************************************
**/
void DISPLAY_drawApplied(vec2_t* pos, int width , int height, color_t* color) {
	VGA_displayRect(((int)pos->x-3), (int)pos->y-5 ,width , height, color, FALSE);
}

/**
*******************************************************************************
* @brief   DISPLAY_drawSelector
* @par 	   Detail description
*              ...
*
* @param       pos(vec2_t*)		vector with x and y position of the option selected
* @param       width(int)		option width
* @param       height(int)		option height
* @param       color(color_t*)	selector color
*
* @return      None
*******************************************************************************
**/
void DISPLAY_drawSelector(vec2_t* pos, int width , int height, color_t* color) {
	VGA_displayRect((int)pos->x-25, (int)pos->y, width, height, color, TRUE);
}

/**
*******************************************************************************
* @brief   DISPLAY_drawHandShape
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void DISPLAY_drawElements(const float* data, const unsigned int* indices, unsigned int count, color_t* color, int rot) {
	int stride = 3; 		/* 3D vertices */
	vec2_t p1, p2, p3;

	for(int i = 0; i < count; i += stride) {
		vec3_t v1 = {
				-(float)*(data + indices[i]*stride + 0)+0.5,
				-(float)*(data + indices[i]*stride + 1)+0.5,
				-(float)*(data + indices[i]*stride + 2)+0.5
		};

		vec3_t v2 = {
				-(float)*(data + indices[i+1]*stride + 0)+0.5,
				-(float)*(data + indices[i+1]*stride + 1)+0.5,
				-(float)*(data + indices[i+1]*stride + 2)+0.5
		};

		vec3_t v3 = {
				-(float)*(data + indices[i+2]*stride + 0)+0.5,
				-(float)*(data + indices[i+2]*stride + 1)+0.5,
				-(float)*(data + indices[i+2]*stride + 2)+0.5
		};

		/* 3D triangle creation */
		TRIANGLE3D_T triangle3D = {v1, v2, v3};

		/* rotation increment */
		if(rot != ROT_NULL){
			if(rot & ROT_X) rotateVec.x += ROT_INC;
			if(rot & ROT_Y) rotateVec.y += ROT_INC;
			if(rot & ROT_Z) rotateVec.z += ROT_INC;
		}
		if(rot != ROT_NULL) DISPLAY_rotate3D(&triangle3D);

		if(rotateVec.x >= 2*M_PI) rotateVec.x = 0.0f;
		if(rotateVec.y >= 2*M_PI) rotateVec.y = 0.0f;
		if(rotateVec.z >= 2*M_PI) rotateVec.z = 0.0f;

		/* 2D isometric points from 3D vertex */
		p1 = isometric_projection(&triangle3D.v1);
		p2 = isometric_projection(&triangle3D.v2);
		p3 = isometric_projection(&triangle3D.v3);

		/* convert points to the reference system */
		transpose2D(&p1, &pRef);
		transpose2D(&p2, &pRef);
		transpose2D(&p3, &pRef);

		/* 2D triangle creation */
		TRIANGLE2D_T triangle2D = {p1, p2, p3};

		/* display the triangle */
		DISPLAY_triangle2D(&triangle2D, color);
	}
}

void DISPLAY_resetRot(void) {
	rotateVec.x = 0.0f;
	rotateVec.y = 0.0f;
	rotateVec.z = 0.0f;

}
/******************************************************************************
**                    	LOCAL FUNCTIONS         	                         **
******************************************************************************/
/**
*******************************************************************************
* @brief   DISPLAY_rotate3D
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void DISPLAY_rotate3D(TRIANGLE3D_T* triangle) {
	triangle->v1 = xRot3D(&triangle->v1, rotateVec.x);
	triangle->v2 = xRot3D(&triangle->v2, rotateVec.x);
	triangle->v3 = xRot3D(&triangle->v3, rotateVec.x);

	triangle->v1 = yRot3D(&triangle->v1, rotateVec.y);
	triangle->v2 = yRot3D(&triangle->v2, rotateVec.y);
	triangle->v3 = yRot3D(&triangle->v3, rotateVec.y);

	triangle->v1 = zRot3D(&triangle->v1, rotateVec.z);
	triangle->v2 = zRot3D(&triangle->v2, rotateVec.z);
	triangle->v3 = zRot3D(&triangle->v3, rotateVec.z);
}

/**
*******************************************************************************
* @brief   DISPLAY_triangle
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void DISPLAY_triangle2D(TRIANGLE2D_T* triangle, color_t* color) {
	VGA_lineP2P((int)triangle->p1.x, (int)triangle->p1.y, (int)triangle->p2.x, (int)triangle->p2.y, color);
	VGA_lineP2P((int)triangle->p2.x, (int)triangle->p2.y, (int)triangle->p3.x, (int)triangle->p3.y, color);
	VGA_lineP2P((int)triangle->p3.x, (int)triangle->p3.y, (int)triangle->p1.x, (int)triangle->p1.y, color);
}


/******************************************************************************
**                  	EOF                                      	         **
******************************************************************************/
