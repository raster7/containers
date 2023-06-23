using namespace s21;

template <typename value_type>
s21::stack<value_type>::stack() {
  size_ = 0;
  head = nullptr;
}

template <typename value_type>
s21::stack<value_type>::~stack() {
  while (head != nullptr) {
    node<value_type>* tmp = head;
    head = head->pNext;
    delete tmp;
  }
  head = nullptr;
  size_ = 0;
}

template <typename value_type>
s21::stack<value_type>::stack(const stack& s) {
  head = nullptr;
  size_ = 0;
  node<value_type>* current = s.head;
  while (current->pNext != nullptr) {
    current = current->pNext;
  }
  head = new node<value_type>(nullptr, nullptr, current->data);
  while (current != nullptr) {
    push(current->data);
    current = current->pPrev;
  }
}

template <typename value_type>
s21::stack<value_type>::stack(stack&& s) {
  head = s.head;
  size_ = s.size_;
  s.head = nullptr;
  s.size_ = 0;
}

template <typename value_type>
s21::stack<value_type>::stack(std::initializer_list<value_type> const& items) {
  head = nullptr;
  size_ = 0;
  for (auto it = items.end() - 1; it >= items.begin(); --it) {
    push(*it);
  }
}

template <typename value_type>
void s21::stack<value_type>::clear() {
  while (head != nullptr) {
    pop();
  }
  head = nullptr;
  size_ = 0;
}

template <typename value_type>
void s21::stack<value_type>::push(const_reference data) {
  head = new node<value_type>(head, nullptr, data);
  if (head->pNext != nullptr) head->pNext->pPrev = head;
  size_++;
}

template <typename value_type>
void s21::stack<value_type>::pop() {
  node<value_type>* tmp = head;
  head = head->pNext;
  delete tmp;
  size_--;
}

template <typename value_type>
bool s21::stack<value_type>::empty() {
  if (size_ == 0) return true;
  return false;
}

template <typename value_type>
typename s21::stack<value_type>::const_reference s21::stack<value_type>::top() {
  return head->data;
}

template <typename value_type>
s21::stack<value_type>& s21::stack<value_type>::operator=(stack&& s) noexcept {
  if (this != &s) {
    head = s.head;
    size_ = s.size_;
    s.head = nullptr;
    s.size_ = 0;
  }
  return *this;
}

template <typename value_type>
typename s21::stack<value_type>::size_type s21::stack<value_type>::size() {
  return size_;
}

template <typename value_type>
typename s21::stack<value_type>::value_type s21::stack<value_type>::get_element(
    int i) {
  if (i < (int)size_ && i >= 0) {
    int counter = 0;
    node<value_type>* current = head;
    while (counter < i) {
      current = current->pNext;
      counter++;
    }
    return current->data;
  } else {
    throw "Error!";
  }
}

template <typename value_type>
void s21::stack<value_type>::swap(stack& other) {
  std::swap(head, other.head);
  std::swap(size_, other.size_);
}

template <typename value_type>
typename s21::stack<value_type>::iterator s21::stack<value_type>::begin() {
  iterator iter(head, this);
  return iter;
}

template <typename value_type>
typename s21::stack<value_type>::iterator s21::stack<value_type>::end() {
  iterator iter(nullptr, this);
  return iter;
}

template <typename value_type>
s21::stack<value_type>::iterator::iterator() {
  current = nullptr;
  stack_ptr = nullptr;
}

template <typename value_type>
s21::stack<value_type>::iterator::iterator(node<value_type>* current) {
  this->current = current;
}

template <typename value_type>
s21::stack<value_type>::iterator::iterator(node<value_type>* current,
                                           stack<value_type>* stack_ptr) {
  this->current = current;
  this->stack_ptr = stack_ptr;
}

template <typename value_type>
typename s21::stack<value_type>::value_type
s21::stack<value_type>::iterator::operator*() {
  return current->data;
}

template <typename value_type>
typename s21::stack<value_type>::iterator
s21::stack<value_type>::iterator::operator++() {
  if (current != nullptr) {
    current = current->pNext;
    return *this;
  } else {
    throw "Error!";
  }
}

template <typename value_type>
typename s21::stack<value_type>::iterator
s21::stack<value_type>::iterator::operator--() {
  if (current != stack_ptr->head && current != nullptr) {
    current = current->pPrev;
    return *this;
  } else {
    throw "Error!";
  }
}

template <typename value_type>
bool s21::stack<value_type>::iterator::operator==(iterator comparable) {
  return current == comparable.current;
}

template <typename value_type>
bool s21::stack<value_type>::iterator::operator!=(iterator comparable) {
  return current != comparable.current;
}

template <typename value_type>
typename s21::stack<value_type>::value_type s21::stack<value_type>::operator[](
    int index) {
  if (index < (int)size_ && index >= 0) {
    node<value_type>* current = head;
    int counter = 0;
    while (current != nullptr) {
      if (counter == index) return current->data;
      current = current->pNext;
      counter++;
    }
  }
  throw CustomException("Error!");
}

template <typename value_type>
void s21::stack<value_type>::print_stack() {
  node<value_type>* current = head;
  int counter = 0;
  while (counter < (int)size_) {
    std::cout << current->data << " ";
    current = current->pNext;
    counter++;
  }
  std::cout << std::endl;
}

template <typename value_type>
bool s21::stack<value_type>::operator==(stack& s) {
  bool flag = true;
  if (size() == s.size()) {
    for (size_type i = 0; i < size(); i++) {
      if (get_element(i) != s[i]) {
        flag = false;
        break;
      }
    }
  } else {
    flag = false;
  }
  return flag;
}