#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Node.hpp"

using namespace std;


/* -------CONSTRUCTORS------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


/**
 * Constructor.
 * Initialize size of list to 0, and initialize _begin and _end to new Node pointers.
*/
template<typename T> LinkedList<T>::LinkedList() : _size(0), _begin(new Node<T>*()), _end(new Node<T>*()) {}

/**
 * Copy Constructor.
 * O(n) :(
*/
template<typename T> LinkedList<T>::LinkedList(const LinkedList<T>& list_copy) : _size(0), _begin(new Node<T>*()), _end(new Node<T>*())
{
    Node<T>* node = list_copy.beginNode();

    // I don't even know
    for (int _size = 0; _size < list_copy._size; _size++)
    {
        push_back(node->element);
        node = node->next;
    }
}


/* -------DESTRUCTOR------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> LinkedList<T>::~LinkedList()
{
    // Start at the beginning.
    Node<T>* node = beginNode();

    // Hold the prev Node.
    // This is needed because we need to delete the Nodes while still checking if they point to null.
    Node<T>* prev_node;

    // While the Node does not point to null.
    while (node)
    {
        
        // Set prev Node to Node.
        prev_node = node;

        // Set the Node to the next Node.
        node = node->next;

        // Delete the prev Node.
        delete prev_node;
    }
}


/* -------ACCESSORS------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> T& LinkedList<T>::beginElement() const
{
    // Dereference begin double Node pointer, then dereference its Node pointer to get its element.
    return (**_begin).element;
}

template<typename T> Node<T>* LinkedList<T>::beginNode() const
{
    return (*_begin);
}

// O(1)
template<typename T> T& LinkedList<T>::endElement() const
{
    return (**_end).element;
}

// O(1)
template<typename T> Node<T>* LinkedList<T>::endNode() const
{
    return (*_end);
}

// O(n)
template<typename T> T& LinkedList<T>::operator[](const int index)
{
    Node<T>* node = (*_begin);
    for (int i = 0; i < index; i++)
        node = node->next;

    return node->element;
}

template<typename T> int LinkedList<T>::size() const 
{
    return _size;
}


/* -------PUSH------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


// Add a Node to the end of the list.
// O(1) Constant time due to the _end double Node pointer.
template<typename T> LinkedList<T>& LinkedList<T>::push_back(const T val)
{
    // Increment size by one.
    _size++;

    // Construct new Node that will represent the container to hold val argument.
    Node<T>* new_node = new Node<T>();

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

template<typename T> LinkedList<T>& LinkedList<T>::push_back(Node<T>* node)
{

    // Since this is the last Node, have its next point to null.
    node->next = nullptr;

    // If we don't have an end, we also don't have a beginning.
    // This means that there are no Nodes in the list.
    if (!*_end)
    {
        // If we only have one Node in the list, then _begin and _end will point to the same Node pointer.
        // That is, if this is the first Node being added to this list, the beginning and end are the same.
        (*_begin) = node;
        (*_end) = node;

        return *this;
    }

    // Add the new Node to the end of the list.
    // Dereference _end to get its Node pointer, and have it point to the new Node.
    (*_end)->next = node;

    // Make the new Node the new _end.
    (*_end) = node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_back(const LinkedList<T>& list)
{
    /* This does NOT create a copy, so modifying the original list modifies this one too. */

    // Increment size by the size of the new list.
    _size += list._size;

    // Have the end Node's next Node point to the beginning Node of the new list.
    (*_end)->next = list.beginNode();

    // Assign the end of this list to point to the last Node of the new list.
    (*_end) = list.endNode();
    
    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_back_copy(const LinkedList<T>& list)
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

template<typename T> LinkedList<T>& LinkedList<T>::push_front(const T val)
{

    // Increment size by one.
    _size++;

    // Construct new Node that will represent the container to hold val argument.
    Node<T>* new_node = new Node<T>();

    // Initialize its element to val argument.
    new_node->element = val;

    // If we don't have an beginning, we also don't have an end.
    // This means that there are no Nodes in the list.
    if (!*_begin)
    {
        // Have the new Node point to nothing for the next Node.
        new_node->next = nullptr;

        // If we only have one Node in the list, then _begin and _end will point to the same Node pointer.
        // That is, if this is the first Node being added to this list, the beginning and end are the same.
        (*_begin) = new_node;
        (*_end) = new_node;

        return *this;
    }

    // Have the new Node's next point to the beginning Node of this list.
    new_node->next = beginNode();

    // Make the new Node the beginning.
    (*_begin) = new_node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_front(Node<T>* node)
{

    // Increment size by one.
    _size++;

    // If we don't have an beginning, we also don't have an end.
    // This means that there are no Nodes in the list.
    if (!*_begin)
    {
        // Have the new Node point to nothing for the next Node.
        node->next = nullptr;

        // If we only have one Node in the list, then _begin and _end will point to the same Node pointer.
        // That is, if this is the first Node being added to this list, the beginning and end are the same.
        (*_begin) = node;
        (*_end) = node;

        return *this;
    }

    // Have the new Node's next point to the beginning Node of this list.
    node->next = beginNode();

    // Make the new Node the beginning.
    (*_begin) = node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_front(const LinkedList<T>& list)
{
    /* This does NOT create a copy, so modifying the original list modifies this one too. */

    // Increment size by the size of the new list.
    _size += list._size;

    // Have the end of the new list point to the beginning of this list.
    (*list._end)->next = beginNode();

    // Assign the beginning of this list to point to the first Node of the new list.
    (*_begin) = list.beginNode();
    
    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_front_copy(const LinkedList<T>& list)
{

    // Construct a copy of the new list.
    LinkedList<T> list_copy(list);

    // Increment size by the size of the new list.
    _size += list_copy._size;

    // Have the end of the list copy point to the beginning of this list.
    (*list_copy._end)->next = beginNode();

    // Assign the beginning of this list to point to the first Node of the list copy.
    (*_begin) = list_copy.beginNode();
    
    return *this;
}


/* -------INSERT------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> LinkedList<T>& LinkedList<T>::insert(Node<T>* prev_node, const T val)
{

    // Construct new Node object to hold val.
    Node<T>* new_node = new Node<T>(val);

    // Hold the prev Node's next Node.
    Node<T>* next_node = prev_node->next;

    // Have the prev Node point to the new Node.
    prev_node->next = new_node;

    // Have the new Node point to the next Node from earlier.
    new_node->next = next_node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::insert(Node<T>* prev_node, Node<T>* node)
{
    // Hold the prev Node's next Node.
    Node<T>* next_node = prev_node->next;

    // Have the prev Node point to the new Node.
    prev_node->next = node;

    // Have the new Node point to the next Node from earlier.
    node->next = next_node;

    return *this;
}


/* -------OPERATORS------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& list)
{
    // Add a copy of the new list to the end of this list.
    push_back_copy(list);

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::operator+=(const T& val)
{
    return push_back(val);
}

template<typename T> LinkedList<T>& LinkedList<T>::operator*=(const int scalar)
{
    for (int i = 0; i < scalar; i++)
        (*this) += (*this);

    return *this;
}

template<typename T> std::ostream& operator<<(std::ostream& out, const LinkedList<T>& ll)
{
    
    Node<T>* node = ll.beginNode();
    out << "[ ";
    while (node)
    {
        out << node->element << " ";
        node = node->next;
    }
    out << "]";

    return out;
}
