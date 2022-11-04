#include <iostream>
#include <map>

int main() {
    std::multimap<std::string, int> test;
    test["test"] = 42;
    test.insert(std::multimap<std::string, int>::value_type("test", 42));
    test.insert(std::multimap<std::string, int>::value_type("test", 1));

    auto range = test.equal_range("test");
    for (auto it = range.first; it != range.second; ++it)
        std::cout << "value for " << it->first << " can be " << it->second << std::endl;
}