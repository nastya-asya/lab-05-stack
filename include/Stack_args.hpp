// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#ifndef INCLUDE_STACK_STACK_ARGS_HPP
#define INCLUDE_STACK_STACK_ARGS_HPP
#include "NonCopiedStack.hpp"

template <typename T>
class Stack_args : public NonCopStack<T> {
 public:
  template <typename... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  const T& head() const;
  T pop();
};
template <typename T>
template <typename... Args>
void Stack_args<T>::push_emplace(Args&&... value) {
  if ((std::is_copy_constructible<T>::value) ||
      (std::is_copy_assignable<T>::value)) {
    throw std::exception();
  }
  auto* elem = new Element<T>{{std::forward<Args>(value)...}, NonCopStack<T>::Head};
  NonCopStack<T>::Head = elem;
}
template <typename T>
void Stack_args<T>::push(T&& value) {
  if ((std::is_copy_constructible<T>::value) ||
      (std::is_copy_constructible<T>::value)) {
    throw std::exception();
  }
  auto* elem = new Element<T>{std::forward<T>(value), NonCopStack<T>::Head};
  NonCopStack<T>::Head = elem;
}
template <typename T>
T Stack_args<T>::pop() {
  if (NonCopStack<T>::Head == nullptr) {
    throw std::exception();
  }
  auto * temp = NonCopStack<T>::Head;
  T val = std::move(NonCopStack<T>::Head->val);
  NonCopStack<T>::Head = NonCopStack<T>::Head->prev;
  delete temp;
  return val;
}
template <typename T>
const T& Stack_args<T>::head() const {
  if (NonCopStack<T>::Head == nullptr) {
    throw std::exception();
  }
  return NonCopStack<T>::Head->val;
}
#endif  // INCLUDE_STACK_STACK_ARGS_HPP
