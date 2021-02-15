// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#ifndef INCLUDE_STACK_NONCOPIEDSTACK_HPP
#define INCLUDE_STACK_NONCOPIEDSTACK_HPP
#include <algorithm>
#include <type_traits>
#include <utility>

template <typename T>

struct Element {
  T val;
  Element<T>* prev;
};
template <typename T>
class NonCopStack {
 public:
  NonCopStack() = default;
  NonCopStack(const NonCopStack&) = delete;
  NonCopStack(NonCopStack&&) = default;
  ~NonCopStack();

  auto operator=(const NonCopStack<T>&) -> NonCopStack<T>& = delete;
  auto operator=(NonCopStack<T>&&) noexcept -> NonCopStack<T>& = default;

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  size_t Size() const;

 protected:
  Element<T>* Head = nullptr;
};

template <typename T>
void NonCopStack<T>::push(T&& value) {
  Element<T>* temp = Head;
  Head = new Element<T>{std::forward<T>(value), temp};
}

template <typename T>
void NonCopStack<T>::push(const T& value) {
  Element<T>* temp = Head;
  Head = new Element<T>{value, temp};
}

template <typename T>
void NonCopStack<T>::pop() {
  if (Head == nullptr) {
    throw std::exception();
  }
  Element<T>* temp = Head;
  Head = Head->prev;
  delete temp;
}

template <typename T>
const T& NonCopStack<T>::head() const {
  if (Head == nullptr) {
    throw std::exception();
  }
  return Head->val;
}

template <typename T>
size_t NonCopStack<T>::Size() const {
  size_t _size = 0;
  Element<T>* temp = Head;
  while (temp != nullptr) {
    ++_size;
    temp = temp->prev;
  }
  return _size;
}

template <typename T>
NonCopStack<T>::~NonCopStack() {
  while (Head != nullptr) {
    pop();
  }
}

#endif  // INCLUDE_STACK_NONCOPIEDSTACK_HPP