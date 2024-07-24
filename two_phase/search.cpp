#include "search.h"
#include <algorithm>

using namespace std;

bool Two_Phase_Search::depth_limited_search_ph1(int co_index, int eo_index, int e_comb_index, int depth)
{
    if (depth == 0 && co_index == 0 && eo_index == 0 && e_comb_index == 0)
    {
        return true;
    }

    if (depth == 0)
    {
        return false;
    }

    // 枝刈り
    if (max(co_e_prune_table[co_index][e_comb_index], eo_e_prune_table[eo_index][e_comb_index]) > depth)
    {
        return false;
    }

    auto prev_move = move.back();

    for (auto next : Cube::move)
    {
        if (!Cube::move_available(prev_move, next))
        {
            continue;
        }

        move.push_back(next);
        int move_index = move_to_index(next);
        int next_co_index = co_move_table[co_index][move_index];
        int next_eo_index = eo_move_table[eo_index][move_index];
        int next_e_comb_index = e_combination_table[e_comb_index][move_index];
        if (depth_limited_search_ph1(next_co_index, next_eo_index, next_e_comb_index, depth - 1))
        {
            return true;
        }
        move.pop_back();
    }
    return false;
}

bool Two_Phase_Search::start_search(Cube state, int max_length)
{
    // 遷移表および枝刈り表を読み込む
    string file_co = "../move_table/co_move_table.csv";
    string file_eo = "../move_table/eo_move_table.csv";
    string file_e = "../move_table/e_combination_table.csv";
    string file_co_e = "../prune_table/co_e_prune_table.csv";
    string file_eo_e = "../prune_table/eo_e_prune_table.csv";
    co_move_table = readCSV(file_co);
    eo_move_table = readCSV(file_eo);
    e_combination_table = readCSV(file_e);
    co_e_prune_table = readCSV(file_co_e);
    eo_e_prune_table = readCSV(file_eo_e);

    int init_ep[sizeE];
    state.get_ep(init_ep);

    vector<int> init_e_comb_vec;
    for (auto i : init_ep)
    {
        if (i < 4)
        {
            init_e_comb_vec.push_back(1);
        }
        else
        {
            init_e_comb_vec.push_back(0);
        }
    }

    int init_co_index = co_to_index(state);
    int init_eo_index = eo_to_index(state);
    int init_e_comb_index = combination_to_index(init_e_comb_vec);

    cout << init_co_index << ", " << init_eo_index << ", " << init_e_comb_index << endl;

    for (int i = 0; i < max_length; i++)
    {
        cout << "start searching length{" << i << "}\n";
        if (depth_limited_search_ph1(init_co_index, init_eo_index, init_e_comb_index, i))
        {
            cout << "ok\n";
            for (auto s : move)
            {
                cout << s << " -> ";
            }
            cout << "End" << endl;

            return true;
        }
    }

    cout << "NG\n";
    return false;
}