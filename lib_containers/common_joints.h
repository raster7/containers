#ifndef COMMON_JOINTS_H
#define COMMON_JOINTS_H

#include <stdexcept>
#include <exception>
#include <algorithm>
#include <limits>
#include <initializer_list>

namespace s21 {
template <typename T>
class node {
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    public:
        node* pNext;
        node* pPrev;
        value_type data;

        node(node* pNext, node* pPrev, value_type data) {
            this->pNext = pNext;
            this->pPrev = pPrev;
            this->data = data;
        }
    };
}


class CustomException : public std::exception {
    // Custom exception class
private:
    char const* message_;

public:
    // Constructor simply copies the message given to it to a field of a class
    explicit CustomException(char const* msg) { message_ = msg; }
    // What is default exception function that returns an explanatory string
    char const* what() { return message_; }
};

#endif // COMMON_JOINTS_H
