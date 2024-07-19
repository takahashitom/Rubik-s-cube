#include "index.h"
#include "operation_csv.h"
#include <cstring>

using namespace std;

vector<vector<int>> make_co_move_table()
{
    const int NUM_CO = 2187; // coのとり得る状態の数
    vector<vector<int>> co_move_table;
    int init_cp[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
    int init_ep[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int init_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < NUM_CO; i++)
    {
        vector<int> next_index;

        int init_co[sizeC];
        vector<int> vec_co = index_to_co(i);

        int j = 0;
        for (auto i : vec_co)
        {
            init_co[j] = i;
            j++;
        }

        Cube state(init_cp, init_co, init_ep, init_eo);

        for (auto move : state.move)
        {
            Cube new_state = state.apply_move(state.operation(move));
            next_index.push_back(co_to_index(new_state));
        }

        co_move_table.push_back(next_index);
    }

    return co_move_table;
}

vector<vector<int>> make_eo_move_table()
{
    const int NUM_EO = 2048; // eoのとり得る状態の数
    vector<vector<int>> eo_move_table;
    int init_cp[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
    int init_co[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
    int init_ep[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < NUM_EO; i++)
    {
        vector<int> next_index;

        int init_eo[sizeE];
        vector<int> vec_eo = index_to_eo(i);

        int j = 0;
        for (auto i : vec_eo)
        {
            init_eo[j] = i;
            j++;
        }

        Cube state(init_cp, init_co, init_ep, init_eo);

        for (auto move : state.move)
        {
            Cube new_state = state.apply_move(state.operation(move));
            next_index.push_back(eo_to_index(new_state));
        }

        eo_move_table.push_back(next_index);
    }

    return eo_move_table;
}

vector<vector<int>> make_e_combination_table()
{
    const int NUM_E_COMB = 495; // e列のエッジパーツの状態の数
    vector<vector<int>> e_combination_table;
    int init_cp[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
    int init_co[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
    int init_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < NUM_E_COMB; i++)
    {
        vector<int> next_index;

        int init_ep[sizeE];
        vector<int> vec_ep = index_to_combination(i);

        int j = 0;
        for (auto i : vec_ep)
        {
            init_ep[j] = i;
            j++;
        }

        Cube state(init_cp, init_co, init_ep, init_eo);

        for (auto move : state.move)
        {
            Cube new_state = state.apply_move(state.operation(move));
            int new_state_ep[sizeE];
            new_state.get_ep(new_state_ep);
            // 配列をvectorに変換する処理
            vector<int> new_state_vec;
            for (auto i : new_state_ep)
            {
                new_state_vec.push_back(i);
            }
            next_index.push_back(combination_to_index(new_state_vec));
        }

        e_combination_table.push_back(next_index);
    }

    return e_combination_table;
}

int main()
{
    // string file_co = "co_move_table.csv";
    // vector<vector<int>> tab_co = make_co_move_table();
    // writeCSV(tab_co, file_co);

    // string file_eo = "eo_move_table.csv";
    // vector<vector<int>> tab_eo = make_eo_move_table();
    // writeCSV(tab_eo, file_eo);

    string file_e_comb = "e_combination_table.csv";
    vector<vector<int>> tab_e_comb = make_e_combination_table();
    writeCSV(tab_e_comb, file_e_comb);
}