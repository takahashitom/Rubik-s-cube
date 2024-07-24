#include "cube.h"

using namespace std;

std::vector<std::string> Cube::move = {"R", "L", "U", "D", "F", "B", "R'", "L'", "U'", "D'", "F'", "B'", "R2", "L2", "U2", "D2", "F2", "B2"};
std::vector<std::string> Cube::phase2_move = {"U", "D", "U'", "D'", "R2", "L2", "U2", "D2", "F2", "B2"};

Cube Cube::apply_move(Cube move) const
{
    Cube new_state;

    for (int i = 0; i < sizeC; i++)
    {
        new_state.cp[i] = cp[move.cp[i]];
    }

    for (int i = 0; i < sizeC; i++)
    {
        new_state.co[i] = (co[move.cp[i]] + move.co[i]) % 3;
    }

    for (int i = 0; i < sizeE; i++)
    {
        new_state.ep[i] = ep[move.ep[i]];
    }

    for (int i = 0; i < sizeE; i++)
    {
        new_state.eo[i] = (eo[move.ep[i]] + move.eo[i]) % 2;
    }

    return new_state;
}

bool Cube::judge()
{
    for (int i = 0; i < sizeC; i++)
    {
        if (cp[i] != i)
        {
            return false;
        }

        if (co[i] != 0)
        {
            return false;
        }
    }

    for (int i = 0; i < sizeE; i++)
    {
        if (ep[i] != i)
        {
            return false;
        }

        if (eo[i] != 0)
        {
            return false;
        }
    }

    return true;
}

int Cube::count_solved_corners()
{
    int count = 0;

    for (int i = 0; i < sizeC; i++)
    {
        if (cp[i] == i and co[i] == 0)
        {
            count++;
        }
    }

    return count;
}

int Cube::count_solved_edges()
{
    int count = 0;

    for (int i = 0; i < sizeE; i++)
    {
        if (ep[i] == i and eo[i] == 0)
        {
            count++;
        }
    }

    return count;
}

bool Cube::move_available(string current, string next)
{
    if (current == "Start")
    {
        return true;
    }

    unordered_map<string, string> opposite;
    opposite["R"] = "L";
    opposite["L"] = "R";
    opposite["U"] = "D";
    opposite["D"] = "U";
    opposite["F"] = "B";
    opposite["B"] = "F";

    string current_char(1, current.at(0));
    string next_char(1, next.at(0));

    if (current_char == next_char)
    {
        return false;
    }
    if (opposite.at(current_char) == next_char)
    {
        return current_char < next_char;
    }
    return true;
}

Cube Cube::operation(string move)
{
    unordered_map<string, Cube> next_operation;
    next_operation["R"] = r_move;
    next_operation["L"] = l_move;
    next_operation["U"] = u_move;
    next_operation["D"] = d_move;
    next_operation["F"] = f_move;
    next_operation["B"] = b_move;
    next_operation["R'"] = rr_move;
    next_operation["L'"] = lr_move;
    next_operation["U'"] = ur_move;
    next_operation["D'"] = dr_move;
    next_operation["F'"] = fr_move;
    next_operation["B'"] = br_move;
    next_operation["R2"] = r2_move;
    next_operation["L2"] = l2_move;
    next_operation["U2"] = u2_move;
    next_operation["D2"] = d2_move;
    next_operation["F2"] = f2_move;
    next_operation["B2"] = b2_move;

    return next_operation.at(move);
}