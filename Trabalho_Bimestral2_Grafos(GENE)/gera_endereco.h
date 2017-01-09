#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include "dirent.h"
using namespace std;


class gera_endereco{
private:
	vector<string> pastas;
	vector<string> sub_pastas;
	vector<string> final;
	vector<string> endereco_final;
	string caminho;
public:

	gera_endereco();
	gera_endereco(string _caminho);
	void lista_pastas(string _caminho);

	vector<string> gerador();

	bool existe(string verificador, vector<string> pastas);
	void imprime(vector<string> vector);
	void salva_arquivo();
	~gera_endereco();

};

