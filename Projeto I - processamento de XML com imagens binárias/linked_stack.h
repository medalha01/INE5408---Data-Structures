//! Copyright [2022] <Tiago Oliveira da Luz>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    for (std::size_t i = 0; i < size_; i++) {
        pop();
    }
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    for (std::size_t i = 0; i < size_; i++) {
        pop();
    }
    size_ = 0;
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *element = new Node(data);
    element->next(top_);
    top_ = element;
    size_++;
}
template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node *aux = top_;
    top_ = top_->next();
    T data = aux->data();
    delete aux;
    size_--;
    return data;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    return top_->data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}


#endif
