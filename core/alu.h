#ifndef ALU_H
#define ALU_H
#include <iostream>
#include <vector>

class ALU {
friend class CPU;
private: // arithmetical operations
    static void mov(const std::vector<std::string>&);
    static void add(const std::vector<std::string>&);
    static void sub(const std::vector<std::string>&);
    static void mul(const std::vector<std::string>&);
    static void div(const std::vector<std::string>&);
    static void inc(const std::vector<std::string>&);
    static void dec(const std::vector<std::string>&);

private: // logical operations
    static void logic_and(const std::vector<std::string>&);
    static void logic_or(const std::vector<std::string>&);
    static void logic_xor(const std::vector<std::string>&);
    static void logic_not(const std::vector<std::string>&);
};

#endif // ALU_H