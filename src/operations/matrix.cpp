#include "operations/matrix.h"

Matrix array_to_matrix(char* data, uint32_t len, uint32_t rows) {
    if (len < rows) {
        return Matrix();
    }
    Matrix result;
    int columns = len / rows;

    if (len % rows != 0) {
        columns++;
    }

    return array_to_matrix(data, len, rows, columns);
}

Matrix array_to_matrix(char* data,
                       uint32_t len,
                       uint32_t rows,
                       uint32_t columns) {
    if (len != rows * columns) {
        return Matrix();
    }
    Matrix result(rows, std::vector<int>(columns, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int index = (i * columns + j);
            if (index < len) {
                memcpy(&result[i][j], data + index * sizeof(int), sizeof(int));
            }
        }
    }
    return result;
}

Matrixs array_to_matrixs(char* data,
                         uint32_t len,
                         uint32_t matrix_num,
                         uint32_t rows) {
    if (matrix_num == 0 || rows == 0) {
        return Matrixs();
    }

    const uint32_t matrix_elements = (len + matrix_num - 1) / matrix_num;

    uint32_t columns = matrix_elements / rows;
    if (matrix_elements % rows != 0) {
        columns++;
    }

    return array_to_matrixs(data, len, matrix_num, rows, columns);
}

Matrixs array_to_matrixs(char* data,
                         uint32_t len,
                         uint32_t matrix_num,
                         uint32_t rows,
                         uint32_t columns) {
    const uint32_t total_elements = matrix_num * rows * columns;

    if (len != total_elements) {
        return Matrixs();
    }

    Matrixs result;
    result.reserve(matrix_num);

    for (uint32_t m = 0; m < matrix_num; ++m) {
        const uint32_t start_byte = m * rows * columns * sizeof(int);
        char* current_data = data + start_byte;

        Matrix mat =
            array_to_matrix(current_data, rows * columns, rows, columns);
        result.push_back(mat);
    }
    return result;
}
