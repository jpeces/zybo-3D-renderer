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


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "state_machine.h"

/******************************************************************************
**                     	DEFINITIONS AND MACROS                           	 **
******************************************************************************/
/* State machine macros */
#define N_MENU_OPTION			4
#define IDLE		 			0
#define START_TRACKING 			1
#define STOP_TRACKING 			2
#define RESET_HAND_SHAPE 		3
#define QUIT 					4

#define INIT_STATE 				START_TRACKING

/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/
typedef struct vec2{
	float x,y;
} vec2_t;

typedef struct option {
	int id;
	vec2_t pos;
	char *p_str;
} OPTION_T;

typedef unsigned char bool_t;


/******************************************************************************
**               		PROTOTYPES OF LOCAL FUNCTIONS                   	 **
******************************************************************************/
void MENU_update(void);
bool_t MENU_shouldCloseApp(void);
void MENU_selectOption(int inc);
void MENU_applyOption(void);

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
unsigned int g_optionApplied = 0;
bool_t g_trackingActive = FALSE;
bool_t to_idle = FALSE;

OPTION_T menu_options[N_MENU_OPTION] = {
	{ 0,{ 0,0 }, "Start tracking" },
	{ 1,{ 0,0 }, "Stop tracking" },
	{ 2,{ 0,0 }, "Reset default hand shape" },
	{ 3,{ 0,0 }, "Quit" },
};


/* STATE MACHINE */
STM_EVEACC transitions_start_tracking[] = {
	{ IDLE, "t_START_TRACKING_to_IDLE", MENU_toIdle, NULL },
	{ 0, 0, 0, 0 }
};

STM_EVEACC transitions_stop_tracking[] = {
	{ IDLE, "t_STOP_TRACKING_to_IDLE", MENU_toIdle, NULL },
	{ 0, 0, 0, 0 }
};

STM_EVEACC transitions_reset_hand_shape[] = {
	{ IDLE, "t_RESET_HAND_SHAPE_to_IDLE", MENU_toIdle, NULL },
	{ 0, 0, 0, 0 }
};

STM_EVEACC transitions_idle[] = {
	{ START_TRACKING, "t_IDLE_to_START_TRACKING",  MENU_toStartTracking, MENU_backToIdle },
	{ STOP_TRACKING, "t_IDLE_to_STOP_TRACKING", MENU_toStopTracking, MENU_backToIdle },
	{ RESET_HAND_SHAPE, "t_IDLE_to_RESET_HAND_SHAPE", MENU_toResetHandShape, MENU_backToIdle },
	{ 0, 0, 0, 0 }
};

STM_STATE stateIdle = { IDLE, "st_IDLE", MENU_idle, transitions_idle };
STM_STATE stateStartTracking = { START_TRACKING, "st_START_TRACKING", MENU_startTracking, transitions_start_tracking };
STM_STATE stateStopTracking = { STOP_TRACKING, "st_STOP_TRACKING", MENU_stopTracking, transitions_stop_tracking };
STM_STATE stateResetHandShape = { RESET_HAND_SHAPE, "st_RESET_HAND_SHAPE", MENU_resetDefaultShape, transitions_reset_hand_shape };

STM_STATE* statesMenu[] = {
	&stateIdle,
	&stateStartTracking,
	&stateStopTracking,
	&stateResetHandShape,
	0
};

STM_MACHINE menu_stm = { "Menu_control_app", 0, INIT_STATE, MENU_shouldCloseApp, statesMenu };

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
	STM_execute(&menu_stm);
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
	if (g_optionApplied == QUIT) {
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

	if (g_optionSelected > N_MENU_OPTION) {
		g_optionSelected = START_TRACKING;
	}
	if (g_optionSelected <= 0) {
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
	printf("Start tracking state entered!\n");
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
	printf("Stop tracking state entered!\n");
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
	printf("Reset default shape state entered!\n");
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
	if (g_optionApplied == START_TRACKING) {
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
	if (g_optionApplied == STOP_TRACKING) {
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
bool_t MENU_toResetHandShape(void) {
	if (g_optionApplied == RESET_HAND_SHAPE) {
		return TRUE;
	}

	return FALSE;
}


#define ACTIVE				0
#define FORW				1
#define BACKW				-1

void main(void) {

	int test[] = { ACTIVE, FORW, ACTIVE, FORW, ACTIVE, BACKW, ACTIVE, BACKW, ACTIVE, BACKW, ACTIVE };
	int it = 0;

	while (!MENU_shouldCloseApp())
	{
		MENU_update();

		switch (test[it])
		{
		case ACTIVE: MENU_applyOption(); break;
		case FORW: MENU_selectOption(FORW); break;
		case BACKW: MENU_selectOption(BACKW); break;
		
		default:
			break;
		}
		
		it++;
	}

	printf("Menu exited...");

	getchar();
}
/******************************************************************************
**                  	EOF                                      	         **
******************************************************************************/

