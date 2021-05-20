#pragma once
using namespace std;

template <typename T>
struct node {
	T key;
	node* next;
	node* prev;
};

template <typename T>
class deque {
public:
	deque();
	~deque();
	T back() {
		if (_size == 0) throw("List is empty");
		return _tail->key;
	}
	T front(){ 
		if (_size == 0) throw("List is empty"); 
		return _head->key; 
	}
	T pop_back();
	T pop_front();
	size_t size() { return _size; }

	node<T>* head() { return _head; }
	node<T>* tail() { return _tail; }
	void push_front(const T&);
	void push_back(const T&);
	bool empty() { return _size == 0; }
	void clear();
	T& operator[] (const size_t);
private:	
	node<T> *_head, *_tail;
	size_t _size;
	void push_first(const T&);
};

template <typename T>
deque<T>::deque() {
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}

template <typename T>
deque<T>::~deque() {
	clear();
}

template <typename T>
void deque<T>::clear() {
	if (_size == 0) return;
	node<T>* temp1 = _tail;
	node<T>* temp2;
	while (temp1->prev != nullptr) {
		temp2 = temp1->prev;
		delete temp1;
		temp1 = temp2;
	}
	delete temp1;
	_head = nullptr; _tail = _head;
	_size = 0;
}

template <typename T>
void deque<T>::push_front(const T& t) {
	if (_size == 0)
		push_first(t);
	else {
		node<T>* head = new node<T>;
		head->key = t;
		head->next = _head;
		head->prev = nullptr;

		_head = head;
		_head->next->prev = _head;
	}
	_size++;
}

template <typename T>
void deque<T>::push_back(const T& t) {
	if (_size == 0)
		push_first(t);
	else {
		node<T>* tail = new node<T>;
		tail->key = t;
		tail->next = nullptr;
		tail->prev = _tail;

		_tail = tail;
		_tail->prev->next = _tail;
	}
	_size++;
}

template <typename T>
void deque<T>::push_first(const T& t) {
	node<T>* temp = new node<T>;
	temp->key = t;
	temp->next = nullptr;
	temp->prev = nullptr;
	_head = temp;
	_tail = temp;
}

template <typename T>
T& deque<T>::operator[] (const size_t index) {
	if (index < 0 || index >= _size)
		throw("Index out of bounds");

	node<T>* temp = _head;
	for (size_t i = 0; i < index; i++)
		temp = temp->next;
	return temp->key;
}

template <typename T>
T deque<T>::pop_back() {
	T res = back();
	node<T>* temp;
	if (_tail->prev != nullptr) {
		temp = _tail->prev;
		temp->next = nullptr;
		delete _tail;
		_tail = temp;
	}
	else {
		delete _tail;
		_tail = nullptr;
		_head = nullptr;
	}
	_size--;
	return res;
}

template <typename T>
T deque<T>::pop_front() {
	if (size == 0) throw("List is empty");
	T res = front();
	node<T>* temp;
	if (_head->next != nullptr) {
		temp = _head->next;
		temp->prev = nullptr;
		delete _head;
		_head = temp;
	}
	else {
		delete _head;
		_tail = nullptr;
		_head = nullptr;
	}
	_size--;
	return res;
}