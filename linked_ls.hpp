#pragma once

#include <iostream>
#include <stdexcept> // std::out_of_range
#include <string>
#include <fstream> // std::ofstream

// Operator declarations

// Must declare linked list class first
template <typename T>
class LinkedList;

// Then declare << operator
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const LinkedList<T> &r_handside);

/*


 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************


*/

/* node definition */
template <typename T>
struct Node
{
    Node(const T &value, Node *next = nullptr)
        : _value(value), _next(next)
    {
        // Empty constructor body
    }

    T _value;
    Node *_next;
};

/*


 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************


*/

/* linked list definition */
template <typename T>
class LinkedList
{
public:
    // Constructor
    LinkedList() : head(nullptr), _size(0)
    {
        // Create empty linked list, head = nullptr
        // Empty constructor body
    }

    // Parameterized constructor
    LinkedList(const T &value) : head(nullptr), _size(0)
    {
        push_back(value);
    }

    // Destructor
    ~LinkedList()
    {
        std::cout << "Destructor performing clean-up.\n";
        clear();
    }

    // Defined below
    // Modifiers
    void push_back(const T &value);

    T pop_back();

    void push_front(const T &value);

    T pop_front();

    void clear();

    void copy(const LinkedList<T> &r_handside);

    // Accessors
    size_t size();

    T front();

    T back();

    bool empty();

    void write_file(const std::string &file_name);

    // Overloaded insertion operator
    // Output stream on left, linked list on right hand side
    // std::cout << sample_list;

    // Friend functions do not belong to a class, they merely have access
    // to members like a member function would.
    friend std::ostream &operator<<<>(std::ostream &ostr, const LinkedList<T> &r_handside);

    LinkedList<T> &operator=(const LinkedList<T> &r_handside);

private:
    // Ptr to -> [head node]
    Node<T> *head;
    size_t _size;
};

/*


 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************


*/

template <typename T>
size_t LinkedList<T>::size()
{
    return _size;
}

template <typename T>
T LinkedList<T>::front()
{
    if (head == nullptr)
        throw std::out_of_range("Attempted to call front() on an empty list");

    // else return value
    return head->_value;
}

template <typename T>
T LinkedList<T>::back()
{
    if (head == nullptr)
        throw std::out_of_range("Attempted to call back() on an empty list");

    Node<T> *current = head;

    while (current->_next != nullptr)
        current = current->_next;

    return current->_value;
}

template <typename T>
bool LinkedList<T>::empty()
{
    return _size == 0;
}

template <typename T>
void LinkedList<T>::write_file(const std::string &file_name)
{
    std::ofstream linked_list_file(file_name, std::ios::out);

    if (!linked_list_file.is_open())
    {
        // concatenate string to throw as error message
        std::string error_report = file_name + " could not be opened.";
        throw std::runtime_error(error_report);
    }

    // if list is empty
    if (head == nullptr)
    {
        linked_list_file << "[]";
        linked_list_file.close();
        return;
    }

    Node<T> *current = head;

    linked_list_file << "[";
    while (current != nullptr)
    {
        if (current->_next == nullptr)
            // if last element
            linked_list_file << current->_value;

        else
            // insert value into file
            linked_list_file << current->_value << ", ";

        // advance pointer
        current = current->_next;
    }
    linked_list_file << "]";

    linked_list_file.close();

    std::cout << "Data written to " << file_name << ".\n";
    // void return
}

// Define push_back
// If linked list is empty, i.e. head = null, handle one way
// If there is at least 1 element, handle differently
template <typename T>
void LinkedList<T>::push_back(const T &value)
{
    if (head == nullptr)
    {
        // Empty case
        /*
            Allocates a node on the heap,
            then returns the address of that
            new node containing the value 
            inserted.

            new = creates node on heap, return value is of heap address
            head = address of node.

            head ---> [_value = value] ---> nullptr (_next = nullptr)
        */
        head = new Node<T>(value);
    }
    else
    {
        // Non-empty case
        // Must traverse list
        Node<T> *current = head;

        /* 
            current ---> ptr to head node, i.e. 
            both point to same node

            example: 
            head --->  [_value = value] ---> nullptr
            current ---^
        */

        while (current->_next != nullptr)
        {
            current = current->_next;

            /* 
                current = current->_next example:

                example: 
                head --->  [_value = value] ---> [_value = value]
                current --------------------------^

                current now points to the next node, per iteration
            */
        }

        Node<T> *temporary = new Node<T>(value); // points to nullptr
        current->_next = temporary;              // current ---> temp
    }

    ++_size;
    // Void return
}

template <typename T>
T LinkedList<T>::pop_back()
{
    T ret_val;

    if (head == nullptr)
    {
        // empty list scenario, size 0
        throw std::out_of_range("Error: attempt to pop from an empty list.");
    }
    else if (head->_next == nullptr)
    {
        // return val
        ret_val = head->_value;

        // size of 1

        // before:
        // head --->  [_value = value] ---> nullptr

        // head ---> X (memory deallocated)
        delete head;

        // head ---> nullptr (no dangling pointer)
        head = nullptr;
    }
    else
    {
        Node<T> *current = head;

        // size >= 2
        while (current->_next->_next != nullptr)
            current = current->_next;

        // return val
        ret_val = (current->_next)->_value;

        delete current->_next;
        current->_next = nullptr;
    }

    --_size;
    return ret_val;
}


template <typename T>
void LinkedList<T>::push_front(const T &value) {
    if (head == nullptr)
    {
        // Empty case
        /*
            Allocates a node on the heap,
            then returns the address of that
            new node containing the value 
            inserted.

            new = creates node on heap, return value is of heap address
            head = address of node.

            head ---> [_value = value] ---> nullptr (_next = nullptr)
        */
        head = new Node<T>(value);
    } else {
        Node<T>* temp = new Node<T>(value, head);
        head = temp;
    }

    ++_size;
    // Void return
}

template <typename T>
T LinkedList<T>::pop_front() {
    T ret_val;

    if (head == nullptr)
    {
        // empty list scenario, size 0
        throw std::out_of_range("Error: attempt to pop from an empty list.");
    }

    // set return value
    ret_val = head->_value;

    // set temp to head pointer
    Node<T>* temp = head;
    head = head->_next;
    delete temp;

    return ret_val;
}

template <typename T>
void LinkedList<T>::clear()
{
    if (head == nullptr)
        return; // already empty

    Node<T> *current = head;

    while (current != nullptr)
    {
        Node<T> *temp = current->_next;
        delete current;
        current = temp; // if it is a list of size 1, this would equate to current = nullptr
    }

    head = nullptr; // avoid a dangling pointer!

    // void return
}

// Copy right hand side linked list to left hand side
template <typename T>
void LinkedList<T>::copy(const LinkedList<T> &r_handside)
{
    // if not empty, clear list
    if (head != nullptr)
    {
        clear();
    }
    else if (r_handside.head == nullptr)
    {
        // attempt to copy empty list, do nothing
        return;
    }
    else
    {
        Node<T> *current_rhs = r_handside.head;

        while (current_rhs != nullptr)
        {
            // push back current value of rhs list
            // to lhs list, then continue iterating through
            push_back(current_rhs->_value);
            current_rhs = current_rhs->_next;
        }
    }

    // void return
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &r_handside)
{
    // use previously defined copy function, along with this pointer
    this->copy(r_handside);
    return *this;
}

// Define insertion operator, which was described above using a templated prototype
template <typename T>
std::ostream &operator<<(std::ostream &ostr, const LinkedList<T> &r_handside)
{
    // since this is a public function that is not part of the LinkedList
    // class we must use the passed in r_handside LL, then access its head pointer
    Node<T> *current = r_handside.head;

    std::cout << "[";
    while (current != nullptr)
    {
        if (current->_next == nullptr)
            std::cout << current->_value;
        else
            std::cout << current->_value << ", ";

        // Advance pointer
        current = current->_next;
    }
    std::cout << "]";

    return ostr;
}