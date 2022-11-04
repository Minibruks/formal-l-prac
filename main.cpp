#include "parse-expression.cpp"
#include "print_ans.cpp"

int main(int argc, char *argv[]) {
    std::string input;
    std::string letter;
    size_t bound = 0;
    if (argc == 1) {
        std::cout << "Регулярное выражение:\n";
        std::cin >> input;
        std::cout << "Буква:\n";
        std::cin >> letter;
        std::cout << "Количество букв:\n";
        std::cin >> bound;
    } else {
        input = argv[1];
        letter = argv[2];
        bound = std::stoi(argv[3]);
    }

    std::vector<RegExpression> stack_reg_exp = ParseExpression(input, letter, bound);

    auto ans = stack_reg_exp.back();
    stack_reg_exp.pop_back();
    size_t min_word_len = ans.Result();

    size_t res = PrintAns(min_word_len);
    if (res > 0) {
        std::cout << res << "\n";
        return 0;
    }
    std::cout << "INF";
    return 0;
}