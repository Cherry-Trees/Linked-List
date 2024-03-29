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
 * Initialize size of list to 0, and initialize _head and _tail to new Node pointers.
*/
template<typename T> LinkedList<T>::LinkedList() : _size(0), _auto_delete(1), _head(new Node<T>*()), _tail(new Node<T>*()) {}


template<typename T> LinkedList<T>::LinkedList(const bool _auto_delete) : _size(0), _auto_delete(_auto_delete), _head(new Node<T>*()), _tail(new Node<T>*()) {}

/**
 * Copy Constructor.
 * O(n) :(
*/
template<typename T> LinkedList<T>::LinkedList(const LinkedList<T>& list_copy, const bool _auto_delete) : 
_size(0), _auto_delete(_auto_delete), _head(new Node<T>*()), _tail(new Node<T>*())
{
    // Node<T>* node = list_copy.beginNode();

    // // I don't even know
    // for (int _size = 0; _size < list_copy._size; _size++)
    // {
    //     push_back(node->data);
    //     node = node->next;
    // }

    for (Node<T>* node = list_copy.beginNode(); node; node = node->next)
        push_back(node->data);
}

/**
 * Parameter Pack Constructor.
*/
template<typename T> template<typename ...E> LinkedList<T>::LinkedList(const E& ...args) : 
_size(0), _auto_delete(1), _head(new Node<T>*()), _tail(new Node<T>*()) {_pack_constructor_helper(args...);}


/* -------DESTRUCTOR------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> LinkedList<T>::~LinkedList()
{

    if (_auto_delete)
    {
        // Start at the beginning.
        Node<T>* node = beginNode();

        // Hold the prev Node.
        // This is needed because we need to delete the Nodes while still checking if they point to null.
        Node<T>* prev_node;




        // While the Node does not point to null.
        while (node)
        {
            // std::cout << node->deletable << std::endl;
            // std::cout << node->data << std::endl;
            // if (node->deletable == 1)
            // {
            // std::cout << __FUNCTION__ << " " << node << " : " << node->data << std::endl;
            // Set prev Node to Node.
            prev_node = node;

            // Set the Node to the next Node.
            node = node->next;

            // prev_node = NULL;

            // prev_node->deletable = 0;

            // Delete the prev Node.
            delete prev_node;


            // }

            // else {
            //     // prev_node = node;
            //     node = node->next;
            // }
        }

        delete _head;
        delete _tail;
    }
}


/* -------HELPERS------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> 
template<typename E> struct LinkedList<T>::_dim
{
    static constexpr int value = 0;
};

template<typename T> 
template<typename E> struct LinkedList<T>::_dim<LinkedList<E>>
{
    static constexpr int value = 1 + _dim<E>::value;
};

template<typename T> 
template<typename E> struct LinkedList<T>::_base_type
{
    using t = E;
};

template<typename T> 
template<typename E> struct LinkedList<T>::_base_type<LinkedList<E>>
{
    using t = typename _base_type<E>::t;
};

template<typename T> 
template<typename E> void LinkedList<T>::_deletable_helper(LinkedList<E>& list, const bool flag)
{
    list._auto_delete = flag;
}

template<typename T> 
template<typename E> void LinkedList<T>::_deletable_helper(E base, const bool flag) {}

template<typename T> 
template<typename E> LinkedList<E> LinkedList<T>::_copy_helper(const LinkedList<E>& list, const bool _auto_delete)
{
    return LinkedList<E>(list, _auto_delete);
}

template<typename T> 
template<typename E> E LinkedList<T>::_copy_helper(const E base, const bool _auto_delete) {return base;}

template<typename T> 
template<typename E, typename ...Args> void LinkedList<T>::_pack_constructor_helper(const E& val, const Args& ...args)
{
    push_back(val);
    return _pack_constructor_helper(args...);
}

template<typename T> 
template<typename E> void LinkedList<T>::_pack_constructor_helper(const E& val)
{
    push_back(val);
    return;
}


/* -------ACCESSORS------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> LinkedList<T> LinkedList<T>::copy() const
{
    return LinkedList(*this);
}

template<typename T> T& LinkedList<T>::beginElement() const
{
    // Dereference begin double Node pointer, then dereference its Node pointer to get its data.
    return (**_head).data;
}

template<typename T> Node<T>* LinkedList<T>::beginNode() const
{
    return (*_head);
}

// O(1)
template<typename T> T& LinkedList<T>::endElement() const
{
    return (**_tail).data;
}

// O(1)
template<typename T> Node<T>* LinkedList<T>::endNode() const
{
    return (*_tail);
}

// O(n)
template<typename T> T& LinkedList<T>::operator[](const int index)
{
    Node<T>* node = (*_head);
    for (int i = 0; i < index; i++)
        node = node->next;

    return node->data;
}

template<typename T> int LinkedList<T>::size() const
{
    return _size;
}

template<typename T> int LinkedList<T>::dim() const
{
    return _dim<LinkedList<T>>::value;
}

template<typename T> bool& LinkedList<T>::deletable()
{
    return _auto_delete;
}

/**
 * Destroy all of the Nodes contained in this list.
*/
template<typename T> void LinkedList<T>::destroy()
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

    delete _head;
    delete _tail;
}

// Linear search.
template<typename T> Node<T>* LinkedList<T>::get(const T& val) const
{
    Node<T>* node = (*_head);
    while (node)
    {
        if (node->data == val)
            return node;
        
        node = node->next;
    }

    return 0;
}


/* -------PUSH------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


// Add a Node to the end of the list.
// O(1) Constant time due to the _tail double Node pointer.

// CHECK IF THE NDIM OF THIS LIST IS BIGGER THAN 1
template<typename T> LinkedList<T>& LinkedList<T>::push_back(const T& _val)
{
    // Increment size by one.
    _size++;
    T val;

    // If the list has more than one dimension, create a copy of the parameter _val and flag it to not be auto deleted.
    // This is so that the destructor doesn't delete val after this method call is completed.
    // A helper is used because the compiler doesn't know whether _val of type LinkedList beforehand. 
    if (_dim<LinkedList<T>>::value > 1) {val = _copy_helper(_val, 0);}
    else {val = _val;}

    // Construct new Node that will represent the container to hold val argument.
    Node<T>* new_node = new Node<T>();

    // Initialize its data to val argument.
    new_node->data = val;

    // Since this is the last Node, have its next point to null.
    new_node->next = nullptr;

    // If we don't have an end, we also don't have a beginning.
    // This means that there are no Nodes in the list.
    if (!*_tail)
    {

        // If we only have one Node in the list, then _head and _tail will point to the same Node pointer.
        // That is, if this is the first Node being added to this list, the beginning and end are the same.
        (*_head) = new_node;
        (*_tail) = new_node;

        return *this;
    }

    // Add the new Node to the end of the list.
    // Dereference _tail to get its Node pointer, and have it point to the new Node.
    (*_tail)->next = new_node;

    // Make the new Node the new _tail.
    (*_tail) = new_node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_back(Node<T>* node)
{

    // Increment size by one.
    _size++;

    // Since this is the last Node, have its next point to null.
    node->next = nullptr;

    // If we don't have an end, we also don't have a beginning.
    // This means that there are no Nodes in the list.
    if (!*_tail)
    {

        // If we only have one Node in the list, then _head and _tail will point to the same Node pointer.
        // That is, if this is the first Node being added to this list, the beginning and end are the same.
        (*_head) = node;
        (*_tail) = node;

        return *this;
    }


    // Add the new Node to the end of the list.
    // Dereference _tail to get its Node pointer, and have it point to the new Node.
    (*_tail)->next = node;

    // Make the new Node the new _tail.
    (*_tail) = node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_back(const LinkedList<T>& list)
{

    // Construct a copy of the new list.
    // Set it's auto_delete flag to false so it does not get deleted when this method exits.
    LinkedList<T> list_copy(list, false);

    _size += list_copy._size;

    if (!*_tail)
    {
        (*_head) = list_copy.beginNode();
        (*_tail) = list_copy.endNode();

        return *this;
    }

    // Have the end Node's next Node point to the beginning Node of the new list copy.
    (*_tail)->next = list_copy.beginNode();

    // Assign the end of this list to point to the last Node of the new list copy.
    (*_tail) = list_copy.endNode();

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_front(const T& _val)
{

    // Increment size by one.
    _size++;
    T val;

    // If the list has more than one dimension, create a copy of the parameter _val and flag it to not be auto deleted.
    // This is so that the destructor doesn't delete val after this method call is completed.
    // A helper is used because the compiler doesn't know whether _val of type LinkedList beforehand. 
    if (_dim<LinkedList<T>>::value > 1) {val = _copy_helper(_val, 0);}
    else {val = _val;}

    // Construct new Node that will represent the container to hold val argument.
    Node<T>* new_node = new Node<T>();

    // Initialize its data to val argument.
    new_node->data = val;


    // If we don't have an beginning, we also don't have an end.
    // This means that there are no Nodes in the list.
    if (!*_head)
    {
        // Have the new Node point to nothing for the next Node.
        new_node->next = nullptr;

        // If we only have one Node in the list, then _head and _tail will point to the same Node pointer.
        // That is, if this is the first Node being added to this list, the beginning and end are the same.
        (*_head) = new_node;
        (*_tail) = new_node;

        return *this;
    }

    // Have the new Node's next point to the beginning Node of this list.
    new_node->next = beginNode();

    // Add the new Node to the front of the list.
 

    // Make the new Node the beginning.
    (*_head) = new_node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_front(Node<T>* node)
{

    // Increment size by one.
    _size++;

    // If we don't have an beginning, we also don't have an end.
    // This means that there are no Nodes in the list.
    if (!*_head)
    {
        // Have the new Node point to nothing for the next Node.
        node->next = nullptr;

        // If we only have one Node in the list, then _head and _tail will point to the same Node pointer.
        // That is, if this is the first Node being added to this list, the beginning and end are the same.
        (*_head) = node;
        (*_tail) = node;

        return *this;
    }

    // Have the new Node's next point to the beginning Node of this list.
    node->next = beginNode();

    // Add the new Node to the front of the list.


    // Make the new Node the beginning.
    (*_head) = node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::push_front(const LinkedList<T>& list)
{

    // Construct a copy of the new list.
    // Set it's auto_delete flag to false so it does not get deleted when this method exits.
    LinkedList<T> list_copy(list, false);

    // Increment size by the size of the new list.
    _size += list_copy._size;

    // If we don't have an end, we also don't have an beginning.
    // This means that there are no Nodes in the list.
    if (!*_tail)
    {
        (*_head) = list_copy.beginNode();
        (*_tail) = list_copy.endNode();

        return *this;
    }

    // Have the end of the list copy point to the beginning of this list.
    (*list_copy._tail)->next = beginNode();

    // Assign the beginning of this list to point to the first Node of the list copy.
    (*_head) = list_copy.beginNode();

    return *this;
}


/* -------REMOVE------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> T LinkedList<T>::pop()
{
    
    Node<T>* temp = beginNode();
    // if (!temp) return 0;

    
    const T val = beginElement();

    if (_size-- == 1) {
        (*_head) = NULL;
        (*_tail) = NULL;
        delete temp;

        return val;
    }

    (*_head) = temp->next;
    temp->next = nullptr;
    delete temp;
    return val;

}


template<typename T> LinkedList<T>& LinkedList<T>::remove(const T& val)
{
    Node<T>* node = beginNode();
    Node<T>* prev = NULL;

    while (node && node->data != val)
    {
        prev = node;
        node = node->next;
    }

    if (!node) return *this;
    if (_size == 1) {pop(); return *this;}

    _size--;

    if (node == beginNode())
    {
        (*_head) = node->next;
        delete node;

        return *this;
    }

    if (node == endNode())
    {
        (*_tail) = prev;
    }


    prev->next = node->next;
    delete node;
    
    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::clear()
{
    this->~LinkedList();
    *this = LinkedList<T>(false);
    return *this;
}


/* -------INSERT------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> LinkedList<T>& LinkedList<T>::insert(Node<T>* prev_node, const T val)
{

    // Increment size by one.
    _size++;

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

    // Increment size by one.
    _size++;

    // Hold the prev Node's next Node.
    Node<T>* next_node = prev_node->next;

    // Have the prev Node point to the new Node.
    prev_node->next = node;

    // Have the new Node point to the next Node from earlier.
    node->next = next_node;

    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::insert(Node<T>* prev_node, const LinkedList<T>& list)
{

    // Increment size by size of the new list.
    _size += list._size;

    // Hold the prev Node's next Node.
    Node<T>* next_node = prev_node->next;

    // Have the prev Node point to the beginning of the new list.
    prev_node->next = list.beginNode();

    // Have the end of the new list point to the next Node from earlier.
    list.endNode()->next = next_node;

    return *this;
}


/* -------SORT------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> LinkedList<T>& LinkedList<T>::swap(Node<T>*& node1, Node<T>*& node2)
{
    T temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
    
    return *this;
}


template<typename T> void LinkedList<T>::_sort_impl(Node<T>** head, Node<T>** tail, bool (*key)(T, T))
{

    // Base case - List is length 0 or 1.
    if (!*head || !(*head)->next)
        return;

    // Merge two lists into one by key.
    auto merge = [head, tail, key](Node<T>** front_list_head, Node<T>** back_list_head,
                                   Node<T>** front_list_tail, Node<T>** back_list_tail) {

        // Inner lambda is needed for recursion.
        auto _merge_impl = [head, tail, key](Node<T>** front_list_head, Node<T>** back_list_head,
                                             Node<T>** front_list_tail, Node<T>** back_list_tail, 
                                             auto& _merge_ref) mutable {
            Node<T>* result = NULL;

            // Base cases.
            // Check if one of the sublists is one bigger than the other. 
            // If the front list head is null, then by default return the back list head.
            // If the back list head is null, then by default return the front list head.
            // If they are both null, then this returns null.
            if (!(*front_list_head)) {*tail = (*back_list_tail); return (*back_list_head);}
            else if (!(*back_list_head)) {*tail = (*front_list_tail); return (*front_list_head);}

            // Compare the elements of the front list head and back list head by key, and recursively build the combined list.
            if (key((*front_list_head)->data, (*back_list_head)->data)) {
                result = (*front_list_head);
                result->next = _merge_ref(&(*front_list_head)->next, back_list_head,
                                          front_list_tail, back_list_tail, _merge_ref);
            } 
            else {
                result = (*back_list_head);
                result->next = _merge_ref(front_list_head, &(*back_list_head)->next, 
                                          front_list_tail, back_list_tail, _merge_ref);
            }

            // Return the combined list and backtrack.   
            *head = result;
            return result;
        };

        // Call inner lambda and pass itself as a parameter for recursion.
        _merge_impl(front_list_head, back_list_head, 
                    front_list_tail, back_list_tail, _merge_impl);
        // *tail = (*tail)->next;
    };

    // Split the list into two halves using fast/slow pointer method.
    auto split = [head, tail](Node<T>** front_list_head, Node<T>** back_list_head,
                              Node<T>** front_list_tail, Node<T>** back_list_tail) {

        Node<T>* slow = (*head);
        Node<T>* fast = (*head)->next;

        // Advance fast by 2, slow by 1 to get the midpoint.
        // for (; fast && fast->next; fast = fast->next, slow = slow->next) fast = fast->next;
        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        // The head of the front list is the starting head.
        *front_list_head = *head;

        // The head of the back last is the next after slow since slow is at the midpoint.
        *back_list_head = slow->next;

        // The tail of the front list is the midpoint.
        *front_list_tail = slow;
        
        // The tail of the back list is the original tail.
        *back_list_tail = *tail;

        // Split off the rest of the list.
        slow->next = NULL;
    };

    Node<T>* front_list_head = NULL;
    Node<T>* back_list_head = NULL;
    Node<T>* front_list_tail = NULL;
    Node<T>* back_list_tail = NULL;

    // Split the current list in two.
    split(&front_list_head, &back_list_head, &front_list_tail, &back_list_tail);

    // Keep splitting until the sublists reach length 0 or 1.
    _sort_impl(&front_list_head, &front_list_tail, key);
    _sort_impl(&back_list_head, &back_list_tail, key);

    // Merge the two split lists by key and backtrack.
    merge(&front_list_head, &back_list_head, &front_list_tail, &back_list_tail);
}

// Merge Sort - O(nlogn)
template<typename T> LinkedList<T>& LinkedList<T>::sort(bool (*key)(T, T))
{
    _sort_impl(_head, _tail, key);
    return *this;
}

template<typename T> LinkedList<T> LinkedList<T>::sorted(bool (*key)(T, T)) const
{
    return LinkedList<T>(*this).sort(key);
}


/* -------OPERATORS------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> LinkedList<T>& LinkedList<T>::operator++()
{
    return push_back(0);
}

template<typename T> LinkedList<T>& LinkedList<T>::operator--()
{
    pop();
    return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::operator+=(const T& val)
{
    return push_back(val);
}

template<typename T> LinkedList<T>& LinkedList<T>::operator+=(Node<T>* node)
{
    return push_back(node);
}

template<typename T> LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& list)
{
    // Add a copy of the new list to the end of this list.
    return push_back(list);

    // return *this;
}

template<typename T> LinkedList<T>& LinkedList<T>::operator*=(const int scalar)
{
    // This is so bad pls fix :(
    for (int i = 0; i < scalar; i++)
        (*this) += (*this);

    return *this;
}

template<typename T> LinkedList<T> LinkedList<T>::operator+(const T& val) const
{
    // This isn't very ideal
    return LinkedList<T>(*this).push_back(val);
}

template<typename T> LinkedList<T> LinkedList<T>::operator+(const LinkedList<T>& list) const
{
    return LinkedList<T>(*this).push_back(list);
}

template<typename T> LinkedList<T> LinkedList<T>::operator*(const int scalar) const
{
    LinkedList<T> result;
    for (int i = 0; i < scalar; i++)
        result.push_back(*this);
    
    return result;
}

template<typename T> bool LinkedList<T>::operator==(const LinkedList<T>& list) const
{   
    if (size() != list.size()) return false;

    for (Node<T> *a = beginNode(), *b = list.beginNode(); a && b; a = a->next, b = b->next)
        if (a->data != b->data) return false;
    
    return true;
}

template<typename T> bool LinkedList<T>::operator!=(const LinkedList<T>& list) const
{   
    if (size() != list.size()) return true;

    for (Node<T> *a = beginNode(), *b = list.beginNode(); a && b; a = a->next, b = b->next)
        if (a->data != b->data) return true;
    
    return false;
}


/* -------I/O------- */
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T> void LinkedList<T>::printNodes()
{
    int count = 0;
    for (Node<T>* node = beginNode(); node; node = node->next, count++)
    {
        // cout << "|    " << node << "\t|\t" << node->data << "\t|\t->\t" << node->next << std::endl;
        cout << std::endl << count << std::endl
             << "---------------------------------" << std::endl
             << "|  " << node << "  |\t" << node->data << "\t| -> " << node->next << std::endl
             << "---------------------------------" << std::endl;// << std::endl;

        node = node->next;
    }
}

template<typename T> std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
{
    out << "[ ";
    for (Node<T>* node = list.beginNode(); node; node = node->next)
        out << node->data << " ";

    out << "]";
    return out;
}
