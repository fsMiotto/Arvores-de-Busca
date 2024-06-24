#ifndef BSTBirthday_H
#define BSTBirthday_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include "User.h"



class BSTBirthday { 
    private:
        //Declarando estruturas e tipos
        typedef std::tm TreeEntry;
        struct TreeNode;
        typedef TreeNode (*TreePointer); // TreePointer é um ponteiro para estrutura TreeNode
        
        //declaração de métodos
        void search(TreeEntry x, TreePointer &t);
        void removeMin(TreePointer &q, TreePointer &r);
        int compareDates(const std::tm& tm1, const std::tm& tm2);

        //Montando as estruturas
        struct TreeNode { 
            User entry; // tipo de dado colocado na árvore
            TreePointer leftNode, rightNode; // subárvores
        };
        
        // declaração de campos
        TreePointer root;
        
    public:
        BSTBirthday(){ root == NULL; } //inicializando
        ~BSTBirthday(){} //encerrando
        int insert(User newUser); //contar as comparações
        bool remove(TreeEntry x);
        TreePointer search(TreeEntry x);

};

#endif  // BSTBirthday_H