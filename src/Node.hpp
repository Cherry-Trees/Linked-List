#pragma once
#include "Node.h"

template<typename T> Node<T>::Node() : data(), next(nullptr) {}
template<typename T> Node<T>::Node(const T& data) : data(data), next(nullptr) {}
