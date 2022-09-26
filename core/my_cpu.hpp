#include "my_cpu.h"

CPU::CPU() : r0{}, r1{}, r2{}, r3{}, r4{}, r5{}, r6{}, r7{}, r8{}, r9{} 
{
    mp["r0"] = &r0;
    mp["r1"] = &r1;
    mp["r2"] = &r2;
    mp["r3"] = &r3;
    mp["r4"] = &r4;
    mp["r5"] = &r5;
    mp["r6"] = &r6;
    mp["r7"] = &r7;
    mp["r8"] = &r8;
    mp["r9"] = &r9;
    cond[">="] = {"jge"};
    cond["<="] = {"jle"};
    cond[">"] = {"jge", "jg"};
    cond["<"] = {"jle", "jl"};
    cond["=="] = {"je", "jge", "jle"};
}

void CPU::translate()
{
    std::ifstream file;
    std::string line;
    std::string op1;
    std::string op2;
    file.open("file.fasm");
    if (!file.is_open()) {
        std::cout << "Can't open the file" << std::endl;
    }
    while (!file.eof()) {
        file >> line;
        if (line == "mov") { 
            file >> op1;
            file >> op2;
            m_cpu.move_instuction(op2, op1);
        }
        else if (line == "add") {
            file >> op1;
            file >> op2;
            m_cpu.add_instruction(op2, op1);
        }
        else if (line == "sub")
        {
            file >> op1;
            file >> op2;
            m_cpu.sub_instruction(op2, op1);
        }
        else if (line == "mul") {
            file >> op1;
            file >> op2;
            m_cpu.mul_instruction(op2, op1);
        }
        else if (line == "div") {
            file >> op1;
            file >> op2;
            m_cpu.div_instruction(op2, op1);
        }
        else if (line == "and") {
            file >> op1;
            file >> op2;
            m_cpu.and_instruction(op2, op1);
        }
        else if (line == "or") {
            file >> op1;
            file >> op2;
            m_cpu.or_instruction(op2, op1);
        }
        else if (line == "xor") {
            file >> op1;
            file >> op2;
            m_cpu.xor_instruction(op2, op1);
        }
        else if (line == "cmp") {
            file >> op1;
            file >> op2;
            file >> line;
            for (const auto& i : m_cpu.cond[m_cpu.compare(op2, op1)])
            {
                if (i == line) {
                    file >> op1;
                    if (m_cpu.jump[op1]) {
                        file.seekg(m_cpu.jump[op1]);
                    }
                    else {
                        while (!file.eof()) {
                            file >> op2;
                            op2.pop_back();
                            if (op2 == op1) {
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            if (op1 == "") {
                file >> op1;
            }
        }
        else if (line == "jmp") {
            file >> op1;
            if (m_cpu.jump[op1]) {
                file.seekg(m_cpu.jump[op1]);
            } else {
                while (!file.eof()) {
                    file >> op2;
                    op2.pop_back();
                    if (op2 == op1) {
                        break;
                    }
                }
            }
        }
        else if (line == "print") {
            file >> op1;
            m_cpu.print(op1);
        }
        else if (line == "ret") {
            break;
        }
        else if (line.find(':') != -1) {
            line.pop_back();
            m_cpu.jump.insert(std::make_pair(line, file.tellg()));
            continue;
        } else {
            std::cout << "No such instruction" << std::endl;
        }
        line.clear();
        op1.clear();
        op2.clear();
    }
    file.close();
}

void CPU::move_instuction(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    if (mp.find(source) == mp.end()) {
        *mp[dest] = std::stoi(source);
        return;
    }
    *mp[dest] = *mp[source];
}

void CPU::add_instruction(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    if (mp.find(source) == mp.end()) {
        *mp[dest] += std::stoi(source);
        return;
    }
    *mp[dest] += *mp[source];
}

void CPU::sub_instruction(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    if (mp.find(source) == mp.end()) {
        *mp[dest] -= std::stoi(source);
        return;
    }
    *mp[dest] -= *mp[source];
}

void CPU::mul_instruction(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    if (mp.find(source) == mp.end()) {
        *mp[dest] *= std::stoi(source);
        return;
    }
    *mp[dest] *= *mp[source];
}

void CPU::div_instruction(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    if (mp.find(source) == mp.end()) {
        *mp[dest] /= std::stoi(source);
        return;
    }
    *mp[dest] /= *mp[source];
}

void CPU::and_instruction(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    if (mp.find(source) == mp.end()) {
        *mp[dest] &= std::stoi(source);
        return;
    }
    *mp[dest] &= *mp[source];
}

void CPU::or_instruction(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    if (mp.find(source) == mp.end()) {
        *mp[dest] |= std::stoi(source);
        return;
    }
    *mp[dest] |= *mp[source];
}

void CPU::xor_instruction(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    if (mp.find(source) == mp.end()) {
        *mp[dest] ^= std::stoi(source);
        return;
    }
    *mp[dest] ^= *mp[source];
}

std::string CPU::compare(std::string& source, std::string& dest) {
    if (mp.find(dest) == mp.end()) {
        std::cout << "Invalid operation" << std::endl;
        exit(1);
    }
    int tmp = mp.find(source) == mp.end() ? std::stoi(source) : *mp[source];
    if (*mp[dest] > tmp) {
        return ">";
    }
    else if (*mp[dest] < tmp) {
        return "<";
    }
    else if (*mp[dest] >= tmp) {
        return ">=";
    }
    else if (*mp[dest] <= tmp) {
        return "<=";
    } else {
        return "==";
    }
}

void CPU::print(std::string& source) {
    if (mp.find(source) == mp.end()) {
        std::cout << source << std::endl;
    } else {
        std::cout << *mp[source] << std::endl;
    }
}