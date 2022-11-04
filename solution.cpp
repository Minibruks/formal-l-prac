#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>

size_t MAX_DIST = 10000000;
std::vector<std::string> alphabet = {"a", "b", "c", "1"};

bool IsInAlphabet(std::string& c) {
    for (const auto &item: alphabet) {
        if (c == item) {
            return true;
        }
    }
    return false;
}

class RegExpression {
    std::vector<size_t> dist_;
    size_t count_limit_ = 0;

public:
    RegExpression(size_t& count_limit) : count_limit_(count_limit) {
        dist_.resize(count_limit + 1, MAX_DIST);
    }

    void SetDist(size_t idx, size_t dist) {
        dist_[idx] = dist;
    }

    RegExpression Concatenate(RegExpression& other) {
        auto res = RegExpression(count_limit_);
        for (size_t i = 0; i < count_limit_ + 1; ++i) {
            for (size_t j = 0; j < i + 1; ++j) {
                res.dist_[i] = std::min(res.dist_[i], dist_[j] + other.dist_[i - j]);
            }
        }
        return res;
    }

    RegExpression Unite(RegExpression& other) {
        auto res = RegExpression(count_limit_);
        for (size_t i = 0; i < count_limit_ + 1; ++i) {
            res.dist_[i] = std::min(dist_[i], other.dist_[i]);
        }
        return res;
    }

    void KliniStar() {
        this->dist_[0] = 0;
        for (size_t i = 1; i < count_limit_; ++i) {
            for (size_t j = 1; j < count_limit_ - i + 1; ++j) {
                dist_[i + j] = std::min(dist_[i + j], dist_[i] + dist_[j]);
            }
        }
    }

    size_t Result() {
        return dist_[count_limit_];
    }
};