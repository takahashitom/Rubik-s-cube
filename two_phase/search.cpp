#include "search.h"
#include <algorithm>

using namespace std;

bool Two_Phase_Search::depth_limited_search_ph1(int co_index, int eo_index, int e_comb_index, int depth, Cube state)
{
    if (depth == 0 && co_index == 0 && eo_index == 0 && e_comb_index == 0)
    {
        cout << "Phase1_finish\n";
        for (auto s : move)
        {
            cout << s << " -> ";
        }
        cout << "End" << endl;
        return start_phase2(state);
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
        if (depth_limited_search_ph1(next_co_index, next_eo_index, next_e_comb_index, depth - 1, state))
        {
            return true;
        }
        move.pop_back();
    }
    return false;
}

bool Two_Phase_Search::depth_limited_search_ph2(int cp_index, int udep_index, int eep_index, int depth)
{
    if (depth == 0 && cp_index == 0 && udep_index == 0 && eep_index == 0)
    {
        return true;
    }

    if (depth == 0)
    {
        return false;
    }

    // 枝刈り
    if (max(cp_e_ep_prune_table[cp_index][eep_index], ud_ep_e_ep_prune_table[udep_index][eep_index]) > depth)
    {
        return false;
    }

    auto prev_move = move.back();
    // cout << "depth: " << depth << " prev_move: " << prev_move << endl;

    for (auto next : Cube::phase2_move)
    {
        if (!Cube::move_available(prev_move, next))
        {
            continue;
        }

        move.push_back(next);
        int move_index = move_to_index_ph2(next);
        int next_cp_index = cp_move_table[cp_index][move_index];
        int next_udep_index = ud_ep_move_table[udep_index][move_index];
        int next_eep_index = e_ep_move_table[eep_index][move_index];
        if (depth_limited_search_ph2(next_cp_index, next_udep_index, next_eep_index, depth - 1))
        {
            return true;
        }
        move.pop_back();
    }
    return false;
}

bool Two_Phase_Search::start_search(Cube state, int length)
{
    max_length = length;

    // 遷移表および枝刈り表を読み込む
    string file_co = "../move_table/co_move_table.csv";
    string file_eo = "../move_table/eo_move_table.csv";
    string file_e = "../move_table/e_combination_table.csv";
    string file_cp = "../move_table/cp_move_table.csv";
    string file_udep = "../move_table/ud_ep_move_table.csv";
    string file_eep = "../move_table/e_ep_move_table.csv";
    string file_co_e = "../prune_table/co_e_prune_table.csv";
    string file_eo_e = "../prune_table/eo_e_prune_table.csv";
    string file_cp_eep = "../prune_table/cp_e_ep_prune_table.csv";
    string file_udep_eep = "../prune_table/ud_ep_e_ep_prune_table.csv";
    co_move_table = readCSV(file_co);
    eo_move_table = readCSV(file_eo);
    e_combination_table = readCSV(file_e);
    cp_move_table = readCSV(file_cp);
    ud_ep_move_table = readCSV(file_udep);
    e_ep_move_table = readCSV(file_eep);
    co_e_prune_table = readCSV(file_co_e);
    eo_e_prune_table = readCSV(file_eo_e);
    cp_e_ep_prune_table = readCSV(file_cp_eep);
    ud_ep_e_ep_prune_table = readCSV(file_udep_eep);

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
        cout << "start PHASE1 searching length{" << i << "}\n";
        if (depth_limited_search_ph1(init_co_index, init_eo_index, init_e_comb_index, i, state))
        {
            return true;
        }
    }

    cout << "NG\n";
    return false;
}

bool Two_Phase_Search::start_phase2(Cube state)
{
    for (auto i : move)
    {
        if (equal(i.begin(), i.end(), "Start"))
        {
            continue;
        }
        state = state.apply_move(state.operation(i));
    }

    int state_cp[sizeC];
    state.get_cp(state_cp);
    vector<int> cp_vec;
    for (auto i : state_cp)
    {
        cp_vec.push_back(i);
    }
    int cp_index = cp_ep_to_index(cp_vec);

    int state_udep[sizeE];
    state.get_ep(state_udep);
    vector<int> udep_vec;
    int j = 0;
    for (auto i : state_udep)
    {
        if (j < 4)
        {
            j++;
            continue;
        }
        udep_vec.push_back(i);
    }
    int udep_index = cp_ep_to_index(udep_vec);

    int state_eep[sizeE];
    state.get_ep(state_eep);
    vector<int> eep_vec;
    j = 0;
    for (auto i : state_eep)
    {
        // state_eepの４列目まで代入する
        if (j >= 4)
        {
            break;
        }
        eep_vec.push_back(i);
        j++;
    }
    int eep_index = e_ep_to_index(eep_vec);

    cout << cp_index << ", " << udep_index << ", " << eep_index << endl;

    for (int i = 0; i < max_length - (move.size() - 1); i++)
    {
        cout << "start PHASE2 searching length{" << i << "}\n";
        if (depth_limited_search_ph2(cp_index, udep_index, eep_index, i))
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