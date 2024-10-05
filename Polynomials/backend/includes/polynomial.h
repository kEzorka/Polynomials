#pragma once

#include <vector>
#include <string>
#include <map>

class Fraction;

class Polynomial {
	struct Node;
public:
	Polynomial() {
		head_ = nullptr;
		tail_ = nullptr;
		size_ = 0;
	}
	Polynomial(int);
	Polynomial(std::string);
	Polynomial(Node*&);
	Polynomial(const Polynomial&);
	~Polynomial() = default;
	friend std::ostream& operator<<(std::ostream& out, Polynomial node);
	friend Polynomial operator+ (const Polynomial lhs, const Polynomial rhs);
	friend Polynomial operator+= (Polynomial& lhs, const Polynomial rhs);
	friend Polynomial operator- (const Polynomial lhs, const Polynomial rhs);
	friend Polynomial operator-= (Polynomial& lhs, const Polynomial rhs);
	friend Polynomial operator*(const Polynomial lhs, const Polynomial rhs);
	friend Polynomial operator*= (Polynomial& lhs, const Polynomial rhs);
	friend Polynomial operator/(Polynomial lhs, Polynomial rhs);
	friend Polynomial operator/= (Polynomial& lhs, Polynomial rhs);
	friend Polynomial operator%(Polynomial lhs, Polynomial rhs);
	friend Polynomial operator%= (Polynomial& lhs, Polynomial rhs);
	friend bool operator == (const Polynomial& lhs, const Polynomial& rhs);
	Polynomial& operator =(const Polynomial rhs);

	friend Node operator*(const Node& lhs, const Node& rhs);
	friend Node operator/(const Node& lhs, const Node& rhs);
	friend bool operator == (Node& lhs, Node& rhs);
	friend bool operator != (Node& lhs, Node& rhs);
	Fraction result(std::vector<std::pair<char, int>>);
	std::vector<int64_t> IntegerSolutions();
	Polynomial derivative(int, char);
	void push_back(Node*);
	std::string to_string();
	void clear();
	std::vector<char> get_all_variables();

private:
	Polynomial::Node* head_ = nullptr;
	Polynomial::Node* tail_ = nullptr;
	int size_ = 0;

	void Separation(std::string);
	int64_t fast_pow(int64_t, int64_t);
	void Reduction();
	std::vector<std::pair<int64_t, int64_t>> factorGenerator(int64_t);
	friend Polynomial diviser_of_two_polynomials(Polynomial lhs, Polynomial rhs);
};
