#pragma once
template<typename T> struct Node
{
    T data;
    Node<T>* next;

    Node();
    Node(const T& data);
};
