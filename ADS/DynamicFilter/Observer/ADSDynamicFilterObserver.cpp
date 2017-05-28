//
// Created by Andrea Semprebon on 28/05/17.
//

#include "ADSDynamicFilterObserver.h"
#include "Math/FEESMath.h"

#define kKP 0.5
#define kKI 0.004

ADSDynamicFilterObserver::ADSDynamicFilterObserver() {

}

bool ADSDynamicFilterObserver::Init() {
    kpsv[0] = 0;
    kpsv[1] = 0;
    kpsv[2] = 0;

    kisv[0] = 0;
    kisv[1] = 0;
    kisv[2] = 0;

    return true;
}

void ADSDynamicFilterObserver::Run(float q_m[4], float q_e[4]) {
    float _inv_q_ads[4];
    float _tmp_mul_res[4];
    float n4sign;

    FEESMath::InvertedQuaternion(q_e, _inv_q_ads);
    FEESMath::QuaternionMultiplication(_inv_q_ads, q_m, _tmp_mul_res);

    //Calcolo il segno della quarta componente del quaternione
    n4sign = FEESMath::ModifiedSign( _tmp_mul_res[3] );

    this->kpsv[0] = _tmp_mul_res[0] * n4sign * 2 * kKP;
    this->kpsv[1] = _tmp_mul_res[1] * n4sign * 2 * kKP;
    this->kpsv[2] = _tmp_mul_res[2] * n4sign * 2 * kKP;

    this->kisv[0] = _tmp_mul_res[0] * n4sign * -2 * kKI;
    this->kisv[1] = _tmp_mul_res[1] * n4sign * -2 * kKI;
    this->kisv[2] = _tmp_mul_res[2] * n4sign * -2 * kKI;

}
