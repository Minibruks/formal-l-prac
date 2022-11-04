#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>

std::vector<std::string> alphabet = {"a", "b", "c", "1"};
int state_gl = 0;

struct Node {
    std::multimap<std::string, Node*> in;
    std::multimap<std::string, Node*> out;
    int state;
    bool is_terminal;

    Node() {
        state = state_gl++;
        is_terminal = false;
    }
};

struct NFA {
    std::vector<Node*> nodes;
    Node* start = nullptr;
    Node* final = nullptr;
//    std::vector<int> states;
    NFA(std::string& letter) {
        Node* tmp1 = new Node();
        Node* tmp2 = new Node();
        nodes.emplace_back(tmp1);
        nodes.emplace_back(tmp2);
        start = nodes[0];
        final = nodes[1];
        nodes[0]->out.insert({letter, nodes[1]});
        nodes[1]->in.insert({letter, nodes[0]});
        nodes[1]->is_terminal = true;
    }
};

bool IsInAlphabet(std::string& c) {
    for (const auto &item: alphabet) {
        if (c == item) {
            return true;
        }
    }
    return false;
}

void Concatenate(NFA* first, NFA* sec) {
    first->final->out.insert({"1", sec->start});
    sec->start->in.insert({"1", first->final});
    first->final->is_terminal = false;
    first->final = sec->final;
    sec->start = nullptr;
    sec->final = nullptr;
    for (const auto& item: sec->nodes) {
        first->nodes.emplace_back(item);
    }
}

void Unite(NFA* first, NFA* sec) {
    Node* unite_start = new Node();
    unite_start->out.insert({"1", first->start});
    unite_start->out.insert({"1", sec->start});
    first->start->in.insert({"1", unite_start});
    sec->start->in.insert({"1", unite_start});

    Node* unite_final = new Node();
    unite_final->in.insert({"1", first->final});
    unite_final->in.insert({"1", sec->final});
    first->final->out.insert({"1", unite_final});
    sec->final->out.insert({"1", unite_final});

    first->final->is_terminal = false;
    sec->final->is_terminal = false;
    first->final = unite_final;
    first->final->is_terminal = true;
    first->start = unite_start;
    sec->start = nullptr;
    sec->final = nullptr;

    first->nodes.emplace_back(unite_start);

    for (const auto& item: sec->nodes) {
        first->nodes.emplace_back(item);
    }

    first->nodes.emplace_back(unite_final);
}

void KliniStar(NFA* first) {
    first->final->out.insert({"1", first->start});
    first->start->in.insert({"1", first->final});
    first->start->is_terminal = true;
    first->final->is_terminal = false;
    first->final = first->start;
}

void PrintNFA(std::vector<NFA*>& stack_nfa) {
    for (auto& nfa : stack_nfa) {
        std::cout << "nfa :\n";
        std::cout << "start: " << nfa->start->state << " final: " << nfa->final->state << "\n";
        for (const auto& item: nfa->nodes) {
            std::cout << "state: " << item->state << ", is terminal: " << item->is_terminal << "\n";
            auto range = item->in.equal_range("a");
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << "Letter: " << it->first << ", transition from: " << it->second->state << std::endl;
            }
            range = item->in.equal_range("b");
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << "Letter: " << it->first << ", transition from: " << it->second->state << std::endl;
            }
            range = item->in.equal_range("c");
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << "Letter: " << it->first << ", transition from: " << it->second->state << std::endl;
            }
            range = item->in.equal_range("1");
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << "Letter: " << it->first << ", transition from: " << it->second->state << std::endl;
            }

            range = item->out.equal_range("a");
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << "Letter: " << it->first << ", transition to: " << it->second->state << std::endl;
            }
            range = item->out.equal_range("b");
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << "Letter: " << it->first << ", transition to: " << it->second->state << std::endl;
            }
            range = item->out.equal_range("c");
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << "Letter: " << it->first << ", transition to: " << it->second->state << std::endl;
            }
            range = item->out.equal_range("1");
            for (auto it = range.first; it != range.second; ++it) {
                std::cout << "Letter: " << it->first << ", transition to: " << it->second->state << std::endl;
            }
        }
    }
}

std::vector<NFA*> ParsePolishNotation(std::string& polish_not) {
    std::vector<NFA*> stack_nfa;
    for (auto symbol_char : polish_not) {
        std::string symbol(1, symbol_char);
        if (IsInAlphabet(symbol)) {
            NFA* tmp = new NFA(symbol);
            stack_nfa.emplace_back(tmp);
        } else if (symbol == ".") {
            auto first_nfa = stack_nfa.back();
            stack_nfa.pop_back();
            auto second_nfa = stack_nfa.back();
            stack_nfa.pop_back();
            Concatenate(second_nfa, first_nfa);
            stack_nfa.emplace_back(second_nfa);
        } else if (symbol == "+") {
            auto first_nfa = stack_nfa.back();
            stack_nfa.pop_back();
            auto second_nfa = stack_nfa.back();
            stack_nfa.pop_back();
            Unite(second_nfa, first_nfa);
            stack_nfa.emplace_back(second_nfa);
        } else if (symbol == "*") {
            auto nfa = stack_nfa.back();
            stack_nfa.pop_back();
            KliniStar(nfa);
            stack_nfa.emplace_back(nfa);
        }
    }

    PrintNFA(stack_nfa);

    return stack_nfa;
}

size_t BFS(NFA* nfa, std::string& letter, size_t count_limit) {
    std::cout << nfa->start->state << "\n";

    std::vector<size_t> dist(state_gl, 10000);
    std::vector<size_t> dist_b(state_gl, 0);
    std::queue<Node*> q;
    size_t a_count = 0;
    size_t b_count = 0;
    size_t letter_count = 0;
    dist[nfa->start->state] = 0;
    dist_b[nfa->start->state] = 0;
    q.push(nfa->start);

    while (!q.empty()) {
        auto current_node = q.front();
        q.pop();

        if (current_node->is_terminal && b_count == count_limit) {
            return dist[current_node->state];
        } else if (b_count > count_limit) {
            break;
        }

        auto range = current_node->out.equal_range("a");
        for (auto it = range.first; it != range.second; ++it) {
            Node* to = it->second;
            dist[to->state] = dist[current_node->state] + 1;
            if (dist_b[to->state] < dist_b[current_node->state]) {
                dist_b[to->state] = dist_b[current_node->state];


            }
            q.push(to);
        }

        range = current_node->out.equal_range("b");
        for (auto it = range.first; it != range.second; ++it) {
            Node* to = it->second;
            if (dist[to->state] == 10000) {
                b_count++;
                dist[to->state] = dist[current_node->state] + 1;
            }
            dist_b[to->state] = dist_b[current_node->state] + 1;
            q.push(to);
        }

        range = current_node->out.equal_range("1");
        for (auto it = range.first; it != range.second; ++it) {
            Node* to = it->second;
            dist[to->state] = dist[current_node->state];
            if (dist_b[to->state] < dist_b[current_node->state]) {
                dist_b[to->state] = dist_b[current_node->state];

            }
            q.push(to);
        }
    }
    return 0;
}

int main() {
    std::string input = "ab.*";
    std::string letter = "b";
    size_t count = 2;
    std::vector<NFA*> nfa = ParsePolishNotation(input);
    size_t res = BFS(nfa.front(), letter, count);
    std::cout << res << "\n";
    return 0;
}

