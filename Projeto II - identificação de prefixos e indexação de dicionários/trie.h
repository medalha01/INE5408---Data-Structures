#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H

#include <string>

#define ALPHABET_SIZE 26

namespace structures { 

class Trie {
 public:
  Trie(); //Novo Trie
  void inserir(std::string word, int index, int length);
  std::pair<int, int> procurar(std::string word);
  int n_prefixo(std::string word);
  int n_children();
  int n_palavras();

 private:
    Trie* children[ALPHABET_SIZE];
    int index{0}, length{0};
};

}  // namespace structures

#endif

//  No novo Trie o index que é a posição e o lenght que é o comprimento vão 
//  ser definidos inicialmente como 0 e as posições de children que 
//  são os nodos filhos são  nulos

structures::Trie::Trie() {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		children[i] = nullptr;
	}
}
// Vai adicionar uma chave na árvore, word é a palavra a ser inserida, 
// o index a posição no dicionario da palavra a ser inserida, e o lenght o 
//comprimento da linha do dicionario que possui a palavra a ser inserida.

void structures::Trie::inserir(std::string word, int index, int length) {
	auto current = this;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			current->children[position] = new Trie;
    	}
		current = current->children[position];
	}
	current->index = index;
	current->length = length;
}

std::pair<int, int> structures::Trie::procurar(std::string word) {
	std::pair<int, int> pair; 

  
	auto current = this;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			pair.first = -1;
			pair.second = -1;
			return pair;
		}
		current = current->children[position];
	}
	if (current && current->length == 0) {
		pair.first = 0;
		pair.second = 0;
		return pair;
	}
	pair.first = current->index;
	pair.second = current->length;
	return pair;
}

int structures::Trie::n_prefixo(std::string word) {
	auto current = this;
	int n_prefix = 0;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			break;
		}
		current = current->children[position];
	}
	if (current) {
		if (current->length != 0) {
			n_prefix++;
		}
		n_prefix += current->n_palavras();
	}
	return n_prefix;
}


int structures::Trie::n_children() {
	auto current = this;
	int n_children = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (current->children[i]) {
			n_children++;
		}
	}
	return n_children;
}

int structures::Trie::n_palavras() {
	int n_words = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (children[i]) {
			if (children[i]->length != 0) {
				n_words++;
			}
			n_words += children[i]->n_palavras();
		}
	}
	return n_words;
}
