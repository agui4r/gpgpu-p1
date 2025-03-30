#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

constexpr short TAM_BL = 10;

void matrix_mult (vector<vector<float>> A, vector<vector<float>> B, vector<vector<float>>& C, size_t size) {
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++) C[i][j] = 0;

    for (size_t i = 0; i < size; i++) 
    {
        printf("%zu/%zu             \r", i, size);
        for (size_t j = 0; j < size; j++)
            for (size_t k = 0; k < size; k++)
                C[i][j] += A[i][k] * B[k][j];
    }
    printf("\n");
}

void matrix_mult_cache_optimized (vector<vector<float>> A, vector<vector<float>> B, vector<vector<float>>& C, size_t size) {
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++) C[i][j] = 0;

    for (size_t j = 0; j < size; j++)
    {
        printf("%zu/%zu             \r", j, size);
        for (size_t jj = 0; jj < size; jj += TAM_BL)
            for (size_t i = 0; i < size; i++)
                for(size_t k = jj; k < size && k < jj + TAM_BL; k++)
                    C[i][j] += A[i][k] * B[k][j];
    }
    printf("\n");
}

int run_with_size(size_t size) {
    vector<vector<float>> A(size, vector<float>(size))
        , B(size, vector<float>(size))
        , C(size, vector<float>(size));

    printf("SIZE = %zu\n", size);

    //init arrays
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            A[i][j] = i + j;
        }
    }
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
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
    unsigned long elapsed;

    //start = chrono::high_resolution_clock::now();
    //matrix_mult_cache_optimized(A, B, C, size);
    //end = chrono::high_resolution_clock::now();

    //elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    //printf ("Cache optimized matrix multiplication time = %f miliseconds\n", static_cast<double>(elapsed) / 1000.0);
    //printf ("Cache optimized matrix multiplication MFLOPS = %f\n", (size*size*size) / static_cast<double>(elapsed));

    // cout << "Cache optimized matrix multiplication result: " << endl;
    // for (size_t i = 0; i < size; i++) {
    //     for (size_t j = 0; j < size; j++) {
    //         cout << C[i][j] << "  ";
    //     }
    //     cout << endl;
    // }

    start = chrono::high_resolution_clock::now();
    matrix_mult(A, B, C, size);
    end = chrono::high_resolution_clock::now();

    elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    printf ("Normal matrix multiplication time = %f miliseconds\n", static_cast<double>(elapsed) / 1000.0);
    printf ("Normal matrix multiplication MFLOPS = %f\n", (size*size*size) / static_cast<double>(elapsed));

    // cout << "Normal matrix multiplication result: " << endl;
    // for (size_t i = 0; i < size; i++) {
    //     for (size_t j = 0; j < size; j++) {
    //         cout << C[i][j] << "  ";
    //     }
    //     cout << endl;
    // }

    return 0;
}

int main (int argc, char *argv[]) {
    run_with_size(100);
    run_with_size(200);
    run_with_size(1000);
    return 0;
}
