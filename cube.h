#ifndef CUBE_H_
#define CUBE_H_

#include <iostream>
#include <cstring>
#include <array>
#include <vector>
#include <string>

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
    std::vector<std::string> move = {"R", "L", "U", "D", "F", "B", "R'", "L'", "U'", "D'", "F'", "B'", "R2", "L2", "U2", "D2", "F2", "B2"};

    // デフォルトコンストラクタ
    Cube() {}

    // コンストラクタ
    Cube(int init_cp[sizeC], int init_co[sizeC], int init_ep[sizeE], int init_eo[sizeE])
    {
        std::memcpy(cp, init_cp, sizeC * sizeof(int));
        std::memcpy(co, init_co, sizeC * sizeof(int));
        std::memcpy(ep, init_ep, sizeE * sizeof(int));
        std::memcpy(eo, init_eo, sizeE * sizeof(int));
    }

    // 操作を行う関数
    Cube apply_move(Cube move) const;

    // 完成状態か判定する関数
    bool judge();

    // 次の操作が可能かどうかを判定する関数
    bool move_available(std::string current, std::string next);

    Cube operation(std::string move);

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

class Search
{
private:
    std::vector<std::string> move{"Start"};

public:
    bool depth_limited_search(Cube current_state, int depth);

    bool start_search(Cube state, int max_length);
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