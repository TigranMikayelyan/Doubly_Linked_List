#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <iostream>
#include <exception>

template <typename T>
class List
{
public:
    List();
	~List();
	List(const List<T>&);
	List(List<T>&&);
public:
	List& operator=(const List<T>&);
	List& operator=(List<T>&&);
	bool operator==(List<T>&);
	bool operator!=(List<T>&);
public:
    void sort();
    void merge(List<T>);
public:
    const T& front();
    const T& back();
    int length();
    bool empty() const;
    void clear();
    void push_front(T);
    void pop_front();
    void push_back(T);
    void pop_back();
    void insert(int, T);
    void erase(int);
    void resize(int);
    void swap(List<T>&);
    void reverse();
    void print();
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node() : data{}, next{nullptr}, prev{nullptr} {}
	Node(const T& rhs) : data{rhs}, next{nullptr}, prev{nullptr} {}
    };
    Node* head;
    Node* tail;
    int m_size;
};

#endif // DOUBLE_LIST_H
