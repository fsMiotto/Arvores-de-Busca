#ifndef BSTBirthday_H
#define BSTBirthday_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>


typedef std::tm TreeEntry;


class BSTBirthday { 
    private:
        //Declarando estruturas e tipos
        struct User;
        struct TreeNode;
        typedef TreeNode (*TreePointer); // TreePointer é um ponteiro para estrutura TreeNode
        
        //declaração de métodos
        void search(TreeEntry x, TreePointer &t);
        void removeMin(TreePointer &q, TreePointer &r);
        int compareDates(const std::tm& tm1, const std::tm& tm2);

        //Montando as estruturas
        struct User { //estrutura do usuário
            std::string name;
            int id;
            std::tm date;
        };
        struct TreeNode { 
            User entry; // tipo de dado colocado na árvore
            TreePointer leftNode, rightNode; // subárvores
        };
        
        // declaração de campos
        TreePointer root;
        
    public:
        BSTBirthday();
        ~BSTBirthday();
        int insert(User newUser); //contar as comparações
        bool remove(TreeEntry x);
        TreePointer search(TreeEntry x);

};

#endif  // BSTBirthday_H