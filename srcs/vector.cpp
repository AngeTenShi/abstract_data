#include "vector.hpp"
#include <vector>
#include <iostream>
#include <ctime>

int main()
{
    std::vector<int> stdVec(10, 42);
    ft::vector<int> ftVec(10, 42);
    clock_t start, end;
    double duration;
    // Test std::vector insert
    std::cout << "std::vector insert: " << std::endl;
    start = clock();
    stdVec.insert(stdVec.begin() + 5, 100);
    end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "std::vector insert execution time: " << duration << " microseconds" << std::endl;

    // Test ft::vector insert
    std::cout << "ft::vector insert: " << std::endl;
    start = clock();
    ftVec.insert(ftVec.begin() + 5, 100);
    end = clock();
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "ft::vector insert execution time: " << duration << " microseconds" << std::endl;

}