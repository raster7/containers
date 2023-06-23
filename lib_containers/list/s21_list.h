#ifndef S21_LIST_H
#define S21_LIST_H

#include "../common_joints.h"

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;

  struct Node {
    value_type data;
    Node *prev;
    Node *next;

    explicit Node(const_reference d = value_type{}, Node *p = nullptr,
                  Node *n = nullptr)
        : data{d}, prev{p}, next{n} {}
  };

  class Iterator {
   public:
    explicit Iterator(Node *n) : node{n} {}
    Iterator(const Iterator &) = default;
    Iterator &operator=(const Iterator &) = default;

    Iterator &operator++() {
      node = node->next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp{node};
      ++(*this);
      return tmp;
    }

    Iterator &operator--() {
      node = node->prev;
      return *this;
    }

    Iterator operator--(int) {
      Iterator tmp{node};
      --(*this);
      return tmp;
    }

    reference operator*() const { return node->data; }
    pointer operator->() const { return &node->data; }

    bool operator==(const Iterator &rhs) const { return node == rhs.node; }
    bool operator!=(const Iterator &rhs) const { return *this != rhs; }

   private:
    Node *node;
  };

  class ConstIterator {
   public:
    explicit ConstIterator(Node *n) : node{n} {}
    ConstIterator(const ConstIterator &) = default;
    ConstIterator &operator=(const ConstIterator &) = default;

    ConstIterator &operator++() {
      node = node->next;
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator tmp{node};
      ++(*this);
      return tmp;
    }

    ConstIterator &operator--() {
      node = node->prev;
      return *this;
    }

    ConstIterator operator--(int) {
      ConstIterator tmp{node};
      --(*this);
      return tmp;
    }

    reference operator*() const { return node->data; }
    pointer operator->() const { return &node->data; }

    bool operator==(const ConstIterator &rhs) const { return node == rhs.node; }
    bool operator!=(const ConstIterator &rhs) const { return *this != rhs; }

   private:
    Node *node;
  };

  using size_type = size_t;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(list<value_type> &&other);
  ~list();
  list &operator=(list<value_type> &&other) noexcept;

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();
  void clear();

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

 private:
  Node *head;
  Node *tail;
  size_type len;
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_LIST_H