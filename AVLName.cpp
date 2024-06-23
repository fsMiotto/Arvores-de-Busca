#include "AVLName.h"


//Esse método de procura acha o elemento na arvore e retorna a estrutura, usado na main para buscar e imprimir o usuário
AVLName::TreePointer AVLName::search(TreeEntry x){
    TreePointer t=root;
    while ( t != NULL && t->entry.name != x ){
        if( x < t->entry.name ){ t = t->leftNode; } // procurar na subárvore esquerda
        else { t = t->rightNode; } // procurar na subárvore direita
    }
    return t; //se t->entry == x retorna a estrutura, se não retorna NULL (verificar estrutura antes de usar)
}

void AVLName::insert(User newUser){ // método público
    bool h = false;// inicio do método de incerção com h = false para recursao
    insert(newUser, root, h);
}


void AVLName::insert(User newUser, TreePointer &pA, bool &h) {
    TreePointer pB, pC;

    if(pA == NULL){ // inserir
        pA = new TreeNode; //criando um nó
        if( pA == NULL ){ //verificacao de memoria
            std::cout << “Sem memória” << std::endl;
            abort();
        }

        h = true; //liberando para rotacao
        pA->entry = newUser;
        pA->leftNode = pA->rightNode = NULL;
        pA->bal = 0;
    } 

    else if(newUser.name < pA->entry.name){ //indo para subarvore esquerda
        insert(newUser, pA->leftNode, h); //recurao para busca e verificacao do balanceamento voltando
        if(h){ // h = true, verificando balanceamento
            switch (pA->bal){
                case -1: // nó balanceado
                    pA->bal = 0; //atribuindo novo valor
                    h = false; // não precisa do balanceamento (altura da subarvore inalterada)
                    break;

                case 0: //nó balanceado e altura da subarvore alterada
                    pA->bal = +1; //atribuindo novo valor 
                    break;

                case +1: // nó desbalanceado (vai para +2)
                    pB = pA->leftNode;

                    if(pB->bal == +1){ // rotação LL
                        pA->leftNode = pB->rightNode; 
                        pB->rightNode = pA;
                        pA->bal = 0; 
                        pA = pB;

                    } else{ // rotação LR
                        pC = pB->rightNode; 
                        pB->rightNode = pC->leftNode;
                        pC->leftNode = pB; 
                        pA->leftNode = pC->rightNode;
                        pC->rightNode = pA;
                        pA->bal = (pC->bal == +1) ? -1 : 0;  // ajustando os balanceamentos
                        pB->bal = (pC->bal == -1) ? +1 : 0;  // ajustando os balanceamentos
                        pA = pC;
                    }

                    pA->bal = 0; 
                    h = false; //arvore balanceada, fechando o balanceamento
            } //fim switch
        }
    }

    else if(newUser.name > pA->entry.name){ //indo para subarvore direita
        insert(newUser, pA->rightNode, h); //recurao para busca e verificacao do balanceamento voltando
        if(h){ // h = true, verificando balanceamento
            switch (pA->bal){
                case +1: // nó balanceado
                    pA->bal = 0; //atribuindo novo valor
                    h = false; // não precisa do balanceamento (altura da subarvore inalterada)
                    break;

                case 0: //nó balanceado e altura da subarvore alterada
                    pA->bal = -1; //atribuindo novo valor
                    break; 

                case -1: // nó desbalanceado (vai para +2)
                    pB = pA->rightNode;
                    
                    if(pB->bal == -1){ // rotação RR
                        pA->rightNode = pB->leftNode; 
                        pB->leftNode = pA;
                        pA->bal = 0;
                        pA = pB;

                    } else{ // rotação RL
                        pC = pB->leftNode; 
                        pB->leftNode = pC->rightNode;
                        pC->rightNode = pB; 
                        pA->rightNode = pC->leftNode;
                        pC->leftNode = pA;
                        pA->bal = (pC->bal == -1) ? +1 : 0;  // ajustando os balanceamentos
                        pB->bal = (pC->bal == +1) ? -1 : 0;  // ajustando os balanceamentos
                        pA = pC;
                    }
                    pA->bal = 0; 
                    h = false; //arvore balanceada, fechando o balanceamento
            } //fim switch
        }
    }

    // elemento encontrado
    else{ std::cerr << "Usuário existente" << std::endl; } 
}

// metodo de remocao
bool AVLName::remove(TreeEntry x, TreePointer &p, bool &h){
    bool removeu;

    if(p == NULL){ return false; } // x não encontrado

    if(x < p->entry.name){ // indo para subarvore esquerda
        removeu = remove(x, p->leftNode, h); //recursividade para busca, remocao e rotacao
        if(h){ rotacaoR(p, h); } //faz a rotacao caso desbalanceado
        return removeu; //retorna se o elemento foi removido ou não
    }
    else if(x > p->entry.name){ // indo para subarvore esquerda
        removeu = remove(x, p->rightNode, h); //recursividade para busca, remocao e rotacao
        if(h){ rotacaoR(p, h); } //faz a rotacao caso desbalanceado
        return removeu; //retorna se o elemento foi removido ou não

    } else { // remover p-> 
        TreePointer q;
        q = p; // guarda o pai do elemento
        if(q->rightNode == NULL){ //não tem subarvore direita, entao sobe a esquerda
            p = q->leftNode;
            h = true; //verificar se precisa balancear
        }
        else if(q->leftNode == NULL){ //não tem subarvore esquerda, entao sobe a direita
            p = q->rightNode;
            h = true; //verificar se precisa balancear
        }
        else{ 
            removeMin(q, q->rightNode, h); //3 caso de remocao
            if(h){ rotacaoL(p, h); } //rotacao se necessario
        }

        delete q; //removendo elemento
        return true; // x removido
    }
}

// 3 caso da remocao
void AVLName::removeMin(TreePointer &q, TreePointer &r, bool &h){
    //busca recursiva (procurando o elemento sucessor) 
    if(r->leftNode != NULL){ //preferencia para esquerda para achar o elemento mais baixo da subarvore
        removeMin(q, r->leftNode, h); //recursao
        if(h){ rotacaoR(r, h); } //rotacao se precisar

    } else{ // realizando a atribuicao do sucessor
        q->entry = r->entry;
        q = r;
        r = r->rightNode;
        h = true; //verificar balanceamento
    }
}

// Rotacao na subarvore direita
void AVLName::rotacaoR(TreePointer &pA, bool &h){
    TreePointer pB, pC; // Ponteiros para auxiliar a rotacao
    int balB, balC; //balanceamento dos nós

    switch(pA->bal){ 
        case +1: // nó balanceado
            pA->bal = 0; //atribuindo novo valor
            h = false; // não precisa do balanceamento (altura da subarvore inalterada)
            break;
            
        case 0: //nó balanceado e altura da arvore alterada
            pA->bal = -1; //atribuindo novo valor
            break;

        case -1: 
            pB = pA->rightNode; 
            balB = pB->bal;

            if(balB <= 0){ // rotacao RR
                pA->rightNode = pB->leftNode;
                pB->leftNode = pA;

                if(balB == 0){ 
                    pA->bal = -1; 
                    pB->bal = +1; 
                    h = false; 
                } else{ 
                    pA->bal = 0; 
                    pB->bal = 0; 
                }
                pA = pB;

            } else{ // rotacao RL
                pC = pB->leftNode; balC = pC->bal;
                pB->leftNode = pC->rightNode;
                pC->rightNode = pB;
                pA->rightNode = pC->leftNode;
                pC->leftNode = pA;
                pA->bal = (balC == -1) ? +1 : 0;  // ajustando os balanceamentos
                pB->bal = (balC == +1) ? -1 : 0;  // ajustando os balanceamentos
                pA = pC; pC->bal = 0;
            }
            break;
    }
}

// Rotacao na subarvore esquerda
void AVLName::rotacaoL(TreePointer &pA, bool &h){
    TreePointer pB, pC;
    int balB, balC;
    // subarvore direita teve altura alterada
    switch(pA->bal){ 
        case -1: pA->bal = 0; break;
        case 0: pA->bal = +1; h = false; break;
        case +1:
            pB = pA->leftNode; balB = pB->bal;

            if(balB >= 0){ // rotacao LL
                pA->leftNode = pB->rightNode;
                pB->rightNode = pA;

                if(balB == 0){ 
                    pA->bal = +1; 
                    pB->bal = -1; 
                    h = false; 
                } else{ 
                    pA->bal = 0; 
                    pB->bal = 0; 
                }
                pA = pB;
                
            } else{ // rotacao LR 
                pC = pB->rightNode; balC = pC->bal;
                pB->rightNode = pC->leftNode;
                pC->leftNode = pB;
                pA->leftNode = pC->rightNode;
                pC->rightNode = pA;
                pA->bal = (balC == +1) ? -1 : 0;  // ajustando os balanceamentos
                pB->bal = (balC == -1) ? +1 : 0;  // ajustando os balanceamentos
                pA = pC; pC->bal = 0;
            }
            break;
    }
}