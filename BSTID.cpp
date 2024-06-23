#include "BSTID.h"


//Esse método de procura acha o elemento na arvore e retorna a estrutura, usado na main para buscar e imprimir o usuário
BSTID::TreePointer BSTID::search(TreeEntry x){
    TreePointer t=root;
    search(x, t);
    return t; //se t->entry == x retorna a estrutura, se não retorna NULL (verificar estrutura antes de usar)
}

//Esse método de procura acha o elemento na arvore, usado em métodos para reciclar codigo
void BSTID::search(TreeEntry x, TreePointer &t){
    while ( t != NULL && t->entry.id != x ){
        if( x < t->entry.id ){ t = t->leftNode; } // procurar na subárvore esquerda
        else { t = t->rightNode; } // procurar na subárvore direita
    }
}

//metodo de inserção
int BSTID::insert(User newUser) { 
    TreePointer p=NULL, q=root, r;
    int comp = 0; //comparações

    r = new TreeNode; //instanciando novo elemento

    if( r == NULL ){     //verificacao de memoria
        return -1;
    }
    comp++; //comparacao da verificacao de memoria
     
    while ( q != NULL ){ //busca para insert
        if (q->entry.id == newUser.id){
            return 0; //elemento ja esta na arvore
        }

        p = q; // p é o pai de q
        if( newUser.id < q->entry.id ){ q = q->leftNode; }
        else{ q = q->rightNode; }
        comp+= 3;// comparacao dos 2 if e do while
    }
    comp++; //comparação do while quando não entra em loop e não é contabilizada

    //Montando o nó
    r->entry = newUser;
    r->leftNode = NULL;
    r->rightNode = NULL;

    comp++; //comparação do if
    if( p == NULL ){ root = r; } // árvore vazia
    else {
        if( newUser.id < p->entry.id ){ p->leftNode = r; } //insercao a esquerda
        else{ p->rightNode = r; } //incercao a direita
        comp++;
    }
    return comp;
}



// remocao de tupla
bool BSTID::remove(TreeEntry x){
    TreePointer t = root;
    //Localizar o x
    search(x, t);// busca do elemento
    if (t == NULL){
        std::cerr << "Elemento não encontrado" << std::endl;
        return false; //elemento não esta na arvore

    } else { //removendo o elemento
        //Remover
        TreePointer q;
        q = t; //q é o pai de tt
            
        if( q->leftNode == NULL ){ t = q->rightNode; } // reconectando a subarvore pelo lado direito
        else if( q->rightNode == NULL ){ t = q->leftNode; } // reconectando a subarvore pelo lado esquerdo

        else{//se possue as 2 subarvores, busca o sucessor
            removeMin(q, q->rightNode);
            delete q;
        }
        return true; // elemento removido

    }
}

//buscando o sucessor (3 caso de remocao)
void BSTID::removeMin(TreePointer &q, TreePointer &r){
    //recursao para busca do menor elemento da arvore depois de t, indo para a esquerda
    if( r->leftNode != NULL ) {removeMin(q, r->leftNode); }
    else { //chegou ao nó sucessor de t
        q->entry = r->entry;
        q = r;
        r = r->rightNode;
    }
}

