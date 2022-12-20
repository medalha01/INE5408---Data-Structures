//! Copyright [2022] <Isac Martins>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
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

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif


template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}
template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    Node* aux = head;
    for (std::size_t i =1; i < size_ +1; i++) {
        Node* temp = aux;
        aux = aux->next();
        delete temp;
    }
    delete aux;
    head = nullptr;
    size_ = 0;}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *element = new Node(data);
    Node *p = head;
    for (std::size_t i =0; i < size_-1; i++) {
        p = p->next();
    }
    p->next(element);
    size_++;
}
template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* P_Node = new Node(data);
    size_++;
    if (P_Node == nullptr) {
        throw std::out_of_range ("Falha na alocação de memória");}
    P_Node->next(head);
    head = P_Node;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    
    if (index > size_ || index < 0){
        throw std::out_of_range ("Index fora de range");}
    if (empty() || index == 0) {
        return push_front(data);  
    }
    Node* P_Node = new Node(data);
    Node* auxiliar = head;
    if (P_Node == nullptr) {
        throw std::out_of_range ("Falha na alocação de memória");}
    for (std::size_t i =0; i < index - 1; i++) {
        auxiliar = auxiliar->next();}
    P_Node->next(auxiliar->next());
    auxiliar->next(P_Node);
    size_++;};

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node* atual = head;
    std::size_t posicao = 0;
    while (posicao < size_ && atual->data() < data) {
        atual = atual->next();
        posicao++;
    }
    insert(data, posicao);
}  // inserir em ordem


template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index fora da range");}
    Node* aux = head;
    for(std::size_t i = 0; i< index; i++){
        aux = aux->next();}
    return aux->data();
    }

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index fora da range");}
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node* aux = head;
    if (index == 0){
        return pop_front();
    }
    for(std::size_t i = 1; i< index; i++){
        aux = aux->next();}
    Node* holder = aux->next();
    T value = holder->data();
    aux->next(holder->next());
    size_--;
    delete holder;
    return value;}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    return pop(size_ - 1);
}  

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("empty");
    } else {
        Node* aux;
        aux = head;
        T value;
        value = head->data();
        head = head->next();
        size_--;
        delete aux;
        return value;
    }
}  

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    int index = find(data);
    pop(index);
}

template<typename T>
bool  structures::LinkedList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
} 

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    Node* aux = head;
    for (std::size_t i = 0 ; i < size_ ; i++) {
        if (data == aux->data()) {
            return true;
        }
        aux = aux->next();
    }
    return false;}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* aux = head;
    for (std::size_t i = 0 ; i < size_ ; i++) {
        if (aux->data() == data)
            return i;
        aux = aux->next();
    }
    return size_;}


template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
} 

