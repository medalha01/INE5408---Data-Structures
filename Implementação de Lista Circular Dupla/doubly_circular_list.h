//! Copyright [2022] <Isac Martins>
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        Node():
            data_{}
        {}
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* position(std::size_t index) {
        if (index < 0 || index > size_) {
            throw std::out_of_range("Index inválido");
        }
        Node *p;
        if (index < size_/2) {
            p = head->next();
            for (std::size_t i = 0; i < index; i++) {
                p = p->next();
            }
        } else {
            p = head->prev();
            for (std::size_t i = size_-1; i > index; i--) {
                p = p->prev();
            }
        }
        return p;
    }

    Node* head;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    Node* p = new Node();
    head = p;
    head->next(head);
    head->prev(head);
    size_ = 0;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    Node* p = head->next();
    for (std::size_t i = 0; i < size_; i++) {
        p = p->next();
        delete p->prev();
    }
    delete head;
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *aux = new Node(data);
    if (!aux) {
        throw std::out_of_range("Falha na alocação de memória");
    }
    head->prev()->next(aux);
    aux->prev(head->prev());
    aux->next(head);
    head->prev(aux);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node *aux = new Node(data);
    if (!aux) {
        throw std::out_of_range("Falha na alocação de memória");
    }
    head->next()->prev(aux);
    aux->next(head->next());
    aux->prev(head);
    head->next(aux);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data,
                                               std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index invalido");
    }
    if (empty() || index == 0) {
        return push_front(data);
    }
    if (index == size_) {
        return push_back(data);
    }
    Node *p = position(index);
    Node *aux = new Node(data);
    if (!aux) {
        throw std::out_of_range("Falha na alocação de memória");
    }
    p->prev()->next(aux);
    aux->prev(p->prev());
    aux->next(p);
    p->prev(aux);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *p = head->next();
    for (std::size_t i = 0; i < size_; i++) {
        if (data < p->data()) {
            return insert(data, i);
        }
        p = p->next();
    }
    return push_back(data);
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index invalido");
    }
    if (size_ == 1) {
        return pop_front();
    }
    if (index == size_-1) {
        return pop_back();
    }
    Node* p = position(index);
    p->prev()->next(p->next());
    p->next()->prev(p->prev());
    T data = p->data();
    delete p;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    if (size_ == 1) {
        return pop_front();
    }
    Node* p = head->prev();
    p->prev()->next(head);
    head->prev(p->prev());
    T data = p->data();
    delete p;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node* p = head->next();
    p->next()->prev(head);
    head->next(p->next());
    T data = p->data();
    delete p;
    size_--;
    return data;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node* p = head->next();
    for (std::size_t i = 0; i < size_; i++) {
        if (data == p->data()) {
            return true;
        }
        p = p->next();
    }
    return false;
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index invalido");
    }
    return position(index)->data();
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    return position(index)->data();
}


template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node* p = head->next();
    for (std::size_t i = 0; i < size_; i++) {
        if (data == p->data()) {
            return i;
        }
        p = p->next();
    }
    return size_;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}

#endif