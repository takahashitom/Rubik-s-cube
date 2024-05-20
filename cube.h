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

public:
    Cube() {}

    Cube(int init_cp[sizeC], int init_co[sizeC], int init_ep[sizeE], int init_eo[sizeE])
    {
        std::memcpy(cp, init_cp, sizeC * sizeof(int));
        std::memcpy(co, init_co, sizeC * sizeof(int));
        std::memcpy(ep, init_ep, sizeE * sizeof(int));
        std::memcpy(eo, init_eo, sizeE * sizeof(int));
    }

    Cube apply_move(Cube move) const
    {
        Cube new_state;

        for (int i = 0; i < sizeC; i++)
        {
            new_state.cp[i] = cp[move.cp[i]];
        }

        for (int i = 0; i < sizeC; i++)
        {
            new_state.co[i] = (co[move.cp[i]] + move.co[i]) % 3;
        }

        for (int i = 0; i < sizeE; i++)
        {
            new_state.ep[i] = ep[move.ep[i]];
        }

        for (int i = 0; i < sizeE; i++)
        {
            new_state.eo[i] = (eo[move.ep[i]] + move.eo[i]) % 2;
        }

        return new_state;
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

extern const Cube r_move;
extern const Cube l_move;
extern const Cube u_move;
extern const Cube d_move;
extern const Cube f_move;
extern const Cube b_move;
extern const Cube rr_move;
extern const Cube lr_move;
extern const Cube ur_move;
extern const Cube dr_move;
extern const Cube fr_move;
extern const Cube br_move;
extern const Cube r2_move;
extern const Cube l2_move;
extern const Cube u2_move;
extern const Cube d2_move;
extern const Cube f2_move;
extern const Cube b2_move;

#endif