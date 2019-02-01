/**
*******************************************************************************
**
**  @file               mathmin.c
**  @brief              File description
**  @par				Detail description
**
**  @version            0.1.0
**  @date               2017-11-26
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
** 	0.1.0    | 2017-11-26  | Javier Peces  	   |  File creation
**
*******************************************************************************
**/


#define MATHMIN_C_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/
#include "mathmin.h"
#include <math.h>


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
vec2_t Vec2(float x0, float y0) {
	vec2_t vec;

	vec.x = x0;
	vec.y = y0;

	return vec;
}

vec3_t Vec3(float x0, float y0, float z0) {
	vec3_t vec;

	vec.x = x0;
	vec.y = y0;
	vec.z = z0;

	return vec;
}

mat2x3_t Mat2x3(vec3_t v1, vec3_t v2) {
	mat2x3_t ret;

	ret.mat[0] = v1.x;
	ret.mat[1] = v1.y;
	ret.mat[2] = v1.z;
	ret.mat[3] = v2.x;
	ret.mat[4] = v2.y;
	ret.mat[5] = v2.z;

	return ret;
}

mat3_t Mat3(vec3_t v1, vec3_t v2, vec3_t v3) {
	mat3_t ret;

	ret.mat[0] = v1.x;
	ret.mat[1] = v1.y;
	ret.mat[2] = v1.z;
	ret.mat[3] = v2.x;
	ret.mat[4] = v2.y;
	ret.mat[5] = v2.z;
	ret.mat[6] = v3.x;
	ret.mat[7] = v3.y;
	ret.mat[8] = v3.z;

	return ret;
}


vec2_t isometric_projection(const vec3_t* vec) {
	vec2_t ret;

	ret.x = isoMtx.mat[0]*vec->x + isoMtx.mat[1]*vec->y + isoMtx.mat[2]*vec->z;
	ret.y = isoMtx.mat[3]*vec->x + isoMtx.mat[4]*vec->y + isoMtx.mat[5]*vec->z;

	return ret;
}

vec3_t xRot3D(vec3_t* vec, float rad) {
	vec3_t ret;

	/* X rotation matrix */
	mat3_t rmat =
	{
		{ 1, 		0, 		   	0,
		  0,		cos(rad), 	-sin(rad),
		  0,		sin(rad),  	cos(rad) }
	};

	ret.x = rmat.mat[0]*vec->x + rmat.mat[1]*vec->y + rmat.mat[2]*vec->z;
	ret.y = rmat.mat[3]*vec->x + rmat.mat[4]*vec->y + rmat.mat[5]*vec->z;
	ret.z = rmat.mat[6]*vec->x + rmat.mat[7]*vec->y + rmat.mat[8]*vec->z;

	return ret;

}

vec3_t yRot3D(const vec3_t* vec, float rad) {
	vec3_t ret;

	/* X rotation matrix */
	mat3_t rmat =
	{
		{ cos(rad), 	0, 		sin(rad),
		  0,			1, 		0,
		  -sin(rad),	0,  	cos(rad) }
	};

	ret.x = rmat.mat[0]*vec->x + rmat.mat[1]*vec->y + rmat.mat[2]*vec->z;
	ret.y = rmat.mat[3]*vec->x + rmat.mat[4]*vec->y + rmat.mat[5]*vec->z;
	ret.z = rmat.mat[6]*vec->x + rmat.mat[7]*vec->y + rmat.mat[8]*vec->z;

	return ret;

}

vec3_t zRot3D(const vec3_t* vec, float rad) {
	vec3_t ret;

	/* X rotation matrix */
	mat3_t rmat =
	{
		{ cos(rad),  	-sin(rad),   0,
		  sin(rad),	 	cos(rad),    0,
		  0,		 	0,  		 1 }
	};

	ret.x = rmat.mat[0]*vec->x + rmat.mat[1]*vec->y + rmat.mat[2]*vec->z;
	ret.y = rmat.mat[3]*vec->x + rmat.mat[4]*vec->y + rmat.mat[5]*vec->z;
	ret.z = rmat.mat[6]*vec->x + rmat.mat[7]*vec->y + rmat.mat[8]*vec->z;

	return ret;

}

void transpose2D(vec2_t* pt, const vec2_t* ref) {
	pt->x = pt->x*60.0f + ref->x;
	pt->y = pt->y*70.0f + ref->y;
}

void incVal(vec2_t* pt, float xinc, float yinc) {
	pt->x += xinc;
	pt->y += yinc;
}

/******************************************************************************
**                      LOCAL FUNCTIONS                                  	 **
******************************************************************************/


/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
