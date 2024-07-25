#ifndef INDEX_H_
#define INDEX_H_

#include "cube.h"

// coからindexを計算する関数
int co_to_index(Cube state);

// indexからcoを計算する関数
std::vector<int> index_to_co(int index);

// eoからindexを計算する関数
int eo_to_index(Cube state);

// indexからeoを計算する関数
std::vector<int> index_to_eo(int index);

// e列エッジの組み合わせからindexを計算する関数
int combination_to_index(std::vector<int> combination);

// indexからe列エッジの組み合わせを計算する関数
std::vector<int> index_to_combination(int index);

// cpもしくはud面のepからindexを計算する関数
int cp_ep_to_index(std::vector<int> parts);

// indexからcpもしくはud面のepを計算する関数
std::vector<int> index_to_cp_ep(int index);

// e列のepからindexを計算する関数
int e_ep_to_index(std::vector<int> parts);

// indexからe列のepを計算する関数
std::vector<int> index_to_e_ep(int index);

// 動作をindex化する関数
int move_to_index(std::string move);

// 動作をindex化する関数(Phase2用)
int move_to_index_ph2(std::string move);

#endif