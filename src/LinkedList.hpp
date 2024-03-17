#include <iostream>
#include "LinkedList.h"

using namespace std;

/**
 * Constructor.
 * Initialize size of list to 0, and initialize _begin and _end to new Node pointers.
*/
template<typename T> LinkedList<T>::LinkedList() : _size(0), _begin(new Node*()), _end(new Node*()) {}

/**
 * Copy Constructor.
 * O(n) :(
*/
template<typename T> LinkedList<T>::LinkedList(const LinkedList<T>& list_copy) : _size(0), _begin(new Node*()), _end(new Node*())
{
    Node* node = list_copy.beginNode();

    // I don't even know
    for (int _size = 0; _size < list_copy._size; _size++)
    {
        this->push(node->element);
        node = node->next;
    }
}

template<typename T> T& LinkedList<T>::beginElement() const
{
    // Dereference begin double Node pointer, then dereference its Node pointer to get its element.
    return (**_begin).element;
}

template<typename T> typename LinkedList<T>::Node* LinkedList<T>::beginNode() const
{
    return (*_begin);
}

// O(1)
template<typename T> T& LinkedList<T>::endElement() const
{
    return (**_end).element;
}

// O(1)
template<typename T> typename LinkedList<T>::Node* LinkedList<T>::endNode() const
{
    return (*_end);
}

// O(n)
template<typename T> T& LinkedList<T>::operator[](const int index)
{
    Node* node = (*_begin);
    for (int i = 0; i < index; i++)
        node = node->next;

    return node->element;
}

template<typename T> int LinkedList<T>::size() const 
{
    return _size;
}

// Add a Node to the end of the list.
// O(1) Constant time due to the _end double Node pointer.
template<typename T> LinkedList<T>& LinkedList<T>::push(const T val)
{
    // Increment size by one.
    _size++;

    // Construct new Node that will represent the container to hold val argument.
    Node* new_node = new Node();

    // Initialize its element to val argument.
    new_node->element = val;

    // Since this is the last Node, have its next point to null.
    new_node->next = nullptr;

    // If we don't have an end, we also don't have a beginning.
    // This means that there are no Nodes in the list.
    if (!*_end)
    {
        // If we only have one Node in the list, then _begin and _end will point to the same Node pointer.
        // That is, if this is the first Node being added to this list, the beginning and end are the same.
        (*_begin) = new_node;
        (*_end) = new_node;

        return *this;
    }

    // Add the new Node to the end of the list.
    // Dereference _end to get its Node pointer, and have it point to the new Node.
    (*_end)->next = new_node;

    // Make the new Node the new _end.
    (*_end) = new_node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push(const LinkedList<T>& list)
{
    /* This does NOT create a copy, so modifying the original list modifies this one too. */

    _size += list._size;

    // Have the end Node's next Node point to the beginning Node of the new list.
    (*_end)->next = list.beginNode();

    // Assign the end of this list to point to the last Node of the new list.
    (*_end) = list.endNode();
    
    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_copy(const LinkedList<T>& list)
{

    // Construct a copy of the new list.
    LinkedList<T> list_copy(list);

    _size += list_copy._size;

    // Have the end Node's next Node point to the beginning Node of the new list copy.
    (*_end)->next = list_copy.beginNode();

    // Assign the end of this list to point to the last Node of the new list copy.
    (*_end) = list_copy.endNode();

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& list)
{
    // Add a copy of the new list to the end of this list.
    push_copy(list);

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::operator+=(const T& val)
{
    return this->push(val);
}

template<typename T> LinkedList<T>& LinkedList<T>::operator*=(const int scalar)
{
    for (int i = 0; i < scalar; i++)
        (*this) += (*this);

    return *this;
}

template<typename T> std::ostream& operator<<(std::ostream& out, const LinkedList<T>& ll)
{
    
    typename LinkedList<T>::Node* node = ll.beginNode();
    out << "[ ";
    while (node)
    {
        out << node->element << " ";
        node = node->next;
    }
    out << "]";

    return out;
}
