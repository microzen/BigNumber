//
// Created by Microzenas on 3/9/23.
//

#include <big_number.h>
#include <regex>

BigNumber::BigInt::BigInt(std::string num) {
    std::regex pattern(R"(^\-?[1-9]+[0-9]*)");
    bool is_mach = std::regex_match(num,pattern);

    if(!is_mach) throw invalid_argument("Invalid argument of number");

    this->_num = num;
}