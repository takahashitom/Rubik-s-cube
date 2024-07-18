#ifndef INDEX_H_
#define INDEX_H_

#include "cube.h"

// coからindexを計算する関数
int co_to_index(Cube state);

// indexからcoを計算する関数
std::vector<int> index_to_co(int index);

int eo_to_index(Cube state);

std::vector<int> index_to_eo(int index);

int combination_to_index(std::vector<int> combination);

std::vector<int> index_to_combination(int index);

int cp_ep_to_index(std::vector<int> parts);

std::vector<int> index_to_cp_ep(int index);

int e_ep_to_index(std::vector<int> parts);

std::vector<int> index_to_e_ep(int index);

#endif