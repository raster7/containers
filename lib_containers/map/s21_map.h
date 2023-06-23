#include <iostream>
#include <vector>
#include "../common_joints.h"
#include <utility>
using namespace std;

template <typename Key, typename T>
class node_pair {
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;

    public:
        value_type pair;
        node_pair* left;
        node_pair* right;
        node_pair(value_type pair, node_pair* left, node_pair* right) : pair(pair), left(left), right(right) {}
};

template <typename Key, typename T>
class map {
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;

    public:
        template <typename K1, typename T1>
        class MapIterator {
            using key_type = K1;
            using mapped_type = T1;
            using value_type = std::pair<const key_type, mapped_type>;
            using reference = value_type &;
            using const_reference = const value_type &;

            public:
                node_pair<key_type, mapped_type>* current;
                map<key_type, mapped_type>* ptr_map;

                MapIterator() {}
                MapIterator(node_pair<key_type, mapped_type>* current, map<key_type, mapped_type>* ptr_map) : current(current), ptr_map(ptr_map) {}
                value_type operator*() {
                    return current->pair;
                }
                MapIterator operator++() {
                    node_pair<key_type, mapped_type>* ans = current;
                    node_pair<key_type, mapped_type>* cur = ptr_map->get_root();
                    while (cur != nullptr) {
                        if (cur->pair.first > current->pair.first) {
                            ans = cur;
                            cur = cur->left;
                        } else {
                            cur = cur->right;
                        }
                    }
                    current = ans;
                    return *this;
                }
                MapIterator operator--() {
                    node_pair<key_type, mapped_type>* ans = current;
                    node_pair<key_type, mapped_type>* cur = ptr_map->get_root();
                    if (current == nullptr) {
                        while (cur->right != nullptr)
                            cur = cur->right;
                        current = cur;
                    } else {
                        while (cur != nullptr) {
                            if (cur->pair.first < current->pair.first) {
                                ans = cur;
                                cur = cur->right;
                            } else {
                                cur = cur->left;
                            }
                        }
                        current = ans;
                    }
                    return *this;
                }
                bool operator==(MapIterator<key_type, mapped_type> comparable_iter) {
                    if (current->pair.first == comparable_iter.current->pair.first) return true;
                    return false;
                }
                bool operator!=(MapIterator<key_type, mapped_type> comparable_iter) {
                    if (current->pair.first != comparable_iter.current->pair.first) return true;
                    return false;
                }
        };

        template <typename K2, typename T2>
        class MapConstIterator {
            using key_type = K2;
            using mapped_type = T2;
            using value_type = std::pair<const key_type, mapped_type>;
            using reference = value_type &;
            using const_reference = const value_type &;

            public:
                const node_pair<key_type, mapped_type>* current;
                map<key_type, mapped_type>* ptr_map;

                MapConstIterator() {}
                MapConstIterator(node_pair<key_type, mapped_type>* current, map<key_type, mapped_type>* ptr_map) : current(current), ptr_map(ptr_map) {}
                value_type operator*() {
                    return current->pair;
                }
                MapConstIterator operator++() {
                    node_pair<key_type, mapped_type>* ans = current;
                    node_pair<key_type, mapped_type>* cur = ptr_map->get_root();
                    while (cur != nullptr) {
                        if (cur->pair.first > current->pair.first) {
                            ans = cur;
                            cur = cur->left;
                        } else {
                            cur = cur->right;
                        }
                    }
                    current = ans;
                    return *this;
                }
                MapConstIterator operator--() {
                    node_pair<key_type, mapped_type>* ans = current;
                    node_pair<key_type, mapped_type>* cur = ptr_map->get_root();
                    while (cur != nullptr) {
                        if (cur->pair.first < current->pair.first) {
                            ans = cur;
                            cur = cur->right;
                        } else {
                            cur = cur->left;
                        }
                    }
                    current = ans;
                    return *this;
                }
                bool operator==(MapConstIterator<key_type, mapped_type> comparable_iter) {
                    if (current->pair.first == comparable_iter.current->pair.first) return true;
                    return false;
                }
                bool operator!=(MapConstIterator<key_type, mapped_type> comparable_iter) {
                    if (current->pair.first != comparable_iter.current->pair.first) return true;
                    return false;
                }
        };

        using iterator = MapIterator<key_type, mapped_type>;
        using const_iterator = MapConstIterator<key_type, mapped_type>;

        map();
        map(std::initializer_list<value_type> const &items);
        map(const map &m);
        map(map &&m);
        ~map();
        map& operator=(map &&m);

        mapped_type& at(const key_type& key);
        mapped_type& operator[](const key_type& key);

        iterator begin();
        iterator end();

        const_iterator const_begin();
        const_iterator const_end();

        bool empty();
        size_type size();
        size_type max_size();

        void clear();
        std::pair<iterator, bool> insert(const_reference value);
        std::pair<iterator, bool> insert(const Key& key, const T& obj);
        std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
        void erase(iterator pos);
        void swap(map& other);
        void merge(map& other);
        bool contains(const key_type& key);

        void print_map(node_pair<key_type, mapped_type>* current);
        void copy_map(node_pair<key_type, mapped_type>* current_from, node_pair<key_type, mapped_type>* current_to);
        void clear_recursive(node_pair<key_type, mapped_type>* current);
        node_pair<key_type, mapped_type>* get_root();
        void from_tree_to_array(std::vector<node_pair<key_type, mapped_type>>& vec, node_pair<key_type, mapped_type>* current, node_pair<key_type, mapped_type>* erasable_element);
        void balanced_tree_recursive(std::vector<node_pair<key_type, mapped_type>> vec);
        void balanced_tree();

    private:
        node_pair<key_type, mapped_type>* root;
        size_type size_;
};

#include "s21_map.tpp"