#include "cube.h"
#include <algorithm>
#include <iterator>

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
    vector<int> co(sizeC);
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

int eo_to_index(Cube state)
{
    int eo[sizeE];
    state.get_eo(eo);

    int index = 0;

    for (int i = 0; i < sizeE - 1; i++)
    {
        index *= 2;
        index += eo[i];
    }

    return index;
}

auto index_to_eo(int index)
{
    vector<int> eo(sizeE);
    int sum_eo = 0;
    for (int i = 10; i > -1; i--)
    {
        eo[i] = index % 2;
        index = index / 2;
        sum_eo += eo[i];
    }
    eo[11] = (2 - sum_eo % 2) % 2;

    return eo;
}

int combination_to_index(vector<int> combination)
{
    const int n = combination.size();
    int k = count(combination.begin(), combination.end(), 1);
    vector<int> current_combination(n, 0);
    int index = 0;

    for (int i = 0; i < k; i++)
    {
        current_combination[i] = 1;
    }

    while (current_combination != combination)
    {
        next_permutation(current_combination.begin(), current_combination.end());
        index++;
    }

    return index;
}

auto index_to_combination(int index)
{
    vector<int> combination(sizeE, 0);

    for (int i = 0; i < 4; i++)
    {
        combination[i] = 1;
    }

    for (int i = 0; i < index; i++)
    {
        next_permutation(combination.begin(), combination.end());
    }

    return combination;
}

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

int cp_ep_to_index(vector<int> parts)
{
    int index = 0;
    for (int i = 0; i < sizeC; i++)
    {
        int count = 0;
        for (int j = i + 1; j < sizeC; j++)
        {
            if (parts[i] > parts[j])
            {
                count++;
            }
        }
        index = index + (factorial(sizeC - 1 - i) * count);
    }

    return index;
}

auto index_to_cp_ep(int index)
{
    vector<int> parts(sizeC);
    vector<int> elements(sizeC);

    for (int i = 0; i < sizeC; i++)
    {
        elements[i] = i;
    }

    for (int i = 0; i < sizeC; i++)
    {
        int fact = factorial(sizeC - 1 - i);
        int selected = index / fact;
        parts[i] = elements[selected];
        elements.erase(elements.begin() + selected);
        index %= fact;
    }

    return parts;
}

int main()
{
    int init_cp[sizeC] = {1, 7, 6, 2, 4, 5, 0, 3};
    int init_co[sizeC] = {0, 0, 1, 2, 0, 0, 0, 0};
    int init_ep[sizeE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int init_eo[sizeE] = {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};

    Cube C(init_cp, init_co, init_ep, init_eo);

    // cout << eo_to_index(C) << endl;

    // vector<int> eo = index_to_eo(1604);

    // for (auto i : eo)
    // {
    //     cout << i << ", ";
    // }
    // cout << endl;

    // vector<int> v{1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0};

    // cout << combination_to_index(v) << endl;

    // vector<int> combination = index_to_combination(494);

    // for (auto i : combination)
    // {
    //     cout << i << ", ";
    // }
    // cout << endl;

    vector<int> cp = index_to_cp_ep(10000);
    for (auto i : cp)
    {
        cout << i << ", ";
    }
    cout << endl;

    cout << cp_ep_to_index(cp) << endl;
}