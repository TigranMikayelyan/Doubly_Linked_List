#include "double_list.h"

template <typename T>
List<T>::List() : head{nullptr}, tail{nullptr}, m_size{0} {}

template <typename T>
List<T>::~List()
{
    if (this->head)
    {
        clear();
    }
}

template <typename T>
List<T>::List(const List& oth)
{   
    if (oth.head == nullptr)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->m_size = 0;     
    }
    else
    {
        this->head = new Node(oth.head->data);
        Node* tmp1 = head;
        Node* tmp2 = oth.head->next;
        while (tmp2)
        {
            tmp1->next = new Node(tmp2->data);
            tmp1->next->prev = tmp1;
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }        
        this->tail = tmp1;
        this->m_size = oth.m_size; 
    }
}

template <typename T>
List<T>::List(List&& oth)
{
    this->head = oth.head;
    this->tail = oth.tail;
    this->m_size = oth.m_size;
    oth.head = nullptr;
    oth.tail = nullptr;
    oth.m_size = 0;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& oth)
{
    if (this == &oth)
    {
        return *this;
    }
    clear();
    if (oth.head) 
    {
        this->head = new Node(oth.head->data);
        Node* tmp1 = this->head;
        Node* tmp2 = oth.head->next;
        while (tmp2)
        {
            tmp1->next = new Node(tmp2->data);
            tmp1->next->prev = tmp1;
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        this->tail = tmp1;
        this->m_size = oth.m_size;    
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& oth)
{
    if (this == &oth)
    {
        return *this;
    }
    this->head = oth.head;
    this->tail = oth.tail;
    this->m_size = oth.m_size;
    oth.head = nullptr;
    oth.tail = nullptr;
    oth.m_size = 0;
    return *this;
}

template <typename T>
bool List<T>::operator==(List<T>& oth)
{   
    if (head == nullptr || oth.head == nullptr || (this->length() != oth.length()))
    {
        return false;
    }
    Node* tmp1 = this->head;
    Node* tmp2 = oth.head;
    while (tmp1)
    {
        if (tmp1->data != tmp2->data)
        {
            return false;
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return true;
}

template <typename T>
bool List<T>::operator!=(List<T>& oth)
{   
    if (head == nullptr || oth.head == nullptr || (this->length() != oth.length()))
    {
        return true;
    }
    Node* tmp1 = this->head;
    Node* tmp2 = oth.head;
    while (tmp1)
    {
        if (tmp1->data != tmp2->data)
        {
            return true;
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return false;
}

template <typename T>
void List<T>::sort()
{
    for (Node* i = head; i != nullptr; i = i->next)
    {
        for (Node* j = i->next; j != nullptr; j = j->next)
        {
            if (i->data > j->data)
            {
                std::swap(i->data, j->data);
            }
        }
    }
}

template <typename T>
void List<T>::merge(List<T> oth)
{
    if (head == nullptr || oth.head == nullptr)
    {
        return;
    }   
    List<T> merged_lists;
    Node* current_this = head;
    Node* current_oth = oth.head;
    while (current_this != nullptr && current_oth != nullptr)
    {
        if (current_this->data <= current_oth->data)
        {
            merged_lists.push_back(current_this->data);
            current_this = current_this->next;
        }
        else
        {
            merged_lists.push_back(current_oth->data);
            current_oth = current_oth->next;
        }
    }
    while (current_this != nullptr)
    {
        merged_lists.push_back(current_this->data);
        current_this = current_this->next;
    }
    while (current_oth != nullptr)
    {
        merged_lists.push_back(current_oth->data);
        current_oth = current_oth->next;
    }
    clear();
    head = merged_lists.head;
    tail = merged_lists.tail;
    m_size = merged_lists.m_size;

    merged_lists.head = nullptr;
    merged_lists.tail = nullptr;
    merged_lists.m_size = 0;
}

template <typename T>
const T& List<T>::front()
{
    if (empty())
	{
		throw std::logic_error("List is empty");
	}
    return head->data;
}

template <typename T>
const T &List<T>::back()
{
    if (empty())
	{
		throw std::logic_error("List is empty");
	}
    return tail->data;
}

template <typename T>
int List<T>::length()
{
    int count = 0;
    Node* tmp = head;
    while (tmp)
    {
        ++count;
        tmp = tmp->next;
    }
    return count;
}

template <typename T>
bool List<T>::empty() const
{
    if (head == nullptr)
    {
        return true;
    }
    return false;
}

template <typename T>
void List<T>::clear()
{
    while (head)
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        tmp = nullptr;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

template <typename T>
void List<T>::push_front(T new_val)
{
    if (head == nullptr)
    {
        head = new Node(new_val);
        return;
    }
    Node* tmp = new Node(new_val);
	tmp->next = head;
	head = tmp;
    m_size++;
}

template <typename T>
void List<T>::pop_front()
{
    if (head == nullptr)
    {
        throw std::logic_error("List is empty");
    }
    Node* tmp = head;
    head = head->next;
    delete tmp;
    m_size--;
}

template <typename T>
void List<T>::push_back(T new_val)
{
    Node* tmp = new Node(new_val);
    if (tail == nullptr)
    {
        head = tail = tmp;
    }
	tmp->prev = tail;
    tail->next = tmp;
	tail = tmp;
    m_size++;
}

template <typename T>
void List<T>::pop_back()
{
    if (tail == nullptr)
    {
        throw std::logic_error("List is empty");
    }
    Node* tmp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete tmp;
    m_size--;
}

template <typename T>
void List<T>::insert(int index, T new_val)
{
    if (head == nullptr)
    {
        throw std::logic_error("List is empty you can't insert a value");
    }
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("Invalid index!!!");
    }
    if (index == 0)
    {
        push_front(new_val);
        return;
    }
    if (index == m_size - 1)
    {
        push_back(new_val);
        return;
    }
    Node* tmp1 = head;
    Node* tmp2 = head;
    for (int i = 0; i < index; ++i)
    {
        tmp1 = tmp1->next;
    }
    for (int i = 0; i < index + 1; ++i)
    {
        tmp2 = tmp2->next;
    }
    tmp1->next = new Node(new_val);
    tmp2->prev = tmp1->next;
    tmp1->next->next = tmp2;
}

template <typename T>
void List<T>::erase(int index)
{
    if (head == nullptr)
    {
        throw std::logic_error("List is empty you can't erase a value");
    }
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("Invalid index!!!");
    }
    if (index == 0)
    {
        pop_front();
        return;
    }
    if (index == m_size - 1)
    {
        pop_back();
        return;
    }
    Node* tmp1 = head;
    Node* tmp2 = head;
    for (int i = 0; i < index - 1; ++i)
    {
        tmp1 = tmp1->next;
    }
    for (int i = 0; i < index + 1; ++i)
    {
        tmp2 = tmp2->next;
    }
    delete tmp1->next;
    tmp1->next = tmp2;
    tmp2->prev = tmp1;
}

template <typename T>
void List<T>::resize(int new_size)
{
    if (new_size < 0)
    {
        throw std::invalid_argument("New size cannot be negative.");
    }
    if (new_size < m_size)
    {
        while (m_size > new_size)
        {
            pop_back();
        }        
    }
    else if (new_size > m_size)
    {
        while (m_size < new_size)
        {
            push_back(T());
        }
    }
}

template <typename T>
void List<T>::swap(List<T>& oth)
{
    Node* tmp_head = head;
    head = oth.head;
    oth.head = tmp_head;

    Node* tmp_tail = tail;
    tail = oth.tail;
    oth.tail = tmp_tail;

    int tmp_size = m_size;
    m_size = oth.m_size;
    oth.m_size = tmp_size;
}

template <typename T>
void List<T>::reverse()
{
    if (empty())
	{
		throw std::logic_error("List is empty");
	}   
    if (head == tail)
    {
        return;
    }
    Node* current = head;
    Node* next_node = nullptr;
    Node* prev_node = nullptr;
    while (current != nullptr)
    {
        next_node = current->next;
        current->next = prev_node;
        current->prev = next_node;
        prev_node = current;
        current = next_node;
    }
    std::swap(head, tail);
}

template <typename T>
void List<T>::print()
{
    Node* tmp = head;
    while (tmp)
    {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    if (head)
    {
        std::cout << std::endl;
    }
}
