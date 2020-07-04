#include "benchmark.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    for(uint32_t i = 1;i < argc;++i){
        std::cout << argv[i] << std::endl;
        BenchOther(argv[i]);
    }
    return 0;
}
