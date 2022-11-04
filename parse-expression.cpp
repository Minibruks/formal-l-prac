#include "solution.cpp"

std::vector<RegExpression> ParseExpression(std::string& input, std::string& letter, size_t bound) {
    std::vector<RegExpression> stack_reg_exp;
    for (auto symbol_char : input) {
        std::string symbol(1, symbol_char);
        if (IsInAlphabet(symbol)) {
            auto reg_exp_tmp = RegExpression(bound);
        if (symbol == letter) {
                reg_exp_tmp.SetDist(1, 1);
            } else {
                reg_exp_tmp.SetDist(0, 1);
            }

            stack_reg_exp.emplace_back(reg_exp_tmp);
        } else if (symbol == ".") {
            auto first_reg_exp = stack_reg_exp.back();
            stack_reg_exp.pop_back();
            auto second_reg_exp = stack_reg_exp.back();
            stack_reg_exp.pop_back();
            auto res = first_reg_exp.Concatenate(second_reg_exp);
            stack_reg_exp.emplace_back(res);
        } else if (symbol == "+") {
            auto first_reg_exp = stack_reg_exp.back();
            stack_reg_exp.pop_back();
            auto second_reg_exp = stack_reg_exp.back();
            stack_reg_exp.pop_back();
            auto res = first_reg_exp.Unite(second_reg_exp);
            stack_reg_exp.emplace_back(res);
        } else if (symbol == "*") {
            auto first_reg_exp = stack_reg_exp.back();
            stack_reg_exp.pop_back();
            first_reg_exp.KliniStar();
            stack_reg_exp.emplace_back(first_reg_exp);
        }
    }

    return stack_reg_exp;
}