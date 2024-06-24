#ifndef AVLID_H
#define AVLID_H

#include <iostream>
#include <iomanip>
#include <string>
#include "User.h"



class AVLID {
    private:
        //Declarando estruturas e tipos
        typedef int TreeEntry; //tipo da variável recebida para inserçã, remoção, e busca
        struct TreeNode; // estrutura TreeNode definida abaixo no código
        typedef TreeNode *TreePointer; // TreePointer é um ponteiro para estrutura TreeNode
        
        //metodos
        int insert(User newUser, TreePointer &pA, bool &h);
        void removeMin(TreePointer &q, TreePointer &r, bool &h);
        void rotacaoL(TreePointer &pA, bool &h);
        void rotacaoR(TreePointer &pA, bool &h);
        int att_alturaEfolhas(TreePointer &p);

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
        AVLID();//inicializando
        ~AVLID(){} //encerrando
        TreePointer search(TreeEntry x);
        int insert(User newUser);
        bool remove(TreeEntry x, TreePointer &p, bool &h);
        void att_alturaEfolhas();

        //variaveis
        float MediaComp; //Média de Comparações por Usuário  
        float MediaRotacao; //Média de Rotações por Usuário
        int QuantUsers; //Quantidade de Usuarios
        int Altura; // altura da arvore
        int Folhas; // Numero de folhas da arvore

};

#endif  // AVLID_H
