
#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <algorithm>
#include "./array_list.h"


namespace structures {

//! Classe Árvore binária
template<typename T>
class BinaryTree {
 public:
    //! Construtor
    BinaryTree();
    //! Destrutor
    ~BinaryTree();
    //! Inserção
    void insert(const T& data);
    //! Remoção
    void remove(const T& data);
    //! Contém
    bool contains(const T& data) const;
    //! Vazio
    bool empty() const;
    //! Tamanho
    std::size_t size() const;
    //! Pré ordem
    ArrayList<T> pre_order() const;
    //! Em ordem
    ArrayList<T> in_order() const;
    //! Pós ordem
    ArrayList<T> post_order() const;

    //******************************************************************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

    //******************************************************************


 private:
    struct Node {
        //! Construtor
        explicit Node(const T& data) :
        data_{data}
        {}

        //! Destrutor
        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};

        //! Inserção
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

        //! Remoção
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

        //! Contém
        bool contains(const T& data) const {
            if (data < data_)
                return left_ == nullptr? false : left_->contains(data);
            else if (data > data_)
                return right_ == nullptr? false : right_->contains(data);
            else
                return true;
        }

        //! Pré ordem
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        //! Em ordem
        void in_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->in_order(v);
            v.push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        //! Pós ordem
        void post_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v.push_back(data_);
        }

        //! Rotação simples à direita
		Node* simpleLeft() {
            Node *k1 = left_;
            left_ = k1->right_;
            k1->right_ = this;
            return k1;
        }

		//! Rotação simples à direita
        Node* simpleRight() {
            Node *k1 = right_;
            right_ = k1->left_;
            k1->left_ = this;
            return k1;
        }

		//! Rotação dupla à esquerda
        Node* doubleLeft() {
            left_ = left_->simpleRight();
            return this->simpleLeft();
        }

		//! Rotação dupla à direita
        Node* doubleRight() {
            right_ = right_->simpleLeft();
            return this->simpleRight();
        }

		//! Encontrar o menor
        Node* minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }

		//! Encontrar o maior
        Node* maximum() {
            if (right_ == nullptr)
                return this;
            return right_->maximum();
        }

        //! Altura
        int height() {
            int heigth_ = -1;
            if (!left_ && !right_) {
                heigth_++;
            } else if (left_) {
                heigth_ = left_->height() + 1;
            } else if (right_) {
                 heigth_ = right_->height() + 1;
            } else {
                heigth_ = std::max(left_->height(), right_->height()) + 1;
            }
            return heigth_;
        }

        //! Número de folhas
        int leaves() {
            int n_leaves = 0;
            if (left_ == nullptr &&
                right_ == nullptr ) {
                n_leaves++;
            } else {
                if (left_ != nullptr) {
                    n_leaves += left_->leaves();
                }
                if (right_ != nullptr) {
                    n_leaves += right_->leaves();
                }
            }
            return n_leaves;
        }

		//! Busca o elemento na árvore
		Node* search(const T& data) {
            if (data < data_) {
				if (left_ != nullptr) {
					return left_->search(data);
				} else {
					return nullptr;
				}
			} else if (data > data_) {
				if (right_ != nullptr) {
					return right_->search(data);
				} else {
					return nullptr;
				}
			} else {
				return this;
			}
        }

        void balance_tree(ArrayList<T>& in_order_list,
                           int start,
                           int end,
                           BinaryTree<T>& B) {
            if (!(start > end)) {
                int mid = (start + end) / 2;
                B.insert(in_order_list[mid]);
                balance_tree(in_order_list, start, mid - 1, B);
                balance_tree(in_order_list, mid + 1, end, B);
            }
        }

     private:
        //! Complemento da funcão de remoção
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
            // doi filhos
            if (arv->right_ != nullptr && arv->left_ != nullptr) {
                Node* temp = arv->right_->minimum();
                arv->data_ = temp->data_;
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            // um filho ou folha
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
    };

    Node* root_{nullptr};
    std::size_t size_{0};
};




//******************************************************************
// Prova prática - implementações necessárias:

//! (1) determinação da altura da árvore:
template<typename T>
int BinaryTree<T>::height() {
	if (root_) {
		return root_->height();
	} else {
		return -1;
	}
}

//! (2) contagem do número de folhas:
template<typename T>
int BinaryTree<T>::leaves() {
    return root_->leaves();
}

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
template<typename T>
ArrayList<T> BinaryTree<T>::limits() {
    ArrayList<T> L(2);
	L.push_back(root_->minimum()->data_);
	L.push_back(root_->maximum()->data_);
    return L;
}

//! (4) criação de uma duplicação, em memória, da árvore:
template<typename T>
BinaryTree<T> BinaryTree<T>::clone() {
    BinaryTree<T> C;
	ArrayList<T> pre_order_list = pre_order();
	for (std::size_t i = 0; i < pre_order_list.size(); i++) {
		C.insert(pre_order_list[i]);
	}
    return C;
}

//! (5) remove nós pelo número de seus filhos:
template<typename T>
void BinaryTree<T>::filter(int n_child) {
	ArrayList<T> post_order_list = post_order();
	for (std::size_t i = 0; i < post_order_list.size(); i++) {
		Node* current = root_->search(post_order_list[i]);
		if (n_child == 0) {
			if (current->left_ == nullptr &&
				current->right_ == nullptr) {
			    remove(post_order_list[i]);
            }
		} else if (n_child == 1) {
			if (current->left_ != nullptr &&
				current->right_ == nullptr) {
			    remove(post_order_list[i]);
            } else if (current->left_ == nullptr &&
				       current->right_ != nullptr) {
			    remove(post_order_list[i]);
            }
		} else if (n_child == 2) {
			if (current->left_ != nullptr &&
				current->right_ != nullptr) {
			    remove(post_order_list[i]);
            }
		}
	}
}

//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
template<typename T>
BinaryTree<T> BinaryTree<T>::balance() {
    BinaryTree<T> B;
	ArrayList<T> in_order_list = in_order();
    std::size_t start = 0;
    std::size_t end = (in_order_list.size() - 1);
    B.root_->balance_tree(in_order_list, start, end, B);
    return B;
}

//******************************************************************


//! Construtor
template<typename T>
BinaryTree<T>::BinaryTree()
{}

//! Destrutor
template<typename T>
BinaryTree<T>::~BinaryTree() {
    delete root_;
}

//! Inserção
template<typename T>
void BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("Full tree!");
    } else {
            root_->insert(data);
    }
    size_++;
}

// Remoção
template<typename T>
void BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree");

    if (size() != 1u) {
        if (root_->remove(data))
            size_--;
    } else {
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            size_--;
        }
    }
}

//! Contém
template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Vazio
template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho
template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré ordem
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! Em ordem
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! Pós ordem
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  // namespace structures

#endif
