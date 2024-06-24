 #include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include "PedirDigitosValidados.h"
#include "User.h"

//importando arvores
#include "BSTName.h"
#include "BSTID.h"
#include "BSTBirthday.h"
#include "AVLName.h"
#include "AVLID.h"
#include "AVLBirthday.h"


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
    BSTName bstName;
    BSTID bstID;
    BSTBirthday bstBirthday;
    AVLName avlName;
    AVLID avlID;
    AVLBirthday avlBirthday;


    for (int i = 0; i < users.size(); i++) {
        int comp; //só pra usar o retorno na criação da arvore
        comp = bstName.insert(users[i]);
        comp = bstID.insert(users[i]);
        comp = bstBirthday.insert(users[i]);
        comp = avlName.insert(users[i]);
        comp = avlID.insert(users[i]);
        comp = avlBirthday.insert(users[i]);
    }


    int escolhaDoMenu;
    int escolhaDoSubMenu;
    bool menuFinalizado = false;
    bool subMenuFinalizado = false;
    char continuar;

    while (!menuFinalizado) {
        subMenuFinalizado = false;
        system("clear || cls");
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Escolha sua opcao: " << std::endl;
        std::cout << "1 - Buscar por um paciente." << std::endl;
        std::cout << "2 - Adicionar um paciente" << std::endl;
        std::cout << "3 - Remover um paciente." << std::endl;
        std::cout << "4 - Sair do programa." << std::endl;
        std::cout << "------------------------------------" << std::endl;

        cin >> escolhaDoMenu;
        switch (escolhaDoMenu) {
            case 1:
                while(!subMenuFinalizado) {
                    system("clear || cls");
                    std::cout << "------------------------------------" << std::endl;
                    std::cout << "Por quais das informacoes voce quer buscar pelo paciente? " << std::endl;
                    std::cout << "1 - ID " << std::endl;
                    std::cout << "2 - Nome " << std::endl;
                    std::cout << "3 - Data de Nascimento: " << std::endl;
                    std::cout << "Digite 4 para voltar ao menu inicial." << std::endl;
                    std::cout << "------------------------------------" << std::endl;
                    
                    cin >> escolhaDoSubMenu;
                    
                    switch(escolhaDoSubMenu) {
                        case 1:
                            User userTemp;
                            system("clear || cls");
                            std::cout << "------------------------------------" << std::endl;
                            std::cout << "Voce escolheu a opcao buscar paciente por ID." << std::endl;
                            std::cout << "------------------------------------\n" << std::endl;                            
                            int idTemporario = pedirId();
                            std::cout << "\n------------------------------------" << std::endl;
                            std::cout << "Voce buscou pelo paciente com o ID " << idTemporario << ".\n" << std::endl;

                            userTemp = avlID.search(idTemporario);
                            if (isNULL(userTemp)){
                                std::cout << "Usuario nao encontrado" << std::endl;

                            } else{
                                std::cout << "ID: " << userTemp.id << "" << std::endl;
                                std::cout << "Nome: " << userTemp.name << "" << std::endl;
                                std::cout << "Dara de Nascimento: " << userTemp.birthday << "" << std::endl;
                                std::cout << "------------------------------------\n" << std::endl;
                            }

                            std::cout << "\nDigite qualquer qualquer coisa para continuar..." << std::endl;
                            cin >> continuar;
                            
                            break;
                        
                        case 2:
                            User userTemp;
                            system("clear || cls");
                            std::cout << "------------------------------------" << std::endl;
                            std::cout << "Voce escolheu a opcao buscar paciente por Nome." << std::endl;
                            std::cout << "------------------------------------\n" << std::endl;
                            string nomeTemporario = pedirNome();
                            std::cout << "\n------------------------------------" << std::endl;
                            std::cout << "Voce buscou pelo paciente com o Nome: " << nomeTemporario << ".\n" << std::endl;

                            userTemp = avlName.search(nomeTemporario);
                            if (isNULL(userTemp)){
                                std::cout << "Usuario nao encontrado" << std::endl;
                                
                            } else{
                                std::cout << "ID: " << userTemp.id << "" << std::endl;
                                std::cout << "Nome: " << userTemp.name << "" << std::endl;
                                std::cout << "Dara de Nascimento: " << userTemp.birthday << "" << std::endl;
                                std::cout << "------------------------------------\n" << std::endl;
                            }
                            
                            std::cout << "\nDigite qualquer qualquer coisa para continuar..." << std::endl;
                            cin >> continuar;

                            break;
                        
                        case 3:
                            User userTemp;
                            system("clear || cls");
                            std::cout << "------------------------------------" << std::endl;
                            std::cout << "Voce escolheu a opcao buscar paciente pela Data de Nascimento." << std::endl;
                            std::cout << "------------------------------------\n" << std::endl;

                            std::tm dataTemporaria = stringToDate(pedirDataDeNascimento());

                            std::cout << "\n------------------------------------" << std::endl;
                            std::cout << "Voce buscou pelo paciente com a Data de Nascimento: " << dataTemporaria << ".\n" << std::endl;

                            userTemp = avlBirthday.search(dataTemporaria);
                            if (isNULL(userTemp)){
                                std::cout << "Usuario nao encontrado" << std::endl;
                                
                            } else{
                                std::cout << "ID: " << userTemp.id << "" << std::endl;
                                std::cout << "Nome: " << userTemp.name << "" << std::endl;
                                std::cout << "Dara de Nascimento: " << userTemp.birthday << "" << std::endl;
                                std::cout << "------------------------------------\n" << std::endl;
                            }

                            std::cout << "\nDigite qualquer qualquer coisa para continuar..." << std::endl;
                            cin >> continuar;

                            break;
                        
                        case 4:
                            system("clear || cls");
                            subMenuFinalizado = true;
                            break;

                        default:
                            std::cout << "escolha invalida" << std::endl;
                            break;
                    }
                }
                break;

            case 2:
                User userTemp;
                system("clear || cls");
                std::cout << "------------------------------------" << std::endl;
                std::cout << "Voce escolheu a opcao adicionar um paciente." << std::endl;
                std::cout << "------------------------------------\n" << std::endl;
                //recebendo o usuario
                userTemp.id = pedirId();
                userTemp.name = pedirNome();
                userTemp.birthday = stringToDate(pedirDataDeNascimento());

                //fazendo as inserções
                int comparacoes;

                //INSERÇÃO EM BSTs

                //ID
                std::cout << "\nBSTID:" << std::endl;
                comparacoes = bstID.insert(userTemp);
                if (comparacoes == -1){
                    std::cout << "Falha na insercao: Sem espaco na memoria" << std::endl;

                }else if (comparacoes == -2){
                    std::cout << "Falha na insercao: Paciente existente " << std::endl;

                } else{
                    std::cout << "Insercao completa. Numero de comparacoes:" << comparacoes << std::endl;
                }

                //NAME
                std::cout << "\nBSTNAME:" << std::endl;
                comparacoes = bstName.insert(userTemp);
                if (comparacoes == -1){
                    std::cout << "Falha na insercao: Sem espaco na memoria" << std::endl;

                }else if (comparacoes == -2){
                    std::cout << "Falha na insercao: Paciente existente " << std::endl;

                } else{
                    std::cout << "Insercao completa. Numero de comparacoes:" << comparacoes << std::endl;
                }

                //BIRTHDAY
                std::cout << "\nBSTBIRTHDAY:" << std::endl;
                comparacoes = bstBirthday.insert(userTemp);
                if (comparacoes == -1){
                    std::cout << "Falha na insercao: Sem espaco na memoria" << std::endl;

                }else if (comparacoes == -2){
                    std::cout << "Falha na insercao: Paciente existente " << std::endl;

                } else{
                    std::cout << "Insercao completa. Numero de comparacoes:" << comparacoes << std::endl;
                }

                //INSERÇÃO EM AVLs

                //ID
                std::cout << "\nAVLID:" << std::endl;
                comparacoes = avlID.insert(userTemp);
                if (comparacoes == -1){
                    std::cout << "Falha na insercao: Sem espaco na memoria" << std::endl;

                }else if (comparacoes == -2){
                    std::cout << "Falha na insercao: Paciente existente " << std::endl;

                } else{
                    std::cout << "Insercao completa. Numero de comparacoes:" << comparacoes << std::endl;
                }

                //NAME
                std::cout << "\nAVLNAME:" << std::endl;
                comparacoes = avlName.insert(userTemp);
                if (comparacoes == -1){
                    std::cout << "Falha na insercao: Sem espaco na memoria" << std::endl;

                }else if (comparacoes == -2){
                    std::cout << "Falha na insercao: Paciente existente " << std::endl;

                } else{
                    std::cout << "Insercao completa. Numero de comparacoes:" << comparacoes << std::endl;
                }

                //BIRTHDAY
                std::cout << "\nAVLBIRTHDAY:" << std::endl;
                comparacoes = avlBirthday.insert(userTemp);
                if (comparacoes == -1){
                    std::cout << "Falha na insercao: Sem espaco na memoria" << std::endl;

                }else if (comparacoes == -2){
                    std::cout << "Falha na insercao: Paciente existente " << std::endl;

                } else{
                    std::cout << "Insercao completa. Numero de comparacoes:" << comparacoes << std::endl;
                }

                break;

            case 3:
                while(!subMenuFinalizado) {
                    system("clear || cls");
                    std::cout << "------------------------------------" << std::endl;
                    std::cout << "Por quais das informacoes voce quer remover um paciente? " << std::endl;
                    std::cout << "1 - ID " << std::endl;
                    std::cout << "2 - Nome " << std::endl;
                    std::cout << "3 - Data de Nascimento: " << std::endl;
                    std::cout << "Digite 4 para voltar ao menu inicial." << std::endl;
                    std::cout << "------------------------------------" << std::endl;
                    
                    cin >> escolhaDoSubMenu;
                    
                    switch(escolhaDoSubMenu) {

                        User userTemp;
                        case 1:
                            system("clear || cls");
                            std::cout << "------------------------------------" << std::endl;
                            std::cout << "Voce escolheu a opcao remover paciente por ID." << std::endl;
                            std::cout << "------------------------------------" << std::endl;      

                            idTemporario = pedirId();
                            userTemp = avlID.search(idTemporario);
                            if (isNULL(userTemp)){
                                std::cout << "\nUsuario nao encontrado" << std::endl;
                                
                            } else{
                                bstName.remove(userTemp.id);
                                bstID.remove(userTemp.name);
                                bstBirthday.remove(userTemp.birthday);
                                avlName.remove(userTemp.id);
                                avlID.remove(userTemp.name);
                                avlBirthday.remove(userTemp.birthday);
                                std::cout << "\nUsuario removido" << std::endl;
                            }
                            

                            std::cout << "\nDigite qualquer qualquer coisa para continuar..." << std::endl;
                            cin >> continuar;
                            
                            break;
                        
                        case 2:
                            User userTemp;
                            system("clear || cls");
                            std::cout << "------------------------------------" << std::endl;
                            std::cout << "Voce escolheu a opcao remover paciente por Nome." << std::endl;
                            std::cout << "------------------------------------" << std::endl;

                            nomeTemporario = pedirNome();
                            userTemp = avlID.search(nomeTemporario);
                            if (isNULL(userTemp)){
                                std::cout << "\nUsuario nao encontrado" << std::endl;
                                
                            } else{
                                bstName.remove(userTemp.id);
                                bstID.remove(userTemp.name);
                                bstBirthday.remove(userTemp.birthday);
                                avlName.remove(userTemp.id);
                                avlID.remove(userTemp.name);
                                avlBirthday.remove(userTemp.birthday);
                                std::cout << "\nUsuario removido" << std::endl;
                            }
                            
                            std::cout << "\nDigite qualquer qualquer coisa para continuar..." << std::endl;
                            cin >> continuar;
                            break;
                        
                        case 3:
                            User userTemp;
                            system("clear || cls");
                            std::cout << "------------------------------------" << std::endl;
                            std::cout << "Voce escolheu a opcao remover paciente pela Data de Nascimento." << std::endl;
                            std::cout << "------------------------------------" << std::endl;
                        
                            std::tm dataTemporaria = stringToDate(pedirDataDeNascimento());
                            userTemp = avlID.search(dataTemporaria);
                            if (isNULL(userTemp)){
                                std::cout << "\nUsuario nao encontrado" << std::endl;
                                
                            } else{
                                bstName.remove(userTemp.id);
                                bstID.remove(userTemp.name);
                                bstBirthday.remove(userTemp.birthday);
                                avlName.remove(userTemp.id);
                                avlID.remove(userTemp.name);
                                avlBirthday.remove(userTemp.birthday);
                                std::cout << "\nUsuario removido" << std::endl;
                            }

                            std::cout << "Usuario removido. \nDigite qualquer qualquer coisa para continuar..." << std::endl;
                            cin >> continuar;
                            break;;
                        
                        case 4:
                            system("clear || cls");
                            subMenuFinalizado = true;
                            break;

                        default:
                            std::cout << "escolha invalida" << std::endl;
                            break;
                    }
                }
                break;

            case 4:
                menuFinalizado = true;
                break;

            default:
                std::cout << "escolha invalida" << std::endl;
                menuFinalizado = false;
                break;
        }
    }
    return 0;

}
