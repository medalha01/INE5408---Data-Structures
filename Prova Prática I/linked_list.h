//! Copyright [2022] <Copyright Owner>

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions


namespace structures {

//! Classe Lista Encadeada
template<typename T>
class LinkedList {
 public:
    LinkedList();  // construtor padrão
    ~LinkedList();  // destrutor
    void clear();  // limpar lista
    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem
    T& at(std::size_t index);  // acessar um elemento na posição index
    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover específico
    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém
    std::size_t find(const T& data) const;  // posição do dado
    std::size_t size() const;  // tamanho da lista

    //*******************************************************************
    // Prova prática - implementações necessárias:

    // (1) inverter a lista, ou seja, o primeiro passa a ser o último,
    //     o segundo passa a ser o penúltimo, e assim por diante:
    void invert();

    // (2) criar uma duplicação, em memória, da lista:
    LinkedList<T> clone();

    // (3) criar uma lista com dados das posições de
    //     início (start) até fim (stop), saltando com um passo (step):
    LinkedList<T> slicing(int start, int stop, int step);

    // (4) acrescentar uma lista ao final
    void append(structures::LinkedList<T> &list_add);

    // (5) criar uma lista contendo outras duas listas:
    //     a primeira, correspondente aos dados em posições pares
    //     a segunda, correspondente aos dados em posições ímpares
    LinkedList< LinkedList<T> * > halve();

    //*******************************************************************

 private:
    class Node {  // Elemento
     public:
        //! Construtor usando apenas o dado.
        explicit Node(const T& data):
        data_{data}
        {}

        //! Construtor de um nodo completo.
        explicit Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        //! Retorna o dado armazenado.
        T& data() {
            return data_;
        }

        //! Retorna o dado armazenado.
        const T& data() const {
            return data_;
        }

        //! Retorna ponteiro para próximo nodo.
        Node* next() {  // getter: próximo
            return next_;
        }

        //! Retorna ponteiro para o o próximo node.
        const Node* next() const {  // getter const: próximo
            return next_;
        }

        //! Altera o ponteiro para o próximo.
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;  // data_
        Node* next_{nullptr};  // next_
    };

    //! Passa pelos nodes até o último.
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    //! Passa pelos nodes até o anterior ao índice procurado.
    Node* before_index(std::size_t index) {  // node anterior ao index
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* before);  // inserir na posicao polimorfico

    Node* head{nullptr};  // head
    std::size_t size_{0u};  // size_
};

}  // namespace structures


//*******************************************************************

//! Inversão da lista
template<typename T>
void structures::LinkedList<T>::invert() {
    Node* primeiroDaLista = end();
    Node* aux = primeiroDaLista;
    for (auto i =size()-1; i > 0; --i) {
        aux->next(before_index(i));
        aux = aux->next();}
    head = primeiroDaLista;

}

//! Duplicação, em memória, da lista
template<typename T>
structures::LinkedList<T> structures::LinkedList<T>::clone() {
    LinkedList<T> list_clone;
    Node* aux = head;
    list_clone.push_back(aux->data());
    for (auto i = 1u; i < size(); ++i) {
            aux = aux->next();
            list_clone.push_back(aux->data());
        }
    return list_clone;
}

//! Fatiamento da lista
template<typename T>
structures::LinkedList<T> structures::LinkedList<T>::slicing(int start,
                                                             int stop,
                                                             int step) {
    LinkedList<T> list_slice;
    Node* aux = head;
    for (int i = start; i < stop; i = i + step) {
        aux = before_index(i + 1);
        list_slice.push_back(aux->data());
        }

    return list_slice;
}

//! Acréscimo de outra lista (list_add) ao final da lista
template<typename T>
void structures::LinkedList<T>::append(structures::LinkedList<T> &list_add) {
    int aux = 0;
    for (std::size_t i = 0; i < list_add.size() ; ++i) {
        aux = list_add.at(i);
        push_back(aux);
}}

//! Divisão da lista em duas partes (elementos com índices pares e ímpares)
template<typename T>
structures::LinkedList< structures::LinkedList<T> * >
                                           structures::LinkedList<T>::halve() {
    LinkedList< LinkedList<T> * > list_halve;
    LinkedList<T>* list_clone1 = new LinkedList();
    LinkedList<T>* list_clone2 = new LinkedList();
    Node* aux;
    for (auto i = 1u; i < size(); i = i + 2) {
            aux = before_index(i+1);
            list_clone1->push_back(aux->data());
        }
    for (auto i = 0u; i < size(); i = i + 2) {
            aux = before_index(i+1);
            list_clone2->push_back(aux->data());
        }
    list_halve.push_back(list_clone2);
    list_halve.push_back(list_clone1);
    
    return list_halve;
}

//*******************************************************************


//! Construtor padrão
template<typename T>
structures::LinkedList<T>::LinkedList() {}

//! Destrutor
template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

//! Esvazia a lista.
template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty())
        pop_front();
}

//! Inserção no fim da lista.
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

//! Inserção no começo da lista.
template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    new_node->next(head);
    head = new_node;
    size_++;
}

//! Inserção em qualquer posição da lista.
template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Invalid index!");

    if (index == 0) {
        push_front(data);
    } else {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        Node* before = before_index(index);
        Node* next = before->next();
        new_node->next(next);
        before->next(new_node);
        size_++;
    }
}

//! Inserção em qualquer posição da lista recebendo um ponteiro para um Node.
template<typename T>
void structures::LinkedList<T>::insert(const T& data, Node* before) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    new_node->next(before->next());
    before->next(new_node);
    size_++;
}

//! Inserção ordenada na lista.
template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* current = head;
        Node* before = head;
        std::size_t position = size();
        for (auto i = 0u; i < size(); ++i) {
            if (!(data > current->data())) {
                position = i;
                break;
            }
            before = current;
            current = current->next();
        }
        position == 0? push_front(data) : insert(data, before);
    }
}

//! Coleta o dado na posição da lista.
template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = index == 0? head : before_index(index)->next();
    return current->data();
}

//! Coleta o dado de uma posição específica, removendo-o da lista.
template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if (index >= size())
        throw std::out_of_range("Invalid index!");

    if (index == 0)
        return pop_front();

    Node* before_out = before_index(index);
    Node* out = before_out->next();
    T data = out->data();
    before_out->next(out->next());
    size_--;
    delete out;
    return data;
}

//! Coleta o dado do final, removendo-o da lista
template<typename T>
T structures::LinkedList<T>::pop_back() {
    return pop(size_ - 1u);
}

//! Coleta o dado do início, removendo-o da lista
template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Empty list!");

    auto out = head;
    T data = out->data();
    head = out->next();
    size_--;
    delete out;
    return data;
}

//! Remoção de um dado da lista.
template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

//! Testa se a lista está vazia.
template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size() == 0u;
}

//! Testa se um dado está na lista.
template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return find(data) != size();
}

//! Procura o índice do dado; se não encontrar, retorna o tamanho da lista.
template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    std::size_t index = 0u;
    Node* current = head;
    while (index < size()) {
        if (current->data() == data)
            break;
        current = current->next();
        index++;
    }
    return index;
}

//! Retorna o tamanho da lista.
template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}


