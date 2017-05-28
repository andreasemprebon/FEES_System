/*
 * FEESMath.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: Andrea Semprebon
 */

#include "FEESMath.h"
#include <math.h>

FEESMath::FEESMath() {

}

/**
 * Scalari
 */
int FEESMath::ScalarSign(float a) {
    if ( a > 0 )
        return 1;
    if ( a < 0 )
        return -1;
    return 0;
}

int FEESMath::ModifiedSign(float a) {
    if ( a >= 0 )
        return 1;
    return -1;
}

/**
 * Vettori
 */
void FEESMath::Vector3Clone(float v[3], float out[3]) {
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
}

void FEESMath::Vector3AddVector3InPlace(float v1[3], float v2[3]) {
    v1[0] = v1[0] + v2[0];
    v1[1] = v1[1] + v2[1];
    v1[2] = v1[2] + v2[2];
}

void FEESMath::Vector3SubVector3InPlace(float v1[3], float v2[3]) {
    v1[0] = v1[0] - v2[0];
    v1[1] = v1[1] - v2[1];
    v1[2] = v1[2] - v2[2];
}

void FEESMath::Vector3SubVector3(float v1[3], float v2[3], float out[3]) {
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];
}

void FEESMath::Vector3PerScalarInPlace(float v[3], float scalar) {
    v[0] = v[0] * scalar;
    v[1] = v[1] * scalar;
    v[2] = v[2] * scalar;
}

void FEESMath::Vector4PerScalarInPlace(float v[4], float scalar) {
    v[0] = v[0] * scalar;
    v[1] = v[1] * scalar;
    v[2] = v[2] * scalar;
    v[3] = v[3] * scalar;
}

void FEESMath::Vector3AddScalarInPlace(float v[3], float scalar) {
    v[0] = v[0] + scalar;
    v[1] = v[1] + scalar;
    v[2] = v[2] + scalar;
}

float FEESMath::Vector3DotProduct(float v1[3], float v2[3]) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

/**
 * Computa il prodotto vettoriale fra v1 e v2 e lo salva in out
 * @param v1
 * @param v2
 * @param out
 */
void FEESMath::Vector3CrossProduct(float v1[3], float v2[3], float out[3]) {
    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

/**
 * Restituisce la norma euclidea di un vettore di lunghezza N
 * @param v il vettore di cui calcolare la norma
 * @param size la dimensione del vettore
 * @return il valore della norma
 */
float FEESMath::VectorEuclideanNorm(float v[], int size) {
    float squared_sum = 0;
    for (int i = 0; i < size; ++i) {
        squared_sum += pow(v[i], 2);
    }
    return sqrt( squared_sum );
}

float FEESMath::Vector3EuclideanNorm(float v[3]) {
    return sqrt( pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2) );
}

float FEESMath::Vector4EuclideanNorm(float v[4]) {
    return sqrt( pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2) + pow(v[3], 2) );
}

void FEESMath::Vector3NormalizeWithEpsilon(float v[3], float v_norm[3], float epsilon) {
    float norm;
    norm = FEESMath::Vector3EuclideanNorm(v);

    if ( norm <= epsilon ) {
        v_norm[0] = 0;
        v_norm[1] = 0;
        v_norm[2] = 0;
    } else {
        v_norm[0] = v[0] / norm;
        v_norm[1] = v[1] / norm;
        v_norm[2] = v[2] / norm;
    }

}

void FEESMath::Vector3NormalizeWithEpsilonInPlace(float v[3], float epsilon) {
    float norm;
    norm = FEESMath::Vector3EuclideanNorm(v);

    if ( norm <= epsilon ) {
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
    } else {
        v[0] = v[0] / norm;
        v[1] = v[1] / norm;
        v[2] = v[2] / norm;
    }
}

void FEESMath::Vector3Normalize(float v[3], float v_norm[3]) {
    float norm;
    norm = FEESMath::Vector3EuclideanNorm(v);

    v_norm[0] = v[0] / norm;
    v_norm[1] = v[1] / norm;
    v_norm[2] = v[2] / norm;
}

void FEESMath::Vector3NormalizeInPlace(float v[3]) {
    float norm;
    norm = FEESMath::Vector3EuclideanNorm(v);

    v[0] = v[0] / norm;
    v[1] = v[1] / norm;
    v[2] = v[2] / norm;
}

void FEESMath::Vector4Normalize(float v[4], float v_norm[4]) {
    float norm;
    norm = FEESMath::Vector4EuclideanNorm(v);

    v_norm[0] = v[0] / norm;
    v_norm[1] = v[1] / norm;
    v_norm[2] = v[2] / norm;
    v_norm[3] = v[3] / norm;
}

void FEESMath::Vector4NormalizeInPlace(float v[4]) {
    float norm;
    norm = FEESMath::Vector4EuclideanNorm(v);

    v[0] = v[0] / norm;
    v[1] = v[1] / norm;
    v[2] = v[2] / norm;
    v[3] = v[3] / norm;
}

void FEESMath::VectorNormalizeInPlace(float v[], int size) {
    float norm;
    norm = FEESMath::VectorEuclideanNorm(v, size);

    for (int i = 0; i < size; ++i) {
        v[i] = v[i] / norm;
    }
}

/**
 * Matrici
 */

/**
 * Una rappresentazione di una generica matrice 3x3 e' la seguente:
 * -------------------------
 * | (0,0) | (0,1) | (0,2) |
 * -------------------------
 * | (1,0) | (1,1) | (1,2) |
 * -------------------------
 * | (2,0) | (2,1) | (2,2) |
 * -------------------------
 */

/**
 * Viene esguita la classica operazione di prodotto matriciale fra
 * le due matrici date in input, m1 ed m2, salvando il risultato in out.
 * L'operazione esegue la moltiplicazione secondo il seguente ordine:
 * out = m1 * m2
 * @param m1
 * @param m2
 * @param out
 */
void FEESMath::Matrix3x3Multiply(float m1[3][3], float m2[3][3], float out[3][3]) {
	// 1 riga x 1 colonna
	out[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0];
	// 1 riga x 2 colonna
	out[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1];
	// 1 riga x 3 colonna
	out[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2];

	// 2 riga x 1 colonna
	out[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0];
	// 2 riga x 2 colonna
	out[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1];
	// 2 riga x 3 colonna
	out[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2];

	// 3 riga x 1 colonna
	out[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0];
	// 3 riga x 2 colonna
	out[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1];
	// 3 riga x 3 colonna
	out[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2];
}

/**
 * Moltiplica una matrice M 3x3 per un vettore di dimensione 3x1
 * Il risultato e' un vettore 3x1
 * @param m1
 * @param v2
 * @param out
 */
void FEESMath::Matrix3x3MultiplyVector3x1(float m1[3][3], float v2[3], float out[3]) {
    out[0] = m1[0][0] * v2[0] + m1[0][1] * v2[1] + m1[0][2] * v2[2];
    out[1] = m1[1][0] * v2[0] + m1[1][1] * v2[1] + m1[1][2] * v2[2];
    out[2] = m1[2][0] * v2[0] + m1[2][1] * v2[1] + m1[2][2] * v2[2];
}

void FEESMath::Matrix4x4MultiplyVector4x1(float m1[4][4], float v2[4], float out[4]) {
    out[0] = m1[0][0] * v2[0] + m1[0][1] * v2[1] + m1[0][2] * v2[2] + m1[0][3] * v2[3];
    out[1] = m1[1][0] * v2[0] + m1[1][1] * v2[1] + m1[1][2] * v2[2] + m1[1][3] * v2[3];
    out[2] = m1[2][0] * v2[0] + m1[2][1] * v2[1] + m1[2][2] * v2[2] + m1[2][3] * v2[3];
    out[3] = m1[3][0] * v2[0] + m1[3][1] * v2[1] + m1[3][2] * v2[2] + m1[3][3] * v2[3];
}

/**
 * In questa funzione facciamo la traposta di una matrice 3x3.
 * L'operazione avviene in-place, ovvero la matrice risultante
 * sara' sovrascritta a m1
 * @param m1
 */
void FEESMath::Matrix3x3TransposeInPlace( float m1[3][3] ) {
    float tmp;

    /**
     * Gli elementi da scambiare sono:
     * (0,1) <-> (1,0)
     * (0,2) <-> (2,0)
     * (1,2) <-> (2,1)
     */

    // (0,1) <-> (1,0)
    tmp = m1[1][0];
	m1[1][0] = m1[0][1];
    m1[0][1] = tmp;

    // (0,2) <-> (2,0)
    tmp = m1[2][0];
    m1[2][0] = m1[0][2];
    m1[0][2] = tmp;

    // (1,2) <-> (2,1)
    tmp = m1[2][1];
    m1[2][1] = m1[1][2];
    m1[1][2] = tmp;

}

/**
 * Trasposta di una matrice 3x3
 * @param m1
 * @param out
 */
void FEESMath::Matrix3x3Transpose( float m1[3][3], float out[3][3] ) {
    out[0][0] = m1[0][0];
    out[0][1] = m1[1][0];
    out[0][2] = m1[2][0];

    out[1][0] = m1[0][1];
    out[1][1] = m1[1][1];
    out[1][2] = m1[2][1];

    out[2][0] = m1[0][2];
    out[2][1] = m1[1][2];
    out[2][2] = m1[2][2];
}

/**
 * Quaternioni
 */

void FEESMath::InvertedQuaternion(float q[4], float out[4]) {
    float squaredNorm;

    squaredNorm = pow(q[0], 2) + pow(q[1], 2) + pow(q[2], 2) + pow(q[3], 2);

    out[0] = - q[0] / squaredNorm;
    out[1] = - q[1] / squaredNorm;
    out[2] = - q[2] / squaredNorm;
    out[3] = + q[3] / squaredNorm;
}

void FEESMath::QuaternionMultiplication(float q[4], float r[4], float out[4]) {

    out[0] = r[3] * q[0] + r[0] * q[3] - r[1] * q[2] + r[2] * q[1];
    out[1] = r[3] * q[1] + r[0] * q[2] + r[1] * q[3] - r[2] * q[0];
    out[2] = r[3] * q[2] - r[0] * q[1] + r[1] * q[0] + r[2] * q[3];
    out[3] = r[3] * q[3] - r[0] * q[0] - r[1] * q[1] - r[2] * q[2];
}

void FEESMath::printMatrix(float m[3][3], int num_row, int num_col, Serial *pc) {
	char _tmp_buf[10];

	pc->printf("\n");
	for(int i = 0; i < num_row; i++) {
		for(int j = 0; j < num_col; j++) {
			ftos(_tmp_buf, m[i][j]);
			pc->printf("|\t%s\t", _tmp_buf);
		}
		pc->printf("|\n");
	}
	pc->printf("\n");
}

void FEESMath::ftos(char *buf, float num) {
	int _d1 	= num;
	float _f2 	= num - _d1;
	int _d2 	= trunc(_f2 * 100000000);

	sprintf((char *)buf, "%d.%08d", _d1, _d2);
}

