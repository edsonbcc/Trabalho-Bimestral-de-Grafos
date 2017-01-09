#pragma once
#include "lista_encadeada.h"

#include <iostream>
using namespace std;
#include <string> // pra dar cout com string
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <utility>


class vertice {
private:
	string nome;
public:
	vertice();
	void set_nome(string nome);
	string get_nome();
	~vertice();

};

class grafo {
private:
	int tam; // tam do grafo
	listaSE * l; // lista de adjacencia
	vertice * vertices; // vertices com rotulo
	int **fechamento; // matriz de fechamento
	const bool MEMBRO = true; // dijkstra
	const bool NAOMEMBRO = false; // dijkstra
	int INFINITO = 999999; 
	int *caminho; // dijkstra 
	int *componente; // utilizado para verificar a estrutura dos componentes
	int id_componente; // possui a quantidade de componentes
	vector<string> stop_words;
public:
	grafo(int TAM); // construtor principal
	grafo(string nome_arquivo); // modo pajek
	grafo(int TAM, int arestas, char conexo, char bidirecionado);
	static grafo * fabrica_grafo();
	void grafo_aleatorio_conexo(int arestas);
	void grafo_aleatorio_conexo_nao_direcionado(int arestas);
	void grafo_aleatorio_desconexo(int arestas);
	bool max_direcionado_desconexo(int arestas);
	bool max_nao_direcionado_desconexo(int arestas);
	void grafo_aleatorio_desconexo_nao_direcionado(int arestas);
	
	void cria_adjacencia(int i, int j, int P);
	void cria_adjacencia_bidirecional(int i, int j, int P);
	void remove_adjacencia(int i, int j);
	void remove_adjacencia_bidirecional(int i, int j);
	void imprime_adjacencia();
	void imprime_adjacencia_nao_vazia();
	bool indice_valido(int i, int j);
	void seta_informacao(int i, string V);
	int adjacentes(int i, int * adj);
	int adjacentes(int i);
	int adjacentes(int i, vector<int> & adj); // com vector 
	int top_adjacentes(int i, vector<pair<int, int>> & adj_peso);
	int forma_frase(int i, int tamanho_frase);
	int adjacentes_bidirecional(int i, vector<int> & adj); //adj ij e ji
	bool vertice_nulo(int vertice); // verifica se um vertice possui pelo menos uma adj

	int email_to_id(string email); // entra com email e retorna a id desse email
	string id_to_email(int id_vertice); // entrada com id_vertice e retorna email equivalente
	int get_tam();
	
	//árvore geradora mínima
	//int ciclico(int origem, vector<int> & visitados);

	//trabalho bimestral 2
	void grava_pajek(); // gera arquivo pajek
	void separador(string nome_arquivo, vector<string> &arg0, vector<string> &arg1, vector<string> &arg2, vector<string> &pajek);

	bool conexo();
	bool componentes(); // retorna false se grafo o grafo tiver + que 1 componente

	float centralidade_de_proximidade(int i);
	float centralidade_de_intermediacao(int x);
	int menor_distancia(int s, int t, vector<int> &caminho_saida);
	int menor_distancia(int s, int t);

	//funciona corretamente
	bool encontra_ciclo(int origem, vector<int>& visitados);

	bool ciclico(); // tem uma flag ciclico que se encontrar um ciclo ja sinaliza e retorna
	int busca_ciclico(int origem, vector<int> & visitados, bool * ciclico, vector<int> copia); // busca profundidade alterada
	
	
	bool euleriano();

	//prim - busca bidirecionada
	void prim(int origem);
	int busca_sem_destino(int origem,vector<int> & visitados);
	int busca_sem_destino_largura(list<int> & fila, vector<int> & visitados);

	int busca_sem_destino_direcionada(int origem, vector<int> & visitados); // profundidade

	// gera componentes do grafo
	int seta_componentes();
	void imprime_componentes();
	void zera_componente();

	//dijkstra
	int melhorCaminho(int s, int t); 
	double piorCaminho2(int s, int t);
	void imprimirDijkstra(int s, int t);

	//warshall
	void faz_fechamento();
	void imprime_fechamento();

	void top_20_sends(); // quem tem maior grau de saida e de entrada
	int quantidade_arestas();
	void maior_contato();

	// busca largura
	bool pertence(int valor, list<int> fila);
	int largura(int destino, list<int> & fila, vector<int> & visitados);
	
	// questao 5 - calcular distancia a partir de um determinado vertice
	int largura_distancias(int max_distancia, list<int> & fila, vector<int> & visitados, vector <pair<int, int>> & id_distancia);
	int busca_nivel_x(int x, vector <pair<int,int>> & id_distancia);

	//busca profundidade
	bool foi_visitado(int valor, vector<int> visitados);
	int busca_profundidade(int origem, int destino, vector<int> & visitados);
	

	bool bidirecional();
	
	//algoritmos auxiliares
	int busca_binaria(string procurado, vertice * vertices); // usado para encontrar string equivalente ao id_vertice
	int busca_binaria(int verificador, vector<pair<int, int>> dicionario);
	void heapsort(vector<pair<int, int>> & pair);
	void heapsort_second(vector<pair<int, int>> & pair);
	void heapsort(int* a, int n);
	vector<string> tokenizer(vector<string> linhas, string retirar);
	vector<string> tokenizer(string linhas, string retirar);
	void inicializa_stop_word();
	bool eh_stop_word(string palavra);
	int * inicializa_vetor();

	


	~grafo();
};

