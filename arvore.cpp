#include <iostream>
using namespace std;

// definir as cores
#define vermelho 1
#define preto 0

// estrutura dos nos
struct No {
	int valor;
	bool cor;
	No *esquerda;
	No *direita;
	No *pai;
};

// criar no
No *criarNo(int valor) {
	No *novo= new No;
	novo->valor=valor;
	novo->cor=vermelho;
	novo->esquerda=nullptr;
	novo->direita=nullptr;
	novo->pai=nullptr;
	return novo;
};

// faz uma rotação a esquerda sobre o no atual
void RotacaoEsquerda(No *&raiz, No *&atual) {
	No *painovo=atual->direita;
	atual->direita=painovo->esquerda;
	
    	if(painovo->esquerda!=nullptr) {
    		painovo->esquerda->pai=atual;
    	}
    	
	painovo->pai=atual->pai;
	
    	if(atual->pai==nullptr) {
    		raiz=painovo;
    	} else if(atual==atual->pai->esquerda) {
    		atual->pai->esquerda=painovo;
    	} else {
    		atual->pai->direita=painovo;
    	}
    	
	painovo->esquerda=atual;
	atual->pai=painovo;
}

// faz uma rotação a direita sobre o no atual
void RotacaoDireita(No *&raiz, No *&atual) {
	No *painovo=atual->esquerda;
	atual->esquerda=painovo->direita;
	if(painovo->direita!=nullptr) {
		painovo->direita->pai=atual;
	}
	painovo->pai=atual->pai;
	if(atual->pai==nullptr) {
		raiz=painovo;
	} else if(atual==atual->pai->direita) {
		atual->pai->direita=painovo;
	} else {
		atual->pai->esquerda=painovo;
	}
	painovo->direita=atual;
	atual->pai=painovo;
}

// ajusta a árvore após uma inserção de um novo nó (que é sempre vermelho).
void Ajustar(No *&raiz, No *&ponteiro) {
	
	// enquanto o ponteiro nao for a raiz e seu pai for vermelho, repete
	while(ponteiro != raiz && ponteiro->pai->cor == vermelho) {
	    
		No *avo= ponteiro->pai->pai;    // define o avô do no atual
	
		if(ponteiro->pai==avo->esquerda) {  // se o pai do no esta a esquerda
			No *tio= avo->direita;          // define o tio como outro filho do avo
		
		
		    // se o tio existe e é vermelho
			if(tio!=nullptr&&tio->cor==vermelho) {  
				avo->cor=vermelho;  // troca a cor do avo pra vermelho
				ponteiro->pai->cor=preto;   // pai e tio ficam pretos
				tio->cor=preto;
				ponteiro=avo;   // sobe o ponteiro pro avo
				
			} else {    // se o tio é preto
			
			    // se o no ta na direita, fazemos rotaçao a esquerda no pai
				if(ponteiro == ponteiro->pai->direita) {
					ponteiro=ponteiro->pai;
					RotacaoEsquerda(raiz,ponteiro);
				}
				
				ponteiro->pai->cor = preto; // pai fica preto
				avo->cor=vermelho;          // avo vermelho
				RotacaoDireita(raiz,avo);   // rotação a direita no avo
			}
			
		} else {
		    
			No *tio= avo->esquerda; // pai a direita do avo
			
			// se for vermelho
			if(tio != nullptr && tio->cor == vermelho) {
				avo->cor=vermelho;  // avo vermelho
				ponteiro->pai->cor=preto;   // pai e tio pretos
				tio->cor=preto;
				ponteiro=avo;       // aponta pro avo como novoNo
				
			} else {
				
				// tio preto ou nulo
				if(ponteiro == ponteiro->pai->esquerda) {   // se o no ta na esquerda, rotação a direita no pai
					ponteiro=ponteiro->pai;
					RotacaoDireita(raiz,ponteiro);  
				}
				
				ponteiro->pai->cor=preto;   // pai preto
				avo->cor=vermelho;          // avo vermelho
				RotacaoEsquerda(raiz,avo);  // rotação a esquerda no avo
			}
		}
	}
	
	raiz->cor = preto;      // raiz preta
}

// insere um novo valor na árvore como em uma árvore binária 
void Inserir(No *&raiz, int valor) {
	No *novo = criarNo(valor);  // cria um novo no
	No *painovo = nullptr;  // vai guardar o pai do novo no 
	No *atual = raiz;       // percorrer
	
	//enquanro nao chegamos em um lugar vazio
	while(atual!=nullptr) {
	    
		painovo=atual;  // atualiza pai com o ultimo no visto
		
		//decide se desce pela direita ou pela esquerda
		if(valor<atual->valor) {    // se o valor <
			atual=atual->esquerda;  
			
		} else if(valor>atual->valor) { // se o valor maior
			atual=atual->direita;
			
		} else {        // se for igual, sai da função
			return;
		}
	}
	
	novo->pai = painovo;  // liga o novo no ao seu pai

    
	if(painovo==nullptr) {  // se pai for nullptr, a arvore esta vazia
		raiz=novo;  // o novoNo sera raiz
		
	// coloca no menor ou maior do pai
	} else if(valor<painovo->valor) {  
		painovo->esquerda=novo;
		
	} else {
		painovo->direita=novo;
	}
	
	// chama a função ajustar para corrigir (caso houver)
	Ajustar(raiz,novo);
}

// substitui um nó original por outro nó sub (ou nullptr) na árvore.
void transplantar(No *&raiz, No *original, No *sub) {
	
	if(original->pai==nullptr) {
		raiz=sub;
		
	} else if(original==original->pai->esquerda) {
		original->pai->esquerda=sub;
		
	} else {
		original->pai->direita=sub;
	}
	

	if(sub!=nullptr) {
		sub->pai=original->pai;
	}
}

// retorna o nó com o menor valor de uma subárvore.
No *minimo(No *no) {
	while(no->esquerda!=nullptr) {
		no = no->esquerda;
	}
	return no;
}

// corrige a árvore após uma remoção, caso o nó removido era preto.
void Corrigir(No *&raiz, No *sub, No *paisub) {

	while(sub!=raiz&&(sub==nullptr||sub->cor==preto)) {
	
		if(sub==paisub->esquerda) {
			No *irmao=paisub->direita;
		
			if(irmao!=nullptr&&irmao->cor==vermelho) {
				irmao->cor=preto;
				paisub->cor=vermelho;
				RotacaoEsquerda(raiz, paisub);
				irmao=paisub->direita;
			}
		
			if((irmao->esquerda==nullptr||irmao->esquerda->cor==preto)&&(irmao->direita==nullptr||irmao->direita->cor==preto)) {
				irmao->cor=vermelho;
				sub=paisub;
				paisub=sub->pai;
				
			} else {
			
				if(irmao->direita==nullptr||irmao->direita->cor==preto) {
				
					if(irmao->esquerda!=nullptr) {
						irmao->esquerda->cor=preto;
					}
					irmao->cor=vermelho;
					RotacaoDireita(raiz,irmao);
					irmao=paisub->direita;
				}
				irmao->cor=paisub->cor;
				paisub->cor=preto;
			
				if(irmao->direita!=nullptr) {
					irmao->direita->cor=preto;
				}
				RotacaoEsquerda(raiz,paisub);
				sub=raiz;
			}
			
		} else {
			No *irmao=paisub->esquerda;
			
			if(irmao!=nullptr&&irmao->cor==vermelho) {
				irmao->cor=preto;
				paisub->cor=vermelho;
				RotacaoDireita(raiz, paisub);
				irmao=paisub->esquerda;
			}
			
			if((irmao->esquerda==nullptr||irmao->esquerda->cor==preto)&&(irmao->direita==nullptr||irmao->direita->cor==preto)) {
				irmao->cor=vermelho;
				sub=paisub;
				paisub=sub->pai;
				
			} else {
			
				if(irmao->esquerda==nullptr||irmao->esquerda->cor==preto) {
				
					if(irmao->direita!=nullptr) {
						irmao->direita->cor=preto;
					}
					irmao->cor=vermelho;
					RotacaoEsquerda(raiz,irmao);
					irmao=paisub->esquerda;
				}
				irmao->cor=paisub->cor;
				paisub->cor=preto;
			
				if(irmao->esquerda!=nullptr) {
					irmao->esquerda->cor=preto;
				}
				RotacaoDireita(raiz,paisub);
				sub=raiz;
			}
		}
	}

	if(sub!=nullptr) {
		sub->cor=preto;
	}
}

// remove um nó com o valor especificado.
void Remover(No *&raiz, int valor) {
	No *Noremovido=raiz;
	
	while(Noremovido!=nullptr&&Noremovido->valor!=valor) {
		
		if(valor<Noremovido->valor) {
			Noremovido=Noremovido->esquerda;
			
		} else {
			Noremovido=Noremovido->direita;
		}
	}
	
	if(Noremovido==nullptr) {
		return;
	}
	
	No *sucessor = Noremovido;
	bool cororiginal = sucessor->cor;
	No *sub;
	No *paisub;
	
	if(Noremovido->esquerda==nullptr) {
		sub=Noremovido->direita;
		paisub=Noremovido->pai;
		transplantar(raiz,Noremovido,Noremovido->direita);
		
	} else if(Noremovido->direita==nullptr) {
		sub=Noremovido->esquerda;
		paisub=Noremovido->pai;
		transplantar(raiz,Noremovido,Noremovido->esquerda);
		
	} else {
		sucessor=minimo(Noremovido->direita);
		cororiginal=sucessor->cor;
		sub=sucessor->direita;
		
		if(sucessor->pai==Noremovido) {
			paisub=sucessor;
			
		} else {
			transplantar(raiz,sucessor,sucessor->direita);
			sucessor->direita=Noremovido->direita;
			
			if(sucessor->direita) {
				sucessor->direita->pai=sucessor;
			}
			paisub=sucessor->pai;
		}
		
		transplantar(raiz,Noremovido,sucessor);
		sucessor->esquerda=Noremovido->esquerda;
		sucessor->esquerda->pai=sucessor;
		sucessor->cor=Noremovido->cor;
	}

	delete Noremovido;
	if(cororiginal==preto) {
		Corrigir(raiz,sub,paisub);
	}
}

// procura recursivamente um valor na árvore.
bool Buscar(No *raiz, int valor) {
    
	if(raiz == nullptr) {
		return false;
	}

	if(valor==raiz->valor) {
		return true;
	}

	if(valor<raiz->valor) {
		return Buscar(raiz->esquerda, valor);
	} else {
		return Buscar(raiz->direita, valor);
	}
}

// exibe a árvore em pré-ordem (raiz → esquerda → direita).
void exibir(No *raiz) {
	if(raiz != nullptr) {
		cout << raiz->valor << "(";
		if(raiz->cor==vermelho) {
			cout << "V";
		} else {
			cout << "P";
		}
		cout << ")";
		if(raiz->esquerda != nullptr || raiz->direita != nullptr) {
			cout << ", ";
		}
		exibir(raiz->esquerda);
		if(raiz->esquerda != nullptr && raiz->direita != nullptr) {
			cout << ", ";
		}
		exibir(raiz->direita);
	}
}
int main() {
    
	No *raiz = nullptr;
	int op = 1;
	int valor = 0;
	
	
	while(op!=0) {
	    
		cout << "---------------------------------------" << endl;
		cout << "Menu:"<<endl;
		cout << "1-Inserir:"<<endl;
		cout << "2-Remover:"<<endl;
		cout << "3-Buscar:"<<endl;
		cout << "4-Exibir:"<<endl;
		cout << "0-Sair:"<<endl;
		cin >> op;
		
		
		if(op == 1) {
			cout << "Digite o valor desejado: " << endl;
			cin >> valor;
			Inserir(raiz,valor);
		    }
		    
		if(op == 2) {
			cout << "Digite o valor que deseja remover: " << endl;
			cin >> valor;
			Remover(raiz,valor);
	    	}
	    	
		if(op == 3) {
			cout << "Digite o valor que deseje buscar : " << endl;
			cin >> valor;
			
			if(Buscar(raiz, valor)) {
				cout << valor << " encontrado!! "<< endl;
				
			} else {
				cout << valor << " nao encontrado!!" << endl;
			}
			
		  }
		
		if(op == 4) {
			exibir(raiz);
		    }
	}
	return 0;
}
