#include <iostream>

template<typename T> class LinkedList
{       

    private:

        struct Node
        {
            T element;
            Node* next;
        };

        // Double Node pointer points to the first Node pointer in this list.
        Node** _begin; 

        // Double Node pointer points to the last Node pointer in this list.
        Node** _end;

        // Number of nodes in this list.
        int _size;

        
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


        T& beginElement() const;

        Node* beginNode() const;

        // O(1)
        T& endElement() const;

        // O(1)
        Node* endNode() const;

        // O(n)
        T& operator[](const int index);

        int size() const;

        // Add a Node to the end of the list.
        // O(1) Constant time due to the _end double Node pointer.
        LinkedList<T>& push(const T val);

        // Add a list to this list.
        // This does NOT create a copy, so modifying the original list modifies this one too.
        // Creates a circular list if the same list is added.
        // O(1)
        LinkedList<T>& push(const LinkedList<T>& list);

        // Add a COPY of a list to this list.
        // O(n)
        LinkedList<T>& push_copy(const LinkedList<T>& list);


        // Add a COPY of a list to this list.
        // O(n)
        LinkedList<T>& operator+=(const LinkedList<T>& list);

        LinkedList<T>& operator+=(const T& val);

        LinkedList<T>& operator*=(const int scalar);


        template<typename _T> friend std::ostream& operator<<(std::ostream& out, const LinkedList<_T>& ll);

};
