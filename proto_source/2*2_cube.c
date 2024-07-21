#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 100000

//状態を示す構造体
typedef struct state
{
    int cp[8]; //コーナーパーツ
    int co[8]; //コーナーパーツの向き
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

int sol_check(Cube, Cube); //完成チェック
void print_route(int prev[], int g, Cube state[]);
int pre_cost(Cube); //残り手数予測
int add(Cube state[], int num, int open[], int size, int top, int prev[]); //新たなノードをopenに追加
int pre_cost2(Cube state);
int cp_cost(int posi, int parts);
int ep_cost(int posi, int parts);

int main(void){
    
    //完成状態
    Cube sol_state = {{0,1,2,3,4,5,6,7}, 
                    {0,0,0,0,0,0,0,0},};

    //開始状態
    // Cube start_state = {{6,3,5,2,0,4,7,1},
    //                 {2,0,2,1,2,1,2,2},
    //                 {4,8,10,5,6,7,9,2,0,1,3,11},
    //                 {1,1,1,0,0,0,1,0,1,0,1,0},
    //                 0,
    //                 -1,
    //                 "S"};

    Cube start_state = {{2,3,6,5,1,0,7,4},
                    {1,2,1,2,2,1,2,1},
                    0,
                    -1,
                    "S"};

    //6手
    // Cube start_state = {{5,6,3,4,0,2,7,1},
    //                 {2,1,0,0,1,1,1,0},
    //                 0,
    //                 -1,
    //                 "S"};

    //8手
    // Cube start_state = {{4,6,7,0,3,2,1,5},
    //                 {1,1,2,1,2,1,2,2},
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
    int num = 0; //配列stateのナンバー
    int size = 0;
    int top, i, mindex, tmp;
    
    int *prev = (int*)calloc(N, sizeof(int));
    if(state == NULL){
        printf("domain error\n");
        exit(-1);
    }

    //開始状態のコスト計算
    start_state.cost = pre_cost(start_state);

    open[size++] = num;
    prev[num] = -1;
    state[num++] = start_state;

    
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

        if(sol_check(state[top], sol_state) == 0){
            printf("\nOK\n");
            print_route(prev, top, state);
            printf("steps: %d\n", state[top].step);
            free(state);
            free(open);
            free(prev);
            return 0;
        }

        if(strncmp(state[top].move, "r", 1) != 0){
            //r回転した場合
            state[num] = r_move(state[top]);
            size = add(state, num, open, size, top, prev);
            printf("%d, %d, %d\n", num, state[num].cost, state[num].step);

            num++;

            //rr回転した場合
            state[num] = rr_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //r2回転した場合
            state[num] = r2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "l", 1) != 0){
            //l回転した場合
            state[num] = l_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //lr回転した場合
            state[num] = lr_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //l2回転した場合
            state[num] = l2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "u", 1) != 0){
            //u回転した場合
            state[num] = u_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //ur回転した場合
            state[num] = ur_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //u2回転した場合
            state[num] = u2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "d", 1) != 0){
            //d回転した場合
            state[num] = d_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //dr回転した場合
            state[num] = dr_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //d2回転した場合
            state[num] = d2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "f", 1) != 0){
            //f回転した場合
            state[num] = f_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //fr回転した場合
            state[num] = fr_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //f2回転した場合
            state[num] = f2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "b", 1) != 0){
            //b回転した場合
            state[num] = b_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //br回転した場合
            state[num] = br_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            //b2回転した場合
            state[num] = b2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

    }

    printf("\nNG\n");

    printf("%d\n", state[0].cost);

    free(state);
    free(open);
    free(prev);
    return 0;
}

int sol_check(Cube state, Cube sol_state){
    int i, cost=0;

    for(i=0; i<8; i++){
        if(state.cp[i] != sol_state.cp[i]){
            cost++;
        }

        if(state.co[i] != sol_state.co[i]){
            cost++;
        }
    }

    return cost;
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

int pre_cost(Cube state){
    int i, eva_c=0, eva_co=0;

    for(i=0; i<8; i++){
        if(state.co[i] == 0){
            eva_co++;
            if(state.cp[i] == i){
                eva_c++;
            } 
        }
    }

    if(eva_c == 8){
        return 0;
    }else if(eva_c >= 4){
        return 1;
    }else if(eva_c >= 2){
        return 2;
    }else if(state.co[1] == 1 && state.co[2] == 2 && state.co[5] == 2 && state.co[6] == 1){
        if(state.co[0] == 2 && state.co[3] == 1 && state.co[4] == 1 && state.co[7] == 2){
            return 2;
        }
    }else if(state.co[2] == 1 && state.co[3] == 2 && state.co[6] == 2 && state.co[7] == 1){
        if(state.co[0] == 1 && state.co[1] == 2 && state.co[4] == 2 && state.co[5] == 1){
            return 2;
        }
    }else if(eva_co == 8){
        return 4;
    }else if(eva_co == 4){
        return 5;
    }

    return 10;
}

int pre_cost2(Cube state){
    int i, cost=0;

    for(i=0; i<8; i++){
        cost = cost + cp_cost(i, state.cp[i]);
    }

    return cost;
}

int cp_cost(int posi, int parts){
    if(posi==parts){
        return 0;
    }else if(posi==0 || posi==6){
        if(parts==6 || parts==0){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==1 || posi==7){
        if(parts==7 || parts==1){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==2 || posi==4){
        if(parts==4 || parts==2){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==3 || posi==5){
        if(parts==5 || parts==3){
            return 2;
        }else{
            return 1;
        }
    }
}

int add(Cube state[], int num, int open[], int size, int top, int prev[]){
    int i, tmp, flag=0;

    state[num].cost = pre_cost2(state[num]);

    for(i=0; i<num; i++){
        if(sol_check(state[num], state[i]) == 0){
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
