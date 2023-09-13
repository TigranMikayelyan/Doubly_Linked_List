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
private:
	void quick_sort(Node* first, Node* last)
	{
		if (first != nullptr && last != nullptr && first != last && first->prev != last)
		{
			Node* pivot_index = partition(first, last);
			quick_sort(first, pivot_index->prev);
			quick_sort(pivot_index->next, last);
		}
	}

	Node* partition(Node* first, Node* last)
	{
		T pivot = last->data;
		Node* i = first->prev;
		for (Node* j = first; j != last; j = j->next)
		{
			if (j->data <= pivot)
			{
				i = (i == nullptr) ? first : i->next;
				std::swap(i->data, j->data);
			}	
		}
		i = (i == nullptr) ? first : i->next;
		std::swap(i->data, last->data);
		return i;
	}	
};

#endif // DOUBLE_LIST_H