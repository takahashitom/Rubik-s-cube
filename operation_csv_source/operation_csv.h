#ifndef OPERATION_CSV_H_
#define OPERATION_CSV_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void writeCSV(const std::vector<std::vector<int>> &data, const std::string &filename);
std::vector<std::vector<int>> readCSV(const std::string &filename);

#endif