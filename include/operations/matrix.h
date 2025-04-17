#pragma once

#include <string.h>
#include <cstdint>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;
typedef std::vector<Matrix> Matrixs;

Matrix array_to_matrix(char* data, uint32_t len, uint32_t rows);
Matrix array_to_matrix(char* data,
                       uint32_t len,
                       uint32_t rows,
                       uint32_t columns);
Matrixs array_to_matrixs(char* data,
                         uint32_t len,
                         uint32_t matrix_num,
                         uint32_t rows);
Matrixs array_to_matrixs(char* data,
                         uint32_t len,
                         uint32_t matrix_num,
                         uint32_t rows,
                         uint32_t columns);
