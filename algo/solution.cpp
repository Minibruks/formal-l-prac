#include "includes/solution.h"

namespace {
    const std::vector<std::string> alphabet = {"a", "b", "c", "1"};
}

namespace Solve {
    bool IsInAlphabet(const std::string &c) {
        auto res = std::find(begin(alphabet), end(alphabet), c);
        return res == end(alphabet);
    }

    RegExpression::RegExpression(const size_t count_limit) : count_limit_(count_limit) {
        dist_.resize(count_limit + 1, MAX_DIST);
    }

    RegExpression::RegExpression(const size_t idx, const size_t dist, const size_t count_limit) : count_limit_(
            count_limit) {
        dist_.resize(count_limit + 1, MAX_DIST);
        dist_[idx] = dist;
    }

    RegExpression RegExpression::Concatenate(RegExpression &other) {
        auto res = RegExpression(count_limit_);
        for (size_t i = 0; i < count_limit_ + 1; ++i) {
            for (size_t j = 0; j <= i; ++j) {
                res.dist_[i] = std::min(res.dist_[i], dist_[j] + other.dist_[i - j]);
            }
        }
        return res;
    }

    RegExpression RegExpression::Unite(RegExpression &other) {
        auto res = RegExpression(count_limit_);
        for (size_t i = 0; i <= count_limit_; ++i) {
            res.dist_[i] = std::min(dist_[i], other.dist_[i]);
        }
        return res;
    }

    void RegExpression::KliniStar() {
        dist_[0] = 0;
        for (size_t i = 1; i < count_limit_; ++i) {
            for (size_t j = 1; j <= count_limit_ - i; ++j) {
                dist_[i + j] = std::min(dist_[i + j], dist_[i] + dist_[j]);
            }
        }
    }

    size_t RegExpression::Result() {
        return dist_[count_limit_];
    }
}