#ifndef S21_LIST_TPP
#define S21_LIST_TPP

using namespace s21;

template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), len(0) {}

template <typename T>
list<T>::list(size_type n) : head{nullptr}, tail{nullptr}, len{0} {
  for (size_type i = 0; i < n; ++i) {
    this->push_back(0);
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : head{nullptr}, tail{nullptr}, len{0} {
  for (auto item : items) {
    this->push_back(item);
  }
}

template <typename T>
list<T>::list(list<T> &&other)
    : head{other.head}, tail{other.tail}, len{other.len} {
  other.head = nullptr;
  other.tail = nullptr;
  other.len = 0;
}

template <typename T>
list<T>::~list() {
  this->clear();
}

template <typename T>
list<T> &list<T>::operator=(list<value_type> &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  clear();
  head = other.head;
  tail = other.tail;
  len = other.len;

  other.head = nullptr;
  other.tail = nullptr;
  other.len = 0;
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  return head->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  return tail->data;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator{head};
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator{nullptr};
}

template <typename T>
bool list<T>::empty() {
  return len == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return len;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *new_node = new Node{value, pos.node->prev, pos.node};
  if (pos.node->prev) {
    pos.node->prev->next = new_node;
  } else {
    head = new_node;
  }
  pos.node->prev = new_node;
  ++len;
  return iterator{new_node};
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos.node->prev) {
    pos.node->prev->next = pos.node->next;
  } else {
    head = pos.node->next;
  }
  if (pos.node->next) {
    pos.node->next->prev = pos.node->prev;
  } else {
    tail = pos.node->prev;
  }
  delete pos.node;
  --len;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node *new_node = new Node{value, tail, nullptr};
  if (tail) {
    tail->next = new_node;
  } else {
    head = new_node;
  }
  tail = new_node;
  ++len;
}

template <typename T>
void list<T>::pop_back() {
  Node *old_tail = tail;
  tail = tail->prev;
  if (tail) {
    tail->next = nullptr;
  } else {
    head = nullptr;
  }
  delete old_tail;
  --len;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node *new_node = new Node{value, nullptr, head};
  if (head) {
    head->prev = new_node;
  } else {
    tail = new_node;
  }
  head = new_node;
  ++len;
}

template <typename T>
void list<T>::pop_front() {
  Node *old_head = head;
  head = head->next;
  if (head) {
    head->prev = nullptr;
  } else {
    tail = nullptr;
  }
  delete old_head;
  --len;
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(len, other.len);
}

template <typename T>
void list<T>::merge(list &other) {
  if (this == &other) {
    return;
  }
  list tmp;
  auto it1 = begin();
  auto it2 = other.begin();
  while (it1 != end() && it2 != other.end()) {
    if (*it1 < *it2) {
      tmp.push_back(*it1);
      ++it1;
    } else {
      tmp.push_back(*it2);
      ++it2;
    }
  }
  while (it1 != end()) {
    tmp.push_back(*it1);
    ++it1;
  }
  while (it2 != other.end()) {
    tmp.push_back(*it2);
    ++it2;
  }
  swap(tmp);
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (this == &other || other.empty()) {
    return;
  }
  Node *first = other.head;
  Node *last = other.tail;
  other.head = nullptr;
  other.tail = nullptr;
  other.len = 0;
  first->prev = pos.node->prev;
  if (pos.node->prev) {
    pos.node->prev->next = first;
  } else {
    head = first;
  }
  last->next = pos.node;
  pos.node->prev = last;
  len += other.len;
}

template <typename T>
void list<T>::reverse() {
  Node *current = head;
  while (current) {
    std::swap(current->prev, current->next);
    current = current->prev;
  }
  std::swap(head, tail);
}

template <typename T>
void list<T>::unique() {
  if (empty()) {
    return;
  }
  Node *current = head;
  while (current->next) {
    if (current->data == current->next->data) {
      Node *tmp = current->next;
      current->next = tmp->next;
      if (tmp->next) {
        tmp->next->prev = current;
      } else {
        tail = current;
      }
      delete tmp;
      --len;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (len < 2) {
    return;
  }
  list left;
  list right;
  auto it = begin();
  for (size_type i = 0; i < len / 2; ++i) {
    left.push_back(*it);
    ++it;
  }
  while (it != end()) {
    right.push_back(*it);
    ++it;
  }
  left.sort();
  right.sort();
  merge(left);
  merge(right);
}

#endif  // S21_LIST_TPP