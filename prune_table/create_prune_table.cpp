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

vector<vector<int>> make_eo_e_prune_table()
{
    // 遷移表を読み込む処理
    string file_eo = "../move_table/eo_move_table.csv";
    string file_e = "../move_table/e_combination_table.csv";
    vector<vector<int>> eo_move_table = readCSV(file_eo);
    vector<vector<int>> e_combination_table = readCSV(file_e);

    const int NUM_EO = 2048;    // coのとり得る状態の数
    const int NUM_E_COMB = 495; // e列のエッジパーツの状態の数
    vector<vector<int>> eo_e_prune_table(NUM_EO, vector<int>(NUM_E_COMB, -1));
    int distance = 0;
    int num_filled = 0;

    while (num_filled < NUM_EO * NUM_E_COMB)
    {
        if (num_filled == 0)
        {
            eo_e_prune_table[0][0] = distance;
            num_filled++;
            cout << "numfilled: " << num_filled << endl;
            continue;
        }

        for (int i_eo = 0; i_eo < NUM_EO; i_eo++)
        {
            for (int i_e = 0; i_e < NUM_E_COMB; i_e++)
            {
                if (eo_e_prune_table[i_eo][i_e] == distance)
                {
                    // 現在の状態から全動作（18個の動作）を行う
                    for (int move = 0; move < 18; move++)
                    {
                        int next_eo = eo_move_table[i_eo][move];
                        int next_e = e_combination_table[i_e][move];
                        if (eo_e_prune_table[next_eo][next_e] == -1)
                        {
                            eo_e_prune_table[next_eo][next_e] = distance + 1;
                            num_filled++;
                            cout << "numfilled: " << num_filled << endl;
                        }
                    }
                }
            }
        }

        distance++;
    }

    return eo_e_prune_table;
}

vector<vector<int>> make_cp_e_ep_prune_table()
{
    // 遷移表を読み込む処理
    string file_cp = "../move_table/cp_move_table.csv";
    string file_eep = "../move_table/e_ep_move_table.csv";
    vector<vector<int>> cp_move_table = readCSV(file_cp);
    vector<vector<int>> e_ep_move_table = readCSV(file_eep);

    const int NUM_CP = 40320; // coのとり得る状態の数
    const int NUM_EP = 24;    // e列のエッジパーツの状態の数
    vector<vector<int>> cp_e_ep_prune_table(NUM_CP, vector<int>(NUM_EP, -1));
    int distance = 0;
    int num_filled = 0;

    while (num_filled < NUM_CP * NUM_EP)
    {
        if (num_filled == 0)
        {
            cp_e_ep_prune_table[0][0] = distance;
            num_filled++;
            cout << "numfilled: " << num_filled << endl;
            continue;
        }

        for (int i_cp = 0; i_cp < NUM_CP; i_cp++)
        {
            for (int i_eep = 0; i_eep < NUM_EP; i_eep++)
            {
                if (cp_e_ep_prune_table[i_cp][i_eep] == distance)
                {
                    // 現在の状態からphase2の動作（10個の動作）を行う
                    for (int move = 0; move < 10; move++)
                    {
                        int next_cp = cp_move_table[i_cp][move];
                        int next_eep = e_ep_move_table[i_eep][move];
                        if (cp_e_ep_prune_table[next_cp][next_eep] == -1)
                        {
                            cp_e_ep_prune_table[next_cp][next_eep] = distance + 1;
                            num_filled++;
                            cout << "cp: " << next_cp << ", eep: " << next_eep << ", numfilled: " << num_filled << endl;
                        }
                    }
                }
            }
        }

        distance++;
    }

    return cp_e_ep_prune_table;
}

vector<vector<int>> make_ud_ep_e_ep_prune_table()
{
    // 遷移表を読み込む処理
    string file_udep = "../move_table/ud_ep_move_table.csv";
    string file_eep = "../move_table/e_ep_move_table.csv";
    vector<vector<int>> cp_move_table = readCSV(file_udep);
    vector<vector<int>> e_ep_move_table = readCSV(file_eep);

    const int NUM_UDEP = 40320; // coのとり得る状態の数
    const int NUM_EP = 24;      // e列のエッジパーツの状態の数
    vector<vector<int>> ud_ep_e_ep_prune_table(NUM_UDEP, vector<int>(NUM_EP, -1));
    int distance = 0;
    int num_filled = 0;

    while (num_filled < NUM_UDEP * NUM_EP)
    {
        if (num_filled == 0)
        {
            ud_ep_e_ep_prune_table[0][0] = distance;
            num_filled++;
            cout << "numfilled: " << num_filled << endl;
            continue;
        }

        for (int i_udep = 0; i_udep < NUM_UDEP; i_udep++)
        {
            for (int i_eep = 0; i_eep < NUM_EP; i_eep++)
            {
                if (ud_ep_e_ep_prune_table[i_udep][i_eep] == distance)
                {
                    // 現在の状態からphase2の動作（10個の動作）を行う
                    for (int move = 0; move < 10; move++)
                    {
                        int next_cp = cp_move_table[i_udep][move];
                        int next_eep = e_ep_move_table[i_eep][move];
                        if (ud_ep_e_ep_prune_table[next_cp][next_eep] == -1)
                        {
                            ud_ep_e_ep_prune_table[next_cp][next_eep] = distance + 1;
                            num_filled++;
                            cout << "udep: " << next_cp << ", eep: " << next_eep << ", numfilled: " << num_filled << endl;
                        }
                    }
                }
            }
        }

        distance++;
    }

    return ud_ep_e_ep_prune_table;
}

int main()
{
    // string file_co_e = "co_e_prune_table.csv";
    // cout << "start" << endl;
    // vector<vector<int>> tab_co_e = make_co_e_prune_table();
    // writeCSV(tab_co_e, file_co_e);

    // string file_eo_e = "eo_e_prune_table.csv";
    // cout << "start" << endl;
    // vector<vector<int>> tab_eo_e = make_eo_e_prune_table();
    // writeCSV(tab_eo_e, file_eo_e);

    // string file_cp_e_ep = "cp_e_ep_prune_table.csv";
    // cout << "start" << endl;
    // vector<vector<int>> tab_cp_e_ep = make_cp_e_ep_prune_table();
    // writeCSV(tab_cp_e_ep, file_cp_e_ep);

    string file_ud_ep_e_ep = "ud_ep_e_ep_prune_table.csv";
    cout << "start" << endl;
    vector<vector<int>> tab_ud_ep_e_ep = make_ud_ep_e_ep_prune_table();
    writeCSV(tab_ud_ep_e_ep, file_ud_ep_e_ep);
}