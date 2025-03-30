#include "timer.hpp"

#include <stdlib.h>
#include <vector>

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

    {
        Timer t("Sequential access time = %f miliseconds\n");
        for (size_t i = 0; i < size; i++) {
            blackhole(arr[indexArr[i]]);
        }
    }

    //random memory access
    {
        Timer t("Random access time = %f miliseconds\n");
        for (size_t i = 0; i < size; i++) {
            blackhole(arr[randomIndexArr[i]]);
        }
    }
    return 0;
}
