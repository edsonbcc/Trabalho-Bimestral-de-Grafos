#include "lista_encadeada.h"

//métodos trabalho bimestral grafo

void listaSE::atualiza_adjacencia(int chave) {
	no * p = primeiro;
	while (p != NULL  && p->dado < chave)
		p = p->prox;
	if (p == NULL)
		p->peso = 8888888;
	else if (p->dado != chave)
		p->peso = 8888888;
	else
		p->peso = p->peso + 1;
}


no::no(int e, int peso) {
	dado = e; // o dado desse novo no recebe 'e' o dado
	prox = NULL; // p->prox é apontado para null
	this->peso = peso;
}
int no::get_dado() {
	return this->dado;
}

void no::set_dado(int DADO) {
	this->dado = DADO;
}

void no::set_no(no *PROX) {
	this->prox = PROX;
}

no * no::get_no() {
	return this->prox;
}

no::~no() {}

listaSE::listaSE() {
	primeiro = ultimo = NULL;
}
listaSE::~listaSE() {}

no * listaSE::aloca_no(int numero, int peso) {
	no *p = new no(numero, peso); // criando p dinamicamente
	return p;
}

bool listaSE::vazia() {
	if (primeiro == NULL)
		return true;
	else
		return false;
}

void listaSE::insere_primeiro(int e, int peso) {
	no *p = aloca_no(e, peso); // aloca dinamicamente  p
	if (vazia()) { // verifica se a lista ainda nao tem nenhum elemento
		primeiro = p; // caso nao tenha o l->pri, ultimo irao apontar para p pois 'p' é primeiro e ultimo
		ultimo = p;
	}
	else { // caso ele nao seja primeiro 
		p->prox = primeiro; //o p->prox(criado aponta para onde l->primeiro (primeiro elemento)
		primeiro = p; // l->primeiro aponta para 'p'
	}
}

void listaSE::insere_ultimo(int e, int peso) {
	if (vazia()) // verifica se a listaSE esta vzia
		insere_primeiro(e, peso); // caso esteja vazia ele chama insere primeiro pq ele sera o primeiro e ultimo
	else // caso contrario ele vai chamar a funcao insere_depois passando l->ultimo
		ultimo = insere_depois(ultimo, e, peso);
}

no * listaSE::insere_depois(no *p, int e, int peso) {
	no *q = aloca_no(e, peso); // cria dinamicamente q 
	q->prox = p->prox; // q->prox aponta para onde p->prox aponta, no caso o fim
	p->prox = q; // o p->prox que apontava para Null agora aponta para q se tornando o penultimo elemento
	return q; // retorna q para funcao
}

void listaSE::insere_em_ordem(int e, int peso) {
	if (vazia())
		insere_primeiro(e, peso);
	else {
		if (e < primeiro->dado)
			insere_primeiro(e, peso);
		else if (e >= ultimo->dado)
			insere_ultimo(e, peso);
		else {
			no *p, *q;
			p = q = primeiro;
			while (p->dado < e) {
				q = p;
				p = p->prox;
			}
			insere_depois(q, e, peso);
		}
	}
}

void listaSE::imprime() {
	if (!vazia()) {
		no* p = primeiro;
		do {
			cout << "[j: " << p->dado << ", P: " << p->peso << "]->";
			p = p->prox;
		} while (p != NULL);
		//cout << endl;
	}
	else
		return; //cout << "Lista Encadeada vazia, impossivel imprimir\n";
}

void listaSE::retorna_top_send() {
	if (!vazia()) {
		no* p = primeiro;
		do {
			cout << "[j: " << p->dado << ", P: " << p->peso << "]->";
			p = p->prox;
		} while (p != NULL);
		//cout << endl;
	}
	else
		return; //cout << "Lista Encadeada vazia, impossivel imprimir\n";
}

int listaSE::retira_primeiro() {
	if (!vazia()) {
		int aux_l1 = primeiro->dado;
		primeiro = primeiro->prox;
		 cout << "Dado retirado = " << aux_l1 << endl;
		return aux_l1;
	}
	else
		cout << "Lista encadeada vazia, impossivel retirar primeiro\n";
	return 0;
}

int listaSE::retira_ultimo() {
	if (!vazia()) {
		if (primeiro->prox == NULL)
			retira_primeiro(); // quando estiver somente um elemento; 
		else {
			int aux_l1 = ultimo->dado;
			ultimo = retira_depois(ultimo);
			cout << "Dado retirado = " << aux_l1 << endl;
			return aux_l1;
		}
	}// verifica se a listaSE  nao esta vzia
	else
		cout << "Lista encadeada vazia, impossivel retirar ultimo\n";
	return 0;
}

no* listaSE::retira_depois(no *p) {
	no *q = primeiro;	// ponteiro p aponta para l->primeiro
	no *r = primeiro;

	if (p->prox == primeiro->prox) {
		retira_primeiro();
		return 0;
	}

	while (q->prox != p->prox) {//enquanto em nao encontrar o ponteiro p 
		r = q;
		q = q->prox; // eu incremento q
	}


	if (p->prox == NULL) { // se chegar a null quer dizer que ele esta no ultima possicao
		ultimo = r; // 
		r->prox = NULL;
		// delete[] p;
		cout << "lista 1: ";
		return r;
	}

	else {
		r->prox = q->prox;
		// delete[] p;
		return r;
	}
}

int listaSE::ultimo_elemento() {
	if (!vazia())
		return ultimo->dado;
}

int listaSE::primeiro_elemento() {
	if (!vazia())
		return primeiro->dado;
}

int listaSE::procura(int chave) {
	no * p = primeiro;
	while (p != NULL  && p->dado < chave)
		p = p->prox;
	if (p == NULL)
		return 0;
	else if (p->dado != chave)
		return 0;
	else
		return 1;
}

int listaSE::retorna_peso(int chave) { // se o nó nao existir retorna infinito, se existir retorna seu peso
	no * p = primeiro;
	while (p != NULL  && p->dado < chave)
		p = p->prox;
	if (p == NULL)
		return 999999;
	else if (p->dado != chave)
		return 999999;
	else
		return p->peso;
}

double listaSE::retorna_peso_inverso(int chave) {
	no * p = primeiro;
	while (p != NULL  && p->dado < chave)
		p = p->prox;
	if (p == NULL)
		return  999999;
	else if (p->dado != chave)
		return  999999;
	else
		return 1.0 / p->peso;
}

int listaSE::retorna_peso2(int chave) { // se o nó nao existir retorna infinito, se existir retorna seu peso
	no * p = primeiro;
	while (p != NULL  && p->dado < chave)
		p = p->prox;
	if (p == NULL)
		return 0;
	else if (p->dado != chave)
		return 0;
	else
		return p->peso;
}

bool listaSE::retira_elemento(int chave) {
	if (!procura(chave)) // caso elemento n existe
		return 0;

	no * p = primeiro;
	no * ant = p;

	while (p != NULL && p->dado != chave) {
		ant = p;
		p = p->prox;
	}

	if (p == NULL)
		return 0;

	if (p->dado == chave) {
		if (p == primeiro)
			retira_primeiro();
		else if (p == ultimo)
			retira_ultimo();
		else {
			ant->prox = p->prox;
			p->prox = NULL;
		}
	}
	return 1;
}

