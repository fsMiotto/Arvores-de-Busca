#ifndef BSTID_H
#define BSTID_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include "User.h"


class BSTID { 
    private:
        //Declarando estruturas e tipos
        typedef int TreeEntry;
        struct TreeNode;
        typedef TreeNode (*TreePointer); // TreePointer é um ponteiro para estrutura TreeNode
        
        //declaração de métodos
        void search(TreeEntry x, TreePointer &t);
        void removeMin(TreePointer &q, TreePointer &r);
        int att_alturaEfolhas(TreePointer& p);

        //Montando as estruturas
        struct TreeNode { 
            User entry; // tipo de dado colocado na árvore
            TreePointer leftNode, rightNode; // subárvores
        };
        
        // declaração de campos
        TreePointer root;
        
    public:
        BSTID(); //inicializando
        ~BSTID(){} //encerrando
        int insert(User newUser); //contar as comparações
        bool remove(TreeEntry x);
        TreePointer search(TreeEntry x);
        void att_alturaEfolhas();

};

#endif  // BSTID_H