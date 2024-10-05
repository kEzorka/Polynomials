#pragma once
#include "fraction.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>

struct Polynomial::Node {
	Polynomial::Node() {
		next = nullptr;
		members = std::vector<std::pair<char, int64_t>>();
		multiplier = 0;
	}
	Polynomial::Node(std::string);
	Polynomial::Node(const Polynomial::Node&);
	~Node();
	void clear();
public:
	Node* next = nullptr;
	std::vector<std::pair<char, int64_t>> members;
	Fraction multiplier = 0;
};
