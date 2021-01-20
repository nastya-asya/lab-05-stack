// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#pragma once

#include <utility>
#include <exception>
template <class T>
struct element {
    T data;
    element *next;
};
template<typename T>
class stack {
protected:
    element<T> *stackHead = nullptr;
public:
    stack() = default;

    virtual void push(T &&value) {
        auto* elem = new element<T>{std::forward<T>(value), stackHead};
        stackHead = elem;
    }

    const T &head() const {
        if (stackHead == nullptr) {
            throw std::exception();
        } else {
            return stackHead->data;
        }
    }

    virtual ~stack(){
        while (stackHead){
            auto *current = stackHead;
            stackHead = stackHead->next;
            delete current;
        }
    }
};
