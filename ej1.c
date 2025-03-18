#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//  blackhole procedure to avoid compiler optimizations, writing the value to 
//  a volatile variable so the compiler cannot optimize away the access
void blackhole(char value) {
    char volatile singularity = value;
    (void)singularity;
};

int main(int argc, char* argv[]) {
    const size_t size = 100 * 1048576; // 100 MB binary def

    char *arr = malloc(sizeof(char) * size);
    if (arr == NULL) {
        perror("Memory alloc failed");
        return 1;
    }

    unsigned int *indexArr = malloc(sizeof(unsigned int) * size);
    if (indexArr == NULL) {
        perror("Memory alloc failed");
        free(arr);
        return 1;
    }

    unsigned int *randomIndexArr = malloc(sizeof(unsigned int) * size);
    if (randomIndexArr == NULL) {
        perror("Memory alloc failed");
        free(arr);
        free(indexArr);
        return 1;
    }

    //init arrays
    srand(time(NULL));
    for (size_t i = 0; i < size; i++) {
        indexArr[i] = i;
        randomIndexArr[i] = rand() % size;
        arr[i] = (char)(rand() % 128);
    }

    LARGE_INTEGER frequency, start, end;
    double elapsed;

    // get the high-resolution counter frequency
    if (!QueryPerformanceFrequency(&frequency)) {
        fprintf(stderr, "QueryPerformanceFrequency failed!\n");
        free(arr);
        free(indexArr);
        free(randomIndexArr);
        return 1;
    }

    //sequential memory access
    QueryPerformanceCounter(&start);
    for (size_t i = 0; i < size; i++) {
        blackhole(arr[indexArr[i]]);
    }
    QueryPerformanceCounter(&end);
    elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf ("Sequential access time = %f seconds\n", elapsed);

    //random memory access
    QueryPerformanceCounter(&start);
    for (size_t i = 0; i < size; i++) {
        blackhole(arr[randomIndexArr[i]]);
    }
    QueryPerformanceCounter(&end);
    elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf ("Random access time = %f seconds\n", elapsed);

    free(arr);
    free(indexArr);
    free(randomIndexArr);
    return 0;
}