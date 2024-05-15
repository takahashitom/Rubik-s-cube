#include "cube.h"

using namespace std;

const int sizeC = 8;
const int sizeE = 12;

void cube_disp(Cube C)
{
    C.cp_disp();
    C.co_disp();
    C.ep_disp();
    C.ep_disp();
    cout << "step: " << C.get_step() << endl;
}

int main()
{
    int init_cp[sizeC] = {0, 1, 2, 3, 4, 5, 6, 7};
    int init_co[sizeC] = {0, 1, 2, 3, 4, 5, 6, 7};
    int init_ep[sizeE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int init_eo[sizeE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    Cube C(init_cp, init_co, init_ep, init_eo, 0);

    Cube R = r_move(C);

    cube_disp(R);
}