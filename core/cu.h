#ifndef CU_H
#define CU_H

#include <iostream>
#include <vector>
class CU {
friend class CPU;
private:
    static void cmp(const std::vector<std::string>&);

private:
    static std::vector<std::string> get_labels_from_file(std::ifstream& file);
};

#endif // CU_H