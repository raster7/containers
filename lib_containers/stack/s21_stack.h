#include <iostream>

#include "../common_joints.h"

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  stack();
  stack(const stack& s);
  stack(stack&& s);
  stack(std::initializer_list<value_type> const& items);
  ~stack();
  const_reference top();
  void push(const_reference data);
  void pop();
  void clear();
  bool empty();
  stack& operator=(stack&& s) noexcept;
  size_type size();
  void swap(stack& other);
  class iterator {
    friend class stack;

   public:
    iterator();
    iterator(node<value_type>* current);
    value_type operator*();
    iterator operator++();
    iterator operator--();
    bool operator==(iterator comparable);
    bool operator!=(iterator comparable);

   private:
    explicit iterator(node<value_type>* current, stack<value_type>* stack_ptr);
    node<value_type>* current;
    stack<value_type>* stack_ptr;
  };

  iterator begin();
  iterator end();
  value_type operator[](int i);
  void print_stack();
  bool operator==(stack& s);

 private:
  node<value_type>* head;
  size_type size_;

  value_type get_element(int i);
};

#include "s21_stack.tpp"

}  // namespace s21