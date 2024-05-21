#include "cube.h"

using namespace std;

int co_to_index(Cube state)
{
    int co[sizeC];
    state.get_co(co);

    int index = 0;

    for (int i = 0; i < sizeC - 1; i++)
    {
        index *= 3;
        index += co[i];
    }

    return index;
}

auto index_to_co(int index)
{
    vector<int> co(8);
    int sum_co = 0;
    for (int i = 6; i > -1; i--)
    {
        co[i] = index % 3;
        index = index / 3;
        sum_co += co[i];
    }
    co[7] = (3 - sum_co % 3) % 3;

    return co;
}

int main()
{
    int init_cp[sizeC] = {0, 1, 2, 3, 4, 5, 6, 7};
    int init_co[sizeC] = {0, 0, 1, 2, 0, 0, 0, 0};
    int init_ep[sizeE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int init_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    Cube C(init_cp, init_co, init_ep, init_eo);

    cout << co_to_index(C) << endl;

    vector<int> co = index_to_co(135);

    for (auto i : co)
    {
        cout << i << ", ";
    }
    cout << endl;
}