#include "BSTName.h"

//inicializando
BSTName::BSTName(){ 
    root == NULL;
    float MediaComp = 0;
    int QuantUsers = 0;
    int Altura = 0;
    int folhas = 0; 
}

void BSTName::altura_e_folhas(){
    if (root == NULL){
        this->Altura = 0; // arvore vazia
        this->Folhas = 0; // arvore vazia

    } else{
        this->Altura = altura_e_folhas(root);
    }
}

int BSTName::altura_e_folhas(TreePointer& p){
    if (p->leftNode == nullptr && p->rightNode == nullptr){
        this->Folhas += 1; // Incrementa a contagem de folhas
        return 1; // A altura desta subárvore é 1
    } else{
        int leftHeight = altura_e_folhas(p->leftNode);
        int rightHeight = altura_e_folhas(p->rightNode);
        return 1 + std::max(leftHeight, rightHeight); // A altura é 1 + maior altura das subárvores
    }
}

//Esse método de procura acha o elemento na arvore e retorna a estrutura, usado na main para buscar e imprimir o usuário
User::User BSTName::search(TreeEntry x){
    TreePointer t=root;
    search(x, t);

    if (t != NULL) {
        return t->entry; // se encontrou, retorna a estrutura
    } else {
        User userEmpty; 
        return userEmpty; // se não encontrou, retorna um User vazio
    }
}

//Esse método de procura acha o elemento na arvore, usado em métodos para reciclar codigo
void BSTName::search(TreeEntry x, TreePointer &t){
    while ( t != NULL && t->entry.name != x ){
        if( x < t->entry.name ){ t = t->leftNode; } // procurar na subárvore esquerda
        else { t = t->rightNode; } // procurar na subárvore direita
    }
}

//metodo de inserção
int BSTName::insert(User newUser) { 
    TreePointer p=NULL, q=root, r;
    int comp = 0; //comparações

    r = new TreeNode; //instanciando novo elemento

    if( r == NULL ){     //verificacao de memoria
        return -1;
    }
    comp++; //comparacao da verificacao de memoria
     
    while ( q != NULL ){ //busca para insert
        if (q->entry.name == newUser.name){
            return -2; //elemento ja esta na arvore
        }

        p = q; // p é o pai de q
        if( newUser.name < q->entry.name ){ q = q->leftNode; }
        else{ q = q->rightNode; }
        comp+= 3;// comparacao dos 2 if e do while
    }
    comp++; //comparação do while quando não entra em loop e não é contabilizada

    //Montando o nó
    r->entry = newUser;
    r->leftNode = NULL;
    r->rightNode = NULL;
    this->QuantUsers += 1;

    comp++; //comparação do if
    if( p == NULL ){ root = r; } // árvore vazia
    else {
        if( newUser.name < p->entry.name ){ p->leftNode = r; } //insercao a esquerda
        else{ p->rightNode = r; } //incercao a direita
        comp++;
    }

    altura_e_folhas(); // atualiza a nova altura
    this->MediaComp = (this->MediaComp*this->QuantUsers + comp) / this->QuantUsers; //atualizando a média de comparações
    return comp;
}



// remocao de tupla
bool BSTName::remove(TreeEntry x){
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

        this->QuantUsers -= 1;
        return true; // elemento removido

    }
}

//buscando o sucessor (3 caso de remocao)
void BSTName::removeMin(TreePointer &q, TreePointer &r){
    //recursao para busca do menor elemento da arvore depois de t, indo para a esquerda
    if( r->leftNode != NULL ) {removeMin(q, r->leftNode); }
    else { //chegou ao nó sucessor de t
        q->entry = r->entry;
        q = r;
        r = r->rightNode;
    }
}

