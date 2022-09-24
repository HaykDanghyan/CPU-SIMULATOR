#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "register.h"
#include "alu.h"
#include "cu.h"

std::vector<std::string> line;
std::vector<Register> registers;

class CPU {
public:
    static void run();

private: // main functionality
    static void load(std::ifstream&);
    static void parse(const std::vector<std::string>&);
    static void print(const std::vector<std::string>&);
    static void initialize_regisers();

private:
    CPU() = delete;
    ~CPU() = delete;

    void* operator new(size_t) = delete;
    void* operator new[](size_t) = delete;
};

#include "instructions.hpp"
#endif // CPU_H