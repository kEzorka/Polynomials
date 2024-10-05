#pragma once
#include <exception>
#include <fstream>

template<typename T>
class Base {
	class Node;
public:
	Base();
	~Base();
	void push_back(T);
	void erase(size_t);
	void clear();
	bool LoadFromFile(std::string);
	void SaveToFile(std::string);
	size_t size();

	T& operator[](size_t);

private:
	Node* head_;
	Node* tail_;
	size_t size_;
};

template<typename T>
inline Base<T>::Base() : head_(nullptr), tail_(nullptr), size_(0) {

}

template<typename T>
class Base<T>::Node {
public:
	Node() : next(nullptr), data(T()) {}
	Node(T new_data) : next(nullptr), data(new_data) {}
	~Node() {
		clear();
	}

	void clear() {
		next = nullptr;
		data = T();
	}

public:
	Node* next;
	T data;
};

template<typename T>
void Base<T>::push_back(T new_data) {
	Base<T>::Node* q = new Base<T>::Node(new_data);
	if (head_ == nullptr) {
		head_ = q;
		tail_ = q;
	} else {
		tail_->next = q;
		tail_ = q;
	}
	++size_;
}

template<typename T>
void Base<T>::erase(size_t pos) {
	if (pos < 0 || pos >= size_) {
		throw std::runtime_error("Base subscript out of range");
	}
	Base<T>::Node* i = head_;
	while (pos--) {
		i = i->next;
	}
	if (i == head_ && i == tail_) {
		head_ = nullptr;
		tail_ = nullptr;
		delete i;
	} else if (i == head_) {
		head_ = i->next;
		delete i;
	} else if (i == tail_) {
		Base<T>::Node* j = head_;
		for (; j->next != tail_; j = j->next);
		j->next = nullptr;
		tail_ = j;
		delete i;
	} else {
		Base<T>::Node* j = head_;
		for (; j->next != i; j = j->next);
		j->next = i->next;
		delete i;
	}
	--size_;
}

template<typename T>
inline void Base<T>::clear() {
	Base<T>::Node* tmp = nullptr;
	for (Base<T>::Node* i = head_; i != nullptr; ) {
		tmp = i->next;
		delete i;
		i = tmp;
	}
	head_ = nullptr;
	tail_ = nullptr;
	size_ = 0;
}

template<typename T>
inline Base<T>::~Base() {
	clear();
}

template<typename T>
inline bool Base<T>::LoadFromFile(std::string str) {
	bool alright = true;
	clear();
	std::ifstream in(str);
	std::string new_str;
	while (std::getline(in, new_str)) {
		try {
			T q = T(new_str);
			push_back(new_str);
		}
		catch (const std::exception& e) {
			alright = false;
			continue;
		}
	}
	in.close();
	return alright;
}

template<typename T>
inline void Base<T>::SaveToFile(std::string str) {
	std::ofstream out(str);
	for (Base<T>::Node* i = head_; i != nullptr; i = i->next) {
		out << i->data << '\n';
	}
	out.close();
}

template<typename T>
T& Base<T>::operator[](size_t size) {
	if (size < 0 || size >= size_) {
		throw std::runtime_error("Base subscript out of range");
	}
	Base<T>::Node* i = head_;
	while (size-- && size != SIZE_MAX) {
		i = i->next;
	}
	return i->data;
}

template<typename T>
size_t Base<T>::size() {
	return size_;
}
