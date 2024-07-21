#ifndef OPERATION_CSV_H_
#define OPERATION_CSV_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void writeCSV(const std::vector<std::vector<int>> &data, const std::string &filename);

#endif