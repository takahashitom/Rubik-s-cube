#ifndef CUBE_H_
#define CUBE_H_

#include <iostream>
#include <cstring>

class Cube
{
    static const int sizeC = 8;
    static const int sizeE = 12;

    int cp[sizeC]; // コーナーパーツ
    int co[sizeC]; // コーナーパーツの向き
    int ep[sizeE]; // エッジパーツ
    int eo[sizeE]; // エッジパーツの向き
    int step;      // 手数
    int cost;      // ゴールまでの予測コスト

public:
    Cube(int init_cp[sizeC], int init_co[sizeC], int init_ep[sizeE], int init_eo[sizeE])
    {
        std::memcpy(cp, init_cp, sizeC * sizeof(int));
        std::memcpy(co, init_co, sizeC * sizeof(int));
        std::memcpy(ep, init_ep, sizeE * sizeof(int));
        std::memcpy(eo, init_eo, sizeE * sizeof(int));

        step = 0;
        cost = -1;
    }
};

Cube r_move(Cube);  // r回転
Cube l_move(Cube);  // l回転
Cube u_move(Cube);  // u回転
Cube d_move(Cube);  // d回転
Cube f_move(Cube);  // f回転
Cube b_move(Cube);  // b回転
Cube rr_move(Cube); // r'回転
Cube lr_move(Cube); // l'回転
Cube ur_move(Cube); // u'回転
Cube dr_move(Cube); // d'回転
Cube fr_move(Cube); // f'回転
Cube br_move(Cube); // b'回転
Cube r2_move(Cube); // r2回転
Cube l2_move(Cube); // l2回転
Cube u2_move(Cube); // u2回転
Cube d2_move(Cube); // d2回転
Cube f2_move(Cube); // f2回転
Cube b2_move(Cube); // b2回転

#endif