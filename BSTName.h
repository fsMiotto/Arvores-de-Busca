#ifndef BSTNAME_H
#define BSTNAME_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include "User.h"



class BSTName { 
    private:
        //Declarando estruturas e tipos
        typedef std::string TreeEntry;
        struct TreeNode;
        typedef TreeNode (*TreePointer); // TreePointer é um ponteiro para estrutura TreeNode
        
        //declaração de métodos
        void search(TreeEntry x, TreePointer &t);
        void removeMin(TreePointer &q, TreePointer &r);
        int altura_e_folhas(TreePointer& p);

        //Montando as estruturas
        struct TreeNode { 
            User entry; // tipo de dado colocado na árvore
            TreePointer leftNode, rightNode; // subárvores
        };
        
        // declaração de campos
        TreePointer root;
        
    public:
        BSTName(); //inicializando
        ~BSTName(){} //encerrando
        int insert(User newUser); //contar as comparações
        bool remove(TreeEntry x);
        User::User search(TreeEntry x);
        void altura_e_folhas();

        //variaveis
        float MediaComp; //Média de Comparações por Usuário
        int QuantUsers; //Quantidade de Usuarios
        int Altura; // altura da arvore
        int Folhas; // Numero de folhas da arvore

};

#endif  // BSTNAME_H