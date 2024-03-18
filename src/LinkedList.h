#pragma once
#include <iostream>
#include "Node.hpp"

template<typename T> class LinkedList
{       

    
    public:

        /**
         * Constructor.
         * Initialize size of list to 0, and initialize _begin and _end to new Node pointers.
        */
        LinkedList();
        
        /**
         * Copy Constructor.
        */
        LinkedList(const LinkedList<T>& list_copy);

        /**
         * Destructor.
         * Delete all of the Nodes in the list.
        */
        ~LinkedList();


        T& beginElement() const;

        Node<T>* beginNode() const;

        // O(1)
        T& endElement() const;

        // O(1)
        Node<T>* endNode() const;

        // O(n)
        T& operator[](const int index);

        int size() const;

        // Add a Node to the end of the list.
        // O(1) Constant time due to the _end double Node pointer.
        LinkedList<T>& push_back(const T val);

        // Add a list to the end of this list.
        // This does NOT create a copy, so modifying the original list modifies this one too.
        // Creates a circular list if the same list is added.
        // O(1)

        // Add a Node to the end of the list.
        LinkedList<T>& push_back(Node<T>* node);


        LinkedList<T>& push_back(const LinkedList<T>& list);


        // Add a COPY of a list to the end of this list.
        // O(n)
        LinkedList<T>& push_back_copy(const LinkedList<T>& list);

        // Add a Node to the front of this list.
        LinkedList<T>& push_front(const T val);

        // Add a Node to the front of the list.
        LinkedList<T>& push_front(Node<T>* node);

        // Add a list to the front of this list.
        // This does NOT create a copy, so modifying the original list modifies this one too.
        // Creates a circular list if the same list is added.
        // O(1)
        LinkedList<T>& push_front(const LinkedList<T>& list);

        // Add a COPY of a list to the front of this list.
        // O(n)
        LinkedList<T>& push_front_copy(const LinkedList<T>& list);

        // O(n)
        LinkedList<T>& insert(const int index, const T val);
        LinkedList<T>& insert(const int index, Node<T>* node);
        LinkedList<T>& insert(const int index, const LinkedList<T>& list);

        // O(1) Given a reference node.
        LinkedList<T>& insert(Node<T>* prev_node, const T val);
        LinkedList<T>& insert(Node<T>* prev_node, Node<T>* node);
        LinkedList<T>& insert(Node<T>* prev_node, const LinkedList<T>& list);

        LinkedList<T>& insert_copy(Node<T>* prev_node, const LinkedList<T>& list);

        // Add a COPY of a list to this list.
        // O(n)
        LinkedList<T>& operator+=(const LinkedList<T>& list);

        LinkedList<T>& operator+=(const T& val);

        LinkedList<T>& operator*=(const int scalar);


        void printNodes();



        template<typename _T> friend std::ostream& operator<<(std::ostream& out, const LinkedList<_T>& ll);
    

    private:

        

        // Double Node pointer points to the first Node pointer in this list.
        Node<T>** _begin; 

        // Double Node pointer points to the last Node pointer in this list.
        Node<T>** _end;

        // Number of nodes in this list.
        int _size;

};
