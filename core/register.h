#ifndef REGISTER_H
#define REGISTER_H
#include "helpers.h"

class Register {
public:
    void set_value(const int&);
    int get_value() const;

    void set_name(const std::string&);
    std::string get_name() const;
    
private:
    std::string m_name{};
    int m_value{};

}; // Register


#endif // REGISTER_H