#include <iostream>
#include <string>
#include <regex>
#include <sstream>  // Para std::ostringstream
#include <iomanip>  // Para std::put_time

using namespace std;

// Esta função percorre por uma string em busca de um espaço.
bool verificarExistenciaDeEspacos(string textoParaVerificar) {
    for(int i = 0; i < textoParaVerificar.size(); i++) { // Loop de acordo com o tamanho da string.
        if(isspace(textoParaVerificar[i])) { // Verifica se o caractere é um espaço, se sim, faz a função retornar true;
            return true;
        }
    }
    return false;
}

// Esta pega o que foi digitado pelo usuario quando foi pedido por um ID e verifica se é um ID valido.
bool validarId(string textoParaValidar) {
    if(verificarExistenciaDeEspacos(textoParaValidar)) { // Verifica se há espaços no que foi digitado quando foi pedido ID, se ha espaços, retorna false, pois não é valido.
        return false;
    }
    
    int valorParaValidar = stoi(textoParaValidar); // Transforma o que foi digitado de string para int e armazena na variavel valorParaValidar.
    if(valorParaValidar < 1) { // Se o valor digitado é menor que 1, se sim, retorna false.
        return false;
    }
    return true;
}

// Esta função verifica se em uma string há apenas digitos de letras alfanumericos ou espaços.
bool verificarLetras(string str) {
    for(int i = 0; i < str.size(); i++) { // Loop de acordo com o tamanho da string.
        if(isalpha(str[i]) || isspace(str[i])) { // Verifica se o caractere atual é uma letra alfanumerica ou espaço, se sim, continua com o loop para o próximo caractere.
            continue;
        } else {
            return false;
        }
    }
    return true;
}

// Esta função pega o que foi digitado pelo usuário quando foi pedido por um nome e verifica se é um nome valido.
bool validarNome(string valorParaValidar) {
    if(valorParaValidar.size() <= 1 || !verificarLetras(valorParaValidar)) { // Verifica se o nome tem só 1 letra ou há caracteres não permitido.
        return false;
    }
    return true;
}

// Esta função pede um nome para o usuário e retorna um nome valido.
string pedirNome() {
    string valorInserido;
    std::cout << "Insira o Nome do paciente: ";
    getline(cin, valorInserido);
    
    while(!validarNome(valorInserido)) { // Enquanto o nome não ser valido vai continuar dando erro e pedindo para digitar um valido.
        std::cout << "Nome invalido, insira novamente: ";
        getline(cin, valorInserido);
    }
    return valorInserido;
}



// Esta função pede um ID para o usuário e retorna um ID valido.
int pedirId() {
    string valorInserido;
    std::cout << "Insira o ID do paciente (o ID nao poser ser menor do que 1): ";
    getline(cin, valorInserido);
    
    while(!validarId(valorInserido)) { // Enquanto o que foi digitado não é um ID valido, ele  vai continuar pedindo para digitar outro.
        std::cout << "ID invalido, insira novamente (o ID nao poser ser menor do que 1): ";
        getline(cin, valorInserido);
    }
    return stoi(valorInserido);
}

// Esta função verifica se o que foi digitado quando foi pedido uma data de nascimento é valido.
bool validarDataDeNascimento(const std::string& valorInserido) {
    // Expressão regular para o formato YYYY-MM-DD
    std::regex padrao("^\\d{4}-\\d{2}-\\d{2}$");

    // Verifica se a string data corresponde ao padrão
    return std::regex_match(valorInserido, padrao);
}


// Esta função pedi e data de nascimento e retorna uma data de nascimento valida.
string pedirDataDeNascimento() {
    string valorInserido;
    std::cout << "Insira a Data de Nascimento do paciente (YYYY-MM-DD): ";
    getline(cin, valorInserido);
    
    while(!validarDataDeNascimento(valorInserido)) {
        std::cout << "Data de Nascimento invalida, insira novamente(YYYY-MM-DD): ";
        getline(cin, valorInserido);
    }
    
    return valorInserido;
}

//transforma o tm por um string para printar
std::string formatDate(const std::tm& date) {
    std::ostringstream oss;
    oss << std::put_time(&date, "%Y-%m-%d");
    return oss.str();
}