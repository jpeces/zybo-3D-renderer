/**
*******************************************************************************
**
**  @file               controls.c
**  @brief              Controls module implementation
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



#define CONTROLS_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "controls.h"
#include "xparameters.h"
#include "xgpio.h"


/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/
#define GPIO_BTNS_DEVICE_ID  	XPAR_GPIO_0_DEVICE_ID
#define GPIO_SWS_DEVICE_ID 		XPAR_GPIO_2_DEVICE_ID

#define CHANNEL					1

#define BTN_0					0x01
#define BTN_1					0x02
#define BTN_2					0x04
#define BTN_3					0x08

#define SWS_0					0x01
#define SWS_1					0x02
#define SWS_2					0x04
#define SWS_3					0x08


/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/


/******************************************************************************
**                      PROTOTYPES OF LOCAL FUNCTIONS                        **
******************************************************************************/


/******************************************************************************
**                     	GLOBAL VARIABLES                                 	 **
******************************************************************************/
XGpio BTN_Gpio; 	/* The Instance of the buttons GPIO Driver */
XGpio SWS_Gpio; 	/* The Instance of the switches GPIO Driver */

/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/

/**
*******************************************************************************
* @brief   CONTROLS_init
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      int		'0' if the initialization was success or '1' if it's not.
*******************************************************************************
**/
int CONTROLS_init(void) {
	int status;

	/* Initialize the buttons GPIO driver */
	status = XGpio_Initialize(&BTN_Gpio, GPIO_BTNS_DEVICE_ID);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Initialize the switches GPIO driver */
	status = XGpio_Initialize(&SWS_Gpio, GPIO_SWS_DEVICE_ID);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* AXI channels direction configuration */
	XGpio_SetDataDirection(&BTN_Gpio, CHANNEL, 0xF);
	XGpio_SetDataDirection(&SWS_Gpio, CHANNEL, 0xF);

	return XST_SUCCESS;
}

/**
*******************************************************************************
* @brief   CONTROLS_isMenuMode
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      bool_t	Returns TRUE if the menu switch (SW3) is activated
* 						or FALSE if it's not.
*******************************************************************************
**/
bool_t CONTROLS_isMenuMode(void) {
	int sws = XGpio_DiscreteRead(&SWS_Gpio, CHANNEL);

	if(sws&SWS_3){
		return TRUE;
	}

	return FALSE;
}

/**
*******************************************************************************
* @brief   CONTROLS_rot3D
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      int		a mask with the pressed switches..
*******************************************************************************
**/
int CONTROLS_rot3D(void) {
	return XGpio_DiscreteRead(&SWS_Gpio, CHANNEL);
}

/**
*******************************************************************************
* @brief   CONTROLS_isMenuMode
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      int		a mask with the pressed buttons.
*******************************************************************************
**/
int CONTROLS_pullButtons(void) {
	return XGpio_DiscreteRead(&BTN_Gpio, CHANNEL);
}

/******************************************************************************
**                      LOCAL FUNCTIONS                                  	 **
******************************************************************************/


/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
