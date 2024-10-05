#include "../includes/polynomial_node.h"

Polynomial::Node::Node(std::string str) {
    bool powing = false;
    bool sign = false;
    bool num = true;
    bool same_varriable = false;
    int64_t summand = 0;
    int pos_in_memders_if_same = -1;
    for (size_t i = 0; i < str.size(); ++i) {
        if ('0' <= str[i] && str[i] <= '9') {
            if (same_varriable) {
                if (powing) {
                    summand *= 10;
                    summand += static_cast<int64_t>(str[i] - '0');
                }
            }
            if (powing) {
                members.back().second *= 10;
                members.back().second += static_cast<int64_t>(str[i] - '0');
            } else {
                if (sign) {
                    if (num) {
                        multiplier.num_ *= static_cast<int64_t>(str[i] - '0');
                        sign = false;
                    } else {
                        multiplier.den_ *= static_cast<int64_t>(str[i] - '0');
                        sign = false;
                    }
                } else {
                    if (num) {
                        multiplier.num_ *= 10;
                        multiplier.num_ = multiplier.num_ + static_cast<int64_t>(str[i] - '0') *
                            (multiplier == 0 ? 1 : std::abs(multiplier.num_) / multiplier.num_);
                    } else {
                        multiplier.den_ *= 10;
                        multiplier.den_ = multiplier.den_ + static_cast<int64_t>(str[i] - '0');
                    }
                }
            }
        } else if (str[i] == '^') {
            powing = true;
        } else if ('a' <= str[i] && str[i] <= 'z') {
            if (same_varriable) {
                members[pos_in_memders_if_same].second += summand;
            }
            same_varriable = false;
            pos_in_memders_if_same = -1;
            summand = 0;
            powing = false;
            if (i == 0) {
                multiplier = 1;
            }
            bool check = false;
            for (int j = 0; j < members.size(); ++j) {
                if (members[j].first == str[i]) {
                    check = true;
                    if (i + 1 < str.size()) {
                        if (str[i + 1] != '^') {
                            members[j].second += 1;
                        } else {
                            same_varriable = true;
                            pos_in_memders_if_same = j;
                        }
                    } else {
                        members[j].second += 1;
                    }
                }
            }
            if (check) {
                continue;
            }
            if (i + 1 < str.size()) {
                if (str[i + 1] != '^') {
                    members.push_back(std::make_pair(str[i], 1));
                } else {
                    members.push_back(std::make_pair(str[i], 0));
                }
            } else {
                members.push_back(std::make_pair(str[i], 1));
            }
        } else if (str[i] == '-') {
            if (same_varriable) {
                members[pos_in_memders_if_same].second += summand;
            }
            same_varriable = false;
            pos_in_memders_if_same = -1;
            summand = 0;
            multiplier = -1;
            sign = true;
        } else if (str[i] == '+') {
            if (same_varriable) {
                members[pos_in_memders_if_same].second += summand;
            }
            same_varriable = false;
            pos_in_memders_if_same = -1;
            summand = 0;
            multiplier = 1;
            sign = true;
        } else if (str[i] == '/') {
            num = false;
            sign = true;
        } else if (str[i] == ')') {
            multiplier.reduce();
        }
    }
}

Polynomial::Node::Node(const Polynomial::Node& node) {
    multiplier = node.multiplier;
    members = node.members;
    next = nullptr;
}

Polynomial::Node::~Node() {
    clear();
}

void Polynomial::Node::clear() {
    multiplier = 0;
    members.clear();
    next = nullptr;
}

Polynomial::Node operator*(const Polynomial::Node& lhs, const Polynomial::Node& rhs) {
    Polynomial::Node* node = new Polynomial::Node(lhs);
    node->multiplier *= rhs.multiplier;
    for (std::pair<char, int> i : rhs.members) {
        bool is_new = true;
        for (size_t j = 0; j < node->members.size(); ++j) {
            if (i.first == node->members[j].first) {
                node->members[j].second += i.second;
                is_new = false;
                break;
            }
        }
        if (is_new) {
            node->members.push_back(i);
        }
    }
    std::sort(node->members.begin(), node->members.end());
    return *node;
}

Polynomial::Node operator/(const Polynomial::Node& lhs, const Polynomial::Node& rhs) {
    Polynomial::Node* node = new Polynomial::Node(lhs);
    node->multiplier /= rhs.multiplier;
    if (node->members.size() == 1 && rhs.members.size() == 1) {
        node->members.back().second -= rhs.members.back().second;
        if (node->members.back().second == 0) {
            node->members.clear();
        }
    }
    return *node;
}

bool operator==(Polynomial::Node& lhs, Polynomial::Node& rhs) {
    if (lhs.multiplier == rhs.multiplier && lhs.members.size() == rhs.members.size()) {
        for (size_t i = 0; i < lhs.members.size(); ++i) {
            if (lhs.members[i] != rhs.members[i]) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

bool operator!=(Polynomial::Node& lhs, Polynomial::Node& rhs) {
    return !(lhs == rhs);
}
