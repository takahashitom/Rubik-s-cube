#include "cube.h"
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

    int init_cp[sizeC] = {0, 1, 2, 3, 4, 5, 6, 7};
    int init_co[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
    int init_ep[sizeE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int init_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    Cube C(init_cp, init_co, init_ep, init_eo);

    Search x, y;

    x.start_search(C, 20);

    C = C.apply_move(r_move);
    C = C.apply_move(u_move);
    C = C.apply_move(rr_move);
    C = C.apply_move(f2_move);
    C = C.apply_move(d2_move);
    C = C.apply_move(l_move);

    y.start_search(C, 20);

    auto t1 = high_resolution_clock::now();
    cout << duration_cast<milliseconds>(t1 - t0).count() / 1000. << " 秒\n";
}