#include "../parse-expression.cpp"
#include "../print_ans.cpp"
#include "gtest/gtest.h"

TEST(ParseTest, StackSize) {
    std::string exp = "ab";
    std::string letter = "b";
    size_t bound = 1;
    auto res = ParseExpression(exp, letter, bound);
    EXPECT_EQ(res.size(), 2);
}

TEST(ParseTest, ConcatenateCase) {
    std::string exp = "ab.";
    std::string letter = "b";
    size_t bound = 1;
    auto res = ParseExpression(exp, letter, bound);
    EXPECT_EQ(res.back().Result(), 2);
}

TEST(ParseTest, UniteCase) {
    std::string exp = "ab+";
    std::string letter = "a";
    size_t bound = 1;
    auto res = ParseExpression(exp, letter, bound);
    EXPECT_EQ(res.back().Result(), 1);
}

TEST(ParseTest, KliniStarCase) {
    std::string exp = "a*";
    std::string letter = "a";
    size_t bound = 3;
    auto res = ParseExpression(exp, letter, bound);
    EXPECT_EQ(res.back().Result(), 3);
}

TEST(MainTest, INFTest) {
    std::string exp = "ab.b.b.";
    std::string letter = "b";
    size_t bound = 1;
    auto parsed = ParseExpression(exp, letter, bound);
    auto res = PrintAns(parsed.back().Result());
    EXPECT_EQ(res, 0);
}

TEST(StressTest, CaseOne) {
    std::string exp = "ab+c.aba.∗.bac.+.+∗";
    std::string letter = "b";
    size_t bound = 2;
    auto parsed = ParseExpression(exp, letter, bound);
    auto res = PrintAns(parsed.back().Result());
    EXPECT_EQ(res, 4);
}

TEST(StressTest, CaseTwo) {
    std::string exp = "acb..bab.c.∗.ab.ba.+.+∗a.";
    std::string letter = "b";
    size_t bound = 3;
    auto parsed = ParseExpression(exp, letter, bound);
    auto res = PrintAns(parsed.back().Result());
    EXPECT_EQ(res, 7);
}