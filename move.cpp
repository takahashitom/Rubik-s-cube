#include "cube.h"

Cube r_move(Cube c_state)
{
    int pre_cp[sizeC];
    int pre_co[sizeC];
    int pre_ep[sizeE];
    int pre_eo[sizeE];
    int new_cp[sizeC];
    int new_co[sizeC];
    int new_ep[sizeE];
    int new_eo[sizeE];

    c_state.get_cp(pre_cp);
    c_state.get_co(pre_co);
    c_state.get_ep(pre_ep);
    c_state.get_eo(pre_eo);

    new_cp[0] = pre_cp[0];
    new_cp[1] = pre_cp[2];
    new_cp[2] = pre_cp[6];
    new_cp[3] = pre_cp[3];
    new_cp[4] = pre_cp[4];
    new_cp[5] = pre_cp[1];
    new_cp[6] = pre_cp[5];
    new_cp[7] = pre_cp[7];

    new_co[0] = (pre_co[0] + 0) % 3;
    new_co[1] = (pre_co[2] + 1) % 3;
    new_co[2] = (pre_co[6] + 2) % 3;
    new_co[3] = (pre_co[3] + 0) % 3;
    new_co[4] = (pre_co[4] + 0) % 3;
    new_co[5] = (pre_co[1] + 2) % 3;
    new_co[6] = (pre_co[5] + 1) % 3;
    new_co[7] = (pre_co[7] + 0) % 3;

    new_ep[0] = pre_ep[0];
    new_ep[1] = pre_ep[5];
    new_ep[2] = pre_ep[9];
    new_ep[3] = pre_ep[3];
    new_ep[4] = pre_ep[4];
    new_ep[5] = pre_ep[2];
    new_ep[6] = pre_ep[6];
    new_ep[7] = pre_ep[7];
    new_ep[8] = pre_ep[8];
    new_ep[9] = pre_ep[1];
    new_ep[10] = pre_ep[10];
    new_ep[11] = pre_ep[11];

    new_eo[0] = pre_eo[0];
    new_eo[1] = pre_eo[5];
    new_eo[2] = pre_eo[9];
    new_eo[3] = pre_eo[3];
    new_eo[4] = pre_eo[4];
    new_eo[5] = pre_eo[2];
    new_eo[6] = pre_eo[6];
    new_eo[7] = pre_eo[7];
    new_eo[8] = pre_eo[8];
    new_eo[9] = pre_eo[1];
    new_eo[10] = pre_eo[10];
    new_eo[11] = pre_eo[11];

    Cube new_state(new_cp, new_co, new_ep, new_eo, c_state.step_plus());

    return new_state;
}

Cube l_move(Cube c_state)
{
    int pre_cp[sizeC];
    int pre_co[sizeC];
    int pre_ep[sizeE];
    int pre_eo[sizeE];
    int new_cp[sizeC];
    int new_co[sizeC];
    int new_ep[sizeE];
    int new_eo[sizeE];

    c_state.get_cp(pre_cp);
    c_state.get_co(pre_co);
    c_state.get_ep(pre_ep);
    c_state.get_eo(pre_eo);

    new_cp[0] = pre_cp[4];
    new_cp[1] = pre_cp[1];
    new_cp[2] = pre_cp[2];
    new_cp[3] = pre_cp[0];
    new_cp[4] = pre_cp[7];
    new_cp[5] = pre_cp[5];
    new_cp[6] = pre_cp[6];
    new_cp[7] = pre_cp[3];

    new_co[0] = (pre_co[4] + 2) % 3;
    new_co[1] = (pre_co[1] + 0) % 3;
    new_co[2] = (pre_co[2] + 0) % 3;
    new_co[3] = (pre_co[0] + 1) % 3;
    new_co[4] = (pre_co[7] + 1) % 3;
    new_co[5] = (pre_co[5] + 0) % 3;
    new_co[6] = (pre_co[6] + 0) % 3;
    new_co[7] = (pre_co[3] + 2) % 3;

    new_ep[0] = pre_ep[11];
    new_ep[1] = pre_ep[1];
    new_ep[2] = pre_ep[2];
    new_ep[3] = pre_ep[7];
    new_ep[4] = pre_ep[4];
    new_ep[5] = pre_ep[5];
    new_ep[6] = pre_ep[6];
    new_ep[7] = pre_ep[0];
    new_ep[8] = pre_ep[8];
    new_ep[9] = pre_ep[9];
    new_ep[10] = pre_ep[10];
    new_ep[11] = pre_ep[3];

    new_eo[0] = pre_eo[11];
    new_eo[1] = pre_eo[1];
    new_eo[2] = pre_eo[2];
    new_eo[3] = pre_eo[7];
    new_eo[4] = pre_eo[4];
    new_eo[5] = pre_eo[5];
    new_eo[6] = pre_eo[6];
    new_eo[7] = pre_eo[0];
    new_eo[8] = pre_eo[8];
    new_eo[9] = pre_eo[9];
    new_eo[10] = pre_eo[10];
    new_eo[11] = pre_eo[3];

    Cube new_state(new_cp, new_co, new_ep, new_eo, c_state.step_plus());

    return new_state;
}

Cube u_move(Cube c_state)
{
    int pre_cp[sizeC];
    int pre_co[sizeC];
    int pre_ep[sizeE];
    int pre_eo[sizeE];
    int new_cp[sizeC];
    int new_co[sizeC];
    int new_ep[sizeE];
    int new_eo[sizeE];

    c_state.get_cp(pre_cp);
    c_state.get_co(pre_co);
    c_state.get_ep(pre_ep);
    c_state.get_eo(pre_eo);

    new_cp[0] = pre_cp[3];
    new_cp[1] = pre_cp[0];
    new_cp[2] = pre_cp[1];
    new_cp[3] = pre_cp[2];
    new_cp[4] = pre_cp[4];
    new_cp[5] = pre_cp[5];
    new_cp[6] = pre_cp[6];
    new_cp[7] = pre_cp[7];

    new_co[0] = pre_co[3];
    new_co[1] = pre_co[0];
    new_co[2] = pre_co[1];
    new_co[3] = pre_co[2];
    new_co[4] = pre_co[4];
    new_co[5] = pre_co[5];
    new_co[6] = pre_co[6];
    new_co[7] = pre_co[7];

    new_ep[0] = pre_ep[0];
    new_ep[1] = pre_ep[1];
    new_ep[2] = pre_ep[2];
    new_ep[3] = pre_ep[3];
    new_ep[4] = pre_ep[7];
    new_ep[5] = pre_ep[4];
    new_ep[6] = pre_ep[5];
    new_ep[7] = pre_ep[6];
    new_ep[8] = pre_ep[8];
    new_ep[9] = pre_ep[9];
    new_ep[10] = pre_ep[10];
    new_ep[11] = pre_ep[11];

    new_eo[0] = pre_eo[0];
    new_eo[1] = pre_eo[1];
    new_eo[2] = pre_eo[2];
    new_eo[3] = pre_eo[3];
    new_eo[4] = pre_eo[7];
    new_eo[5] = pre_eo[4];
    new_eo[6] = pre_eo[5];
    new_eo[7] = pre_eo[6];
    new_eo[8] = pre_eo[8];
    new_eo[9] = pre_eo[9];
    new_eo[10] = pre_eo[10];
    new_eo[11] = pre_eo[11];

    Cube new_state(new_cp, new_co, new_ep, new_eo, c_state.step_plus());

    return new_state;
}

Cube d_move(Cube c_state)
{
    int pre_cp[sizeC];
    int pre_co[sizeC];
    int pre_ep[sizeE];
    int pre_eo[sizeE];
    int new_cp[sizeC];
    int new_co[sizeC];
    int new_ep[sizeE];
    int new_eo[sizeE];

    c_state.get_cp(pre_cp);
    c_state.get_co(pre_co);
    c_state.get_ep(pre_ep);
    c_state.get_eo(pre_eo);

    new_cp[0] = pre_cp[0];
    new_cp[1] = pre_cp[1];
    new_cp[2] = pre_cp[2];
    new_cp[3] = pre_cp[3];
    new_cp[4] = pre_cp[5];
    new_cp[5] = pre_cp[6];
    new_cp[6] = pre_cp[7];
    new_cp[7] = pre_cp[4];

    new_co[0] = pre_co[0];
    new_co[1] = pre_co[1];
    new_co[2] = pre_co[2];
    new_co[3] = pre_co[3];
    new_co[4] = pre_co[5];
    new_co[5] = pre_co[6];
    new_co[6] = pre_co[7];
    new_co[7] = pre_co[4];

    new_ep[0] = pre_ep[0];
    new_ep[1] = pre_ep[1];
    new_ep[2] = pre_ep[2];
    new_ep[3] = pre_ep[3];
    new_ep[4] = pre_ep[4];
    new_ep[5] = pre_ep[5];
    new_ep[6] = pre_ep[6];
    new_ep[7] = pre_ep[7];
    new_ep[8] = pre_ep[9];
    new_ep[9] = pre_ep[10];
    new_ep[10] = pre_ep[11];
    new_ep[11] = pre_ep[8];

    new_eo[0] = pre_eo[0];
    new_eo[1] = pre_eo[1];
    new_eo[2] = pre_eo[2];
    new_eo[3] = pre_eo[3];
    new_eo[4] = pre_eo[4];
    new_eo[5] = pre_eo[5];
    new_eo[6] = pre_eo[6];
    new_eo[7] = pre_eo[7];
    new_eo[8] = pre_eo[9];
    new_eo[9] = pre_eo[10];
    new_eo[10] = pre_eo[11];
    new_eo[11] = pre_eo[8];

    Cube new_state(new_cp, new_co, new_ep, new_eo, c_state.step_plus());

    return new_state;
}

Cube f_move(Cube c_state)
{
    int pre_cp[sizeC];
    int pre_co[sizeC];
    int pre_ep[sizeE];
    int pre_eo[sizeE];
    int new_cp[sizeC];
    int new_co[sizeC];
    int new_ep[sizeE];
    int new_eo[sizeE];

    c_state.get_cp(pre_cp);
    c_state.get_co(pre_co);
    c_state.get_ep(pre_ep);
    c_state.get_eo(pre_eo);

    new_cp[0] = pre_cp[0];
    new_cp[1] = pre_cp[1];
    new_cp[2] = pre_cp[3];
    new_cp[3] = pre_cp[7];
    new_cp[4] = pre_cp[4];
    new_cp[5] = pre_cp[5];
    new_cp[6] = pre_cp[2];
    new_cp[7] = pre_cp[6];

    new_co[0] = (pre_co[0] + 0) % 3;
    new_co[1] = (pre_co[1] + 0) % 3;
    new_co[2] = (pre_co[3] + 1) % 3;
    new_co[3] = (pre_co[7] + 2) % 3;
    new_co[4] = (pre_co[4] + 0) % 3;
    new_co[5] = (pre_co[5] + 0) % 3;
    new_co[6] = (pre_co[2] + 2) % 3;
    new_co[7] = (pre_co[6] + 1) % 3;

    new_ep[0] = pre_ep[0];
    new_ep[1] = pre_ep[1];
    new_ep[2] = pre_ep[6];
    new_ep[3] = pre_ep[10];
    new_ep[4] = pre_ep[4];
    new_ep[5] = pre_ep[5];
    new_ep[6] = pre_ep[3];
    new_ep[7] = pre_ep[7];
    new_ep[8] = pre_ep[8];
    new_ep[9] = pre_ep[9];
    new_ep[10] = pre_ep[2];
    new_ep[11] = pre_ep[11];

    new_eo[0] = (pre_eo[0] + 0) % 2;
    new_eo[1] = (pre_eo[1] + 0) % 2;
    new_eo[2] = (pre_eo[6] + 1) % 2;
    new_eo[3] = (pre_eo[10] + 1) % 2;
    new_eo[4] = (pre_eo[4] + 0) % 2;
    new_eo[5] = (pre_eo[5] + 0) % 2;
    new_eo[6] = (pre_eo[3] + 1) % 2;
    new_eo[7] = (pre_eo[7] + 0) % 2;
    new_eo[8] = (pre_eo[8] + 0) % 2;
    new_eo[9] = (pre_eo[9] + 0) % 2;
    new_eo[10] = (pre_eo[2] + 1) % 2;
    new_eo[11] = (pre_eo[11] + 0) % 2;

    Cube new_state(new_cp, new_co, new_ep, new_eo, c_state.step_plus());

    return new_state;
}

Cube b_move(Cube c_state)
{
    int pre_cp[sizeC];
    int pre_co[sizeC];
    int pre_ep[sizeE];
    int pre_eo[sizeE];
    int new_cp[sizeC];
    int new_co[sizeC];
    int new_ep[sizeE];
    int new_eo[sizeE];

    c_state.get_cp(pre_cp);
    c_state.get_co(pre_co);
    c_state.get_ep(pre_ep);
    c_state.get_eo(pre_eo);

    new_cp[0] = pre_cp[1];
    new_cp[1] = pre_cp[5];
    new_cp[2] = pre_cp[2];
    new_cp[3] = pre_cp[3];
    new_cp[4] = pre_cp[0];
    new_cp[5] = pre_cp[4];
    new_cp[6] = pre_cp[6];
    new_cp[7] = pre_cp[7];

    new_co[0] = (pre_co[1] + 1) % 3;
    new_co[1] = (pre_co[5] + 2) % 3;
    new_co[2] = (pre_co[2] + 0) % 3;
    new_co[3] = (pre_co[3] + 0) % 3;
    new_co[4] = (pre_co[0] + 2) % 3;
    new_co[5] = (pre_co[4] + 1) % 3;
    new_co[6] = (pre_co[6] + 0) % 3;
    new_co[7] = (pre_co[7] + 0) % 3;

    new_ep[0] = pre_ep[4];
    new_ep[1] = pre_ep[8];
    new_ep[2] = pre_ep[2];
    new_ep[3] = pre_ep[3];
    new_ep[4] = pre_ep[1];
    new_ep[5] = pre_ep[5];
    new_ep[6] = pre_ep[6];
    new_ep[7] = pre_ep[7];
    new_ep[8] = pre_ep[0];
    new_ep[9] = pre_ep[9];
    new_ep[10] = pre_ep[10];
    new_ep[11] = pre_ep[11];

    new_eo[0] = (pre_eo[4] + 1) % 2;
    new_eo[1] = (pre_eo[8] + 1) % 2;
    new_eo[2] = (pre_eo[2] + 0) % 2;
    new_eo[3] = (pre_eo[3] + 0) % 2;
    new_eo[4] = (pre_eo[1] + 1) % 2;
    new_eo[5] = (pre_eo[5] + 0) % 2;
    new_eo[6] = (pre_eo[6] + 0) % 2;
    new_eo[7] = (pre_eo[7] + 0) % 2;
    new_eo[8] = (pre_eo[0] + 1) % 2;
    new_eo[9] = (pre_eo[9] + 0) % 2;
    new_eo[10] = (pre_eo[10] + 0) % 2;
    new_eo[11] = (pre_eo[11] + 0) % 2;

    Cube new_state(new_cp, new_co, new_ep, new_eo, c_state.step_plus());

    return new_state;
}

Cube rr_move(Cube c_state)
{
    Cube new_state;

    new_state = r_move(r_move(r_move(c_state)));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube lr_move(Cube c_state)
{
    Cube new_state;

    new_state = l_move(l_move(l_move(c_state)));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube ur_move(Cube c_state)
{
    Cube new_state;

    new_state = u_move(u_move(u_move(c_state)));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube dr_move(Cube c_state)
{
    Cube new_state;

    new_state = d_move(d_move(d_move(c_state)));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube fr_move(Cube c_state)
{
    Cube new_state;

    new_state = f_move(f_move(f_move(c_state)));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube br_move(Cube c_state)
{
    Cube new_state;

    new_state = b_move(b_move(b_move(c_state)));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube r2_move(Cube c_state)
{
    Cube new_state;

    new_state = r_move(r_move(c_state));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube l2_move(Cube c_state)
{
    Cube new_state;

    new_state = l_move(l_move(c_state));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube u2_move(Cube c_state)
{
    Cube new_state;

    new_state = u_move(u_move(c_state));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube d2_move(Cube c_state)
{
    Cube new_state;

    new_state = d_move(d_move(c_state));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube f2_move(Cube c_state)
{
    Cube new_state;

    new_state = f_move(f_move(c_state));

    new_state.set_step(c_state.step_plus());

    return new_state;
}

Cube b2_move(Cube c_state)
{
    Cube new_state;

    new_state = b_move(b_move(c_state));

    new_state.set_step(c_state.step_plus());

    return new_state;
}