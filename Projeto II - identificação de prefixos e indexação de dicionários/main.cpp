// Copyright [2022] <Isac Martis>

#include <fstream>
#include <iostream>
#include <string>
#include "trie.h"

int main() {
    using namespace std;
    using namespace structures;


    Trie trie;
    string filename;
    cin >> filename;  // Arquido de entrada.
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        int next_index = 0;
        while (getline(file, line)) {
            string word_read;
            if (line[0] != '[') {
                next_index += line.length() + 1;
                continue;
            }
            for (int i = 1; i < line.length(); i++) {
				if (line[i] == ']') {
                    break;
                }
				word_read += line[i];
			}
            trie.inserir(word_read, next_index, line.length());
            next_index += line.length() + 1;
        }
        file.close();
    }

    string word;
    pair<int, int> pair;
    int n;
    int c;
    int d;
    while (1) {  // Leitura das palavras até encontrar "0".
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        pair = trie.procurar(word);
        string p = word;
        if (pair.first  == 0) {
            if (pair.second == 0){
                n = trie.n_prefixo(word);
                cout << p << " is prefix of " << n << " words" << endl;}
            else if (pair.first  == -1) {
            cout << p << " is not prefix" << endl;}
            else {
            n = trie.n_prefixo(word);
            d = pair.first;
            c = pair.second;
            cout << p << " is prefix of " << n << " words" << endl;
            cout << p << " is at " << "(" << d << "," << c << ")" << endl;
        }
        } else if (pair.first  == -1) {
            cout << p << " is not prefix" << endl;
        } else {
            n = trie.n_prefixo(word);
            d = pair.first;
            c = pair.second;
            cout << p << " is prefix of " << n << " words" << endl;
            cout << p << " is at " << "(" << d << "," << c << ")" << endl;
        }
    }
    return 0;
}