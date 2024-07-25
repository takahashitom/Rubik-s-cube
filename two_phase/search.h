#ifndef SEARCH_H_
#define SEARCH_H_

#include "cube.h"
#include "operation_csv.h"
#include "index.h"

class Two_Phase_Search : Search
{
private:
    std::vector<std::vector<int>> co_move_table;
    std::vector<std::vector<int>> eo_move_table;
    std::vector<std::vector<int>> e_combination_table;
    std::vector<std::vector<int>> cp_move_table;
    std::vector<std::vector<int>> ud_ep_move_table;
    std::vector<std::vector<int>> e_ep_move_table;
    std::vector<std::vector<int>> co_e_prune_table;
    std::vector<std::vector<int>> eo_e_prune_table;
    std::vector<std::vector<int>> cp_e_ep_prune_table;
    std::vector<std::vector<int>> ud_ep_e_ep_prune_table;

    int max_length;

public:
    bool depth_limited_search_ph1(int co_index, int eo_index, int e_comb_index, int depth, Cube state);

    bool depth_limited_search_ph2(int cp_index, int udep_index, int eep_index, int depth);

    bool start_search(Cube state, int length) override;

    bool start_phase2(Cube state);
};

#endif