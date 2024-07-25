#include "search.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void cube_disp(Cube C)
{
    C.cp_disp();
    C.co_disp();
    C.ep_disp();
    C.eo_disp();
}

int main()
{
    auto t0 = high_resolution_clock::now();

    // int init_cp[sizeC] = {0, 1, 2, 3, 4, 5, 6, 7};
    // int init_co[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
    // int init_ep[sizeE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    // int init_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int init_cp[sizeC] = {0, 1, 4, 3, 5, 2, 7, 6};
    int init_co[sizeC] = {2, 1, 1, 2, 1, 2, 2, 1};
    int init_ep[sizeE] = {4, 9, 5, 6, 3, 5, 9, 10, 1, 2, 11, 0};
    int init_eo[sizeE] = {0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0};

    Cube C(init_cp, init_co, init_ep, init_eo);

    Two_Phase_Search x, y;

    x.start_search(C, 24);

    // C = C.apply_move(r_move);
    // C = C.apply_move(u_move);
    // C = C.apply_move(rr_move);
    // C = C.apply_move(f2_move);
    // C = C.apply_move(d2_move);
    // C = C.apply_move(l_move);
    // C = C.apply_move(fr_move);

    vector<string> move = {"R'", "U'", "F", "R'", "B'", "F2", "L2", "D'", "U'", "L2", "F2", "D'", "L2", "D'", "R", "B", "D2", "L", "D2", "F2", "U2", "L", "R'", "U'", "F"};
    // vector<string> move = {"R'", "U'", "L", "R'", "B2", "U'", "L2", "F", "U'", "L2", "F2", "D'"};

    for (auto i : move)
    {
        if (equal(i.begin(), i.end(), "Start"))
        {
            continue;
        }
        C = C.apply_move(C.operation(i));
    }

    // y.start_search(C, 100);

    auto t1 = high_resolution_clock::now();
    cout << duration_cast<milliseconds>(t1 - t0).count() / 1000. << " 秒\n";
}