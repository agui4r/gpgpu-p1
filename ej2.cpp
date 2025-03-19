#include <cstdio>
#include <vector>
#include <chrono>

using namespace std;

constexpr short TAM_BL = 10;

void matrix_mult (const vector<vector<float>>& A, const vector<vector<float>>& B, vector<vector<float>>& C, size_t size) {
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++) C[i][j] = 0;

    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            for (size_t k = 0; k < size; k++)
                C[i][j] += A[i][k] * B[k][j];
}

void matrix_mult_cache_optimized (const vector<vector<float>>& A, const vector<vector<float>>& B, vector<vector<float>>& C, size_t size) {
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++) C[i][j] = 0;

    for (size_t j = 0; j < size; j++)
        for (size_t jj = 0; jj < size; jj += TAM_BL)
            for (size_t i = 0; i < size; i++)
                for(size_t k = jj; k < size && k < jj + TAM_BL; k++)
                    C[i][j] += A[i][k] * B[k][j];
}

int main(int argc, char* argv[]) {
    constexpr size_t size = 2500;
    vector<vector<float>> A(size, vector<float>(size))
        , B(size, vector<float>(size))
        , C(size, vector<float>(size));

    //init arrays
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            A[i][j] = i + j;
            B[i][j] = i * j + i + j;
        }
    }

    // cout << "Matrix A: " << endl;

    // for (size_t i = 0; i < size; i++) {
    //     for (size_t j = 0; j < size; j++) {
    //         cout << A[i][j] << "     ";
    //     }
    //     cout << endl;
    // }

    // cout << "Matrix B: " << endl;

    // for (size_t i = 0; i < size; i++) {
    //     for (size_t j = 0; j < size; j++) {
    //         cout << B[i][j] << "     ";
    //     }
    //     cout << endl;
    // }

    chrono::time_point<chrono::high_resolution_clock> start, end;

    start = chrono::high_resolution_clock::now();
    matrix_mult(A, B, C, size);
    end = chrono::high_resolution_clock::now();

    unsigned long elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    printf ("Normal matrix multiplication time = %f miliseconds\n", static_cast<double>(elapsed) / 1000.0);

    // cout << "Normal matrix multiplication result: " << endl;
    // for (size_t i = 0; i < size; i++) {
    //     for (size_t j = 0; j < size; j++) {
    //         cout << C[i][j] << "  ";
    //     }
    //     cout << endl;
    // }

    start = chrono::high_resolution_clock::now();
    matrix_mult_cache_optimized(A, B, C, size);
    end = chrono::high_resolution_clock::now();

    elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    printf ("Cache optimized matrix multiplication time = %f miliseconds\n", static_cast<double>(elapsed) / 1000.0);

    // cout << "Cache optimized matrix multiplication result: " << endl;
    // for (size_t i = 0; i < size; i++) {
    //     for (size_t j = 0; j < size; j++) {
    //         cout << C[i][j] << "  ";
    //     }
    //     cout << endl;
    // }

    return 0;
}
