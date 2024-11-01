#include "AVLName.h"

//inicializando
AVLName::AVLName(){ 
    root == NULL;
    float MediaComp = 0;
    float MediaRotacao = 0;
    int QuantUsers = 0;
    int Altura = 0;
    int folhas = 0; 
}

void AVLName::altura_e_folhas(){
    if (root == NULL){
        this->Altura = 0; // arvore vazia
        this->Folhas = 0; // arvore vazia

    } else{
        this->Altura = altura_e_folhas(root);
    }
}

int AVLName::altura_e_folhas(TreePointer& p){
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
User AVLName::search(TreeEntry x){
    TreePointer t=root;
    while ( t != NULL && t->entry.name != x ){
        if( x < t->entry.name ){ t = t->leftNode; } // procurar na subárvore esquerda
        else { t = t->rightNode; } // procurar na subárvore direita
    }

    if (t != NULL) {
        return t->entry; // se encontrou, retorna a estrutura
    } else {
        User userEmpty; 
        return userEmpty; // se não encontrou, retorna um User vazio
    }}

int AVLName::insert(User newUser){ // método público
    bool h = false;// inicio do método de incerção com h = false para recursao
    return insert(newUser, root, h);;
}


int AVLName::insert(User newUser, TreePointer &pA, bool &h) {
    TreePointer pB, pC;
    int comp = 0, rotacao = 0; //comparações e rotações

    if(pA == NULL){ // inserir
        pA = new TreeNode; //criando um nó
        if( pA == NULL ){ //verificacao de memoria
            return -1;//não tem memória
        }
        comp++;//comparação se é nulo

        h = true; //liberando para rotacao
        pA->entry = newUser;
        pA->leftNode = pA->rightNode = NULL;
        pA->bal = 0;
        comp++;//comparação só do do if
        this->QuantUsers++; //Quantidade de Usuarios aumentou
    }

    else if(newUser.name < pA->entry.name){ //indo para subarvore esquerda
        comp += 2; //comparação do if + else if
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
                    
                    rotacao++;
                    comp++; // comparação do if (linha 56)
                    pA->bal = 0; 
                    h = false; //arvore balanceada, fechando o balanceamento
            } //fim switch
            comp++;//comparação do switch
        }
        comp++;//comparação do if (linha 42)
    }

    else if(newUser.name > pA->entry.name){ //indo para subarvore direita
        comp += 3; //comparação do if + 2 else if
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

                    rotacao++;
                    comp++; // comparação do if (linha 99)
                    pA->bal = 0; 
                    h = false; //arvore balanceada, fechando o balanceamento
            } //fim switch
            comp++;//comparação do switch
        }
        comp++; //comparação do if (linha 86)
    }

    else{// elemento encontrado
        return -2;
    }

    altura_e_folhas(); // atualiza a nova altura
    this->MediaRotacao = (this->MediaRotacao*this->QuantUsers + rotacao) / this->QuantUsers; //atualizando a média de rotações
    this->MediaComp = (this->MediaComp*this->QuantUsers + comp) / this->QuantUsers; //atualizando a média de comparações
    return comp;// finalizandoo e retornando a quantidade de comparações desta inserção
}

//metodo de remocao publico
void AVLName::remove(TreeEntry x){
    bool h = false;
    if(remove(x, root, h)){
        std::cout << "\n Paciente removido" << std::endl; 
    } else{
        std::cout << "\n falha ao remover o paciente" << std::endl;
    }
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
        altura_e_folhas(); //atualizar a nova altura
        this->QuantUsers--; //Quantidade de Usuarios diminuiu
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