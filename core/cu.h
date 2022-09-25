#ifndef CU_H
#define CU_H

#include <iostream>
#include <vector>

const std::vector<std::string> jmp_types {"jmp", "jg", "jge", "jl", "jle", "je"};

class CU {
friend class CPU;
private:
    static void cmp(const std::vector<std::string>&);

private:
    static void get_jmp(int, int);
    static void get_type_of_jmp(const std::string&, int, int);
};

#endif // CU_H