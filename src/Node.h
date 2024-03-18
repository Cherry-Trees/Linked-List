#pragma once
template<typename T> struct Node
{
    T element;
    Node<T>* next;

    Node();
    Node(const T& element);
    Node(const T& element, Node<T>* next);
};