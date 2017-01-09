#include "adjacencias.h"
//MODO_ RÁPIDO: QUEBRA LINHA EM 2 PARTES E COLOCA NO PAIR CORRESPONDENTE (ID_VERTICES E ADJ)
void adjacencias::quebra_linha(string file_id_vertices, string file_adj) {
	int i, j, k, vertice, _from, _to;
	vector<string> saida;
	string temp, email;
	ifstream file;

	file.open(file_id_vertices); // passando arquivo rotulo / int

	if (!file)
		cout << "Erro ao abrir arquivo: " << file_id_vertices << endl;

	while (getline(file, temp)) {
		saida.push_back(temp);
	}
	temp.clear();
	cout << "****quantidade de vertices necessaria (emails): " << saida.size() << endl;

	for (i = 0; i < saida.size(); i++) { // quebra arquivo em duas partes
		for (j = 0; saida[i][j] != ' '; j++) {
			temp.push_back(saida[i][j]);
		}
		email = temp; // id_vertices.first receberá email
		temp.clear();
		for (j; saida[i][j] != '\0'; j++) {
			temp.push_back(saida[i][j]);
		}
		vertice = atoi(temp.c_str()); // id_vertices.second recebe id-vertice do email (convertido para int)
		temp.clear();

		this->id_vertices.push_back(make_pair(email, vertice)); // fazendo pair com as variaveis temporárias
	}

	file.close();
	file.open(file_adj); // passando arquivo int / int

	if (!file)
		cout << "Erro ao abrir arquivo: " << file_adj << endl;

	temp.clear();
	saida.clear();

	while (getline(file, temp)) {
		saida.push_back(temp);
	}
	temp.clear();
	//cout << "****adj indices tamanho: " << saida.size() << endl;

	for (i = 0; i < saida.size(); i++) {
		for (j = 0; saida[i][j] != ' '; j++) {
			temp.push_back(saida[i][j]);
		}
		_from = atoi(temp.c_str()); // adj_first receberá _from convertido
		temp.clear();
		for (j; saida[i][j] != '\0'; j++) {
			temp.push_back(saida[i][j]);
		}
		_to = atoi(temp.c_str()); // adj.second receberá _to convertido
		temp.clear();

		adj.push_back(make_pair(_from, _to)); // fazendo pair _from _to de inteiros
	}

	//cout << "Id vertices: " << endl;
	//imprime_id_vertices(id_vertices);
	//cout << "Adj: " << endl;
	//imprime_adj(adj);


}

adjacencias::adjacencias(string id_vertices, string adj) {
	quebra_linha(id_vertices, adj);
}
//FIM MODO RÁPIDO

//___ funcoes externas
int adjacencias::quantidade_vertices() {
	return id_vertices.size();
}

int adjacencias::quantidade_adj() {
	return adj.size();
}

string adjacencias::nome_vertice(int vertice) {
	return id_vertices[vertice].first; //retorna email equivalente ao vertice
}

int adjacencias::retorna_from(int i) {
	return adj[i].first;
}

int adjacencias::retorna_to(int i) {
	return adj[i].second;
}


adjacencias::adjacencias(vector<string> _enderecos) {
	this->enderecos = _enderecos;
	//imprime_vector(this->enderecos);
	armazena_adjacencias();
}

void adjacencias::retira_repetidos(vector<string> & nomes) {
	vector<string> temp;

	for (int i = 0; i < nomes.size(); i++) {
		if (i == 0)
			temp.push_back(nomes[i]);
		else {
			if (nomes[i] == nomes[i - 1])
				;
			else
				temp.push_back(nomes[i]);
		}
	}

	nomes.clear();

	nomes = temp;
}

void adjacencias::armazena_adjacencias()
 {
	int i, j, k, _from, _to, debug = 500;
	string temp, from, to;
	vector<string> aux;

	ifstream file;

	for (k = 0; k < enderecos.size(); k++) {
		if (k == debug) {
			cout << "Limpando arquivo : " << k << endl;
			debug = debug + 500;
		}

		file.open(enderecos[k]);

		while (getline(file, temp)) {
			linhas.push_back(temp);
		}

		//cout << "vector sujo: " << endl; for (i = 0; i < linhas.size(); i++) cout << linhas[i] << endl;

		palavras = tokenizer(linhas, ",.\t:-;()|");

		linhas.clear();

		//pega to e from e faz um pair 
		for (i = 0; i < palavras.size(); i++) {
			if (palavras[i] == "From:")
				from = palavras[++i]; // pega palavra depois de "From"
			else if (palavras[i] == "To:") {
				for (j = i + 1; j != palavras.size(); j++) { // pega emails a partir de "to: +1"
					to = palavras[j];
					adj_nome.push_back(make_pair(from, to));
				}
				break; // for aninhado ja pega todos os enviados então n precisa continuar
			}
		}
		palavras.clear();
		file.close();
	}


	salva_arquivos();

	cout << "Criando tabela email - id! (merge from + to + ordenando e retirando repetidos) " << endl;

	// copia pra aux para gerar a tabela email - id_vertice
	for (i = 0; i < adj_nome.size(); i++) { // nao adicionar repetidos em sequencia
		if (i == 0) {
			aux.push_back(adj_nome[i].first);
			aux.push_back(adj_nome[i].second);
		}
		else {
			if (adj_nome[i].first != adj_nome[i - 1].first)
				aux.push_back(adj_nome[i].first);
			if (adj_nome[i].second != adj_nome[i - 1].second)
				aux.push_back(adj_nome[i].second);
		}

	}

	heapsort(aux); // ordena
				   //imprime_vector(aux);
	retira_repetidos(aux); // retira repetidos
						   //imprime_vector(aux);

	for (i = 0; i < aux.size(); i++) {
		id_vertices.push_back(make_pair(aux[i], i)); // colocar email + indice
	}

	vector<int> vector_from;
	int from_repetido;

	cout << "Transformando From em Int!" << endl;

	for (i = 0; i < adj_nome.size(); i++) {
		if (i == 0) {
			_from = busca_binaria(adj_nome[i].first, id_vertices);
			vector_from.push_back(_from);
		}
		else if (adj_nome[i].first == adj_nome[i - 1].first) {
			vector_from.push_back(_from);
		}
		else {
			_from = busca_binaria(adj_nome[i].first, id_vertices);
			vector_from.push_back(_from);
		}
	}

	salva_arquivos();

	cout << "**** Transformando to em int! // tem " << adj_nome.size() << " arquivos para transforma int int! " << endl;
	debug = 100;

	for (i = 0; i < adj_nome.size();i++) {
		if (i == debug) {
			cout << "Esta no valor: " << i << endl;
			debug = debug + 100;
		}

		//_from = busca_binaria(adj_nome[i].first, id_vertices);
		_to = busca_binaria(adj_nome[i].second, id_vertices);
		adj.push_back(make_pair(vector_from[i], _to));
	}

	cout << "Salvando Arquivos" << endl;
	salva_arquivos();
	/*
	cout << endl << "Adjacencias com nomes " << endl;
	imprime_adj_nome(adj_nome);

	cout << endl << "Rotulo Id e Vertices " << endl;
	imprime_id_vertices(id_vertices);

	cout << endl << "Adjacencias com inteiros equivalentes" << endl;
	imprime_adj(adj);
	*/
	cout << "Adjacencias armazenadas com sucesso!" << endl;

}
vector<string> adjacencias::tokenizer(vector<string> linhas, string retirar) {
	vector<string> palavras;
	int i, j, k;
	bool valido = true;
	string aux;

	for (i = 0; i < linhas.size(); i++) {
		for (j = 0; linhas[i][j] != NULL; j++) {
			for (k = 0, valido = true; retirar[k] != NULL; k++) {
				if (linhas[i][j] == retirar[k]) {
					valido = false;
					break;
				}
			}
			if (valido)
				aux.push_back(linhas[i][j]);
			else if (aux.size() != 0) {
				if (aux == "Subject:") // pra n pegar mais nada do arquivo
					return palavras;
				palavras.push_back(aux);
				aux.clear();
			}
		}
		if (aux.size() != 0) { // excecao
			palavras.push_back(aux);
			aux.clear();
		}
	}
	return palavras;
}

bool adjacencias::existe(vector<pair<string, int>> nomes, string verifica) { // verifica se o email já existe no pair
	for (int i = 0; i < nomes.size(); i++) {
		if (nomes[i].first == verifica)
			return true;
	}
	return false;
}

int adjacencias::vertice_int(vector<pair<string, int>> id_vertices, string email) {
	int i, j, valor;

	for (i = 0; i < id_vertices.size(); i++) {
		if (email == id_vertices[i].first)
			return id_vertices[i].second;

	}
	cout << "Erro, Vertice NAO encontrado";
	return -1;
}

void adjacencias::salva_arquivos() {
	int i;
	vector<string> linha;

	for (int i = 0; i < adj_nome.size(); i++)
		linha.push_back(adj_nome[i].first + " " + adj_nome[i].second);

	ofstream output_file("./adj_nome.txt");
	ostream_iterator<std::string> output_iterator(output_file, "\n");
	std::copy(linha.begin(), linha.end(), output_iterator);

	linha.clear();

	for (int i = 0; i < id_vertices.size(); i++)
		linha.push_back(id_vertices[i].first + " " + (to_string(id_vertices[i].second)));

	ofstream output_file2("./id_vertices.txt");
	ostream_iterator<std::string> output_iterator2(output_file2, "\n");
	std::copy(linha.begin(), linha.end(), output_iterator2);

	linha.clear();

	for (int i = 0; i < adj.size(); i++)
		linha.push_back((to_string(adj[i].first)) + " " + (to_string(adj[i].second)));

	ofstream output_file3("./adj.txt");
	ostream_iterator<std::string> output_iterator3(output_file3, "\n");
	std::copy(linha.begin(), linha.end(), output_iterator3);
}


void adjacencias::imprime_id_vertices(vector<pair<string, int>> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i].first << " ";
		cout << vector[i].second << endl;
	}
}

void adjacencias::imprime_adj(vector<pair<int, int>> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i].first << " ";
		cout << vector[i].second << endl;
	}
}

void adjacencias::imprime_adj_nome(vector<pair<string, string>> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i].first << " ";
		cout << vector[i].second << endl;
	}
}

void adjacencias::imprime_vector(vector<string> vector) {
	cout << endl;
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i] << endl;
	}
}

void adjacencias::heapsort(vector<string> & vector) {
	int n = vector.size();
	int i = n / 2, pai, filho;
	string t;
	for (;;) {
		if (i > 0) {
			i--;
			t = vector[i];
		}
		else {
			n--;
			if (n == 0) return;
			t = vector[n];
			vector[n] = vector[0];
		}
		pai = i;
		filho = i * 2 + 1;
		while (filho < n) {
			if ((filho + 1 < n) && (vector[filho + 1] > vector[filho]))
				filho++;
			if (vector[filho] > t) {
				vector[pai] = vector[filho];
				pai = filho;
				filho = pai * 2 + 1;
			}
			else {
				break;
			}
		}
		vector[pai] = t;
	}
}


void adjacencias::heapsort(vector<pair<int, int>> & pair) {
	int n = pair.size();
	int i = n / 2, pai, filho;
	int t1, t2;
	for (;;) {
		if (i > 0) {
			i--;
			t2 = pair[i].second;
			t1 = pair[i].first;
		}
		else {
			n--;
			if (n == 0) return;
			t2 = pair[n].second;
			t1 = pair[n].first;
			pair[n].second = pair[0].second;
			pair[n].first = pair[0].first;
		}
		pai = i;
		filho = i * 2 + 1;
		while (filho < n) {
			if ((filho + 1 < n) && (pair[filho + 1].second > pair[filho].second))
				filho++;
			if (pair[filho].second > t2) {
				pair[pai].second = pair[filho].second;
				pair[pai].first = pair[filho].first;
				pai = filho;
				filho = pai * 2 + 1;
			}
			else {
				break;
			}
		}
		pair[pai].second = t2;
		pair[pai].first = t1;
	}


}


int adjacencias::busca_binaria(string verificador, vector<pair<string, int>> dicionario) {

	int inf, media, sup;
	inf = 0; sup = dicionario.size() -1;
	while (inf <= sup) {
		media = (inf + sup) / 2;
		if (dicionario[media].first == verificador)
			return dicionario[media].second;
		if (dicionario[media].first < verificador)
			inf = media + 1;
		else
			sup = media - 1;
	}
	return -1;

}

adjacencias::~adjacencias() {

}
