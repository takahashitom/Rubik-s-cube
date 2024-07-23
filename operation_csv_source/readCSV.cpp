#include "operation_csv.h"

using namespace std;

vector<vector<int>> readCSV(const string &filename)
{
    vector<vector<int>> data;
    ifstream file(filename);

    if (!file)
    {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        vector<int> row;
        string cell;

        while (getline(ss, cell, ','))
        {
            row.push_back(stoi(cell)); // 文字列を整数に変換して配列に追加
        }

        data.push_back(row);
    }

    file.close();

    return data;
}