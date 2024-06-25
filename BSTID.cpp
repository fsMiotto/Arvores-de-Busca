#include "BSTID.h"

//inicializando
BSTID::BSTID(){ 
    root == NULL;
    float MediaComp = 0;
    int QuantUsers = 0;
    int Altura = 0;
    int folhas = 0; 
}

void BSTID::altura_e_folhas(){
    if (root == NULL){
        this->Altura = 0; // arvore vazia
        this->Folhas = 0; // arvore vazia

    } else{
        this->Altura = altura_e_folhas(root);
    }
}

int BSTID::altura_e_folhas(TreePointer& p){
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
User BSTID::search(TreeEntry x){
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
            return -2; //elemento ja esta na arvore
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
    this->QuantUsers += 1;

    comp++; //comparação do if
    if( p == NULL ){ root = r; } // árvore vazia
    else {
        if( newUser.id < p->entry.id ){ p->leftNode = r; } //insercao a esquerda
        else{ p->rightNode = r; } //incercao a direita
        comp++;
    }

    altura_e_folhas(); // atualiza a nova altura
    this->MediaComp = (this->MediaComp*this->QuantUsers + comp) / this->QuantUsers; //atualizando a média de comparações
    return comp;
}

//metodo publico de remocao
void BSTID::remove(TreeEntry x){
    if(remove(x, root)){
        std::cout << "\n Paciente removido" << std::endl; 
    } else{
        std::cout << "\n falha ao remover o paciente" << std::endl;
    }
}

// remocao de tupla
bool BSTID::remove(TreeEntry x, TreePointer &p){

    //verificando se oelemnto existe
    if (p == NULL){
        std::cout << "\n falha ao remover o paciente" << std::endl;
        return false; //elemento não esta na arvore
    }

    //Localizar o x
    if( x < p->entry.id ){ return remove(x, p->leftNode); } // vai para esquerda
    else if( x > p->entry.id ){ return remove(x, p->rightNode); } // vai para direita
    
    else { //removendo o elemento
        //Remover
        TreePointer q;
        q = p; //q é o pai de p
            
        if( q->leftNode == NULL ){ p = q->rightNode; } // reconectando a subarvore pelo lado direito
        else if( q->rightNode == NULL ){ p = q->leftNode; } // reconectando a subarvore pelo lado esquerdo

        else{//se possue as 2 subarvores, busca o sucessor
            removeMin(q, q->rightNode);
        }

        delete q;
        this->QuantUsers -= 1; // elemento removido
        return true;
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

