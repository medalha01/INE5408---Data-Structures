// Copyright [2018] <Isac Martins>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>

namespace structures {

  template < typename T >
class ArrayList {
 public:
    ArrayList();
  explicit ArrayList(std::size_t max_size);
  ~ArrayList();
  void clear();
  void push_back(const T & data);
  void push_front(const T & data);
  void insert(const T & data, std::size_t index);
  void insert_sorted(const T & data);
  T pop(std::size_t index);
  T pop_back();
  T pop_front();
  void remove(const T & data);
  bool full() const;
  bool empty() const;
  bool contains(const T & data) const;
  std::size_t find(const T & data) const;
  std::size_t size() const;
  std::size_t max_size() const;
  T & at(std::size_t index);
  T & operator[](std::size_t index);
  const T & at(std::size_t index) const;
  const T & operator[](std::size_t index) const;
      // descricao do 'operator []' na FAQ da disciplina

 private:
        T * contents;
      std::size_t size_;
      std::size_t max_size_;

      static
      const auto DEFAULT_MAX = 10u;};
}  // namespace structures

#endif

template < typename T >
structures::ArrayList < T > ::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
  }

template < typename T >
  structures::ArrayList < T > ::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size_];
  }

template < typename T >
  structures::ArrayList < T > ::~ArrayList() {
    delete[] contents;
  }

template < typename T >
  void structures::ArrayList < T > ::clear() {
    size_ = 0;
  }

template < typename T >
  void structures::ArrayList < T > ::push_back(const T & data) {
    if (full()) {
      throw std::out_of_range("Lista Cheia");
    }
    size_++;
    contents[size_ - 1] = data;
  }

template < typename T >
  void structures::ArrayList < T > ::push_front(const T & data) {
    if (full()) {
      throw std::out_of_range("Lista Cheia");
    }
    for (std::size_t i = size_; i > 0; i--) {
      contents[i] = contents[i - 1];
    }
    size_++;
    contents[0] = data;
  }

template < typename T >
  void structures::ArrayList < T > ::insert(const T & data, std::size_t index) {
    if (full()) {
      throw std::out_of_range("Lista Cheia");}
     if ((index > size_) || (index < 0)) {
        throw std::out_of_range("Fora de Index");
    }
    if (index == size_) {
      contents[index] = data;
      size_++;
      } else {
      for (std::size_t i = size_ - 1; i > index; i--) {
        contents[i] = contents[i - 1];
      }
      contents[index] = data;
      size_++;
    }
  }

template < typename T >
  T structures::ArrayList < T > ::pop(std::size_t index) {
    if ((index >= size_) || (index < 0)) {
      throw std::out_of_range("Fora de Index");
    }
    if (index == size_ - 1) {
      return pop_back();
    } else {
    T aux = contents[index];
      for (std::size_t i = index; i < size_ - 1; i++) {
        contents[i] = contents[i + 1];
      }
    size_--;
    return aux;
    }
  }

template < typename T >
  T structures::ArrayList < T > ::pop_front() {
    if (empty()) {
      throw std::out_of_range("Lista Vazia");
    }
    return pop(0);
  }

template < typename T >
  T structures::ArrayList < T > ::pop_back() {
    if (empty()) {
      throw std::out_of_range("Lista Vazia");
    }
    T aux;
    size_--;
    aux = contents[size_];
    return aux;
  }

template < typename T >
  bool structures::ArrayList < T > ::full() const {
    if (size_ == max_size_) {
      return true;
    }
    return false;
  }
template < typename T >
  bool structures::ArrayList < T > ::empty() const {
    if (size_ == 0) {
      return true;
    }
    return false;
  }

template < typename T >
  void structures::ArrayList < T > ::remove(const T & data) {
    for (std::size_t i = 0; i < size_; i++)
      if (contents[i] == data) {
        pop(i);
        break;
      }
  }
template < typename T >
  bool structures::ArrayList < T > ::contains(const T & data) const {
    for (std::size_t i = 0; i < size_; i++) {
      if (contents[i] == data) {
        return true;
      }
    }
    return false;
  }

template < typename T >
  std::size_t structures::ArrayList < T > ::find(const T & data) const {
    for (std::size_t i = 0; i < size_; i++) {
      if (contents[i] == data) {
        return i;
      }
    }
    return data;
  }

template < typename T >
  std::size_t structures::ArrayList < T > ::max_size() const {
    return max_size_;
  }

template < typename T >
  std::size_t structures::ArrayList < T > ::size() const {
    return size_;
  }



template < typename T >
  T & structures::ArrayList < T > ::at(std::size_t index) {
    if (empty()) {
      throw std::out_of_range("Out of Range");
    }
    if (index > size_) {
      throw std::out_of_range("Out of Range");
    }
    return contents[index];
  }

template < typename T >
  const T & structures::ArrayList < T > ::at(std::size_t index) const {
    if (empty()) {
      throw std::out_of_range("fila vazia");
    }
    if (index > size_) {
      throw std::out_of_range("fora do range");
    }
    return contents[index];
  }

template < typename T >
  T & structures::ArrayList < T > ::operator[](std::size_t index) {
    if (index < 0) {
      throw std::out_of_range("index menor que 0");
    }
    return contents[index];
  }

template < typename T >
  const T & structures::ArrayList < T > ::operator[](std::size_t index) const {
    if (index < 0) {
      throw std::out_of_range("index menor que 0");
    }
    return contents[index];
  }

  template < typename T >
  void structures::ArrayList < T > ::insert_sorted(const T & data) {
    if (full()) {
      throw std::out_of_range("Lista Cheia");
    } else {
      std::size_t i = 0;
      while (i < size_ && data > contents[i])
        i++;
      insert(data, i);
    }
}
