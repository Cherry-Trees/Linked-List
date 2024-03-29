#pragma once
#include <iostream>
#include "Node.hpp"

/**
 * Linked List Generic.
*/
template<typename T> class LinkedList
{       

    private:

        // Double Node pointer points to the first Node pointer in this list.
        Node<T>** _head; 

        // Double Node pointer points to the last Node pointer in this list.
        Node<T>** _tail;

        // Number of nodes in this list.
        int _size;

        // Flag that controls whether the destructor deletes the Nodes contained in this list.
        bool _auto_delete;

        // Metafunction helper for dim() method.
        template<typename E> struct _dim;

        // Metafunction to extract the base type of the list.
        template<typename E> struct _base_type;


        template<typename E> static void _deletable_helper(LinkedList<E>& list, const bool flag);
        template<typename E> static void _deletable_helper(E base, const bool flag);

        template<typename E> static LinkedList<E> _copy_helper(const LinkedList<E>& list, const bool _auto_delete = 1);
        template<typename E> static E _copy_helper(const E base, const bool _auto_delete = 1);

        template<typename E, typename ...Args> void _pack_constructor_helper(const E& val, const Args& ...args);
        template<typename E> void _pack_constructor_helper(const E& val);

        void _sort_impl(Node<T>** head, Node<T>** tail, bool (*key)(T, T) = [](T a, T b){return a < b;});




    
    public:

        /**
         * Constructor.
         * Initialize size of list to 0, and initialize _begin and _end to new Node pointers.
        */
        LinkedList();

        LinkedList(const bool _auto_delete);

        
        /**
         * Copy Constructor.
        */
        LinkedList(const LinkedList<T>& list_copy, const bool _auto_delete = 1);


        /**
         * Parameter Pack Constructor.
        */
        template<typename ...E> LinkedList(const E& ...args);



        /**
         * Destructor.
         * Delete all of the Nodes in the list.
        */
        ~LinkedList();

        LinkedList<T> copy() const;

       


        T& beginElement() const;

        Node<T>* beginNode() const;

        // O(1)
        T& endElement() const;

        // O(1)
        Node<T>* endNode() const;

        // O(n)
        T& operator[](const int index);

        int size() const;

        int dim() const;

        bool& deletable();

        void destroy();

        Node<T>* get(const T& val) const;

        // Add a Node to the end of the list.
        LinkedList<T>& push_back(const T& _val);

        // Add a Node to the end of the list.
        LinkedList<T>& push_back(Node<T>* node);


        LinkedList<T>& push_back(const LinkedList<T>& list);

        // Add a Node to the front of this list.
        LinkedList<T>& push_front(const T& _val);

        // Add a Node to the front of the list.
        LinkedList<T>& push_front(Node<T>* node);

        LinkedList<T>& push_front(const LinkedList<T>& list);




        T pop();
        T pop(const int index);

        LinkedList<T>& remove(const T& val);

        LinkedList<T>& clear();

        LinkedList<T>& swap(Node<T>*& node1, Node<T>*& node2);
        
        LinkedList<T>& sort(bool (*key)(T, T) = [](T a, T b){return a < b;});
        LinkedList<T> sorted(bool (*key)(T, T) = [](T a, T b){return a < b;}) const;

        

        // O(n)
        LinkedList<T>& insert(const int index, const T val);
        LinkedList<T>& insert(const int index, Node<T>* node);
        LinkedList<T>& insert(const int index, const LinkedList<T>& list);

        // O(1) Given a reference node.
        LinkedList<T>& insert(Node<T>* prev_node, const T val);
        LinkedList<T>& insert(Node<T>* prev_node, Node<T>* node);
        LinkedList<T>& insert(Node<T>* prev_node, const LinkedList<T>& list);

        LinkedList<T>& operator++();
        LinkedList<T>& operator--();
        
        LinkedList<T>& operator+=(const T& val);
        LinkedList<T>& operator+=(Node<T>* node);
        LinkedList<T>& operator+=(const LinkedList<T>& list);

        LinkedList<T>& operator*=(const int scalar);

        LinkedList<T> operator+(const T& val) const;
        LinkedList<T> operator+(Node<T>* node) const;
        LinkedList<T> operator+(const LinkedList<T>& list) const;

        LinkedList<T> operator*(const int scalar) const;

        bool operator==(const LinkedList<T>& list) const;
        bool operator!=(const LinkedList<T>& list) const;


        void printNodes();

        template<typename _T> friend std::ostream& operator<<(std::ostream& out, const LinkedList<_T>& list);

};

typedef LinkedList<char> List1c;
typedef LinkedList<int> List1i;
typedef LinkedList<unsigned int> List1u;
typedef LinkedList<float> List1f;
typedef LinkedList<double> List1;

typedef LinkedList<List1c> List2c;
typedef LinkedList<List1i> List2i;
typedef LinkedList<List1u> List2u;
typedef LinkedList<List1f> List2f;
typedef LinkedList<List1> List2;

typedef LinkedList<List2c> List3c;
typedef LinkedList<List2i> List3i;
typedef LinkedList<List2u> List3u;
typedef LinkedList<List2f> List3f;
typedef LinkedList<List2> List3;

typedef LinkedList<List3c> List4c;
typedef LinkedList<List3i> List4i;
typedef LinkedList<List3u> List4u;
typedef LinkedList<List3f> List4f;
typedef LinkedList<List3> List4;
