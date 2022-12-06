#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "includes/parse-expression.h"

using Solve::RegExpression;

std::vector<RegExpression> ParseExpression(std::string& input, std::string& letter, size_t bound) {
    std::vector<RegExpression> stack_reg_exp;
    for (auto symbol_char : input) {
        std::string symbol(1, symbol_char);
        if (Solve::IsInAlphabet(symbol)) {
            if (symbol == letter) {
                RegExpression reg_exp_tmp = RegExpression(1, 1,bound);
                stack_reg_exp.emplace_back(reg_exp_tmp);
            } else {
                RegExpression reg_exp_tmp = RegExpression(0, 1,bound);
                stack_reg_exp.emplace_back(reg_exp_tmp);
            }
        } else {
            auto first_reg_exp = stack_reg_exp.back();
            stack_reg_exp.pop_back();
            if (symbol == "*") {
                first_reg_exp.KliniStar();
                stack_reg_exp.emplace_back(first_reg_exp);
                continue;
            }
            auto second_reg_exp = stack_reg_exp.back();
            stack_reg_exp.pop_back();
            if (symbol == ".") {
                auto res = first_reg_exp.Concatenate(second_reg_exp);
                stack_reg_exp.emplace_back(res);
            } else if (symbol == "+") {
                auto res = first_reg_exp.Unite(second_reg_exp);
                stack_reg_exp.emplace_back(res);
            }
        }
    }

    return stack_reg_exp;
}