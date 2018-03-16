/**
*******************************************************************************
**
**  @file               mathmin.h
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
** 	0.1.0    | 2017-11-26  | Javier Peces	   |  File creation
**
*******************************************************************************
**/


#ifndef MATHMIN_H_
#define MATHMIN_H_


/******************************************************************************
**             			MODULES USED                           			 	 **
******************************************************************************/

/******************************************************************************
**						DEFINITIONS AND MACROS                          	 **
******************************************************************************/

/******************************************************************************
**                      TYPEDEFS AND STRUCTURES                              **
******************************************************************************/
typedef struct {
	float x;
	float y;
} vec2_t ;

typedef struct {
	float x;
	float y;
	float z;
} vec3_t ;

typedef struct {
	float mat[6];
}mat2x3_t;

typedef struct {
	float mat[9];
}mat3_t;

typedef struct {
	float mat[12];
}camMat_t;


/******************************************************************************
**                     	GLOBAL VARIABLES                                 	 **
******************************************************************************/

/* Isometric projection matrix */
static const mat2x3_t isoMtx =
{
	{ 0.894427191f,  -0.894427191f,  0.0f,
	 -0.4472135955f, -0.4472135955f, 1.0f }
};

static const camMat_t camMtx =
{
		{1.0f,	 0.0f,	 0.0f,  0.0f,
		 0.0f,   1.0f,   0.0f,  0.0f,
		 0.0f,   0.0f,   1.0f,  0.0f }
};

/******************************************************************************
**                      PUBLIC FUNCTIONS                                     **
******************************************************************************/

//https://github.com/coreh/gl-matrix.c/blob/master/gl-matrix.h
//https://github.com/Kazade/kazmath
vec2_t Vec2(float x0, float y0);
vec3_t Vec3(float x0, float y0, float z0);
mat2x3_t Mat2x3(vec3_t v1, vec3_t v2);
mat3_t Mat3(vec3_t v1, vec3_t v2, vec3_t v3);

vec2_t isometric_projection(const vec3_t* vec);
vec3_t xRot3D(vec3_t* vec, float rad);
vec3_t yRot3D(const vec3_t* vec, float rad);
vec3_t zRot3D(const vec3_t* vec, float rad);

void transpose2D(vec2_t* pt, const vec2_t* ref);

void incVal(vec2_t* pt, float xinc, float yinc);

#endif /* MATHMIN_H_ */

/******************************************************************************
**                      EOF				                                     **
******************************************************************************/
