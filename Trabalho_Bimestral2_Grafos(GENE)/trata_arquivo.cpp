#include "trata_arquivo.h"


trata_arquivo::trata_arquivo(vector<string> _enderecos) {
	this->enderecos = _enderecos;
	//imprime_vector(this->enderecos);
	//armazena_adjacencias();
	
}



trata_arquivo::trata_arquivo(string _nome_arquivo){
	this->nome_arquivo = _nome_arquivo;
}

//MODO_ RÁPIDO: QUEBRA LINHA EM 2 PARTES E COLOCA NO PAIR CORRESPONDENTE (ID_VERTICES E ADJ)
void trata_arquivo::quebra_linha(string file_id_vertices, string file_adj) {
	int i, j, k, vertice, _from, _to;
	vector<string> saida;
	string temp, email, aux1, aux2;
	ifstream file;

	file.open(file_id_vertices); // passando arquivo rotulo / int

	if (!file)
		cout << "Erro ao abrir arquivo: " << file_id_vertices << endl;

	while (getline(file, temp)) {
		saida.push_back(temp);
		//cout << temp << endl;
	}
	temp.clear();
	cout << "****quantidade de vertices necessaria (emails): " << saida.size() << endl;

	for (i = 0; i < saida.size(); i++) { // quebra arquivo em duas partes
		for (j = 0; saida[i][j] != '\0'; j++) {
			temp.push_back(saida[i][j]);
		}
		reverse(temp.begin(), temp.end());
		for (j = 0; temp[j] != ' '; j++) {
			aux1.push_back(temp[j]);
		}
		for (j = j+1 ; temp[j] != '\0'; j++) {
			aux2.push_back(temp[j]);
		}
		reverse(aux1.begin(), aux1.end());
		reverse(aux2.begin(), aux2.end());
		//cout << aux1 << " -> " << aux2 << endl;
		email = aux2; // id_vertices.first receberá email

		vertice = atoi(aux1.c_str()); // id_vertices.second recebe id-vertice do email (convertido para int)
		temp.clear(); aux1.clear(); aux2.clear();

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

trata_arquivo::trata_arquivo(string id_vertices, string adj) {
	quebra_linha(id_vertices, adj);
}
//FIM MODO RÁPIDO

//___ funcoes externas
int trata_arquivo::quantidade_vertices() {
	return id_vertices.size();
}

int trata_arquivo::quantidade_adj() {
	return adj.size();
}

string trata_arquivo::nome_vertice(int vertice) {
	return id_vertices[vertice].first; //retorna email equivalente ao vertice
}

int trata_arquivo::retorna_from(int i) {
	return adj[i].first;
}

int trata_arquivo::retorna_to(int i) {
	return adj[i].second;
}



vector<string> trata_arquivo::tokenizer(vector<string> linhas, string retirar) {
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
				//if (aux == "Subject:") // pra n pegar mais nada do arquivo
				//	return palavras;
				if (aux[0] != '<' && aux[0] != '>' && aux[0] != '#')
					palavras.push_back(aux);
				aux.clear();
			}
		}
		if (aux.size() != 0) { // excecao
			if (aux[0] != '<' && aux[0] != '>' && aux[0] != '#')
				palavras.push_back(aux);
			aux.clear();
		}
	}
	return palavras;
}

vector<string> trata_arquivo::tokenizer(string linhas, string retirar) {
	vector<string> str;
	str.push_back(linhas);
	return tokenizer(str, retirar);
}

vector<string> trata_arquivo::legenda() {
	vector<string> vet, saida;
	string temp;
	ifstream file;
	int i, j;

	file.open(nome_arquivo); // passando arquivo rotulo / int

	if (!file) {
		cerr << "Erro ao abrir arquivo: " << nome_arquivo << endl;
		exit(0);
	}

	while (getline(file, temp)) {
		if ((temp[0] < 47 || temp[0] > 57) && temp.size() > 0)
			saida.push_back(temp);
	}

	for (i = 0; i < saida.size();i++) {
		cout << saida[i] << endl;
	}
	//temp.clear();
	//cout << "****quantidade de vertices necessaria (emails): " << saida.size() << endl;

	palavras_legenda = tokenizer(saida, "-,\"?!. |");

	for (i = 0; i < palavras_legenda.size();i++) {
		cout << "***" << palavras_legenda[i] << endl;
	}

	armazena_adjacencias();

	return palavras_legenda;
}

grafo * trata_arquivo::armazena_adjacencias() {
	int i, j, k,l,m, _from, _to, debug = 500;
	string temp, from, to;
	vector<string> aux, gene, diagnostico;

	ifstream file;
	for (k = 0; k < enderecos.size(); k++) {
		if (k == debug) {
			cout << "Limpando arquivo : " << k << endl;
			debug = debug + 500;
		}

		file.open(enderecos[k]);


		if (!file) {
			cerr << "Erro ao abrir arquivo: " << nome_arquivo << endl;
			exit(0);
		}

		while (getline(file, temp)) {
				linhas.push_back(temp);
				//cout << temp << endl;
		}
		//cout << "Arquivo em um vector!" << endl;
		vector<string> aux;
		cout << "Criando Adj_nome.txt" << endl;
		for (i = 0; i < linhas.size();i++) {
			aux.push_back(linhas[i]);
			palavras_legenda = tokenizer(aux, "\t");
			if (palavras_legenda.size() > 2) {
				gene = tokenizer(palavras_legenda[1], "|");
				diagnostico = tokenizer(palavras_legenda[2], "|");
			}
			// para fazer multiplos genes x multiplos diagnosticos (nxn)
			for (l = 0; l < gene.size(); l++) {
				for (m = 0; m < diagnostico.size(); m++) {
					adj_nome.push_back(make_pair(gene[l], diagnostico[m]));
					//cout << gene[l] << " -> " << diagnostico[m] << endl;
				}
			}
			//cin >> k;
			palavras_legenda.clear();
			aux.clear();
		}
		cout << "Adj_nome.txt criada" << endl;
		//palavras_legenda = tokenizer(linhas, " -,\"?!*=.[]{}()&:;|@");
		linhas.clear();
	

		/*
		for (i = 0; i < palavras_legenda.size() - 1; i++) {
			adj_nome.push_back(make_pair(palavras_legenda[i], palavras_legenda[i + 1]));
		}
		*/
		palavras_legenda.clear();
		file.close();
	}

	cout << "Adjacencias a processar (repetidas): " << adj_nome.size() << endl;

	//imprime_adj_nome(adj_nome);
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

	grafo * G = new grafo(id_vertices.size());
	cout << "Setando informacao do grafo" << endl;
	for (i = 0; i < id_vertices.size();i++) {
		G->seta_informacao(i, id_vertices[i].first);
	}
	cout << "Rotulos setados!" << endl;
	debug = 100;
	cout << "Quantidade de vertices: " << id_vertices.size() << endl;
	cout << "Criando adjacencias!" << endl;

	for (i = 0; i < adj_nome.size(); i++) {
		if (i == debug) {
			cout << "Esta no valor: " << i << endl;
			debug = debug + 100;
		}
		_from = G->email_to_id(adj_nome[i].first);
		_to = G->email_to_id(adj_nome[i].second);
		G->cria_adjacencia(_from, _to, 1);
	}
	//imprime_id_vertices(id_vertices);

	/*
	//vector<int> vector_from;
	int from_repetido;
	
	cout << "Vertices: " << id_vertices.size() << endl;
	cout << "Transformando From em Int!" << endl;
	debug = 100;


	for (i = 0; i < adj_nome.size(); i++) {
		if (i == debug) {
			cout << "Esta no valor: " << i << endl;
			debug = debug + 100;
		}
		if (i == 0) {
			_from = busca_binaria(adj_nome[i].first, id_vertices);
			_to = busca_binaria(adj_nome[i].second, id_vertices);
			adj.push_back(make_pair(_from, _to));
		}
		else {
			_from = busca_binaria(adj_nome[i].first, id_vertices);
			_to = busca_binaria(adj_nome[i].second, id_vertices);
			adj.push_back(make_pair(_from, _to));
		}
	}
	*/
	/*

	for (i = 0; i < adj_nome.size(); i++) {
		if (i == debug) {
			cout << "Esta no valor: " << i << endl;
			debug = debug + 100;
		}
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
	*/
	cout << "Salvando Arquivos" << endl;
	salva_arquivos();
	return G;
}

void trata_arquivo::retira_repetidos(vector<string> & nomes) {
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

void trata_arquivo::salva_arquivos() {
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


void trata_arquivo::imprime_id_vertices(vector<pair<string, int>> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i].first << " ";
		cout << vector[i].second << endl;
	}
}

void trata_arquivo::imprime_adj(vector<pair<int, int>> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i].first << " ";
		cout << vector[i].second << endl;
	}
}

void trata_arquivo::imprime_adj_nome(vector<pair<string, string>> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i].first << " ";
		cout << vector[i].second << endl;
	}
}

void trata_arquivo::imprime_vector(vector<string> vector) {
	cout << endl;
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i] << endl;
	}
}

void trata_arquivo::heapsort(vector<string> & vector) {
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


void trata_arquivo::heapsort(vector<pair<int, int>> & pair) {
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

int trata_arquivo::busca_binaria(string verificador, vector<pair<string, int>> dicionario) {

	int inf, media, sup;
	inf = 0; sup = dicionario.size() - 1;
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

trata_arquivo::~trata_arquivo()
{
}
