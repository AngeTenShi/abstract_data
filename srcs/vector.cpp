#include "vector.hpp"
#include <vector>
#include <iostream>
#include <ctime>

// TODO MAKE CONVERSION FOR ITERATORS AND TEST

int main()
{
    std::vector<int> stdVec;
    ft::vector<int> ftVec;
    clock_t start, end;
    double duration;
    // Test std::vector insert
    std::cout << "std::vector insert: ";
    start = clock();
    stdVec.insert(stdVec.begin() + 5, 100);
    end = clock();
    std::cout << std::endl;
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "std::vector insert execution time: " << duration << " microseconds" << std::endl;

    // Test ft::vector insert
    std::cout << "ft::vector insert: ";
    start = clock();
    ftVec.insert(ftVec.begin() + 5, 100); // why begin does not return an const_iterator?
    end = clock();
    std::cout << std::endl;
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "ft::vector insert execution time: " << duration << " microseconds" << std::endl;

    // Test std::vector erase
    std::cout << "std::vector erase: ";
    start = clock();
    stdVec.erase(stdVec.begin() + 5);
    end = clock();
    std::cout << std::endl;
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "std::vector erase execution time: " << duration << " microseconds" << std::endl;

    // Test ft::vector erase
    std::cout << "ft::vector erase: ";
    start = clock();
    ftVec.erase(ftVec.begin() + 5);
    end = clock();
    std::cout << std::endl;
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "ft::vector erase execution time: " << duration << " microseconds" << std::endl;

    // Test std::vector resize
    std::cout << "std::vector resize: ";
    start = clock();
    stdVec.resize(5);
    end = clock();
    std::cout << std::endl;
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "std::vector resize execution time: " << duration << " microseconds" << std::endl;

    // Test ft::vector resize
    std::cout << "ft::vector resize: ";
    start = clock();
    ftVec.resize(5);
    end = clock();
    std::cout << std::endl;
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "ft::vector resize execution time: " << duration << " microseconds" << std::endl;

    // Test std::vector reserve
    std::cout << "std::vector reserve: ";
    start = clock();
    stdVec.reserve(100);
    end = clock();
    std::cout << std::endl;
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "std::vector reserve execution time: " << duration << " microseconds" << std::endl;

    // Test ft::vector reserve
    std::cout << "ft::vector reserve: ";
    start = clock();
    ftVec.reserve(100);
    end = clock();
    std::cout << std::endl;
    duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "ft::vector reserve execution time: " << duration << " microseconds" << std::endl;
}