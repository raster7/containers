template<typename key_type, typename mapped_type>
map<key_type, mapped_type>::map() : root(nullptr), size_(0) {}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(std::initializer_list<value_type> const &items) {
    root = nullptr;
    size_ = 0;
    for (auto iter = items.begin(); iter != items.end(); ++iter) {
        insert(*iter);
    }
}

template<typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map &m) {
    size_ = m.size_;
    root = m.root;
    copy_map(m.root, root);
}


template<typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map &&m) {
    size_ = m.size_;
    root = m.root;
    m.size_ = 0;
    m.root = nullptr;
}

template<typename key_type, typename mapped_type>
map<key_type, mapped_type>::~map() {
    root = nullptr;
    size_ = 0;
}

template<typename key_type, typename mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(map &&m) {
    size_ = m.size_;
    root = m.root;
    m.size_ = 0;
    m.root = nullptr;
}

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::mapped_type& map<key_type, mapped_type>::at(const key_type& key) {
    node_pair<key_type, mapped_type>* current = root;
    while (current->pair.first != key) {
        if (key < current->pair.first) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current->pair.second;
}

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::mapped_type& map<key_type, mapped_type>::operator[](const key_type& key) {
    return at(key);
}

template<typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::empty() {
    if (!root) return true;
    return false;
}

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type map<key_type, mapped_type>::size() {
    return size_;
}

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type map<key_type, mapped_type>::max_size() {
    return std::numeric_limits<size_type>::max();
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
    clear_recursive(root);
    root = nullptr;
    size_ = 0;
}

template<typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool> map<key_type, mapped_type>::insert(const_reference value) {
    node_pair<key_type, mapped_type>* current = root;
    while (current != nullptr) {
        if (value.first < current->pair.first) {
            if (!current->left) {
                current->left = new node_pair<key_type, mapped_type>(value, nullptr, nullptr);
                size_++;
                iterator iter(current->left, this);
                return std::make_pair(iter, true);
            }
            current = current->left;
        } else if (value.first > current->pair.first) {
            if (!current->right) {
                current->right = new node_pair<key_type, mapped_type>(value, nullptr, nullptr);
                size_++;
                iterator iter(current->right, this);
                return std::make_pair(iter, true);
            }
            current = current->right;
        } else {
            iterator iter(current, this);
            return std::make_pair(iter, false);
        }
    }
    root = new node_pair<key_type, mapped_type>(value, nullptr, nullptr);
    size_++;
    iterator iter(root, this);
    return std::make_pair(iter, true);
}

template<typename key_type, typename mapped_type> 
std::pair<typename map<key_type, mapped_type>::iterator, bool> map<key_type, mapped_type>::insert(const key_type& key, const mapped_type& obj) {
    node_pair<key_type, mapped_type>* current = root;
    while (current != nullptr) {
        if (current->pair.first > key) {
            if (!current->left) {
                current->left = new node_pair<key_type, mapped_type>(std::make_pair(key, obj), nullptr, nullptr);
                size_++;
                iterator iter(current->left, this);
                return std::make_pair(iter, true);
            }
            current = current->left;
        } else if (current->pair.first < key) {
            if (!current->right) {
                current->right = new node_pair<key_type, mapped_type>(std::make_pair(key, obj), nullptr, nullptr);
                size_++;
                iterator iter(current->right, this);
                return std::make_pair(iter, true);
            }
            current = current->right;
        } else {
            iterator iter(current, this);
            return std::make_pair(iter, false);
        }
    }
    root = new node_pair<key_type, mapped_type>(std::make_pair(key, obj), nullptr, nullptr);
    size_++;
    iterator iter(root, this);
    return std::make_pair(iter, true);
}

template<typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool> map<key_type, mapped_type>::insert_or_assign(const key_type& key, const mapped_type& obj) {
    node_pair<key_type, mapped_type>* current = root;
    while (current != nullptr) {
        if (current->pair.first > key) {
            if (!current->left) {
                current->left = new node_pair<key_type, mapped_type>(std::make_pair(key, obj), nullptr, nullptr);
                size_++;
                iterator iter(current->left, this);
                return std::make_pair(iter, true);
            }
            current = current->left;
        } else if (current->pair.first < key) {
            if (!current->left) {
                current->right = new node_pair<key_type, mapped_type>(std::make_pair(key, obj), nullptr, nullptr);
                size_++;
                iterator iter(current->right, this);
                return std::make_pair(iter, true);
            }
            current = current->right;
        } else {
            current->pair.second = obj;
            iterator iter(current, this);
            return std::make_pair(iter, false);
        }
    }
    root = new node_pair<key_type, mapped_type>(std::make_pair(key, obj), nullptr, nullptr);
    size_++;
    iterator iter(root, this);
    return std::make_pair(iter, true);
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(typename map<key_type, mapped_type>::iterator pos) {
    std::vector<node_pair<key_type, mapped_type>> vec;
    from_tree_to_array(vec, root, pos.current);
    clear();
    balanced_tree_recursive(vec);
    size_--;
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map& other) {
    std::swap(root, other.root);
    std::swap(size_, other.size_);
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map& other) {
    std::vector<node_pair<key_type, mapped_type>> vec;
    from_tree_to_array(vec, get_root(), nullptr);
    from_tree_to_array(vec, other.get_root(), nullptr);
    clear();
    balanced_tree_recursive(vec);
    vec.clear();
    from_tree_to_array(vec, get_root(), nullptr);
    clear();
    balanced_tree_recursive(vec);
}

template<typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type& key) {
    node_pair<key_type, mapped_type>* current = root;
    bool res = false;
    while (current != nullptr) {
        if (current->pair.first > key) {
            current = current->left;
        } else if (current->pair.first < key) {
            current = current->right;
        } else {
            res = true;
            break;
        }
    }
    return res;
}

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator map<key_type, mapped_type>::begin() {
    iterator iter(root, this);
    return iter;
}

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator map<key_type, mapped_type>::end() {
    iterator iter(nullptr, this);
    return iter;
}

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::const_iterator map<key_type, mapped_type>::const_begin() {
    const_iterator iter(root, this);
    return iter;
}

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::const_iterator map<key_type, mapped_type>::const_end() {
    const_iterator iter(nullptr, this);
    return iter;
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::print_map(node_pair<key_type, mapped_type>* current) {
    if (current->left != nullptr)
        print_map(current->left);
    std::cout << current->pair.second << " ";
    if (current->right != nullptr)
        print_map(current->right);
}

template<typename key_type, typename mapped_type>
node_pair<key_type, mapped_type>* map<key_type, mapped_type>::get_root() {
    return root;
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::copy_map(node_pair<key_type, mapped_type>* current_from, node_pair<key_type, mapped_type>* current_to) {
    if (current_from->left != nullptr) {
        current_to->left = current_from->left;
        copy_map(current_from->left, current_to->left);
    }
    current_to = new node_pair<key_type, mapped_type>(current_from->pair, current_from->left, current_from->right);
    if (current_from->right != nullptr) {
        current_to->right = current_from->right;
        copy_map(current_from->right, current_to->right);
    }
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear_recursive(node_pair<key_type, mapped_type>* current) {
    if (current->left != nullptr) {
        clear_recursive(current->left);
    }
    if (current->right != nullptr) {
        clear_recursive(current->right);
    }
    delete current;
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::from_tree_to_array(std::vector<node_pair<key_type, mapped_type>>& vec, node_pair<key_type, mapped_type>* current, node_pair<key_type, mapped_type>* erasable_element) {
    if (current->left != nullptr) {
        from_tree_to_array(vec, current->left, erasable_element);
    }
    if (erasable_element != nullptr) {
        if (current->pair.first != erasable_element->pair.first) {
            vec.push_back(*current);
        }
    } else {
        vec.push_back(*current);
    }
    if (current->right != nullptr) {
        from_tree_to_array(vec, current->right, erasable_element);
    }
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::balanced_tree_recursive(std::vector<node_pair<key_type, mapped_type>> vec) {
    if (vec.size() == 1) {
        insert(vec[0].pair);
    } else if (vec.size() == 2) {
        insert(vec[0].pair);
        insert(vec[1].pair);
    } else {
        int middle = (vec.size()-1)/2;
        insert(vec[middle].pair);
        std::vector<node_pair<key_type, mapped_type>> vec1;
        for (int i = 0; i < middle; i++) {
            vec1.push_back(vec[i]);
        }
        balanced_tree_recursive(vec1);
        std::vector<node_pair<key_type, mapped_type>> vec2;
        for (int i = middle + 1; i < vec.size(); i++) {
            vec2.push_back(vec[i]);
        }
        balanced_tree_recursive(vec2);
    }
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::balanced_tree() {
    std::vector<node_pair<key_type, mapped_type>> vec;
    from_tree_to_array(vec, get_root(), nullptr);
    clear();
    balanced_tree_recursive(vec);
}