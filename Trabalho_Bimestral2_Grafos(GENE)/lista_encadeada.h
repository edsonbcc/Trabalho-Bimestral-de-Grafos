#pragma once
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

class no {
	friend class listaSE;
private:
	int dado; // DADO digitado
	int peso;
	no *prox; // ponteiro no pra prox
public:
	no(int e, int peso);
	void set_dado(int DADO);
	int get_dado();
	void set_no(no *PROX);
	no * get_no();
	~no();
};

class listaSE {
private:
	no * primeiro;
	no * ultimo;
public:
	listaSE();
	~listaSE();
	no * aloca_no(int numero, int peso);
	bool vazia(); // verifica se esta vazia
	void insere_primeiro(int e, int peso);
	void insere_ultimo(int e, int peso);
	no * insere_depois(no *p, int e, int peso);
	void insere_em_ordem(int e, int peso);
	void imprime();
	int retira_primeiro(); // retira o primeiro no
	int retira_ultimo(); // retira o ultimo no
	no* retira_depois(no *p); // retira um determinado no passado no* p
	int ultimo_elemento(); // retorna o ultimo elemento
	int primeiro_elemento(); // retorna o primeiro elemento
	int procura(int chave);
	bool retira_elemento(int chave);



	//métodos trabalho bimestral
	void atualiza_adjacencia(int chave);
	int retorna_peso(int chave);
	double retorna_peso_inverso(int chave);
	int retorna_peso2(int chave);

	//nao usada
	void retorna_top_send();


	
	
};

