// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#pragma once

#include "ParentStack.hpp"

template<typename T>
class stackArgs : public stack<T> {
public:
    template<typename ... Args>
    void push_emplace(Args &&... value) {
        auto *temp = new element<T>{{std::forward<Args>(value)...}, stack<T>::stackHead};
        stack<T>::stackHead = temp;
    }

    T pop() {
        if (stack<T>::stackHead == nullptr) {
            throw std::exception();
        } else {
            auto *upper = stack<T>::stackHead;
            stack<T>::stackHead = stack<T>::stackHead->next;
            auto temp = std::move(upper->data);
            delete upper;
            return temp;
        }
    }
};
