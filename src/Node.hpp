#pragma once
#include "Node.h"

template<typename T> Node<T>::Node() : element(), next(nullptr) {}

template<typename T> Node<T>::Node(const T& element) : element(element) {}

template<typename T> Node<T>::Node(const T& element, Node<T>* next) : element(element), next(next) {}