#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>

int get_opcode_index(const std::string& token) {
    if (token == "print") {
        return 0;
    }
    if (token == "mov") {
        return 1;
    }
    if (token == "add") {
        return 2;
    }
    if (token == "sub") {
        return 3;
    }
    if (token == "mul") {
        return 4;
    }
    if (token == "div") {
        return 5;
    }
    if (token == "inc") {
        return 6;
    }
    if (token == "dec") {
        return 7;
    }
    if (token == "and") {
        return 8;
    }
    if (token == "or") {
        return 9;
    }
    if (token == "not") {
        return 10;
    }
    if (token == "xor") {
        return 11;
    }
    if (token == "cmp") {
        return 12;
    }
    return -1;
}

bool is_register(const std::string& name) {
    for (int i = 0; i < 10; ++i) {
        std::string register_name = "r" + std::to_string(i);
        if (register_name == name) {
            return true;
        }
    }
    return false;
}

#endif // HELPERS_H