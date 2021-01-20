// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#pragma once

#include "ParentStack.hpp"

template<typename T>
class usualStack : public stack<T> {
public:
    void push(const T &value) {
        auto* elem = new element<T>{value, stack<T>::stackHead};
        stack<T>::stackHead = elem;
    }

    void push(T &&arg) override {
        stack<T>::push(std::forward<T>(arg));
    }

    void pop() {
        if (stack<T>::stackHead == nullptr) {
            throw std::exception();
        } else {
            auto *upper = stack<T>::stackHead;
            stack<T>::stackHead = stack<T>::stackHead->next;
            delete upper;
        }
    }
};
