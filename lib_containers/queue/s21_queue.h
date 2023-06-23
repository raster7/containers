#include <iostream>
#include "../common_joints.h"

namespace s21 {
template <typename T>
class queue {
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    public:
        queue();
        queue(std::initializer_list<value_type> const &items);
        queue(const queue &q);
        queue(queue &&q);
        ~queue();
        queue& operator=(queue &&q) noexcept;

        const_reference & front();
        const_reference & back();
        bool empty();
        size_type size();
        void push(value_type data);
        void pop();
        void swap(queue& other);
        
        class iterator {
            friend class queue;
            private:
                node<value_type>* current;
                queue<value_type>* queue_ptr;
            public:
                iterator();
                iterator(node<value_type>* current);
                iterator(node<value_type>* current, queue<value_type>* queue_ptr);
                value_type operator*();
                iterator operator++();
                iterator operator--();
                bool operator==(iterator comparable);
                bool operator!=(iterator comparable);
        };

        iterator begin();
        iterator end();
        void print_queue();
        value_type operator [] (int index);

    private:
        node<value_type>* head;
        node<value_type>* tail;
        size_type size_;
};

#include "s21_queue.tpp"

}