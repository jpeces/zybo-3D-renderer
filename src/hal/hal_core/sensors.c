/**
*******************************************************************************
**
**  @file               sensors.c
**  @brief              Sensors module implementation for gyroscopes management
**  @par				Detail description
**						...
**
**  @version            0.1.0
**  @date               2017-12-19
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
** 	0.1.0    | 2017-12-19  | Javier Peces	   | File creation
**
*******************************************************************************
**/


#define SENSORS_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "sensors.h"
#include "i2c.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/
enum Sensors {SN_1=0x01, SN_2, SN_3, SN_4, SN_5, SN_6};


/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/


/******************************************************************************
**                      PROTOTYPES OF LOCAL FUNCTIONS                        **
******************************************************************************/
void SENSORS_calibrate(void);
int SENSORS_check(void);
Sensor SENSORS_getSensorData(unsigned int id);
int SENSORS_getRand(void);

/******************************************************************************
**                     	GLOBAL VARIABLES                                 	 **
******************************************************************************/
float Gyro[10] = {0.00f, 0.14f, 0.34f, 0.40f, 0.48f, 0.56f, 0.67f, 0.74f, 0.85f, 0.98f};
float Accel[10] = {0.98f, 0.80f, 0.75f, 0.42f, 0.35f, 0.20f, 0.15f, 0.11f, 0.06f, 0.00f};

/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/

/**
*******************************************************************************
* @brief   SENSORS_init
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void SENSORS_init() {
	I2C_init();

	while(SENSORS_check() != 0) {
		printf("the sensors are not ready\r\n");
	}

	SENSORS_calibrate();
}

/**
*******************************************************************************
* @brief   SENSORS_getDataSensors
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      SENSORS_T
*******************************************************************************
**/
SENSORS_T SENSORS_getDataSensors() {
	SENSORS_T data;

	for(unsigned int id = SN_1; id < SN_6; id++){
		data.sensors[id-1] = SENSORS_getSensorData(id);
	}
	// TODO get data

	return data;
}
/******************************************************************************
**                      LOCAL FUNCTIONS                                  	 **
******************************************************************************/

/**
*******************************************************************************
* @brief   SENSORS_calibrate
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
void SENSORS_calibrate(void) {

}

/**
*******************************************************************************
* @brief   SENSORS_check
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      None
*******************************************************************************
**/
int SENSORS_check(void) {
	int checking = 0;
	int times = 10;

	/* checking with I2C */
	do {
		for(unsigned int sen= SN_1; sen < SN_6; sen++){
			checking += I2C_ping(sen);
		}

		times--;
	}while(checking != 0 && times != 0);

	return 0;
}

/**
*******************************************************************************
* @brief   SENSORS_getSensorData
* @par 	   Detail description
*              ...
*
* @param       id(unsigned int)		sensor device id
* @return      None
*******************************************************************************
**/
Sensor SENSORS_getSensorData(unsigned int id) {
	Sensor ret;
	int sign = 1;

	int rand = SENSORS_getRand();
	printf("%i", rand);

	if(rand >= 7) {
		sign ^= 1;
	}

	ret.ax = Accel[rand];
	ret.ay = Accel[rand + sign*1];
	ret.az = Accel[rand + sign*2];
	ret.gx = Gyro[rand];
	ret.gy = Gyro[rand + sign*1];
	ret.gz = Gyro[rand + sign*2];

	return ret;
}

/**
*******************************************************************************
* @brief   SENSORS_getRand
* @par 	   Detail description
*              ...
*
* @param       Empty
* @return      (int)		rand num between 0-9
*******************************************************************************
**/
int SENSORS_getRand(void) {
	return rand() / (RAND_MAX /(9 + 1 - 0) + 0);
}


/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
