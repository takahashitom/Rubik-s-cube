#ifndef CUBE_H_
#define CUBE_H_

#include <iostream>
#include <cstring>
#include <array>

constexpr int sizeC = 8;
constexpr int sizeE = 12;

class Cube
{
private:
    int cp[sizeC]; // コーナーパーツ
    int co[sizeC]; // コーナーパーツの向き
    int ep[sizeE]; // エッジパーツ
    int eo[sizeE]; // エッジパーツの向き
    // std::array<int, sizeC> cp;
    // std::array<int, sizeC> co;
    // std::array<int, sizeE> ep;
    // std::array<int, sizeE> eo;
    int step; // 手数
    int cost; // ゴールまでの予測コスト

public:
    Cube() {}

    Cube(int init_cp[sizeC], int init_co[sizeC], int init_ep[sizeE], int init_eo[sizeE], int init_step) : step(init_step)
    {
        std::memcpy(cp, init_cp, sizeC * sizeof(int));
        std::memcpy(co, init_co, sizeC * sizeof(int));
        std::memcpy(ep, init_ep, sizeE * sizeof(int));
        std::memcpy(eo, init_eo, sizeE * sizeof(int));
    }

    void get_cp(int out_cp[sizeC])
    {
        std::memcpy(out_cp, cp, sizeC * sizeof(int));
    }

    void get_co(int out_co[sizeC])
    {
        std::memcpy(out_co, co, sizeC * sizeof(int));
    }

    void get_ep(int out_ep[sizeE])
    {
        std::memcpy(out_ep, ep, sizeE * sizeof(int));
    }

    void get_eo(int out_eo[sizeE])
    {
        std::memcpy(out_eo, eo, sizeE * sizeof(int));
    }

    int step_plus()
    {
        step += step;
        return step;
    }

    int get_step()
    {
        return step;
    }

    void set_step(int setS)
    {
        step = setS;
    }

    void cp_disp() const
    {
        std::cout << "cp: ";
        for (int i = 0; i < sizeC; i++)
        {
            std::cout << cp[i] << ", ";
        }
        std::cout << std::endl;
    }

    void co_disp() const
    {
        std::cout << "co: ";
        for (int i = 0; i < sizeC; i++)
        {
            std::cout << co[i] << ", ";
        }
        std::cout << std::endl;
    }

    void ep_disp() const
    {
        std::cout << "ep: ";
        for (int i = 0; i < sizeE; i++)
        {
            std::cout << ep[i] << ", ";
        }
        std::cout << std::endl;
    }

    void eo_disp() const
    {
        std::cout << "eo: ";
        for (int i = 0; i < sizeE; i++)
        {
            std::cout << eo[i] << ", ";
        }
        std::cout << std::endl;
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