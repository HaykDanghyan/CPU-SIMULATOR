#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP
#include "cpu.h"

void Register::set_name(const std::string& name) {
    m_name = name;
}

void Register::set_value(const int& value) {
    m_value = value;
}

std::string Register::get_name() const {
    return m_name;
}

int Register::get_value() const {
    return m_value;
}


void CPU::run() {
    std::ifstream file;
    file.open("file.fasm");
    if (!file.is_open()) {
        exit(0);
    }
    initialize_regisers();
    load(file);
    file.close();
}

void CPU::load(std::ifstream& file) {
    while (!file.eof()) {
        std::string linee;
        getline(file, linee);
        std::stringstream s(linee);
        std::string token;
        while (s >> token) {
            line.push_back(token);
            token = "";
        }
        parse(line);
        line.clear();
    }
}

void CPU::parse(const std::vector<std::string>& line) {
    int idx = get_opcode_index(line[0]);
    if (idx == 0) {
        print(line);
    }
    if (idx == 1) {
        ALU::mov(line);
    } 
    if (idx == 2) {
        ALU::add(line);  
    }
    if (idx == 3) {
        ALU::sub(line);
    }
    if (idx == 4) {
        ALU::mul(line);
    }
    if (idx == 5) {
        ALU::div(line);
    }
    if (idx == 6) {
        ALU::inc(line);
    }
    if (idx == 7) {
        ALU::dec(line);
    }
    if (idx == 8) {
        ALU::logic_and(line);
    }
    if (idx == 9) {
        ALU::logic_or(line);
    }
    if (idx == 10) {
        ALU::logic_not(line);
    }
    if (idx == 11) {
        ALU::logic_xor(line);
    }
    if (idx == 12) {
        CU::cmp(line);
    }
    if (idx == -1) {
        std::cout << "Wrong opcode " << line[0] << std::endl;
        exit(0);
    }
}

void ALU::mov(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 3) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    if (!is_register(line[2])) {
        int value = std::stoi(line[2]);
        registers[reg_number].set_value(value);
    } else {
        if (is_register(line[2])) {
            int mov_reg_number = std::stoi(line[2].substr(1));
            int value = registers[mov_reg_number].get_value();
            registers[reg_number].set_value(value);
        }
    }
    ++line_counter;
}

void ALU::add(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 3) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    if (!is_register(line[2])) {
        int value = std::stoi(line[2]);
        int current_value = registers[reg_number].get_value();
        registers[reg_number].set_value(current_value + value);
    } else {
        if (is_register(line[2])) {
            int mov_reg_number = std::stoi(line[2].substr(1));
            int value = registers[mov_reg_number].get_value();
            int current_value = registers[reg_number].get_value();
            registers[reg_number].set_value(value + current_value);
        }
    }
    ++line_counter;
}

void ALU::sub(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 3) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    if (!is_register(line[2])) {
        int current_value = registers[reg_number].get_value();
        int value = std::stoi(line[2]);
        registers[reg_number].set_value(current_value - value);
    } else {
        if (is_register(line[2])) {
            int sub_reg_number = std::stoi(line[2].substr(1));
            int value = registers[sub_reg_number].get_value();
            int current_value = registers[reg_number].get_value();
            registers[reg_number].set_value(current_value - value);
        }
    }
    ++line_counter;
}

void ALU::mul(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 3) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    if (!is_register(line[2])) {
        int current_value = registers[reg_number].get_value();
        int value = std::stoi(line[2]);
        registers[reg_number].set_value(current_value * value);
    } else {
        if (is_register(line[2])) {
            int mul_reg_number = std::stoi(line[2].substr(1));
            int value = registers[mul_reg_number].get_value();
            int current_value = registers[reg_number].get_value();
            registers[reg_number].set_value(value * current_value);
        }
    }
    ++line_counter;
}

void ALU::div(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 3) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    if (!is_register(line[2])) {
        int current_value = registers[reg_number].get_value();
        int value = std::stoi(line[2]);
        if (value == 0) {
            std::cout << "Division by zero is undefined\nAborting...";
            std::abort();
        }
        registers[reg_number].set_value(current_value / value);
    } else {
        if (is_register(line[2])) {
            int div_reg_number = std::stoi(line[2].substr(1));
            int value = registers[div_reg_number].get_value();
            int current_value = registers[reg_number].get_value();
            if (value == 0) {
                std::cout << "Division by zero is undefined\nAborting...";
                std::abort();
            }
            registers[reg_number].set_value(current_value / value);
        }
    }
    ++line_counter;
}

void ALU::inc(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 2) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    int current_value = registers[reg_number].get_value();
    registers[reg_number].set_value(++current_value);
    ++line_counter;
}

void ALU::dec(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 2) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    int current_value = registers[reg_number].get_value();
    registers[reg_number].set_value(--current_value);
    ++line_counter;
}

void ALU::logic_and(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 3) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    if (!is_register(line[2])) {
        int current_value = registers[reg_number].get_value();
        int value = std::stoi(line[2]);
        registers[reg_number].set_value(current_value & value);
    } else {
        if (is_register(line[2])) {
            int and_reg_number = std::stoi(line[2].substr(1));
            int value = registers[and_reg_number].get_value();
            int current_value = registers[reg_number].get_value();
            registers[reg_number].set_value(current_value & value);
        }
    }
    ++line_counter;
}

void ALU::logic_or(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 3) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    if (!is_register(line[2])) {
        int current_value = registers[reg_number].get_value();
        int value = std::stoi(line[2]);
        registers[reg_number].set_value(current_value & value);
    } else {
        if (is_register(line[2])) {
            int and_reg_number = std::stoi(line[2].substr(1));
            int value = registers[and_reg_number].get_value();
            int current_value = registers[reg_number].get_value();
            registers[reg_number].set_value(current_value | value);
        }
    }
    ++line_counter;
}

void ALU::logic_not(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 2) {
        std::cout << "Wrong expression\n";
        exit(0);
    } else {
        int reg_number = std::stoi(line[1].substr(1));
        int current_value = registers[reg_number].get_value(); 
        registers[reg_number].set_value(~current_value);
    }
    ++line_counter;
}

void ALU::logic_xor(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 3) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    if (!is_register(line[2])) {
        int current_value = registers[reg_number].get_value();
        int value = std::stoi(line[2]);
        registers[reg_number].set_value(current_value & value);
    } else {
        if (is_register(line[2])) {
            int and_reg_number = std::stoi(line[2].substr(1));
            int value = registers[and_reg_number].get_value();
            int current_value = registers[reg_number].get_value();
            registers[reg_number].set_value(current_value ^ value);
        }
    }
    ++line_counter;
}

void CPU::initialize_regisers() {
    registers.resize(11);
    for (int i = 0; i < registers.size(); ++i) {
        registers[i].set_name("r" + std::to_string(i));
        registers[i].set_value(0);
    }
    registers[registers.size() - 1].set_name("flag");
    registers[registers.size() - 1].set_value(0);    
}

void CPU::print(const std::vector<std::string>& line) {
    if (!is_register(line[1]) || line.size() > 2) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int reg_number = std::stoi(line[1].substr(1));
    std::cout << registers[reg_number].get_value() << std::endl;
    ++line_counter;
}

void CU::cmp(const std::vector<std::string>& line) {
    if (line.size() != 3 || !is_register(line[1]) || !is_register(line[2])) {
        std::cout << "Wrong expression\n";
        exit(0);
    }
    int lhs_index = std::stoi(line[1].substr(1));
    int rhs_index = std::stoi(line[2].substr(1));
    int lhs_value = registers[lhs_index].get_value();
    int rhs_value = registers[rhs_index].get_value();    
    if (lhs_value - rhs_value > 0) {
        registers[FLAG].set_value(1);
    } else if (lhs_value - rhs_value < 0) {
        registers[FLAG].set_value(-1);
    } else {
        registers[FLAG].set_value(0);
    }
    ++line_counter;
    get_jmp(lhs_value, rhs_value);
}

void CU::get_jmp(int lhs, int rhs) {
    std::ifstream file;
    file.open("file.fasm");
    int tmp = line_counter;
    std::string jmp;
    while (tmp--) { 
        std::getline(file, jmp);
    }
    get_type_of_jmp(jmp, lhs, rhs);
}

void CU::get_type_of_jmp(const std::string& line, int lhs, int rhs) {
    int pos = line.find(' ');
    std::string jmp_type = line.substr(0, pos);
    if (jmp_type == "jg") {
        if (registers[FLAG].get_value() != 1) {
            return;
        } else {
            pos = line.find('.');
            std::string label_name = line.substr(pos, line.length() - 1);
            std::cout << label_name << std::endl;
        }
    }
}

#endif // INSTRUCTIONS_HPP