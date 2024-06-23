#ifndef AVLNAME_H
#define AVLNAME_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include "User.h"



class AVLName {
    private:
        //Declaração dos tipos e estruturas
        typedef std::string TreeEntry; //tipo da variável recebida para inserçã, remoção, e busca
        struct TreeNode; // estrutura TreeNode definida abaixo no código
        typedef TreeNode *TreePointer; // TreePointer é um ponteiro para estrutura TreeNode
        
        //metodos
        void insert(User newUser, TreePointer &pA, bool &h);
        void removeMin(TreePointer &q, TreePointer &r, bool &h);
        void rotacaoL(TreePointer &pA, bool &h);
        void rotacaoR(TreePointer &pA, bool &h);

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
        AVLName();
        ~AVLName();
        TreePointer search(TreeEntry x);
        int insert(User newUser);
        bool remove(TreeEntry x, TreePointer &p, bool &h);

};

#endif  // AVLNAME_H
