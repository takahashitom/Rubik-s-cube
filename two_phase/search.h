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
    std::vector<std::vector<int>> co_e_prune_table;
    std::vector<std::vector<int>> eo_e_prune_table;

public:
    bool depth_limited_search_ph1(int co_index, int eo_index, int e_comb_index, int depth);

    bool start_search(Cube state, int max_length) override;
};

#endif