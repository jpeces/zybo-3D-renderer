/**
*******************************************************************************
**
**  @file               display.h
**  @brief              Display module definition for rendering proposes
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

#ifndef DISPLAY_H_
#define DISPLAY_H_

/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "mathmin.h"
#include "color.h"

/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/
typedef struct {
	vec2_t p1;
	vec2_t p2;
	vec2_t p3;
}TRIANGLE2D_T;

typedef struct {
	vec3_t v1;
	vec3_t v2;
	vec3_t v3;
}TRIANGLE3D_T;

/******************************************************************************
**                   	DEFINITIONS AND MACROS  	                         **
******************************************************************************/
#define HDMI				0
#define VGA					1

#define ROT_NULL			-1
#define ROT_X				0x01
#define ROT_Y				0x02
#define ROT_Z				0x04

/******************************************************************************
**                  	PUBLIC FUNCTIONS                                  	 **
******************************************************************************/

void DISPLAY_init();
void DISPLAY_stop(void);
void DISPLAY_clearFrame(void);
void DISPLAY_updateFrame(void);
void DISPLAY_printString(char *str, vec2_t *pos, color_t* color);
void DISPLAY_drawDataBox(vec2_t *pos, int width , int height, color_t* color);
void DISPLAY_drawStatusBar(vec2_t *pos, int width , int height, color_t* color);
void DISPLAY_drawApplied(vec2_t *pos, int width , int height, color_t* color);
void DISPLAY_drawSelector(vec2_t *pos, int width , int height, color_t* color);
void DISPLAY_drawElements(const float* data, const unsigned int* indices, unsigned int count, color_t* color, int rot);

void DISPLAY_resetRot(void);

#endif /* DISPLAY_H_ */

/******************************************************************************
**                  	EOF                                      	         **
******************************************************************************/

