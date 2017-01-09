#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <utility>
#include "dirent.h"
#include "gera_endereco.h"
using namespace std;


class adjacencias {
	vector<string> enderecos;
	vector<string> linhas;
	vector<string> palavras;
	vector<pair<string, string>> adj_nome;
	vector <pair<string, int>> id_vertices; // email e id ( rotulo e indice do vertice)
	vector <pair<int, int>> adj; // (adjacencia 'i' e 'j' )
public:
	//______ MODO RÁPIDO! Carrega o arquivo limpo com todos os emails-vertices e adj(vertice-vertice)
	adjacencias(string id_vertices, string adj);
	void quebra_linha(string file_id_vertices, string file_adj);
	//_______

	//_______ funcoes externas
	int quantidade_vertices();
	int quantidade_adj();

	string nome_vertice(int vertice);

	int retorna_from(int i);
	int retorna_to(int i);

	//__ funcoes usadas em outras classes
	static void heapsort(vector < pair<int, int>> & pair);



	//passa e vetor de enderecos para abrir cada arquivo
	adjacencias(vector<string> _enderecos);

	//funcao chamada no construtor que realiza as operacoes
	void armazena_adjacencias();

	//quebra linhas em palavras e retira caracteres indesejados : retirar =", :|\t\n";
	vector<string> tokenizer(vector<string> linhas, string retirar);


	//verifica se a string existe no pair que guarda rótulo-id
	bool existe(vector<pair<string, int>> nomes, string verifica);

	// retorna o valor inteiro do vertice rótulo "xxx"
	int vertice_int(vector<pair<string, int>> id_vertices, string email);

	void heapsort(vector<string> & vector);
	void retira_repetidos(vector<string> & nomes);
	int busca_binaria(string verificador, vector<pair<string, int>> dicionario);

	void imprime_id_vertices(vector<pair<string, int>> vector);
	void imprime_adj(vector<pair<int, int>> vector);
	void imprime_adj_nome(vector<pair<string, string>> vector);
	void imprime_vector(vector<string> vector);

	void salva_arquivos();


	~adjacencias();
};

