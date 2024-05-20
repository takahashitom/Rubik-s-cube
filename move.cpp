#include "cube.h"

// r操作の定義
int r_cp[sizeC] = {0, 2, 6, 3, 4, 1, 5, 7};
int r_co[sizeC] = {0, 1, 2, 0, 0, 2, 1, 0};
int r_ep[sizeE] = {0, 5, 9, 3, 4, 2, 6, 7, 8, 1, 10, 11};
int r_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const Cube r_move(r_cp, r_co, r_ep, r_eo);

// l操作の定義
int l_cp[sizeC] = {4, 1, 2, 0, 7, 5, 6, 3};
int l_co[sizeC] = {2, 0, 0, 1, 1, 0, 0, 2};
int l_ep[sizeE] = {11, 1, 2, 7, 4, 5, 6, 0, 8, 9, 10, 3};
int l_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const Cube l_move(l_cp, l_co, l_ep, l_eo);

// u操作の定義
int u_cp[sizeC] = {3, 0, 1, 2, 4, 5, 6, 7};
int u_co[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
int u_ep[sizeE] = {0, 1, 2, 3, 7, 4, 5, 6, 8, 9, 10, 11};
int u_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const Cube u_move(u_cp, u_co, u_ep, u_eo);

// d操作の定義
int d_cp[sizeC] = {0, 1, 2, 3, 5, 6, 7, 4};
int d_co[sizeC] = {0, 0, 0, 0, 0, 0, 0, 0};
int d_ep[sizeE] = {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 8};
int d_eo[sizeE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const Cube d_move(d_cp, d_co, d_ep, d_eo);

// f操作の定義
int f_cp[sizeC] = {0, 1, 3, 7, 4, 5, 2, 6};
int f_co[sizeC] = {0, 0, 1, 2, 0, 0, 2, 1};
int f_ep[sizeE] = {0, 1, 6, 10, 4, 5, 3, 7, 8, 9, 2, 11};
int f_eo[sizeE] = {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0};

const Cube f_move(f_cp, f_co, f_ep, f_eo);

// b操作の定義
int b_cp[sizeC] = {1, 5, 2, 3, 0, 4, 6, 7};
int b_co[sizeC] = {1, 2, 0, 0, 2, 1, 0, 0};
int b_ep[sizeE] = {4, 8, 2, 3, 1, 5, 6, 7, 0, 9, 10, 11};
int b_eo[sizeE] = {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};

const Cube b_move(b_cp, b_co, b_ep, b_eo);

// 反回転操作の定義
const Cube r2_move = r_move.apply_move(r_move);
const Cube l2_move = l_move.apply_move(l_move);
const Cube u2_move = u_move.apply_move(u_move);
const Cube d2_move = d_move.apply_move(d_move);
const Cube f2_move = f_move.apply_move(f_move);
const Cube b2_move = b_move.apply_move(b_move);

// 半回転操作の定義
const Cube rr_move = r_move.apply_move(r_move.apply_move(r_move));
const Cube lr_move = l_move.apply_move(l_move.apply_move(l_move));
const Cube ur_move = u_move.apply_move(u_move.apply_move(u_move));
const Cube dr_move = d_move.apply_move(d_move.apply_move(d_move));
const Cube fr_move = f_move.apply_move(f_move.apply_move(f_move));
const Cube br_move = b_move.apply_move(b_move.apply_move(b_move));