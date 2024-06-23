#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
//importando arvores
#include "BSTName.h"
#include "BSTID.h"
#include "BSTBirthday.h"
#include "AVLName.h"
#include "AVLID.h"
#include "AVLBirthday.h"
#include "User.h"

// Função auxiliar para converter a data de string para std::tm
std::tm stringToDate(const std::string& birthday) {
    std::tm tm = {};
    std::istringstream ss(birthday);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) {
        std::cerr << "Falha ao converter a data: " << birthday << std::endl;
    }
    return tm;
}

// Função para ler o arquivo CSV e separar os dados em variáveis apropriadas
std::vector<User> readCSV(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line, word;

    // Verificar se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return users;
    }

    // Ignorar a primeira linha (cabeçalho)
    std::getline(file, line);

    // Ler o arquivo linha por linha
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        User user;

        // Ler e atribuir ID (inteiro)
        std::getline(ss, word, ',');
        user.id = std::stoi(word);

        // Ler e atribuir Nome (string)
        std::getline(ss, word, ',');
        user.name = word;

        // Ler e atribuir Data de Nascimento (data tm da lib <ctime>)
        std::getline(ss, word, ',');
        user.birthday = stringToDate(word);

        users.push_back(user);
    }

    // Fechar o arquivo
    file.close();
    return users;
}

int main() {
    std::string filename = "users.csv";

    // Ler os dados do arquivo CSV e criar um vetor "users". Ao final do processamento, cada usuário estará em "users".
    std::vector<User> users = readCSV(filename);

    //iniciando as arvores
    BSTName bst_name;
    BSTID bst_id;
    BSTBirthday bst_birthday;
    AVLName  avl_name;
    AVLID avl_id;
    AVLBirthday avl_birthday;


    for (int i = 0; i < users.size(); i++) {
        bst_name.insert(users[i]);
        bst_id.insert(users[i]);
        bst_birthday.insert(users[i]);
        avl_name.insert(users[i]);
        avl_id.insert(users[i]);
        avl_birthday.insert(users[i]);
    }


    return 0;
}

