#include <iostream>

size_t PrintAns(size_t min_word_len) {
    return min_word_len == MAX_DIST ? 0 : min_word_len;
}