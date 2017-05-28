/*
 * FEESMath.h
 *
 *  Created on: Jan 31, 2017
 *      Author: IEUser
 */

#ifndef FEESMATH_H_
#define FEESMATH_H_

#include "mbed.h"

#define kINTEGRATION_TIME 0.1

class FEESMath {
public:
	FEESMath();
    /**
     * Scalari
     */
    static int ScalarSign(float a);
    static int ModifiedSign(float a);

    /**
     * Vettori
     */
    static void Vector3Clone(float v[3], float out[3]);

    static float Vector3DotProduct(float v1[3], float v2[3]);

    static void Vector3PerScalarInPlace(float v[3], float scalar);
    static void Vector4PerScalarInPlace(float v[4], float scalar);

    static void Vector3AddScalarInPlace(float v[3], float scalar);

    static void Vector3AddVector3InPlace(float v1[3], float v2[3]);
    static void Vector3SubVector3InPlace(float v1[3], float v2[3]);

	static void Vector3SubVector3(float v1[3], float v2[3], float out[3]);

    static void Vector3CrossProduct(float v1[3], float v2[3], float out[3]);

    static float VectorEuclideanNorm(float v[], int size);
    static float Vector3EuclideanNorm(float v[3]);
    static float Vector4EuclideanNorm(float v[4]);
    static void Vector3Normalize(float v[3], float v_norm[3]);
	static void Vector3NormalizeInPlace(float v[3]);
    static void Vector3NormalizeWithEpsilon(float v[3], float v_norm[3], float epsilon);
    static void Vector3NormalizeWithEpsilonInPlace(float v[3], float epsilon);
    static void Vector4Normalize(float v[4], float v_norm[4]);
    static void Vector4NormalizeInPlace(float v[4]);
    static void VectorNormalizeInPlace(float v[], int size);

    /**
     * Matrici
     */
	static void Matrix3x3TransposeInPlace(float m1[3][3]);
    static void Matrix3x3Transpose( float m1[3][3], float out[3][3] );
	static void Matrix3x3Multiply(float m1[3][3], float m2[3][3], float out[3][3]);

    static void Matrix3x3MultiplyVector3x1(float m1[3][3], float v2[3], float out[3]);

    static void Matrix4x4MultiplyVector4x1(float m1[4][4], float v2[4], float out[4]);


    /**
     * Quaternioni
     */
    static void InvertedQuaternion(float q[4], float out[4]);
    static void QuaternionMultiplication(float q[4], float r[4], float out[4]);

	/**
	 * Printing function
	 */
	static void printMatrix(float m[3][3], int num_row, int num_col, Serial *pc);
	static void printFloat(float num, Serial *pc);
	static void ftos(char *buf, float num);


};

#endif /* FEESMATH_H_ */
