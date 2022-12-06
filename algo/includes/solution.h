#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>

namespace {
    size_t MAX_DIST = 10000000;
}

namespace Solve {
    bool IsInAlphabet(const std::string& c);
    class RegExpression {
        std::vector<size_t> dist_;
        size_t count_limit_ = 0;

    public:
        RegExpression(size_t count_limit);

        RegExpression(size_t idx, size_t dist, size_t count_limit);

        RegExpression Concatenate(RegExpression &other);

        RegExpression Unite(RegExpression &other);

        void KliniStar();

        size_t Result();
    };
}