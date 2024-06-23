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
        void insert(User newUser, TreePointer &pA, bool &h);
        void removeMin(TreePointer &q, TreePointer &r, bool &h);
        void rotacaoL(TreePointer &pA, bool &h);
        void rotacaoR(TreePointer &pA, bool &h);
        int compareDates(const std::tm& tm1, const std::tm& tm2);

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
        ~AVLBirthday(); 
        TreePointer search(TreeEntry x);
        int insert(User newUser);
        bool remove(TreeEntry x, TreePointer &p, bool &h);

};

#endif  // AVLBIRTHDAY_H
