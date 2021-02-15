// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#include <gtest/gtest.h>

#include "NonCopiedStack.hpp"
#include "Stack_args.hpp"
class NonCopEx {
  double data;
  double dada;

 public:
  NonCopEx() = default;
  NonCopEx(const NonCopEx&) = delete;
  NonCopEx(NonCopEx&&) = default;
  NonCopEx(double _data, double _dada) {
    data = _data;
    dada = _dada;
  }
  ~NonCopEx() = default;
  auto operator=(NonCopEx&&) -> NonCopEx& = default;
  auto operator=(const NonCopEx&) -> NonCopEx& = delete;
  double getData() const { return this->data; }
};
TEST(Example, EmptyTest) { EXPECT_TRUE(true); }

TEST(NonCopiedStack, EmptyStack) {
  NonCopStack<int> stack;
  EXPECT_ANY_THROW(stack.head());
  EXPECT_ANY_THROW(stack.pop());
}
TEST(NonCopiedStack, PushValue) {
  NonCopStack<int> stack1;
  stack1.push(5);
  EXPECT_EQ(stack1.head(), 5);
  NonCopStack<std::string> stack2;
  std::string st{"It's too late"};
  stack2.push(std::move(st));
  EXPECT_EQ(stack2.head(), "It's too late");
  int a = 10;
  stack1.push(a);
  EXPECT_EQ(stack1.head(), a);
}
TEST(NonCopiedStack, PopValues) {
  NonCopStack<int> stack;
  stack.push(15);
  stack.push(20);
  int a = 25;
  int b = 30;
  stack.push(a);
  stack.push(b);
  stack.pop();
  EXPECT_EQ(stack.head(), 25);
  size_t size = stack.Size();
  for (size_t i = 0; i < size; ++i) {
    stack.pop();
  }
  EXPECT_ANY_THROW(stack.pop());
  EXPECT_ANY_THROW(stack.head());
}
TEST(NonCopiedStack, MoveExtensions) {
  EXPECT_TRUE(std::is_move_constructible<NonCopStack<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<NonCopStack<std::string>>::value);
  EXPECT_TRUE(std::is_move_assignable<NonCopStack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<NonCopStack<std::string>>::value);
}
TEST(NonCopiedStack, CopyExtensions) {
  EXPECT_FALSE(std::is_copy_assignable<NonCopStack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<NonCopStack<std::string>>::value);
  EXPECT_FALSE(std::is_copy_constructible<NonCopStack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<NonCopStack<std::string>>::value);
}
TEST(NonCopEx, CorrectObject) {
  EXPECT_TRUE(std::is_move_constructible<NonCopEx>::value);
  EXPECT_TRUE(std::is_move_assignable<NonCopEx>::value);
  EXPECT_FALSE(std::is_copy_constructible<NonCopEx>::value);
  EXPECT_FALSE(std::is_copy_assignable<NonCopEx>::value);
}
TEST(Stack_args, PushValues) {
  Stack_args<NonCopEx> arg_stack;
  arg_stack.push(NonCopEx(3.14, 294.2));
  EXPECT_EQ(arg_stack.head().getData(), 3.14);
  arg_stack.push_emplace(6.28, 24.2);
  EXPECT_EQ(arg_stack.head().getData(), 6.28);
  EXPECT_EQ(arg_stack.pop().getData(), 6.28);
  EXPECT_EQ(arg_stack.head().getData(), 3.14);
}
