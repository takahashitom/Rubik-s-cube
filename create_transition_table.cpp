#include "index.h"
#include "operation_csv.h"
#include <cstring>

using namespace std;

vector<vector<int>> co_move_table()
{
    const int NUM_CO = 2187;
    vector<vector<int>> co_move_table;
    int init_cp[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
    int init_ep[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int init_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < NUM_CO; i++)
    {
        vector<int> next_index;

        int init_co[sizeC];
        vector<int> vec_co = index_to_co(i);
        memcpy(init_co, vec_co.data(), sizeC);

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

int main()
{
    string filename = "co_move_table.csv";
    vector<vector<int>> table = co_move_table();
    writeCSV(table, filename);
}