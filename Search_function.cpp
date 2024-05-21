#include "cube.h"

using namespace std;

bool prune(int depth, Cube state)
{
    if (depth == 1 and (state.count_solved_corners() < 4 or state.count_solved_edges() < 8))
    {
        return true;
    }

    if (depth == 2 and state.count_solved_edges() < 4)
    {
        return true;
    }

    if (depth == 3 and state.count_solved_edges() < 2)
    {
        return true;
    }

    return false;
}

bool Search::depth_limited_search(Cube current_state, int depth)
{
    if (depth == 0 && current_state.judge())
    {
        return true;
    }
    if (depth == 0)
    {
        return false;
    }

    if (prune(depth, current_state))
    {
        return false;
    }

    auto prev_move = move.back();

    for (auto next : current_state.move)
    {
        if (current_state.move_available(prev_move, next) == 0)
        {
            continue;
        }

        move.push_back(next);
        if (depth_limited_search(current_state.apply_move(current_state.operation(next)), depth - 1))
        {
            return true;
        }
        move.pop_back();
    }
    return false;
}

bool Search::start_search(Cube state, int max_length)
{
    for (int i = 0; i < max_length; i++)
    {
        cout << "start searching length{" << i << "}\n";
        if (depth_limited_search(state, i))
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