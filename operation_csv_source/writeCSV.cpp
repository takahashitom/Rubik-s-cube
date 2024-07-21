#include "operation_csv.h"

using namespace std;

void writeCSV(const vector<vector<int>> &data, const string &filename)
{
    ofstream file(filename);

    if (!file)
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    for (const auto &row : data)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            file << row[i];
            if (i != row.size() - 1)
                file << ","; // CSVはカンマで列を区切る
        }
        file << endl; // 行を区切る
    }

    file.close();
}