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
#include "Grafo.h"
using namespace std;



class trata_arquivo {
private:
	string nome_arquivo;
	vector<string> enderecos;
	vector<string> palavras_legenda, linhas;
	vector<pair<string, string>> adj_nome;
	vector <pair<string, int>> id_vertices; // email e id ( rotulo e indice do vertice)
	vector <pair<int, int>> adj; // (adjacencia 'i' e 'j' )
public:
	trata_arquivo(vector<string> _enderecos);
	trata_arquivo(string _nome_arquivo);
	trata_arquivo(string id_vertices, string adj);
	//trata_arquivo(vector<string> _enderecos); //passa e vetor de enderecos para abrir cada arquivo

	void quebra_linha(string file_id_vertices, string file_adj);
	
	int quantidade_vertices();
	int quantidade_adj();

	string nome_vertice(int vertice);

	int retorna_from(int i);
	int retorna_to(int i);

	vector<string> legenda();
	static vector<string> tokenizer(vector<string> linhas, string retirar);
	vector<string> tokenizer(string linhas, string retirar);
	grafo * armazena_adjacencias();
	
	void salva_arquivos();

	void imprime_id_vertices(vector<pair<string, int>> vector);
	void imprime_adj(vector<pair<int, int>> vector);
	void imprime_adj_nome(vector<pair<string, string>> vector);
	void imprime_vector(vector<string> vector);

	static void heapsort(vector < pair<int, int>> & pair);
	void heapsort(vector<string> & vector);
	void retira_repetidos(vector<string> & nomes);
	int busca_binaria(string verificador, vector<pair<string, int>> dicionario);
	

	~trata_arquivo();
};





