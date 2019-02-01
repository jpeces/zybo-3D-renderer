/**
*******************************************************************************
**
**  @file               databox.c
**  @brief              Databox module implementation for data visualization
**  @par				Detail description
**						...
**  @version            0.1.0
**  @date               2018-01-18
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
** 	0.1.0    | 2018-01-18  | Javier Peces	   | File creation
**
*******************************************************************************
**/


#define DATABOX_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "databox.h"
#include "conf.h"
#include "new_types.h"
#include "display.h"

#include "mathmin.h"
#include "color.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/
#define NEXT_DATA_LINE			10.0f
#define NEXT_TITLE_LINE			15.0f
#define NEXT_SENSOR				30.0f

#define DATABOX_WIDTH 			(26 * 8)
#define DATABOX_HEIGHT			(85 + (5 * NEXT_SENSOR) + (6 * NEXT_TITLE_LINE))

/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/


/******************************************************************************
**                      PROTOTYPES OF LOCAL FUNCTIONS                        **
******************************************************************************/
void DATABOX_GyroData2str(char* str,int id);
void DATABOX_AccelData2str(char* str, int id);


/******************************************************************************
**                     	GLOBAL VARIABLES                                 	 **
******************************************************************************/
SENSORS_T g_rawData;
bool_t tracking = FALSE;
static vec2_t g_pos = { DISPLAY_WIDTH - DATABOX_WIDTH-10, 50 };
static color_t g_color = { 0, 255, 0 };


/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/
/**
*******************************************************************************
* @brief   Databox element initialization
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void DATABOX_init(void) {

}

/**
*******************************************************************************
* @brief   Pauses the databox element
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void DATABOX_pause(void) {
	tracking = FALSE;
}

/**
*******************************************************************************
* @brief   Updates the databox element
* @par 	   Detail description
*          ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void DATABOX_update(void) {
	vec2_t dataPos = { g_pos.x + 10.0f, g_pos.y + 10.0f };

	/* update databox drawing */
	DISPLAY_drawDataBox(&g_pos, DATABOX_WIDTH, DATABOX_HEIGHT, &g_color);

	if(!tracking) return;

	/* update data */
	char *printeable = (char *) malloc(50);

	for(int count=0; count < SENSORS_COUNT; count++) {
		/* Sensor title */
		DISPLAY_printString("Sensor", &dataPos, &g_color);
		incVal(&dataPos, 0, NEXT_TITLE_LINE);

		/* Gyroscope data */
		DATABOX_GyroData2str(printeable, count);
		DISPLAY_printString(printeable, &dataPos, &g_color);
		incVal(&dataPos, 0, NEXT_DATA_LINE);

		/* Accelerometer data */
		DATABOX_AccelData2str(printeable, count);
		DISPLAY_printString(printeable, &dataPos, &g_color);
		incVal(&dataPos, 0, NEXT_SENSOR);
	}

	free(printeable);
}

/**
*******************************************************************************
* @brief
* @par 	   Detail description
*              ...
*
* @param[out]  data(SENSORS_T*)		Data which will be display in the DataBox
* @return      None
*******************************************************************************
**/
void DATABOX_setData(SENSORS_T* data) {
	g_rawData.sensors[0] = data->sensors[0];
	g_rawData.sensors[1] = data->sensors[1];
	g_rawData.sensors[2] = data->sensors[2];
	g_rawData.sensors[3] = data->sensors[3];
	g_rawData.sensors[4] = data->sensors[4];
	g_rawData.sensors[5] = data->sensors[5];

	tracking = TRUE;
}

/******************************************************************************
**                      LOCAL FUNCTIONS                                  	 **
******************************************************************************/
/**
*******************************************************************************
* @brief
* @par 	   Detail description
*              ...
*
* @param[in]  id(int)		sensor id
* @param[out] str(char*)	string with the gyroscope data converted
* @return     None
*******************************************************************************
**/
void DATABOX_GyroData2str(char * str, int id) {
	char* aux = (char*) malloc(5);
	strcpy(str, "Gyro  {\0");
	snprintf(aux, 5, "%f", g_rawData.sensors[id].gx);
	strcat(str, aux);
	snprintf(aux, 5, "%f", g_rawData.sensors[id].gy);
	strcat(str, ", \0");
	strcat(str, aux);
	snprintf(aux, 5, "%f", g_rawData.sensors[id].gz);
	strcat(str, ", \0");
	strcat(str, aux);
	strcat(str, "}\0");

	free(aux);
}

/**
*******************************************************************************
* @brief
* @par 	   Detail description
*              ...
*
* @param[in]  id(int)		sensor id
* @param[out] str(char*)	string with the accelerometer data converted
* @return     None
*******************************************************************************
**/
void DATABOX_AccelData2str(char* str, int id) {
	char* aux = (char*) malloc(5);

	strcpy(str, "Accel {\0");
	snprintf(aux, 5, "%f", g_rawData.sensors[id].ax);
	strcat(str, aux);
	snprintf(aux, 5, "%f", g_rawData.sensors[id].ay);
	strcat(str, ", \0");
	strcat(str, aux);
	snprintf(aux, 5, "%f", g_rawData.sensors[id].az);
	strcat(str, ", \0");
	strcat(str, aux);
	strcat(str, "}\0");
}

/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
