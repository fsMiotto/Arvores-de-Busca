#include "BSTBirthday.h"


//Esse método de procura acha o elemento na arvore e retorna a estrutura, usado na main para buscar e imprimir o usuário
BSTBirthday::TreePointer BSTBirthday::search(TreeEntry x){
    TreePointer t=root;
    search(x, t);
    return t; //se t->entry == x retorna a estrutura, se não retorna NULL (verificar estrutura antes de usar)
}

//Esse método de procura acha o elemento na arvore, usado em métodos para reciclar codigo
void BSTBirthday::search(TreeEntry x, TreePointer &t){
    while ( t != NULL && compareDates(x, t->entry.date) != 0 ){
        if( compareDates(x, t->entry.date) == -1 ){ t = t->leftNode; } // procurar na subárvore esquerda
        else { t = t->rightNode; } // procurar na subárvore direita
    }
}

//metodo de inserção
int BSTBirthday::insert(User newUser) { 
    TreePointer p=NULL, q=root, r;
    int comp = 0; //comparações

    r = new TreeNode; //instanciando novo elemento

    if( r == NULL ){     //verificacao de memoria
        std::cout << “Sem memória” << std::endl;
        abort();
    }
    comp++; //comparacao da verificacao de memoria
     
    while ( q != NULL ){ //busca para insert
        if (compareDates(newUser.date, q->entry.date) == 0){
            return 0; //elemento ja esta na arvore
        }

        p = q; // p é o pai de q
        if( compareDates(newUser.date, q->entry.date) == -1 ){ q = q->leftNode; }
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
        if(compareDates(newUser.date, p->entry.date) == -1){ p->leftNode = r; } //insercao a esquerda
        else{ p->rightNode = r; } //incercao a direita
        comp++;
    }
    return comp;
}



// remocao de tupla
bool BSTBirthday::remove(TreeEntry x){
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
void BSTBirthday::removeMin(TreePointer &q, TreePointer &r){
    //recursao para busca do menor elemento da arvore depois de t, indo para a esquerda
    if( r->leftNode != NULL ) {removeMin(q, r->leftNode); }
    else { //chegou ao nó sucessor de t
        q->entry = r->entry;
        q = r;
        r = r->rightNode;
    }
}

int BSTBirthday::compareDates(const std::tm& tm1, const std::tm& tm2) {
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&tm1));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&tm2));
    if (time1 > time2){ return 1; }
    else if (time1 < time2){ return -1; }
    else{ return 0; } // As datas são iguais
}
