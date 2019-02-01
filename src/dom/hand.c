/**
*******************************************************************************
**
**  @file               hand.c
**  @brief              Hand module implementation for hand management
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


#define HAND_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "hand.h"
#include "sensors.h"
#include "display.h"

#include "color.h"
#include "mathmin.h"
#include "model.h"

/******************************************************************************
**                     	DEFINITIONS AND MACROS                           	 **
******************************************************************************/


/******************************************************************************
**               		PROTOTYPES OF LOCAL FUNCTIONS                   	 **
******************************************************************************/
void HAND_drawHand(void);
void HAND_processData(SENSORS_T* data);

/******************************************************************************
**                   	GLOBAL VARIABLES                                 	 **
******************************************************************************/
HAND_T g_defaultShape;
HAND_T g_shape;
int g_rot = 0;

/******************************************************************************
**                  	PUBLIC FUNCTIONS                                  	 **
******************************************************************************/
/**
*******************************************************************************
* @brief   HAND_update
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void HAND_update(void) {
	HAND_drawHand();
}

/**
*******************************************************************************
* @brief   HAND_prepareData
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void HAND_prepareData(void) {
	SENSORS_T data = SENSORS_getDataSensors();
	HAND_processData(&data);
}

/**
*******************************************************************************
* @brief   HAND_getShape
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      HAND_T
*******************************************************************************
**/
HAND_T HAND_getShape(void) {
	return g_shape;
}

/**
*******************************************************************************
* @brief   HAND_setShape
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void HAND_setShape(HAND_T shape) {
	g_shape = shape;
}

/**
*******************************************************************************
* @brief   HAND_getDefaultShape
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
HAND_T HAND_getDefaultShape(void) {
	return g_defaultShape;
}

/**
*******************************************************************************
* @brief   HAND_setDefaultShape
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void HAND_setDefaultShape(void) {
	g_shape = g_defaultShape;
	DISPLAY_resetRot();
}

/**
*******************************************************************************
* @brief   HAND_moveFinger
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*
* @todo 	   3D model movement
*******************************************************************************
**/
void HAND_moveFinger(/*...*/) {
	// TODO
}

/**
*******************************************************************************
* @brief   HAND_changeRotation
* @par 	   Detail description
*              ...
*
* @param       rot(int)		axis rotation macro defined in display.h
* @return      None
*******************************************************************************
**/
void HAND_changeRotation(int rot) {
	g_rot = rot & 0x07;
}


/******************************************************************************
**                    	LOCAL FUNCTIONS         	                         **
******************************************************************************/
/**
*******************************************************************************
* @brief   Draw the 3D model in the res/model.h file
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void HAND_drawHand(void) {
	color_t color = Color(0,255,0);
	//DISPLAY_drawElements(&model[0], &model_indices[0], sizeof(model_indices)/sizeof(unsigned int), &color, g_rot);
	DISPLAY_drawElements(&sphere_model[0], &sphere_indices[0], sizeof(sphere_indices)/sizeof(unsigned int), &color, g_rot);
	//DISPLAY_drawElements(&axis[0], &axis_indices[0], sizeof(axis_indices)/sizeof(unsigned int), &color, ROT_NULL);
}

/**
*******************************************************************************
* @brief   HAND_processData
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void HAND_processData(SENSORS_T* data) {

}

/******************************************************************************
**                  	EOF                                      	         **
******************************************************************************/

