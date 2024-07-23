#include "index.h"
#include "operation_csv.h"

using namespace std;

vector<vector<int>> make_co_e_prune_table()
{
    // 遷移表を読み込む処理
    string file_co = "../move_table/co_move_table.csv";
    string file_e = "../move_table/e_combination_table.csv";
    vector<vector<int>> co_move_table = readCSV(file_co);
    vector<vector<int>> e_combination_table = readCSV(file_e);

    const int NUM_CO = 2187;    // coのとり得る状態の数
    const int NUM_E_COMB = 495; // e列のエッジパーツの状態の数
    vector<vector<int>> co_e_prune_table(NUM_CO, vector<int>(NUM_E_COMB, -1));
    int distance = 0;
    int num_filled = 0;

    while (num_filled < NUM_CO * NUM_E_COMB)
    {
        if (num_filled == 0)
        {
            co_e_prune_table[0][0] = distance;
            num_filled++;
            cout << "numfilled: " << num_filled << endl;
            continue;
        }

        for (int i_co = 0; i_co < NUM_CO; i_co++)
        {
            for (int i_e = 0; i_e < NUM_E_COMB; i_e++)
            {
                if (co_e_prune_table[i_co][i_e] == distance)
                {
                    // 現在の状態から全動作（18個の動作）を行う
                    for (int move = 0; move < 18; move++)
                    {
                        int next_co = co_move_table[i_co][move];
                        int next_e = e_combination_table[i_e][move];
                        if (co_e_prune_table[next_co][next_e] == -1)
                        {
                            co_e_prune_table[next_co][next_e] = distance + 1;
                            num_filled++;
                            cout << "numfilled: " << num_filled << endl;
                        }
                    }
                }
            }
        }

        distance++;
    }

    return co_e_prune_table;
}

int main()
{
    string file_co_e = "co_e_prune_table.csv";
    cout << "start" << endl;
    vector<vector<int>> tab_co_e = make_co_e_prune_table();
    writeCSV(tab_co_e, file_co_e);
}