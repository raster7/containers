#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include "../common_joints.h"

namespace s21 {
template <typename T>
class vector {
 public:
  // Vector Member type
  using value_type = T;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;

  // Vector Member functions
  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();
  vector &operator=(const vector &&v);

  // Vector Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  value_type *data();

  // Vector Iterators
  iterator begin();
  iterator end();

  // Vector Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

 private:
  value_type *m_data;
  size_type m_size;
  size_type m_capacity{};
};
}  // namespace s21

#include "s21_vector.tpp"

#endif  // S21_VECTOR_H
