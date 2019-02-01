/**
*******************************************************************************
**
**  @file               frame.c
**  @brief              Frame module implementation for frame management
**  @par				Detail description
**  					...
**
**  @version            0.1.0
**  @date               2017-12-08
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
**  -------- | ----------- | ----------------- | -----------------------------
** 	0.1.0    | 2017-12-08  | Javier Peces	   | File creation
**
*******************************************************************************
**/


#define FRAME_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "frame.h"
#include "display.h"
#include "databox.h"
#include "statusbar.h"
#include "controls.h"
#include "sensors.h"
#include "menu.h"
#include "hand.h"

#include "conf.h"


/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/


/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/


/******************************************************************************
**                      PROTOTYPES OF LOCAL FUNCTIONS                        **
******************************************************************************/


/******************************************************************************
**                     	GLOBAL VARIABLES                                 	 **
******************************************************************************/


/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/

/**
*******************************************************************************
* @brief   Frame module initialization
* @par 	   Detail description
*          This function initialize all the modules that are use in the
*          application.
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void FRAME_init(void) {
	DISPLAY_init();
	CONTROLS_init();
	SENSORS_init();
	DATABOX_init();
	STATUSBAR_init();
	HAND_setDefaultShape();
}

/**
*******************************************************************************
* @brief   Stop the frame module and disable the hardware controllers
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void FRAME_stop(void) {
	DISPLAY_stop();
}

/**
*******************************************************************************
* @brief   Prepare all data and the display for the next frame
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void FRAME_prepare(void) {
	HAND_prepareData();
	DISPLAY_clearFrame();
}

/**
*******************************************************************************
* @brief   Update the frame
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void FRAME_update(void) {
	MENU_update();
	HAND_update();
	STATUSBAR_update();
	DATABOX_update();
	DISPLAY_updateFrame();
}

/**
*******************************************************************************
* @brief   Listen all posible events in the application
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*
* @todo 	   Control the hand 3D model with the data acquired
*******************************************************************************
**/
void FRAME_pollEvents(void) {
	int menu_btns;
	SENSORS_T data;
	static int btn_state = OFF, pulse = OFF;


	bool_t menuMode = CONTROLS_isMenuMode();
	bool_t tracking = MENU_isTrackingActive();
	int rot3D = CONTROLS_rot3D();

	if(tracking) {
		data = SENSORS_getDataSensors();

		DATABOX_setData(&data);

		// TODO (nextHand)
	}else {
		DATABOX_pause();
	}

	if(menuMode) {
		menu_btns = CONTROLS_pullButtons();

		if(menu_btns && !pulse && !btn_state) {
			pulse = ON;
			btn_state = ON;
		}else if(!menu_btns){
			btn_state = OFF;
		}

		switch(menu_btns){
			case BTN_MENU_FORWARD: 	if(pulse) MENU_selectOption(MENU_NEXT); pulse = OFF; break;		/* select the next menu option */
			case BTN_MENU_BACKWARD: if(pulse) MENU_selectOption(MENU_PREV); pulse = OFF; break;		/* select the previous menu option */
			case BTN_MENU_APPLY: 	if(pulse) MENU_applyOption(); pulse = OFF; break;				/* apply the selected menu option */
		}
	}

	HAND_changeRotation(rot3D);

}

/******************************************************************************
 **                      LOCAL FUNCTIONS                                  	 **
 ******************************************************************************/

/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
