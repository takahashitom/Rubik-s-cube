#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 100000

//状態を示す構造体
typedef struct state
{
    int cp[8]; //コーナーパーツ
    int co[8]; //コーナーパーツの向き
    int ep[12]; //エッジパーツ
    int eo[12]; //エッジパーツの向き
    int step; //手数
    int cost; //ゴールまでの予測コスト
    char move[2];
} Cube;

Cube r_move(Cube); //r回転
Cube l_move(Cube); //l回転
Cube u_move(Cube); //u回転
Cube d_move(Cube); //d回転
Cube f_move(Cube); //f回転
Cube b_move(Cube); //b回転
Cube rr_move(Cube); //r'回転
Cube lr_move(Cube); //l'回転
Cube ur_move(Cube); //u'回転
Cube dr_move(Cube); //d'回転
Cube fr_move(Cube); //f'回転
Cube br_move(Cube); //b'回転
Cube r2_move(Cube); //r2回転
Cube l2_move(Cube); //l2回転
Cube u2_move(Cube); //u2回転
Cube d2_move(Cube); //d2回転
Cube f2_move(Cube); //f2回転
Cube b2_move(Cube); //b2回転

int search(Cube state[], int open[], int prev[], int ph, int *num);
int sol_check(Cube, int); //完成チェック
void print_route(int prev[], int g, Cube state[]);
int pre_cost(Cube, int); //残り手数予測
int add(Cube state[], int num, int open[], int size, int top, int prev[], int ph); //新たなノードをopenに追加
int state_check(Cube state, Cube sol_state);
int pre_cost_0(Cube);
int pre_cost_1(Cube);
int pre_cost_2(Cube);
int pre_cost_3(Cube);

int pre_cost_00(Cube);
int pre_cost_11(Cube);
int pre_cost_22(Cube);
int pre_cost_33(Cube);

int main(void){
    
    //開始状態
    //4手
    // Cube start_state = {{6,3,5,2,0,4,7,1},
    //                 {2,0,2,1,2,1,2,2},
    //                 {4,8,10,5,6,7,9,2,0,1,3,11},
    //                 {1,1,1,0,0,0,1,0,1,0,1,0},
    //                 0,
    //                 -1,
    //                 "S"};

    Cube start_state = {{2,3,6,5,1,0,7,4},
                    {1,2,1,2,2,1,2,1},
                    {5,7,10,8,0,4,2,11,1,9,3,6},
                    {1,1,1,1,1,0,1,0,1,0,1,0},
                    0,
                    -1,
                    "S"};

    //5手
    // Cube start_state = {{1,3,5,0,2,4,7,6},
    //                 {2,0,2,2,1,1,2,2},
    //                 {5,8,10,4,6,7,9,11,0,1,3,2},
    //                 {0,1,1,1,0,0,1,0,1,0,1,0},
    //                 0,
    //                 -1,
    //                 "S"};

    Cube *state = (Cube*)calloc(N, sizeof(Cube));
    if(state == NULL){
        printf("domain error\n");
        exit(-1);
    }
    
    int *open = (int*)calloc(N, sizeof(int));
    if(state == NULL){
        printf("domain error\n");
        exit(-1);
    }

    int *prev = (int*)calloc(N, sizeof(int));
    if(state == NULL){
        printf("domain error\n");
        exit(-1);
    }

    int num = 0; //配列stateのナンバー
    int size = 0;
    int phase = 0;
    int tmp;

    //開始状態のコスト計算
    start_state.cost = pre_cost(start_state, phase);

    open[size++] = num;
    prev[num] = -1;
    state[num++] = start_state;

    for(; phase<4; phase++){
        tmp = search(state, open, prev, phase, &num);
        if(tmp != -1){
            open[0] = tmp;
        }else{
            printf("\nNG\n");
            free(state);
            free(open);
            free(prev);
            return -1;
        }
    }
    
    free(state);
    free(open);
    free(prev);
    return 0;
}

int search(Cube state[], int open[], int prev[], int ph, int *num){
    int i, tmp, top, mindex;
    int size = 1;

    while (size>0)
    {
        mindex = 0;

        for(i=1; i<size; i++){
            if((state[open[i]].step + state[open[i]].cost) <= (state[open[mindex]].step + state[open[mindex]].cost)){
                mindex = i;
            }
        }

        tmp = open[size-1];
        open[size-1] = open[mindex];
        open[mindex] = tmp;

        top = open[--size];

        printf("%d %d\n", top, state[top].cost);

        if(sol_check(state[top], ph) == 0){
            printf("\nphase%d OK\n", ph);
            print_route(prev, top, state);
            printf("steps: %d\n", state[top].step);
            return top;
        }

        if(strncmp(state[top].move, "r", 1) != 0){
            if(ph<2){
                //r回転した場合
                state[*num] = r_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);
                printf("%d, %d, %d, %s\n", *num, state[*num].cost, state[*num].step, state[*num].move);

                *num = *num + 1;

                //rr回転した場合
                state[*num] = rr_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);
                
                *num = *num + 1;
            }

            //r2回転した場合
            state[*num] = r2_move(state[top]);
            size = add(state, *num, open, size, top, prev, ph);

            *num = *num + 1;
        }

        if(strncmp(state[top].move, "l", 1) != 0){
            if(ph<2){
                //l回転した場合
                state[*num] = l_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;

                //lr回転した場合
                state[*num] = lr_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;
            }

            //l2回転した場合
            state[*num] = l2_move(state[top]);
            size = add(state, *num, open, size, top, prev, ph);

            *num = *num + 1;
        }

        if(strncmp(state[top].move, "u", 1) != 0){
            if(ph<3){
                //u回転した場合
                state[*num] = u_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;

                //ur回転した場合
                state[*num] = ur_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;
            }

            //u2回転した場合
            state[*num] = u2_move(state[top]);
            size = add(state, *num, open, size, top, prev, ph);

            *num = *num + 1;
        }

        if(strncmp(state[top].move, "d", 1) != 0){
            if(ph<3){
                //d回転した場合
                state[*num] = d_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;

                //dr回転した場合
                state[*num] = dr_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;
            }

            //d2回転した場合
            state[*num] = d2_move(state[top]);
            size = add(state, *num, open, size, top, prev, ph);

            *num = *num + 1;
        }

        if(strncmp(state[top].move, "f", 1) != 0){
            if(ph<1){
                //f回転した場合
                state[*num] = f_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;

                //fr回転した場合
                state[*num] = fr_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;
            }

            //f2回転した場合
            state[*num] = f2_move(state[top]);
            size = add(state, *num, open, size, top, prev, ph);

            *num = *num + 1;
        }

        if(strncmp(state[top].move, "b", 1) != 0){
            if(ph<1){
                //b回転した場合
                state[*num] = b_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;

                //br回転した場合
                state[*num] = br_move(state[top]);
                size = add(state, *num, open, size, top, prev, ph);

                *num = *num + 1;
            }

            //b2回転した場合
            state[*num] = b2_move(state[top]);
            size = add(state, *num, open, size, top, prev, ph);

            *num = *num + 1;
        }

    }

    return -1;
}

int sol_check(Cube state, int ph){
    int i, cp=0, co=0, ep=0, eo=0, ep_posi=0, ep_posi2=0, cp_posi=0;

    Cube sol_state = {{0,1,2,3,4,5,6,7}, 
                    {0,0,0,0,0,0,0,0},
                    {0,1,2,3,4,5,6,7,8,9,10,11},
                    {0,0,0,0,0,0,0,0,0,0,0,0}};

    for(i=0; i<8; i++){
        if(state.cp[i] != sol_state.cp[i]){
            cp++;
        }

        if(ph==2){
            if(i==0 || i==2 || i==5 || i==7){
                if(state.cp[i] != 0 && state.cp[i] != 2 && state.cp[i] != 5 && state.cp[i] != 7){
                    cp_posi = 1;
                }
            }
        }

        if(state.co[i] != sol_state.co[i]){
            co++;
        }
    }

    for(i=0; i<12; i++){
        if(state.ep[i] != sol_state.ep[i]){
            ep++;
        }

        if(ph==1){
            if(i<4){
                if(state.ep[i]>=4){
                    ep_posi = 1;
                }
            }
        }

        if(ph==2){
            if(i==4 || i==6 || i==8 || i==10){
                if(state.ep[i] != 4 && state.ep[i] != 6 && state.ep[i] != 8 && state.ep[i] != 10){
                    ep_posi2 = 1;
                }
            }else if(i==5 || i==7 || i==9 || i==11){
                if(state.ep[i] != 5 && state.ep[i] != 7 && state.ep[i] != 9 && state.ep[i] != 11){
                    ep_posi2 = 1;
                }
            }
        }

        if(state.eo[i] != sol_state.eo[i]){
            eo++;
        }
    }

    if(ph == 3){
        if(cp==0 && co==0 && ep==0 && eo==0){
            return 0;
        }
    }else if(ph == 2){
        if(cp_posi == 0 && ep_posi2 == 0){
            return 0;
        }
    }else if(ph == 1){
        if(co == 0 && ep_posi == 0){
            return 0;            
        }
    }else if(ph == 0){
        if(eo == 0){
            return 0;
        }
    }

    return -1;
}

void print_route(int prev[], int g, Cube state[])
{
  int tmp;
  printf("%s", state[g].move);
  tmp = prev[g];
  while(tmp >= 0){
    printf(" <- %s", state[tmp].move);
    tmp = prev[tmp];
  }
  printf("\n");
  return;
}

int add(Cube state[], int num, int open[], int size, int top, int prev[], int ph){
    int i, tmp, flag=0;

    state[num].cost = pre_cost(state[num], ph);

    for(i=0; i<num; i++){
        if(state_check(state[num], state[i]) == 0){
            if(prev[i] != -1){
                tmp = i;
                flag = 1;
            }
        }
    }

    if(flag==0){
        open[size++] = num;
        prev[num] = top;
    }else{
        if(state[num].step < state[tmp].step){
            open[size++] = num;
            prev[num] = top;
        }else{
            prev[num] = -1;
        }
    }

    return size;
}

int pre_cost(Cube state, int ph){
    
    if(ph==0){
        return pre_cost_00(state);
    }else if(ph==1){
        return pre_cost_11(state);
    }else if(ph==2){
        return pre_cost_22(state);
    }else if(ph==3){
        return pre_cost_33(state);
    }else{
        return -1;
    }
}

int pre_cost_0(Cube state){
    int i, eva_eo=0;

    for(i=0; i<12; i++){
        if(state.eo[i] != 0){
            eva_eo++;
        }
    }

    if(eva_eo==0){
        return 0;
    }else if(eva_eo==4){
        if(state.eo[2] == 1 && state.eo[3] == 1 && state.eo[6] == 1 && state.eo[10] == 1){
            return 1;
        }else if(state.eo[0] == 1 && state.eo[1] == 1 && state.eo[4] == 1 && state.eo[8] == 1){
            return 1;
        }else{
            return 4;
        }
    }else if(eva_eo==8){
        if(state.eo[5] == 0 && state.eo[7] == 0 && state.eo[9] == 0 && state.eo[11] == 0){
            return 2;
        }else{
            return 5;
        }
    }else{
        return 10;
    }
}

int pre_cost_1(Cube state){
    int i, eva_co=0, sum_co=0;

    for(i=0; i<8; i++){
        if(state.co[i] != 0){
            eva_co++;
            sum_co = sum_co + state.co[i];
        }
    }

    if(eva_co==0){
        return 0;
    }else if(eva_co==4){
        if(state.co[1] == 1 && state.co[2] == 2 && state.co[5] == 2 && state.co[6] == 1){
            if((state.ep[5] == 0 || state.ep[5] == 1 || state.ep[5] == 2 || state.ep[5] == 3) && (state.ep[9] == 0 || state.ep[9] == 1 || state.ep[9] == 2 || state.ep[9] == 3)){
                return 1;
            }
        }else if(state.co[0] == 2 && state.co[3] == 1 && state.co[4] == 1 && state.co[7] == 2){
            if((state.ep[7] == 0 || state.ep[7] == 1 || state.ep[7] == 2 || state.ep[7] == 3) && (state.ep[11] == 0 || state.ep[11] == 1 || state.ep[11] == 2 || state.ep[11] == 3)){
                return 1;
            }
        }else if(sum_co == 6){
            return 3;
        }
    }else if(eva_co==8){
        if(state.co[1] == 1 && state.co[2] == 2 && state.co[5] == 2 && state.co[6] == 1 && state.co[0] == 2 && state.co[3] == 1 && state.co[4] == 1 && state.co[7] == 2){
            if((state.ep[5] == 0 || state.ep[5] == 1 || state.ep[5] == 2 || state.ep[5] == 3) && (state.ep[9] == 0 || state.ep[9] == 1 || state.ep[9] == 2 || state.ep[9] == 3)
                && (state.ep[7] == 0 || state.ep[7] == 1 || state.ep[7] == 2 || state.ep[7] == 3) && (state.ep[11] == 0 || state.ep[11] == 1 || state.ep[11] == 2 || state.ep[11] == 3)){
                return 2;
            }
        }else if(sum_co==12){
            return 5;
        }
    }else{
        return 10;
    }
}

int pre_cost_2(Cube state){
    int i, eva_cp=0, u=0, d=0;

    for(i=0; i<8; i++){
        if(i==0 || i==2 || i==5 || i==7){
            if(state.cp[i] != 0 && state.cp[i] != 2 && state.cp[i] != 5 && state.cp[i] != 7){
                eva_cp++;
                if(i==0 || i==2){
                    u++;
                }else{
                    d++;
                }
            }
        }else{
            if(state.cp[i] != 1 && state.cp[i] != 3 && state.cp[i] != 4 && state.cp[i] != 6){
                eva_cp++;
                if(i==1 || i==3){
                    u++;
                }else{
                    d++;
                }
            }
        }
    }

    if(eva_cp==0){
        return 0;
    }else if(eva_cp==4){
        if(u==4 || d==4){
            return 1;
        }
    }else if(eva_cp==8){
        return 2;
    }else{
        return 5;
    }
}

int pre_cost_3(Cube state){
    int i, eva=0;

    for(i=0; i<8; i++){
        if(state.cp[i] != i){
            eva++;
        }
    }

    for(i=0; i<12; i++){
        if(state.ep[i] != i){
            eva++;
        }
    }

    return eva/8;
}

int pre_cost_00(Cube state){
    int i, eva=0;

    for(i=0; i<12; i++){
        if(state.eo[i] != 0){
            if(i==5 || i==7 || i==9 || i==11){
                eva = eva + 2;
            }else{
                eva++;
            }
        }
    }

    // if(eva==4){
    //     if(state.eo[2] == 1 && state.eo[3] == 1 && state.eo[6] == 1 && state.eo[10] == 1){
    //         return 1;
    //     }else if(state.eo[0] == 1 && state.eo[1] == 1 && state.eo[4] == 1 && state.eo[8] == 1){
    //         return 1;
    //     }
    // }else if(eva==8){
    //     if(state.eo[5] == 0 && state.eo[7] == 0 && state.eo[9] == 0 && state.eo[11] == 0){
    //         return 2;
    //     }
    // }

    return eva;
}

int pre_cost_11(Cube state){
    int i, eva_co=0, eva_ep=0;

    for(i=0; i<8; i++){
        if(i==0 || i==7){
            if(state.co[i] == 2){
                eva_co++;
            }else if(state.co[i] == 1){
                eva_co = eva_co + 2;
            }
        }else if(i==1 || i==6){
            if(state.co[i] == 1){
                eva_co++;
            }else if(state.co[i] == 2){
                eva_co = eva_co + 2;
            }
        }else if(i==2 || i==5){
            if(state.co[i] == 2){
                eva_co++;
            }else if(state.co[i] == 1){
                eva_co = eva_co + 2;
            }
        }else if(i==3 || i==4){
            if(state.co[i] == 1){
                eva_co++;
            }else if(state.co[i] == 2){
                eva_co = eva_co + 2;
            }
        }
    }

    for(i=0; i<4; i++){
        if(state.ep[i]>=4){
            eva_ep++;
        }
    }

    return (eva_co + eva_ep)/4;
}

int pre_cost_22(Cube state){
    int i, eva_cp=0, eva_ep=0;

    for(i=0; i<8; i++){
        if(i==0 || i==2 || i==5 || i==7){
            if(state.cp[0] != i && state.cp[2] != i && state.cp[5] != i && state.cp[7] != i){
                eva_cp++;
            }
        }else{
            if(state.cp[1] != i && state.cp[3] != i && state.cp[4] != i && state.cp[6] != i){
                eva_cp++;
            }
        }
    }

    for(i=0; i<12; i++){
        if(i==4 || i==6 || i==8 || i==10){
            if(state.ep[4] != i && state.ep[6] != i && state.ep[8] != i && state.ep[10] != i){
                eva_ep++;
            }
        }else if(i==5 || i==7 || i==9 || i==11){
            if(state.ep[5] != i && state.ep[7] != i && state.ep[9] != i && state.ep[11] != i){
                eva_ep++;
            }
        }
    }

    return (eva_cp + eva_ep)/4;
}

int pre_cost_33(Cube state){
    int i, eva_cp=0, eva_ep=0;

    for(i=0; i<8; i++){
        if(state.cp[i] != i){
            eva_cp++;
        }
    }

    if(state.ep[0] != 0){
        if(state.ep[1] == 0 || state.ep[3] == 0){
            eva_ep++;
        }else if(state.ep[2] == 0){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[1] != 1){
        if(state.ep[0] == 1 || state.ep[2] == 1){
            eva_ep++;
        }else if(state.ep[3] == 1){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[2] != 2){
        if(state.ep[1] == 2 || state.ep[3] == 2){
            eva_ep++;
        }else if(state.ep[0] == 2){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[3] != 3){
        if(state.ep[0] == 3 || state.ep[2] == 3){
            eva_ep++;
        }else if(state.ep[1] == 3){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[4] != 4){
        if(state.ep[6] == 4 || state.ep[8] == 4){
            eva_ep++;
        }else if(state.ep[10] == 4){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[6] != 6){
        if(state.ep[4] == 6 || state.ep[10] == 6){
            eva_ep++;
        }else if(state.ep[8] == 6){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[8] != 8){
        if(state.ep[4] == 8 || state.ep[10] == 8){
            eva_ep++;
        }else if(state.ep[6] == 8){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[10] != 10){
        if(state.ep[6] == 10 || state.ep[8] == 10){
            eva_ep++;
        }else if(state.ep[4] == 10){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[5] != 5){
        if(state.ep[7] == 5 || state.ep[9] == 5){
            eva_ep++;
        }else if(state.ep[11] == 5){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[7] != 7){
        if(state.ep[5] == 7 || state.ep[11] == 7){
            eva_ep++;
        }else if(state.ep[9] == 7){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[9] != 9){
        if(state.ep[5] == 9 || state.ep[11] == 9){
            eva_ep++;
        }else if(state.ep[7] == 9){
            eva_ep = eva_ep + 2;
        }
    }

    if(state.ep[11] != 11){
        if(state.ep[7] == 11 || state.ep[9] == 11){
            eva_ep++;
        }else if(state.ep[5] == 11){
            eva_ep = eva_ep + 2;
        }
    }

    return (eva_cp + eva_ep);
}

int state_check(Cube state, Cube sol_state){
    int i, cost=0;

    for(i=0; i<8; i++){
        if(state.cp[i] != sol_state.cp[i]){
            cost++;
        }

        if(state.co[i] != sol_state.co[i]){
            cost++;
        }
    }

    for(i=0; i<12; i++){
        if(state.ep[i] != sol_state.ep[i]){
            cost++;
        }

        if(state.eo[i] != sol_state.eo[i]){
            cost++;
        }
    }

    return cost;
}

Cube r_move(Cube c_state){
    Cube n_state;

    n_state.cp[0] = c_state.cp[0];
    n_state.cp[1] = c_state.cp[2];
    n_state.cp[2] = c_state.cp[6];
    n_state.cp[3] = c_state.cp[3];
    n_state.cp[4] = c_state.cp[4];
    n_state.cp[5] = c_state.cp[1];
    n_state.cp[6] = c_state.cp[5];
    n_state.cp[7] = c_state.cp[7];

    n_state.co[0] = (c_state.co[0] + 0) % 3;
    n_state.co[1] = (c_state.co[2] + 1) % 3;
    n_state.co[2] = (c_state.co[6] + 2) % 3;
    n_state.co[3] = (c_state.co[3] + 0) % 3;
    n_state.co[4] = (c_state.co[4] + 0) % 3;
    n_state.co[5] = (c_state.co[1] + 2) % 3;
    n_state.co[6] = (c_state.co[5] + 1) % 3;
    n_state.co[7] = (c_state.co[7] + 0) % 3;

    n_state.ep[0] = c_state.ep[0];
    n_state.ep[1] = c_state.ep[5];
    n_state.ep[2] = c_state.ep[9];
    n_state.ep[3] = c_state.ep[3];
    n_state.ep[4] = c_state.ep[4];
    n_state.ep[5] = c_state.ep[2];
    n_state.ep[6] = c_state.ep[6];
    n_state.ep[7] = c_state.ep[7];
    n_state.ep[8] = c_state.ep[8];
    n_state.ep[9] = c_state.ep[1];
    n_state.ep[10] = c_state.ep[10];
    n_state.ep[11] = c_state.ep[11];

    n_state.eo[0] = c_state.eo[0];
    n_state.eo[1] = c_state.eo[5];
    n_state.eo[2] = c_state.eo[9];
    n_state.eo[3] = c_state.eo[3];
    n_state.eo[4] = c_state.eo[4];
    n_state.eo[5] = c_state.eo[2];
    n_state.eo[6] = c_state.eo[6];
    n_state.eo[7] = c_state.eo[7];
    n_state.eo[8] = c_state.eo[8];
    n_state.eo[9] = c_state.eo[1];
    n_state.eo[10] = c_state.eo[10];
    n_state.eo[11] = c_state.eo[11];

    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "r");

    return n_state;
}

Cube l_move(Cube c_state){
    Cube n_state;

    n_state.cp[0] = c_state.cp[4];
    n_state.cp[1] = c_state.cp[1];
    n_state.cp[2] = c_state.cp[2];
    n_state.cp[3] = c_state.cp[0];
    n_state.cp[4] = c_state.cp[7];
    n_state.cp[5] = c_state.cp[5];
    n_state.cp[6] = c_state.cp[6];
    n_state.cp[7] = c_state.cp[3];

    n_state.co[0] = (c_state.co[4] + 2) % 3;
    n_state.co[1] = (c_state.co[1] + 0) % 3;
    n_state.co[2] = (c_state.co[2] + 0) % 3;
    n_state.co[3] = (c_state.co[0] + 1) % 3;
    n_state.co[4] = (c_state.co[7] + 1) % 3;
    n_state.co[5] = (c_state.co[5] + 0) % 3;
    n_state.co[6] = (c_state.co[6] + 0) % 3;
    n_state.co[7] = (c_state.co[3] + 2) % 3;

    n_state.ep[0] = c_state.ep[11];
    n_state.ep[1] = c_state.ep[1];
    n_state.ep[2] = c_state.ep[2];
    n_state.ep[3] = c_state.ep[7];
    n_state.ep[4] = c_state.ep[4];
    n_state.ep[5] = c_state.ep[5];
    n_state.ep[6] = c_state.ep[6];
    n_state.ep[7] = c_state.ep[0];
    n_state.ep[8] = c_state.ep[8];
    n_state.ep[9] = c_state.ep[9];
    n_state.ep[10] = c_state.ep[10];
    n_state.ep[11] = c_state.ep[3];

    n_state.eo[0] = c_state.eo[11];
    n_state.eo[1] = c_state.eo[1];
    n_state.eo[2] = c_state.eo[2];
    n_state.eo[3] = c_state.eo[7];
    n_state.eo[4] = c_state.eo[4];
    n_state.eo[5] = c_state.eo[5];
    n_state.eo[6] = c_state.eo[6];
    n_state.eo[7] = c_state.eo[0];
    n_state.eo[8] = c_state.eo[8];
    n_state.eo[9] = c_state.eo[9];
    n_state.eo[10] = c_state.eo[10];
    n_state.eo[11] = c_state.eo[3];

    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "l");

    return n_state;
}

Cube u_move(Cube c_state){
    Cube n_state;

    n_state.cp[0] = c_state.cp[3];
    n_state.cp[1] = c_state.cp[0];
    n_state.cp[2] = c_state.cp[1];
    n_state.cp[3] = c_state.cp[2];
    n_state.cp[4] = c_state.cp[4];
    n_state.cp[5] = c_state.cp[5];
    n_state.cp[6] = c_state.cp[6];
    n_state.cp[7] = c_state.cp[7];

    n_state.co[0] = c_state.co[3];
    n_state.co[1] = c_state.co[0];
    n_state.co[2] = c_state.co[1];
    n_state.co[3] = c_state.co[2];
    n_state.co[4] = c_state.co[4];
    n_state.co[5] = c_state.co[5];
    n_state.co[6] = c_state.co[6];
    n_state.co[7] = c_state.co[7];

    n_state.ep[0] = c_state.ep[0];
    n_state.ep[1] = c_state.ep[1];
    n_state.ep[2] = c_state.ep[2];
    n_state.ep[3] = c_state.ep[3];
    n_state.ep[4] = c_state.ep[7];
    n_state.ep[5] = c_state.ep[4];
    n_state.ep[6] = c_state.ep[5];
    n_state.ep[7] = c_state.ep[6];
    n_state.ep[8] = c_state.ep[8];
    n_state.ep[9] = c_state.ep[9];
    n_state.ep[10] = c_state.ep[10];
    n_state.ep[11] = c_state.ep[11];

    n_state.eo[0] = c_state.eo[0];
    n_state.eo[1] = c_state.eo[1];
    n_state.eo[2] = c_state.eo[2];
    n_state.eo[3] = c_state.eo[3];
    n_state.eo[4] = c_state.eo[7];
    n_state.eo[5] = c_state.eo[4];
    n_state.eo[6] = c_state.eo[5];
    n_state.eo[7] = c_state.eo[6];
    n_state.eo[8] = c_state.eo[8];
    n_state.eo[9] = c_state.eo[9];
    n_state.eo[10] = c_state.eo[10];
    n_state.eo[11] = c_state.eo[11];

    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "u");

    return n_state;
}

Cube d_move(Cube c_state){
    Cube n_state;

    n_state.cp[0] = c_state.cp[0];
    n_state.cp[1] = c_state.cp[1];
    n_state.cp[2] = c_state.cp[2];
    n_state.cp[3] = c_state.cp[3];
    n_state.cp[4] = c_state.cp[5];
    n_state.cp[5] = c_state.cp[6];
    n_state.cp[6] = c_state.cp[7];
    n_state.cp[7] = c_state.cp[4];

    n_state.co[0] = c_state.co[0];
    n_state.co[1] = c_state.co[1];
    n_state.co[2] = c_state.co[2];
    n_state.co[3] = c_state.co[3];
    n_state.co[4] = c_state.co[5];
    n_state.co[5] = c_state.co[6];
    n_state.co[6] = c_state.co[7];
    n_state.co[7] = c_state.co[4];

    n_state.ep[0] = c_state.ep[0];
    n_state.ep[1] = c_state.ep[1];
    n_state.ep[2] = c_state.ep[2];
    n_state.ep[3] = c_state.ep[3];
    n_state.ep[4] = c_state.ep[4];
    n_state.ep[5] = c_state.ep[5];
    n_state.ep[6] = c_state.ep[6];
    n_state.ep[7] = c_state.ep[7];
    n_state.ep[8] = c_state.ep[9];
    n_state.ep[9] = c_state.ep[10];
    n_state.ep[10] = c_state.ep[11];
    n_state.ep[11] = c_state.ep[8];

    n_state.eo[0] = c_state.eo[0];
    n_state.eo[1] = c_state.eo[1];
    n_state.eo[2] = c_state.eo[2];
    n_state.eo[3] = c_state.eo[3];
    n_state.eo[4] = c_state.eo[4];
    n_state.eo[5] = c_state.eo[5];
    n_state.eo[6] = c_state.eo[6];
    n_state.eo[7] = c_state.eo[7];
    n_state.eo[8] = c_state.eo[9];
    n_state.eo[9] = c_state.eo[10];
    n_state.eo[10] = c_state.eo[11];
    n_state.eo[11] = c_state.eo[8];

    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "d");

    return n_state;
}

Cube f_move(Cube c_state){
    Cube n_state;

    n_state.cp[0] = c_state.cp[0];
    n_state.cp[1] = c_state.cp[1];
    n_state.cp[2] = c_state.cp[3];
    n_state.cp[3] = c_state.cp[7];
    n_state.cp[4] = c_state.cp[4];
    n_state.cp[5] = c_state.cp[5];
    n_state.cp[6] = c_state.cp[2];
    n_state.cp[7] = c_state.cp[6];

    n_state.co[0] = (c_state.co[0] + 0) % 3;
    n_state.co[1] = (c_state.co[1] + 0) % 3;
    n_state.co[2] = (c_state.co[3] + 1) % 3;
    n_state.co[3] = (c_state.co[7] + 2) % 3;
    n_state.co[4] = (c_state.co[4] + 0) % 3;
    n_state.co[5] = (c_state.co[5] + 0) % 3;
    n_state.co[6] = (c_state.co[2] + 2) % 3;
    n_state.co[7] = (c_state.co[6] + 1) % 3;

    n_state.ep[0] = c_state.ep[0];
    n_state.ep[1] = c_state.ep[1];
    n_state.ep[2] = c_state.ep[6];
    n_state.ep[3] = c_state.ep[10];
    n_state.ep[4] = c_state.ep[4];
    n_state.ep[5] = c_state.ep[5];
    n_state.ep[6] = c_state.ep[3];
    n_state.ep[7] = c_state.ep[7];
    n_state.ep[8] = c_state.ep[8];
    n_state.ep[9] = c_state.ep[9];
    n_state.ep[10] = c_state.ep[2];
    n_state.ep[11] = c_state.ep[11];

    n_state.eo[0] = (c_state.eo[0] + 0) % 2;
    n_state.eo[1] = (c_state.eo[1] + 0) % 2;
    n_state.eo[2] = (c_state.eo[6] + 1) % 2;
    n_state.eo[3] = (c_state.eo[10] + 1) % 2;
    n_state.eo[4] = (c_state.eo[4] + 0) % 2;
    n_state.eo[5] = (c_state.eo[5] + 0) % 2;
    n_state.eo[6] = (c_state.eo[3] + 1) % 2;
    n_state.eo[7] = (c_state.eo[7] + 0) % 2;
    n_state.eo[8] = (c_state.eo[8] + 0) % 2;
    n_state.eo[9] = (c_state.eo[9] + 0) % 2;
    n_state.eo[10] = (c_state.eo[2] + 1) % 2;
    n_state.eo[11] = (c_state.eo[11] + 0) % 2;

    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "f");

    return n_state;
}

Cube b_move(Cube c_state){
    Cube n_state;

    n_state.cp[0] = c_state.cp[1];
    n_state.cp[1] = c_state.cp[5];
    n_state.cp[2] = c_state.cp[2];
    n_state.cp[3] = c_state.cp[3];
    n_state.cp[4] = c_state.cp[0];
    n_state.cp[5] = c_state.cp[4];
    n_state.cp[6] = c_state.cp[6];
    n_state.cp[7] = c_state.cp[7];

    n_state.co[0] = (c_state.co[1] + 1) % 3;
    n_state.co[1] = (c_state.co[5] + 2) % 3;
    n_state.co[2] = (c_state.co[2] + 0) % 3;
    n_state.co[3] = (c_state.co[3] + 0) % 3;
    n_state.co[4] = (c_state.co[0] + 2) % 3;
    n_state.co[5] = (c_state.co[4] + 1) % 3;
    n_state.co[6] = (c_state.co[6] + 0) % 3;
    n_state.co[7] = (c_state.co[7] + 0) % 3;

    n_state.ep[0] = c_state.ep[4];
    n_state.ep[1] = c_state.ep[8];
    n_state.ep[2] = c_state.ep[2];
    n_state.ep[3] = c_state.ep[3];
    n_state.ep[4] = c_state.ep[1];
    n_state.ep[5] = c_state.ep[5];
    n_state.ep[6] = c_state.ep[6];
    n_state.ep[7] = c_state.ep[7];
    n_state.ep[8] = c_state.ep[0];
    n_state.ep[9] = c_state.ep[9];
    n_state.ep[10] = c_state.ep[10];
    n_state.ep[11] = c_state.ep[11];

    n_state.eo[0] = (c_state.eo[4] + 1) % 2;
    n_state.eo[1] = (c_state.eo[8] + 1) % 2;
    n_state.eo[2] = (c_state.eo[2] + 0) % 2;
    n_state.eo[3] = (c_state.eo[3] + 0) % 2;
    n_state.eo[4] = (c_state.eo[1] + 1) % 2;
    n_state.eo[5] = (c_state.eo[5] + 0) % 2;
    n_state.eo[6] = (c_state.eo[6] + 0) % 2;
    n_state.eo[7] = (c_state.eo[7] + 0) % 2;
    n_state.eo[8] = (c_state.eo[0] + 1) % 2;
    n_state.eo[9] = (c_state.eo[9] + 0) % 2;
    n_state.eo[10] = (c_state.eo[10] + 0) % 2;
    n_state.eo[11] = (c_state.eo[11] + 0) % 2;

    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "b");

    return n_state;
}

Cube rr_move(Cube c_state){
    Cube n_state;

    n_state = r_move(r_move(r_move(c_state)));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "rr");
    return n_state;
}

Cube lr_move(Cube c_state){
    Cube n_state;

    n_state = l_move(l_move(l_move(c_state)));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "lr");
    return n_state;
}

Cube ur_move(Cube c_state){
    Cube n_state;

    n_state = u_move(u_move(u_move(c_state)));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "ur");
    return n_state;
}

Cube dr_move(Cube c_state){
    Cube n_state;

    n_state = d_move(d_move(d_move(c_state)));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "dr");
    return n_state;
}

Cube fr_move(Cube c_state){
    Cube n_state;

    n_state = f_move(f_move(f_move(c_state)));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "fr");
    return n_state;
}

Cube br_move(Cube c_state){
    Cube n_state;

    n_state = b_move(b_move(b_move(c_state)));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "br");
    return n_state;
}

Cube r2_move(Cube c_state){
    Cube n_state;

    n_state = r_move(r_move(c_state));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "r2");
    return n_state;
}

Cube l2_move(Cube c_state){
    Cube n_state;

    n_state = l_move(l_move(c_state));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "l2");
    return n_state;
}

Cube u2_move(Cube c_state){
    Cube n_state;

    n_state = u_move(u_move(c_state));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "u2");
    return n_state;
}

Cube d2_move(Cube c_state){
    Cube n_state;

    n_state = d_move(d_move(c_state));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "d2");
    return n_state;
}

Cube f2_move(Cube c_state){
    Cube n_state;

    n_state = f_move(f_move(c_state));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "f2");
    return n_state;
}

Cube b2_move(Cube c_state){
    Cube n_state;

    n_state = b_move(b_move(c_state));
    n_state.step = c_state.step + 1;
    strcpy(n_state.move, "b2");
    return n_state;
}
