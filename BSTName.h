#ifndef BSTNAME_H
#define BSTNAME_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>


typedef std::string TreeEntry;

class BSTName { 
    private:
        //Declarando estruturas e tipos
        struct User;
        struct TreeNode;
        typedef TreeNode (*TreePointer); // TreePointer é um ponteiro para estrutura TreeNode
        
        //declaração de métodos
        void search(TreeEntry x, TreePointer &t);
        void removeMin(TreePointer &q, TreePointer &r);

        //Montando as estruturas
        struct User { //estrutura do usuário
            std::string name;
            int id;
            std::string date;
        };
        struct TreeNode { 
            User entry; // tipo de dado colocado na árvore
            TreePointer leftNode, rightNode; // subárvores
        };
        
        // declaração de campos
        TreePointer root;
        
    public:
        BSTName();
        ~BSTName();
        int insert(User newUser); //contar as comparações
        bool remove(TreeEntry x);
        TreePointer search(TreeEntry x);

};

#endif  // BSTNAME_H