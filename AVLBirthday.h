#ifndef AVLBIRTHDAY_H
#define AVLBIRTHDAY_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include "User.h"


class AVLBirthday {
    private:
        //Declarando estruturas e tipos
        typedef std::tm TreeEntry; //tipo da variável recebida para inserçã, remoção, e busca
        struct TreeNode; // estrutura TreeNode definida abaixo no código
        typedef TreeNode *TreePointer; // TreePointer é um ponteiro para estrutura TreeNode
        
        //metodos
        int insert(User newUser, TreePointer &pA, bool &h);
        void removeMin(TreePointer &q, TreePointer &r, bool &h);
        void rotacaoL(TreePointer &pA, bool &h);
        void rotacaoR(TreePointer &pA, bool &h);
        int altura_e_folhas(TreePointer &p);

        //Montando as estruturas
        struct TreeNode { 
            User entry; // tipo de dado colocado na árvore
            int bal; // -1, 0, +1
            TreePointer leftNode, rightNode; // subárvores
        };
        
        // declaração de campos
        TreePointer root;
    
    
    public:
        //metodos
        AVLBirthday();
        ~AVLBirthday(){}//encerrando
        User::User search(TreeEntry x);
        int insert(User newUser);
        bool remove(TreeEntry x, TreePointer &p, bool &h);
        void altura_e_folhas();

        //variaveis
        float MediaComp; //Média de Comparações por Usuário
        float MediaRotacao; //Média de Rotações por Usuário
        int QuantUsers; //Quantidade de Usuarios
        int Altura; // altura da arvore
        int Folhas; // Numero de folhas da arvore

};

#endif  // AVLBIRTHDAY_H
