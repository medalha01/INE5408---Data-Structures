#ifndef STRUCTURES_BINARY_TREE_B
#define STRUCTURES_BINARY_TREE_B

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "array_list.h"

namespace structures {
//! Classe arvore binaria

template<typename T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const T& data);
    void remove(const T& data);
    bool contains(const T& data) const;

    bool empty() const;
    std::size_t size() const;
    std::size_t height() const;


    ArrayList<T> pre_order() const;
    ArrayList<T> in_order() const;
    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data) :
        data_{data}
        {}

        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};

        void insert(const T& data) {
            if (data < data_) {
                if (left_ == nullptr) {
                    left_ = new Node(data);
                    if (left_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    left_->insert(data);
                }
            } else {
                if (right_ == nullptr) {
                    right_ = new Node(data);
                    if (right_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    right_->insert(data);
                }
            }
        }

        bool remove(const T& data) {
            bool deleted = false;
            if (data < data_ && left_ != nullptr) {
                left_ = remove(data, left_, deleted);
            } else if (data > data_ && right_ != nullptr) {
                right_ = remove(data, right_, deleted);
            } else {
                if (right_ != nullptr && left_ != nullptr) {
                    Node* temp = right_->minimum();
                    data_ = temp->data_;
                    right_ = remove(data_, right_, deleted);
                } else if (right_ != nullptr) {
                    Node* temp = right_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                    deleted = true;
                } else if (left_ != nullptr) {
                    Node* temp = left_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                    deleted = true;
                }
            }
            return deleted;
        }

        bool contains(const T& data) const {
            if (data < data_)
                return left_ == nullptr? false : left_->contains(data);
            else if (data > data_)
                return right_ == nullptr? false : right_->contains(data);
            else
                return true;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        void in_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->in_order(v);
            v.push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        void post_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v.push_back(data_);
        }

     private:
        Node* remove(const T& data, Node* arv, bool& deleted) {
            deleted = false;
            if (arv == nullptr)
                return arv;
            if (data < arv->data_) {
                arv->left_ = remove(data, arv->left_, deleted);
                return arv;
            }
            if (data > arv->data_) {
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            if (arv->right_ != nullptr && arv->left_ != nullptr) {
                Node* temp = arv->right_->minimum();
                arv->data_ = temp->data_;
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            Node* temp = nullptr;
            if (arv->right_ != nullptr)
                temp = arv->right_;
            else
                temp = arv->left_;

            arv->right_ = arv->left_ = nullptr;
            delete arv;
            deleted = true;
            return temp;
        }

        Node* minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }
    };

    Node* root_{nullptr};
    std::size_t size_{0};
    std::size_t height_{0};

};

//! construtor
template<typename T>
AVLTree<T>::AVLTree()
{}

//! destrutor
template<typename T>
AVLTree<T>::~AVLTree() {
    delete root_;
}

//! insere
template<typename T>
void AVLTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("Full tree!");
    } else {
        root_->insert(data);
    }
    ++size_;
    ++height_;
}

//! remove
template<typename T>
void AVLTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree!");

    if (size() != 1u) {
        if (root_->remove(data))
            --size_;
    } else {
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            --size_;
        }
    }
}

//! contemn
template<typename T>
bool AVLTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

// vazia
template<typename T>
bool AVLTree<T>::empty() const {
    return size() == 0;
}

//! tamanho
template<typename T>
std::size_t AVLTree<T>::size() const {
    return size_;
}

template<typename T>
std::size_t AVLTree<T>::height() const {
    return height_;
}

//! pre ordem
template<typename T>
ArrayList<T> AVLTree<T>::pre_order() const {
    ArrayList<T> v{size()};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! em ordem
template<typename T>
ArrayList<T> AVLTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! pos ordem
template<typename T>
ArrayList<T> AVLTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  // namespace structures

#endif
