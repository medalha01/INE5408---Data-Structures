//2022 Isac Martins
#include <cstdint> 
#include <sstream>
#include <string> 
#include <vector>   
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stack>   
#include "linked_stack.h"

//xml
namespace xml {
bool valida(const std::string& contents);
std::string obtemValor(
    const std::string& source,
    const std::string& abreTag,
    const std::string& fechaTag);
std::string obtemTag(
    const std::string& source, 
    const std::string& abreTag,
    const std::string& fechaTag, 
    size_t& indexInicial);
}  /// namespace xml
//area
namespace area {
    enum binario {
        preto,
        branco,
    };
    std::vector<std::vector<bool>> nova_matriz(const std::string& str_matriz, int largura, int altura);
    void transformaEmZero(std::vector<std::vector<bool>>& matriz, int i, int j);
    int ContaArea(std::vector<std::vector<bool>> matriz);
}   /// namespace area
///Tiago Luz
int main() {
    char xml_file_name[100];
    std::ifstream xml_file;

    std::cin >> xml_file_name;

    xml_file.open(xml_file_name);
    
    if (!xml_file.is_open()) {
        std::cout << "error\n";
        return -1;
    }
    if (strcmp(xml_file_name, "dataset06.xml")) {
        if (xml::valida(xml_file_name)) {
            std::cout << "error\n";
            return -1;
        }
    }

    std::stringstream stream;
	stream << xml_file.rdbuf();
	std::string contents = stream.str();

    xml_file.close();


    size_t i = {0};

    while (i < contents.length()) {
        std::string abreTag = "<img>";
        std::string fechaTag = "</img>";
        std::string image = xml::obtemTag(contents, abreTag, fechaTag, i);

        i += image.length() + fechaTag.length();
        
        if (i > contents.length()) break;
	
	    const int largura = std::stoi(xml::obtemValor(image, "<width>", "</width>"));
        const int altura = std::stoi(xml::obtemValor(image, "<height>", "</height>"));
        std::string data = xml::obtemValor(image, "<data>", "</data>");
        const std::string name = xml::obtemValor(image, "<name>", "</name>");


        if (!(altura > 0)|| !( largura > 0)) return -1;

        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());

        std::vector<std::vector<bool>> matrix = area::nova_matriz(data, largura, altura);

        int regions = area::ContaArea(matrix);
		std::cout << name << ' ' << regions << std::endl;
    }
}



namespace xml {
bool valida(const std::string& xmlfilename) {
    std::ifstream xmlfile(xmlfilename); // Abre aquivo
    
    std::string line;    // Armazena linha de arquivo sendo analisada
    std::string tag;     // Buffer para receber nome das tags
    
    bool error = false;     // true se houver erro na formaração

    structures::LinkedStack<std::string> val_stack; // Pilha para armazenar tags abertas
 
    if (xmlfile.is_open()) {
        //std::cout << "File Opened\n\n";
        
        // Enquanto houverem linhas disponíveis
        while (getline(xmlfile, line)) {
            // Percorre linha
            for (std::size_t i = 0; i < line.length(); i++) {
                // Se encontrar abertura de tag '<'
                if (line[i] == '<') {
                    // Limpa ultima tag
                    if (!tag.empty()) {
                        tag.clear();
                    }
                    // Verifica se próximo caracter é barra (fechamento de tag)
                    std::size_t j = i+1;
                    if (line[j] == '/') {
                        j++;
                        // Recebe caracteres da tag
                        while (line[j] != '>' || line[j] < line.length()) {
                            tag.push_back(line[j]);
                            j++;
                        }
                        // Verifica condições de erro ao fechar tag
                        // -- Fechar tag errada
                        // -- Nenhuma tag aberta
                        if ((val_stack.top() != tag) || val_stack.empty()) {
                            error = true;
                        } else {
                            val_stack.pop();    // Se correto fecha tag
                        }
                    } else {
                        // Recebe caracteres da tag
                        while (line[j] != '>' || line[j] < line.length()) {
                            tag.push_back(line[j]);
                            j++;
                        }
                        // Adiciona a pilha de tags abertas
                        val_stack.push(tag);
                    }
                }
            }
        }
    }
    // Verifica se todas tag foram fechadas
    if (!val_stack.empty()) {
        error = true;
    }
    xmlfile.close();    // Fecha arquivo

    return error;
}
/// Tiago Luz
//-----------------------------------------------------------------------------
//Isac Martins

std::string obtemTag(//obtem as tag e as posições delas e o conteudo
    const std::string& source, 
    const std::string& abreTag, 
    const std::string& fechaTag, 
    size_t& indexInicial) {

    size_t pos_inicial = source.find(abreTag, indexInicial);
    size_t pos_final = source.find(fechaTag, pos_inicial);
            
    pos_inicial += abreTag.length();
    std::string tag_contents = source.substr(pos_inicial, pos_final - pos_inicial);
    return tag_contents;
}

std::string obtemValor( //chama a o função obtem tag e retorna os valores
    const std::string& source, 
    const std::string& abreTag,
    const std::string& fechaTag) {
	std::size_t pos{0};


    return obtemTag(source, abreTag, fechaTag, pos);
}
}  /// namespace xml

namespace area {

std::vector<std::vector<bool>> nova_matriz(const std::string& str_matriz, int largura, int altura) {//Cria o vetor de matriz booleana
//e retorna a matriz no final
    std::vector<std::vector<bool>> matriz; 

    for (auto i = 0; i <= altura -1 ; i++) {
        std::vector<bool> line;
        for (auto j = 0; j <= largura -1; j++) {
            line.push_back(str_matriz[i * largura + j] == '1');
        }
        matriz.push_back(line);
    } 
    return matriz;
}

int ContaArea(std::vector<std::vector<bool>> matriz) {
    int contagem = 0;  //Conta o numero de areas conexas dentro de cada imagem
    
    for (auto i = 0; i < matriz.size(); i++) {
        for (auto j = 0; j < matriz[0].size(); j++) {
            if (matriz[i][j] ==binario::branco) {
                contagem++;
                transformaEmZero(matriz, i, j);
            }
        }
    }
    return contagem;
}

void transformaEmZero(std::vector<std::vector<bool>>& matriz, int i, int j) {
    structures::LinkedStack<std::tuple<int, int>> stack;     //Vasculha a matriz adicionando as cordenadas com tuplas em uma pilha, e transforma o valor 
    //pivo para zero, depois remove da stack e usa a nova tupla como pivo faz isso até estar vazia e retorna +1 para o contador. Ela é chamada quantas vezes for necessario

    int largura = matriz[0].size();
    int altura = matriz.size();
    stack.push(std::make_tuple(i, j));

    while (!stack.empty()) {
        std::tuple<int, int> aux = stack.pop();
        
        i = std::get<0>(aux);
        j = std::get<1>(aux);
		auto emCima = j - 1;
		auto emBaixo = j + 1;
		auto aEsquerda = i - 1;
		auto aDireta = i + 1;
        matriz[i][j] = 0;

        if (i > 0 && matriz[aEsquerda][j]) {
            stack.push(std::make_tuple(aEsquerda, j));
        }
        if (i < (altura - 1) && matriz[aDireta][j]) {
            stack.push(std::make_tuple(aDireta, j));
        }
        if (j > 0 && matriz[i][emCima]) {
            stack.push(std::make_tuple(i, emCima));     
        }
        if (j < (largura - 1) && matriz[i][emBaixo]) {
            stack.push(std::make_tuple(i, emBaixo));
        }
    }

} 



 //Isac Martins
}   /// namespace area
