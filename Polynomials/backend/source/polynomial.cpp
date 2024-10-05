#include "../includes/polynomial_node.h"


std::ostream& operator<<(std::ostream& out, Polynomial polynomial) {
    for (Polynomial::Node* node = polynomial.head_; node != nullptr; node = node->next) {
        if (node == polynomial.head_) {
            if (node->multiplier >= 0) {
                if (node->multiplier != 1 || node->members.empty()) {
                    out << node->multiplier;
                }
            } else {
                if (node->multiplier != -1 || node->members.empty()) {
                    out << "-" << -node->multiplier;
                } else {
                    out << "-";
                }
            }
            for (std::pair<char, int> i : node->members) {
                if (i.second == 1) {
                    out << i.first;
                } else {
                    out << i.first << "^" << i.second;
                }
            }
        } else {
            if (node->multiplier >= 0) {
                if (node->multiplier != 1 || node->members.empty()) {
                    out << " + " << node->multiplier;
                } else {
                    out << " + ";
                }
            } else {
                if (node->multiplier != -1 || node->members.empty()) {
                    out << " - " << -node->multiplier;
                } else {
                    out << " - ";
                }
            }
            for (std::pair<char, int> i : node->members) {
                if (i.second == 1) {
                    out << i.first;
                } else {
                    out << i.first << "^" << i.second;
                }
            }
        }
    }
    return out;
}

Polynomial operator+(const Polynomial lhs, const Polynomial rhs) {
    Polynomial new_polynomial;
    Polynomial::Node* lhs_walk = lhs.head_;
    Polynomial::Node* rhs_walk = rhs.head_;
    for (; lhs_walk != nullptr && rhs_walk != nullptr; ) {
        int64_t lhs_sum = 0, rhs_sum = 0;
        for (std::pair<char, int> i : lhs_walk->members) {
            lhs_sum += i.second;
        }
        for (std::pair<char, int> i : rhs_walk->members) {
            rhs_sum += i.second;
        }
        if (lhs_sum > rhs_sum) {
            Polynomial::Node* node = new Polynomial::Node(*lhs_walk);
            new_polynomial.push_back(node);
            lhs_walk = lhs_walk->next;
        } else if (lhs_sum < rhs_sum) {
            Polynomial::Node* node = new Polynomial::Node(*rhs_walk);
            new_polynomial.push_back(node);
            rhs_walk = rhs_walk->next;
        } else {
            if (rhs_walk->members == lhs_walk->members) {
                Polynomial::Node* node = new Polynomial::Node(*lhs_walk);
                node->multiplier += rhs_walk->multiplier;
                new_polynomial.push_back(node);
                rhs_walk = rhs_walk->next;
                lhs_walk = lhs_walk->next;
            } else {
                Polynomial::Node* node = new Polynomial::Node(*lhs_walk);
                new_polynomial.push_back(node);
                lhs_walk = lhs_walk->next;
            }
        }
    }
    for (; lhs_walk != nullptr; lhs_walk = lhs_walk->next) {
        Polynomial::Node* node = new Polynomial::Node;
        node->multiplier = lhs_walk->multiplier;
        node->members = lhs_walk->members;
        new_polynomial.push_back(node);
    }
    for (; rhs_walk != nullptr; rhs_walk = rhs_walk->next) {
        Polynomial::Node* node = new Polynomial::Node;
        node->multiplier = rhs_walk->multiplier;
        node->members = rhs_walk->members;
        new_polynomial.push_back(node);
    }
    new_polynomial.Reduction();
    return new_polynomial;
}

Polynomial operator+=(Polynomial& lhs, const Polynomial rhs) {
    lhs = lhs + rhs;
    return lhs;
}

Polynomial operator-(const Polynomial lhs, const Polynomial rhs) {
    Polynomial new_polynomial;
    Polynomial::Node* lhs_walk = lhs.head_;
    Polynomial::Node* rhs_walk = rhs.head_;
    for (; lhs_walk != nullptr && rhs_walk != nullptr; ) {
        int64_t lhs_sum = 0, rhs_sum = 0;
        for (std::pair<char, int> i : lhs_walk->members) {
            lhs_sum += i.second;
        }
        for (std::pair<char, int> i : rhs_walk->members) {
            rhs_sum += i.second;
        }
        if (lhs_sum > rhs_sum) {
            Polynomial::Node* node = new Polynomial::Node(*lhs_walk);
            new_polynomial.push_back(node);
            lhs_walk = lhs_walk->next;
        } else if (lhs_sum < rhs_sum) {
            Polynomial::Node* node = new Polynomial::Node(*rhs_walk);
            node->multiplier = -node->multiplier;
            new_polynomial.push_back(node);
            rhs_walk = rhs_walk->next;
        } else {
            if (rhs_walk->members == lhs_walk->members) {
                Polynomial::Node* node = new Polynomial::Node(*lhs_walk);
                node->multiplier -= rhs_walk->multiplier;
                new_polynomial.push_back(node);
                rhs_walk = rhs_walk->next;
                lhs_walk = lhs_walk->next;
            } else {
                Polynomial::Node* node = new Polynomial::Node(*lhs_walk);
                new_polynomial.push_back(node);
                lhs_walk = lhs_walk->next;
            }
        }
    }
    for (; lhs_walk != nullptr; lhs_walk = lhs_walk->next) {
        Polynomial::Node* node = new Polynomial::Node(*lhs_walk);
        new_polynomial.push_back(node);
    }
    for (; rhs_walk != nullptr; rhs_walk = rhs_walk->next) {
        Polynomial::Node* node = new Polynomial::Node(*rhs_walk);
        node->multiplier = -node->multiplier;
        new_polynomial.push_back(node);
    }
    new_polynomial.Reduction();
    return new_polynomial;
}

Polynomial operator-=(Polynomial& lhs, const Polynomial rhs) {
    lhs = lhs - rhs;
    return lhs;
}

Polynomial operator*(const Polynomial lhs, const Polynomial rhs) {
    Polynomial new_polynomial;
    for (Polynomial::Node* lhs_move = lhs.head_; lhs_move != nullptr; lhs_move = lhs_move->next) {
        for (Polynomial::Node* rhs_move = rhs.head_; rhs_move != nullptr; rhs_move = rhs_move->next) {
            Polynomial::Node node;
            node = *rhs_move * *lhs_move;
            Polynomial::Node* node_pointer = new Polynomial::Node(node);
            new_polynomial.push_back(node_pointer);
        }
    }
    new_polynomial.Reduction();
    return new_polynomial;
}

Polynomial operator*=(Polynomial& lhs, const Polynomial rhs) {
    lhs = lhs * rhs;
    return lhs;
}

Polynomial operator/(Polynomial lhs, Polynomial rhs) {
    char varriable = ' ';
    for (Polynomial::Node* node = lhs.head_; node != nullptr; node = node->next) {
        if (node->members.size() >= 2) {
            throw std::runtime_error("Your polynomials gotta have just one same varriable to divide them");
        } else if (node->members.size() == 1) {
            if (varriable == ' ') {
                varriable = node->members.back().first;
            } else if (varriable != node->members.back().first) {
                throw std::runtime_error("Your polynomials gotta have just one same varriable to divide them");
            }
        }
    }
    for (Polynomial::Node* node = rhs.head_; node != nullptr; node = node->next) {
        if (node->members.size() >= 2) {
            throw std::runtime_error("Your polynomials gotta have just one same varriable to divide them");
        } else if (node->members.size() == 1) {
            if (varriable == ' ') {
                varriable = node->members.back().first;
            } else if (varriable != node->members.back().first) {
                throw std::runtime_error("Your polynomials gotta have just one same varriable to divide them");
            }
        }
    }
    return diviser_of_two_polynomials(lhs, rhs);
}

Polynomial diviser_of_two_polynomials(Polynomial lhs, Polynomial rhs) {
    if (lhs.head_ == nullptr || rhs.head_ == nullptr) {
        return Polynomial();
    }
    std::vector<std::pair<char, int64_t>> dividend = lhs.head_->members;
    std::vector<std::pair<char, int64_t>> divisor = rhs.head_->members;
    int j = 0;
    for (int i = 0; i < divisor.size(); ++i) {
        bool check = false;
        for (; j < dividend.size(); ++j) {
            if (divisor[i].first == dividend[j].first) {
                if (dividend[j].second < divisor[i].second) {
                    return 0;
                } else {
                    check = true;
                    ++j;
                    break;
                }
            }
        }
        if (!check) {
            return 0;
        }
    }
    Polynomial::Node* quotienter = new Polynomial::Node(*lhs.head_ / *rhs.head_);
    Polynomial quotient(quotienter);
    Polynomial tmp = rhs * quotient;
    lhs -= tmp;
    return quotient + lhs / rhs;
}

Polynomial operator/=(Polynomial& lhs, Polynomial rhs) {
    lhs = lhs / rhs;
    return lhs;
}

Polynomial operator%(Polynomial lhs, Polynomial rhs) {
    Polynomial divide = lhs / rhs;
    Polynomial multiplie = divide * rhs;
    Polynomial minus = lhs - multiplie;
    return minus;
}

Polynomial operator%=(Polynomial& lhs, Polynomial rhs) {
    return lhs = lhs % rhs;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial::Node* lhs_move = lhs.head_;
    Polynomial::Node* rhs_move = rhs.head_;
    for (; rhs_move != nullptr && lhs_move != nullptr; lhs_move = lhs_move->next, rhs_move = rhs_move->next) {
        if (*lhs_move != *rhs_move) {
            return false;
        }
    }
    if (rhs_move != nullptr || lhs_move != nullptr) {
        return false;
    }
    return true;
}


Polynomial::Polynomial(int d) : head_(nullptr), tail_(nullptr), size_(0) {
    std::string str = std::to_string(d);
    *this = Polynomial(str);
}

Polynomial::Polynomial(std::string str) {
    Separation(str);
    Reduction();
}

Polynomial::Polynomial(Node*& node) {
    head_ = node;
    tail_ = node;
    size_ = 1;
}

Polynomial::Polynomial(const Polynomial& polynomial) {
    for (Polynomial::Node* i = polynomial.head_; i != nullptr; i = i->next) {
        Polynomial::Node* q = new Polynomial::Node();
        q->members = i->members;
        q->multiplier = i->multiplier;
        q->next = nullptr;
        push_back(q);
    }
}

void Polynomial::Separation(std::string str) {
    if (str == "") {
        throw std::runtime_error("Your data is empty");
    }
    int prev = 0;
    // 1 = '+' || '-'
    // 2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    // 3 = '^'
    // 4 = alphabet
    // 5 = divide

    bool is_space = false;
    bool parenthesis = false;
    int parenthesis_count = 0;
    std::string node = "";
    for (char i : str) {
        if (i == '+' || i == '-') {
            if (parenthesis) {
                clear();
                throw std::runtime_error("You can write only numbers and division sign in parenthesis");
            }
            if (prev == 0) {
                node.push_back(i);
            } else if (prev == 2 || prev == 4) {
                Polynomial::Node* q = new Polynomial::Node(node);
                push_back(q);
                node = i;
                parenthesis_count = 0;
                parenthesis = false;
            } else {
                clear();
                if (prev == 1) {
                    throw std::runtime_error("Please, write only one sign");
                } else {
                    throw std::runtime_error("You can write power without sign, so do that");
                }
            }
            prev = 1;
            is_space = false;
        } else if (i == ' ') {
            is_space = true;
        } else if (('0' <= i && i <= '9')) {
            if (is_space) {
                if (prev == 0 || prev == 1 || prev == 3 || prev == 5) {
                    node.push_back(i);
                } else {
                    clear();
                    if (prev == 4) {
                        throw std::runtime_error("You can't add multiplier after varriable");
                    } else {
                        throw std::runtime_error("You can't write number with space between digits");
                    }
                }
            } else {
                if (prev == 0 || prev == 1 || prev == 2 || prev == 3 || prev == 5) {
                    node.push_back(i);
                } else {
                    clear();
                    throw std::runtime_error("You can't add multiplier after varriable");
                }
            }
            prev = 2;
            is_space = false;
        } else if (i == '^') {
            if (parenthesis) {
                clear();
                throw std::runtime_error("You can write only numbers and division sign in parenthesis");
            }
            if (prev == 4) {
                node.push_back(i);
            } else {
                clear();
                throw std::runtime_error("You gotta write '^' only after character");
            }
            prev = 3;
            is_space = false;
        } else if (('a' <= i && i <= 'z')) {
            if (parenthesis) {
                clear();
                throw std::runtime_error("You can write only numbers and division sign in parenthesis");
            }
            if (prev == 0 || prev == 1 || prev == 2 || prev == 4) {
                node.push_back(i);
            } else {
                clear();
                throw std::runtime_error("Your power can't contain characters");
            }
            prev = 4;
            is_space = false;
        } else if (i == '(') {
            if (parenthesis_count == 1) {
                clear();
                throw std::runtime_error("You can use parenthesis only for multipier and just once");
            }
            if (prev == 1 || prev == 0) {
                node.push_back(i);
            } else {
                clear();
                throw std::runtime_error("There have to be just sign before parenthesis");
            }
            is_space = false;
            parenthesis = true;
            ++parenthesis_count;
        } else if (i == ')') {
            if (!parenthesis) {
                clear();
                throw std::runtime_error("Hmmm... I can't find opened parenthesis");
            }
            if (prev != 5) {
                node.push_back(i);
            } else {
                clear();
                throw std::runtime_error("You have to writer a number after division sign");
            }
            is_space = false;
            parenthesis = false;
        } else if (i == '/') {
            if (parenthesis) {
                node.push_back(i);
            } else {
                clear();
                throw std::runtime_error("You can divide just in paranthesis");
            }
            prev = 5;
            is_space = false;
        } else {
            clear();
            throw std::runtime_error("You can't use this symbol");
        }
    }
    if (prev == 1 || prev == 3) {
        throw std::logic_error("Your polynomial can't end with sign");
    } else if (parenthesis) {
        throw std::logic_error("Hmmm... I can't find closed parenthesis");
    } else if (prev == 0) {
        throw std::runtime_error("Your data is empty");
    } else {
        Polynomial::Node* q = new Polynomial::Node(node);
        push_back(q);
        node = "";
    }
}

int64_t Polynomial::fast_pow(int64_t n, int64_t pow) {
    if (pow == 0) {
        return 1;
    }
    if (pow % 2 == 0) {
        int64_t tmp = fast_pow(n, pow / 2);
        return tmp * tmp;
    } else {
        return fast_pow(n, pow - 1) * n;
    }
}

void Polynomial::Reduction() {
    for (Node* i = head_, *i_prev = nullptr; i != nullptr; ) {
        if (i->multiplier == 0) {
            if (i == head_) {
                if (i->next == nullptr) {
                    i->members.clear();
                    i_prev = i;
                    i = i->next;
                    continue;
                } else {
                    head_ = i->next;
                    delete i;
                    --size_;
                    i = head_;
                    i_prev = nullptr;
                    continue;
                }
            } else {
                i_prev->next = i->next;
                delete i;
                --size_;
                i = i_prev->next;
                continue;
            }
        }
        for (Node* j = i->next, *prev_j = i; j != nullptr; ) {
            if (i->members == j->members) {
                i->multiplier += j->multiplier;
                prev_j->next = j->next;
                delete j;
                --size_;
                j = prev_j->next;
            } else {
                prev_j = j;
                j = j->next;
            }
        }
        i_prev = i;
        i = i->next;
    }
    Node* prev_i = head_;
    for (Node* i = head_; i != nullptr; ) {
        if (i->multiplier == 0 && i != head_) {
            prev_i->next = i->next;
            delete i;
            --size_;
            i = prev_i->next;
        } else if (i->multiplier == 0) {
            i->members.clear();
            prev_i = i;
            i = i->next;
        } else {
            for (int j = 0; j < i->members.size(); ++j) {
                if (i->members[j].second == 0) {
                    i->members.erase(i->members.begin() + j);
                }
            }
            prev_i = i;
            i = i->next;
        }
    }
    tail_ = prev_i;
}

Polynomial& Polynomial::operator=(const Polynomial rhs) {
    clear();
    for (Polynomial::Node* i = rhs.head_; i != nullptr; i = i->next) {
        push_back(i);
    }
    return *this;
}

Fraction Polynomial::result(std::vector<std::pair<char, int>> mask) {
    std::sort(mask.begin(), mask.end());
    Fraction sum = 0;
    for (Polynomial::Node* i = head_; i != nullptr; i = i->next) {
        Fraction cur_sum = i->multiplier;
        for (int j = 0; j < i->members.size(); ++j) {
            bool check = false;
            for (int k = 0; k < mask.size(); ++k) {
                if (i->members[j].first == mask[k].first) {
                    cur_sum *= fast_pow(mask[k].second, i->members[j].second);
                    check = true;
                    break;
                }
            }
            if (!check) {
                throw std::logic_error("Can't find value for some varriables");
            }
        }
        sum += cur_sum;
    }
    return sum;
}

void Polynomial::push_back(Node* node) {
    if (node == nullptr) {
        return;
    }
    Polynomial::Node* q = new Polynomial::Node();
    q->members = node->members;
    q->multiplier = node->multiplier;
    q->next = nullptr;
    ++size_;
    std::sort(q->members.begin(), q->members.end());
    if (head_ == nullptr) {
        q->next = nullptr;
        head_ = q;
        tail_ = q;
    } else {
        int64_t cur_sum = 0;
        for (std::pair<char, int> i : q->members) {
            cur_sum += i.second;
        }
        int64_t sum = 0;
        for (std::pair<char, int> j : head_->members) {
            sum += j.second;
        }
        if (sum < cur_sum) {
            q->next = head_;
            head_ = q;
            return;
        }
        for (Node* i = head_; i->next != nullptr; i = i->next) {
            sum = 0;
            for (std::pair<char, int> j : i->next->members) {
                sum += j.second;
            }
            if (sum < cur_sum) {
                q->next = i->next;
                i->next = q;
                return;
            }
        }
        tail_->next = q;
        q->next = nullptr;
        tail_ = q;
    }
}

std::string Polynomial::to_string() {
    std::string ans;
    for (Polynomial::Node* node = head_; node != nullptr; node = node->next) {
        if (node == head_) {
            if (node->multiplier >= 0) {
                if (node->multiplier != 1 || node->members.empty()) {
                    ans += abs(node->multiplier).to_string();
                }
            } else {
                if (node->multiplier != -1 || node->members.empty()) {
                    ans += "-";
                    ans += abs(node->multiplier).to_string();
                } else {
                    ans += "-";
                }
            }
            for (std::pair<char, int> i : node->members) {
                if (i.second == 1) {
                    ans += i.first;
                } else {
                    ans += i.first;
                    ans += "^";
                    ans += std::to_string(i.second);
                }
            }
        } else {
            if (node->multiplier >= 0) {
                if (node->multiplier != 1 || node->members.empty()) {
                    ans += " + ";
                    ans += abs(node->multiplier).to_string();
                } else {
                    ans += " + ";
                }
            } else {
                if (node->multiplier != -1 || node->members.empty()) {
                    ans += " - ";
                    ans += abs(node->multiplier).to_string();
                } else {
                    ans += " - ";
                }
            }
            for (std::pair<char, int> i : node->members) {
                if (i.second == 1) {
                    ans += i.first;
                } else {
                    ans += i.first;
                    ans += "^";
                    ans += std::to_string(i.second);
                }
            }
        }
    }
    return ans;
}

void Polynomial::clear() {
    Node* tmp = nullptr;
    for (Node* i = head_; i != nullptr;) {
        tmp = i->next;
        delete i;
        i = tmp;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

std::vector<char> Polynomial::get_all_variables() {
    std::set<char> tmp_set;
    for (Polynomial::Node* i = head_; i != nullptr; i = i->next) {
        for (int j = 0; j < i->members.size(); ++j) {
            tmp_set.insert(i->members[j].first);
        }
    }
    std::vector<char> ans;
    for (char i : tmp_set) {
        ans.push_back(i);
    }
    return ans;
}

std::vector<std::pair<int64_t, int64_t>> Polynomial::factorGenerator(int64_t n) {
    std::vector<std::pair<int64_t, int64_t>> factors;
    for (int64_t i = 2; i * i <= n; ++i) {
        int count = 0;
        while (n % i == 0) {
            n /= i;
            ++count;
        }
        if (count > 0) {
            factors.push_back(std::make_pair(i, count));
        }
    }
    if (n > 1) {
        factors.push_back(std::make_pair(n, 1));
    }
    return factors;
}

std::vector<int64_t> Polynomial::IntegerSolutions() {
    std::vector<int64_t> ans;
    char varriable = ' ';
    for (Polynomial::Node* i = head_; i != nullptr; i = i->next) {
        if (i->members.size() >= 2) {
            throw std::logic_error("Your polynomial have to have just one varriable");
        } else if (i->members.size() == 1) {
            if (varriable == ' ') {
                varriable = i->members.back().first;
            } else if (varriable != i->members.back().first) {
                throw std::logic_error("Your polynomial have to have just one varriable");
            }
        }
    }
    Polynomial remainder("0");
    std::vector<std::pair<int64_t, int64_t>> prime_factors;
    prime_factors = factorGenerator(std::abs(tail_->multiplier.num_));
    std::vector<int64_t> new_pow(prime_factors.size(), 0);
    if (tail_->members.size() > 0) {
        ans.push_back(0);
    }

    while (true) {
        int64_t divisor = 1;
        for (int i = 0; i < prime_factors.size(); ++i) {
            divisor *= fast_pow(prime_factors[i].first, new_pow[i]);
        }
        std::string tmp_str;
        tmp_str += varriable;
        tmp_str += "-";
        tmp_str += std::to_string(divisor);
        Polynomial answer = *this % Polynomial(tmp_str);
        if (*this % Polynomial(tmp_str) == remainder) {
            ans.push_back(divisor);
        }
        tmp_str.clear();
        tmp_str += varriable;
        tmp_str += "+";
        tmp_str += std::to_string(divisor);
        answer = *this % Polynomial(tmp_str);
        if (*this % Polynomial(tmp_str) == remainder) {
            ans.push_back(-divisor);
        }
        if (!new_pow.empty()) {
            int i = 0;
            while (true) {
                new_pow[i]++;
                if (new_pow[i] <= prime_factors[i].second) {
                    break;
                }
                new_pow[i] = 0;
                i++;
                if (i >= prime_factors.size()) {
                    return ans;
                }
            }
        } else {
            return ans;
        }
    }
}

Polynomial Polynomial::derivative(int n, char varriable) {
    Polynomial ans(*this);
    while (n--) {
        if (ans == Polynomial("0")) {
            return ans;
        }
        for (Polynomial::Node* i = ans.head_; i != nullptr; i = i->next) {
            bool check = false;
            for (int j = 0; j < i->members.size(); ++j) {
                if (i->members[j].first == varriable) {
                    check = true;
                    i->multiplier *= i->members[j].second;
                    --i->members[j].second;
                    break;
                }
            }
            if (!check) {
                i->multiplier.num_ = 0;
                i->multiplier.den_ = 1;
            }
        }
        ans.Reduction();
    }
    return ans;
}
