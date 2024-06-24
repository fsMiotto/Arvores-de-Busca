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

        //Montando as estruturas
        struct TreeNode { 
            User entry; // tipo de dado colocado na árvore
            TreePointer leftNode, rightNode; // subárvores
        };
        
        // declaração de campos
        TreePointer root;
        
    public:
        BSTName(){ root == NULL; } //inicializando
        ~BSTName(){} //encerrando
        int insert(User newUser); //contar as comparações
        bool remove(TreeEntry x);
        TreePointer search(TreeEntry x);

};

#endif  // BSTNAME_H