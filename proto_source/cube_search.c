#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define N 1000000

typedef struct state
{
    int cp[8];
    int co[8];
    int ep[12];
    int eo[12];
    int step;
    int cost;
    char move[2];
} Cube;

Cube r_move(Cube);
Cube l_move(Cube);
Cube u_move(Cube);
Cube d_move(Cube);
Cube f_move(Cube);
Cube b_move(Cube);
Cube rr_move(Cube);
Cube lr_move(Cube);
Cube ur_move(Cube);
Cube dr_move(Cube);
Cube fr_move(Cube);
Cube br_move(Cube);
Cube r2_move(Cube);
Cube l2_move(Cube);
Cube u2_move(Cube);
Cube d2_move(Cube);
Cube f2_move(Cube);
Cube b2_move(Cube);

int sol_check(Cube, Cube);
void print_route(int prev[], int g, Cube state[]);
int pre_cost(Cube);
int add(Cube state[], int num, int open[], int size, int top, int prev[]);
int pre_cost2(Cube state);
int cp_cost(int posi, int parts);
int ep_cost(int posi, int parts);

int main(void){
    
    Cube sol_state = {{0,1,2,3,4,5,6,7}, 
                    {0,0,0,0,0,0,0,0},
                    {0,1,2,3,4,5,6,7,8,9,10,11},
                    {0,0,0,0,0,0,0,0,0,0,0,0}};

    Cube start_state = {{6,3,5,2,0,4,7,1},
                    {2,0,2,1,2,1,2,2},
                    {4,8,10,5,6,7,9,2,0,1,3,11},
                    {1,1,1,0,0,0,1,0,1,0,1,0},
                    0,
                    -1,
                    "S"};

    Cube *state = (Cube*)calloc(N, sizeof(Cube));
    
    int *open = (int*)calloc(N, sizeof(int));
    
    int num = 0;
    int size = 0;
    int top, i, mindex, tmp;
    
    int *prev = (int*)calloc(N, sizeof(int));

    clock_t start_time, end_time;

    if(state == NULL){
        printf("domain error\n");
        exit(-1);
    }

    if(open == NULL){
        printf("domain error\n");
        exit(-1);
    }

    if(prev == NULL){
        printf("domain error\n");
        exit(-1);
    }
    
    start_time = clock();

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

        if(sol_check(state[top], sol_state) == 0){
            printf("OK\n");
            print_route(prev, top, state);
            printf("steps: %d\n", state[top].step);
            free(state);
            free(open);
            free(prev);

            end_time = clock();
            printf("clock:%f\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
            return 0;
        }

        if(strncmp(state[top].move, "r", 1) != 0){
        
            state[num] = r_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = rr_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = r2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "l", 1) != 0){
        
            state[num] = l_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = lr_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = l2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "u", 1) != 0){
        
            state[num] = u_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = ur_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = u2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "d", 1) != 0){
        
            state[num] = d_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = dr_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = d2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "f", 1) != 0){
        
            state[num] = f_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = fr_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = f2_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;
        }

        if(strncmp(state[top].move, "b", 1) != 0){

            state[num] = b_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

            state[num] = br_move(state[top]);
            size = add(state, num, open, size, top, prev);

            num++;

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
    int i, eva_c=0, eva_e=0, eva_eo=0;

    for(i=0; i<8; i++){
        if(state.cp[i] == i && state.co[i] == 0){
            eva_c++;
        } 
    }

    for(i=0; i<12; i++){
        if(state.eo[i] == 0){
            if(state.ep[i] == i){
                eva_e++;
            }
        }else{
            eva_eo++;
        }
    }

    if(eva_c == 8 && eva_e == 12){
        return 0;
    }else if(eva_c >= 4 && eva_e >= 8){
        return 1;
    }else if(eva_e >= 4){
        return 2;
    }else if(eva_e >= 2){
        return 3;
    }else if(eva_eo == 0){
        return 7;
    }else if(eva_eo == 4){
        if(state.eo[2] == 1 && state.eo[3] == 1 && state.eo[6] == 1 && state.eo[10] == 1){
            return 8;
        }
        if(state.eo[0] == 1 && state.eo[1] == 1 && state.eo[4] == 1 && state.eo[8] == 1){
            return 8;
        }
    }else if(eva_eo == 8){
        if(state.eo[5] == 0 && state.eo[7] == 0 && state.eo[9] == 0 && state.eo[11] == 0){
            return 9;
        }
    }else if(eva_eo == 4){
        return 11;
    }else if(eva_eo == 8){
        return 12;
    }

    return 15;
}

int pre_cost2(Cube state){
    int i, cost=0;

    for(i=0; i<8; i++){
        cost = cost + cp_cost(i, state.cp[i]);
    }

    for(i=0; i<12; i++){
        cost = cost + ep_cost(i, state.ep[i]);
    }

    return cost/8;
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

    return -1;
}

int ep_cost(int posi, int parts){
    if(posi==parts){
        return 0;
    }else if(posi==0){
        if(parts==2 || parts==5 || parts==6 || parts==9 || parts==10){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==1){
        if(parts==3 || parts==6 || parts==7 || parts==10 || parts==11){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==2){
        if(parts==0 || parts==4 || parts==7 || parts==8 || parts==11){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==3){
        if(parts==1 || parts==4 || parts==5 || parts==8 || parts==9){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==4){
        if(parts==2 || parts==3 || parts==9 || parts==10 || parts==11){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==5){
        if(parts==0 || parts==3 || parts==8 || parts==10 || parts==11){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==6){
        if(parts==0 || parts==1 || parts==8 || parts==9 || parts==11){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==7){
        if(parts==1 || parts==2 || parts==8 || parts==9 || parts==10){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==8){
        if(parts==2 || parts==3 || parts==5 || parts==6 || parts==7){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==9){
        if(parts==0 || parts==3 || parts==4 || parts==6 || parts==7){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==10){
        if(parts==0 || parts==1 || parts==4 || parts==5 || parts==7){
            return 2;
        }else{
            return 1;
        }
    }else if(posi==11){
        if(parts==1 || parts==2 || parts==4 || parts==5 || parts==6){
            return 2;
        }else{
            return 1;
        }
    }

    return -1;
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
