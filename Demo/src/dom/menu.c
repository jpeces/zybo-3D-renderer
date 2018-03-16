/**
*******************************************************************************
**
**  @file               menu.c
**  @brief              Menu module implementation for menu management
**  @par				Detail description
**  					@image html state_machine.png
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


#define MENU_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "menu.h"
#include "hand.h"
#include "display.h"
#include "controls.h"
#include "statusbar.h"

#include "mathmin.h"
#include "state_machine.h"

#include <string.h>

/******************************************************************************
**                     	DEFINITIONS AND MACROS                           	 **
******************************************************************************/

/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/
typedef struct option {
		int id;
		vec2_t pos;
		char *p_str;
} OPTION_T;


/******************************************************************************
**               		PROTOTYPES OF LOCAL FUNCTIONS                   	 **
******************************************************************************/
void MENU_drawMenu(void);
void MENU_startTracking(void);
void MENU_stopTracking(void);
void MENU_resetDefaultShape(void);
void MENU_idle(void);

void MENU_backToIdle(void);

bool_t MENU_toIdle(void);
bool_t MENU_toStartTracking(void);
bool_t MENU_toStopTracking(void);
bool_t MENU_toResetHandShape(void);

/******************************************************************************
**                 		GLOBAL VARIABLES                                 	 **
******************************************************************************/
unsigned int g_optionSelected = 1;
unsigned int g_optionApplied = 1;
bool_t g_trackingActive = FALSE;
bool_t to_idle = FALSE;

OPTION_T menu_options[N_MENU_OPTION] =
{
	{ 0, {0,0}, "Start tracking" },
	{ 1, {0,0}, "Stop tracking" },
	{ 2, {0,0}, "Reset default hand shape" },
	{ 3, {0,0}, "Quit" },
	{ 4, {0,0}, "test"}
};


/* STATE MACHINE */
STM_EVEACC transitions_start_tracking[] = {
		{IDLE, "t_START_TRACKING_to_IDLE", MENU_toIdle, NULL},
		{0, 0, 0, 0}
};

STM_EVEACC transitions_stop_tracking[] = {
		{IDLE, "t_STOP_TRACKING_to_IDLE", MENU_toIdle, NULL},
		{0, 0, 0, 0}
};

STM_EVEACC transitions_reset_hand_shape[] = {
		{IDLE, "t_RESET_HAND_SHAPE_to_IDLE", MENU_toIdle, NULL},
		{0, 0, 0, 0}
};

STM_EVEACC transitions_idle[] = {
		{START_TRACKING, "t_IDLE_to_START_TRACKING",  MENU_toStartTracking, MENU_backToIdle},
		{STOP_TRACKING, "t_IDLE_to_STOP_TRACKING", MENU_toStopTracking, MENU_backToIdle},
		{RESET_HAND_SHAPE, "t_IDLE_to_RESET_HAND_SHAPE", MENU_toResetHandShape, MENU_backToIdle},
		{0, 0, 0, 0}
};

STM_STATE stateIdle = {IDLE, "st_IDLE", MENU_idle, transitions_idle };
STM_STATE stateStartTracking = {START_TRACKING, "st_START_TRACKING", MENU_startTracking, transitions_start_tracking };
STM_STATE stateStopTracking = {STOP_TRACKING, "st_STOP_TRACKING", MENU_stopTracking, transitions_stop_tracking };
STM_STATE stateResetHandShape = {RESET_HAND_SHAPE, "st_RESET_HAND_SHAPE", MENU_resetDefaultShape, transitions_reset_hand_shape };

STM_STATE* statesMenu[] = {
		&stateIdle,
		&stateStartTracking,
		&stateStopTracking,
		&stateResetHandShape,
		0
};

STM_MACHINE menu_stm = {"Menu_control_app", 0, INIT_STATE, MENU_shouldCloseApp, statesMenu};

/******************************************************************************
**                    	PUBLIC FUNCTIONS                             	     **
******************************************************************************/

/**
*******************************************************************************
* @brief   MENU_update
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void MENU_update(void) {
	MENU_drawMenu();
	STM_execute(&menu_stm);
}

/**
*******************************************************************************
* @brief   MENU_getOptionSelected
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      unsigned int 	Returns the menu option selected.
*******************************************************************************
**/
unsigned int MENU_getOptionSelected(void) {
	return g_optionSelected;
}

/**
*******************************************************************************
* @brief   MENU_isTrackingActive
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      bool_t	Returns TRUE if tracking is active or FALSE if it's not.
*******************************************************************************
**/
bool_t MENU_isTrackingActive(void) {
	return g_trackingActive;
}

/**
*******************************************************************************
* @brief   MENU_shouldCloseApp
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      bool_t	Returns TRUE if the user hit the quit menu option or
* 						FALSE if it's not.
*******************************************************************************
**/
bool_t MENU_shouldCloseApp(void) {
	if(g_optionApplied == QUIT){
		return TRUE;
	}

	return FALSE;
}


/**
*******************************************************************************
* @brief   MENU_selectOption
* @par 	   Detail description
*              ...
*
* @param       inc(int)		Menu select increment.
* @return      None
*******************************************************************************
**/
void MENU_selectOption(int inc) {

	g_optionSelected += inc;

	if(g_optionSelected > N_MENU_OPTION){
		g_optionSelected = START_TRACKING;
	}
	if(g_optionSelected < 0){
		g_optionSelected = QUIT;
	}
}

/**
*******************************************************************************
* @brief   MENU_applyOption
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void MENU_applyOption(void) {
	g_optionApplied = g_optionSelected;
}


/******************************************************************************
**                    	LOCAL FUNCTIONS         	                         **
******************************************************************************/

/**
*******************************************************************************
* @brief   MENU_drawMenu
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*
*******************************************************************************
**/
void MENU_drawMenu(void) {
	int i;
	float ypos = YPOS;

	for(i=0; i< N_MENU_OPTION; i++){
		menu_options[i].pos = Vec2(XPOS, ypos);
		DISPLAY_printString(menu_options[i].p_str, &menu_options[i].pos, &MENU_COLOR);
		ypos += OPTION_OFFSET;
	}

	/* draw the pointer to the option selected: g_optionSelected */
	DISPLAY_drawSelector(&menu_options[g_optionSelected-1].pos, 15, 7, &MENU_COLOR);

	/* draw the the option applied: g_optionApplied */
	int size = (strlen(menu_options[g_optionApplied-1].p_str)*8) + 5;
	DISPLAY_drawApplied(&menu_options[g_optionApplied-1].pos, size, 17, &MENU_COLOR);
}

/**
*******************************************************************************
* @brief   MENU_startTracking
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void MENU_startTracking(void) {
	g_trackingActive = TRUE;
	STATUSBAR_setStatus("Tracking mode ON", LOGGER_INFO);
}

/**
*******************************************************************************
* @brief   MENU_stopTracking
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void MENU_stopTracking(void) {
	g_trackingActive = FALSE;
	STATUSBAR_setStatus("Tracking mode OFF", LOGGER_INFO);

}

/**
*******************************************************************************
* @brief   MENU_resetDefaultShape
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void MENU_resetDefaultShape(void) {
	HAND_setDefaultShape();
	STATUSBAR_setStatus("Default hand shape restored", LOGGER_INFO);
}

/**
*******************************************************************************
* @brief   MENU_idle
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void MENU_idle(void) {
	to_idle = TRUE;
}

/**
*******************************************************************************
* @brief   MENU_backToIdle
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void MENU_backToIdle(void) {
	to_idle = FALSE;
}

/**
*******************************************************************************
* @brief   MENU_toIdle
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      bool_t
*******************************************************************************
**/
bool_t MENU_toIdle(void) {
	return !to_idle;
}

/**
*******************************************************************************
* @brief   MENU_toStartTracking
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      bool_t
*******************************************************************************
**/
bool_t MENU_toStartTracking(void) {
	if(g_optionApplied == START_TRACKING){
		return TRUE;
	}

	return FALSE;
}

/**
*******************************************************************************
* @brief   MENU_toStopTracking
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      bool_t
*******************************************************************************
**/
bool_t MENU_toStopTracking(void) {
	if(g_optionApplied == STOP_TRACKING){
		return TRUE;
	}

	return FALSE;
}

/**
*******************************************************************************
* @brief   MENU_toResetHandShape
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      bool_t
*******************************************************************************
**/
bool_t MENU_toResetHandShape(void){
	if(g_optionApplied == RESET_HAND_SHAPE){
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
**                  	EOF                                      	         **
******************************************************************************/

