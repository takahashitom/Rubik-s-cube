#include "index.h"
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

vector<int> index_to_co(int index)
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

vector<int> index_to_eo(int index)
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

vector<int> index_to_combination(int index)
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

vector<int> index_to_cp_ep(int index)
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

int e_ep_to_index(vector<int> parts)
{
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        int count = 0;
        for (int j = i + 1; j < 4; j++)
        {
            if (parts[i] > parts[j])
            {
                count++;
            }
        }
        index = index + (factorial(4 - 1 - i) * count);
    }

    return index;
}

vector<int> index_to_e_ep(int index)
{
    vector<int> parts(4);
    vector<int> elements(4);

    for (int i = 0; i < 4; i++)
    {
        elements[i] = i;
    }

    for (int i = 0; i < 4; i++)
    {
        int fact = factorial(4 - 1 - i);
        int selected = index / fact;
        parts[i] = elements[selected];
        elements.erase(elements.begin() + selected);
        index %= fact;
    }

    return parts;
}

int move_to_index(string move)
{
    unordered_map<string, int> next_operation;
    next_operation["R"] = 0;
    next_operation["L"] = 1;
    next_operation["U"] = 2;
    next_operation["D"] = 3;
    next_operation["F"] = 4;
    next_operation["B"] = 5;
    next_operation["R'"] = 6;
    next_operation["L'"] = 7;
    next_operation["U'"] = 8;
    next_operation["D'"] = 9;
    next_operation["F'"] = 10;
    next_operation["B'"] = 11;
    next_operation["R2"] = 12;
    next_operation["L2"] = 13;
    next_operation["U2"] = 14;
    next_operation["D2"] = 15;
    next_operation["F2"] = 16;
    next_operation["B2"] = 17;

    return next_operation.at(move);
}

int move_to_index_ph2(string move)
{
    unordered_map<string, int> next_operation;
    next_operation["U"] = 0;
    next_operation["D"] = 1;
    next_operation["U'"] = 2;
    next_operation["D'"] = 3;
    next_operation["R2"] = 4;
    next_operation["L2"] = 5;
    next_operation["U2"] = 6;
    next_operation["D2"] = 7;
    next_operation["F2"] = 8;
    next_operation["B2"] = 9;

    return next_operation.at(move);
}