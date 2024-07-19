#include "index.h"
#include <cstring>

using namespace std;

int main()
{
    int index = 0;
    vector<int> conf_vec = index_to_eo(index);

    for (auto i : conf_vec)
    {
        cout << i << ",";
    }
    cout << endl;

    int f_cp[sizeC] = {0, 1, 3, 7, 4, 5, 2, 6};
    int f_co[sizeC] = {0, 0, 1, 2, 0, 0, 2, 1};
    int f_ep[sizeE] = {0, 1, 6, 10, 4, 5, 3, 7, 8, 9, 2, 11};
    int f_eo[sizeE] = {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0};

    Cube move(f_cp, f_co, f_ep, f_eo);
    int f_index = eo_to_index(move);
    cout << f_index << endl;
}