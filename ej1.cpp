#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <chrono>

//  blackhole procedure to avoid compiler optimizations, writing the value to 
//  a volatile variable so the compiler cannot optimize away the access
void blackhole(char value) {
    char volatile singularity = value;
    (void)singularity;
};

int main(int argc, char* argv[]) {
    constexpr size_t size = 100 * 1048576; // 100 MB binary def

    std::vector<char> arr(size);
    std::vector<size_t> indexArr(size);
    std::vector<size_t> randomIndexArr(size);

    //init arrays
    srand(420*69);
    for (size_t i = 0; i < size; i++) {
        indexArr[i] = i;
        randomIndexArr[i] = rand() % size;
        arr[i] = (char)(rand() % 128);
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    //sequential memory access
    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < size; i++) {
        blackhole(arr[indexArr[i]]);
    }
    end = std::chrono::system_clock::now();
    unsigned long elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf ("Sequential access time = %f miliseconds\n", static_cast<double>(elapsed) / 1000.0);

    //random memory access
    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < size; i++) {
        blackhole(arr[randomIndexArr[i]]);
    }
    end = std::chrono::system_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf ("Random access time = %f miliseconds\n", static_cast<double>(elapsed) / 1000.0);
    return 0;
}
