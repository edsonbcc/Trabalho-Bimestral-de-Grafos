#include "Grafo.h"
// todas as inicializações estão no construtor(matriz de fechamento, vetor..)

//construtor principal do grafo (chamado em todos os outros construtores (pajek e aleatorio))
grafo::grafo(int TAM) {
	int i, j;

	this->tam = TAM;
	vertices = new vertice[tam];
	caminho = new int[tam];

	l = new listaSE[tam]; // cria lista de adjacencia

	componente = new int[tam];
	/*
	// inicializando matriz de fechamento dinamicamente
	fechamento = new int*[tam];
	for (i = 0; i < tam; i++) {
		fechamento[i] = new int[tam];
	}

	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			fechamento[i][j] = INFINITO;
		}
	}
	*/
	for (i = 0;i < tam; i++) {
		vertices[i].set_nome(to_string(i)); //to_string() converte int em string (inicializa rotulos com nome padrao(0,1,2,3,4))
		componente[i] = -1;
		//cout << "componente: [" << i << "]: " << componente[i] << endl;
	}


	inicializa_stop_word();

}

//carrega pajek - usa metodo separador
grafo::grafo(string nome_arquivo) {
	int i, j, k, tam;
	string rotulo = "";
	vector<string> arg0, arg1, arg2, pajek, palavras;
	separador(nome_arquivo, arg0, arg1, arg2, pajek);

	tam = atoi(arg1[0].c_str()); // pegando o tamanho do grafo na primeira linha
	cout << "Vertices : " << tam << endl;

	new (this) grafo(tam); // fazendo inicializacoes do grafo (usando tamanho) na primeira linha


	for (i = 0, j = 1; i < arg0.size(); i++, j++) {
		//cout << "Ta no: " << i << endl;
		if (arg0[j] == "*Arcs") {
			break;
		}

		else {
			palavras = tokenizer(pajek[j], " ");
			for (k = 1; k < palavras.size(); k++)
				rotulo = rotulo + palavras[k] + " ";
			rotulo = rotulo.substr(1, rotulo.size() - 3); // retirando aspas "nome"
			//cout << rotulo << endl;
			//rotulo = arg1[j]; // sem aspas
			vertices[i].set_nome(rotulo);
			rotulo.clear();
			palavras.clear();
		}
	}


	for (j = j + 1; j < arg0.size(); j++) { // cria adj i j + peso (arg0, arg1, arg2)
		cria_adjacencia(atoi(arg0[j].c_str()) -1, atoi(arg1[j].c_str()) -1, atoi(arg2[j].c_str()));
	}

	//cria_adjacencia(7, 2, 1);
	//grafo::grafo(tam);

}

// grafo aleatorio
grafo::grafo(int TAM, int arestas, char conexo, char bidirecionado) {
	int max_arestas;
	new (this) grafo(TAM); // 100 mil nao passa daqui

	max_arestas = this->tam *(this->tam - 1); // para grafos direcionados

	if (bidirecionado == '1' && conexo == '1') { // conexo bipartido
		max_arestas = this->tam *(this->tam - 1) / 2; // para grafos bidirecionados 
		////////////*arrumar
		if (arestas > max_arestas) {
			cout << "Impossivel criar este grafo" << endl;
			cout << "Maximo de arestas: " << max_arestas << endl;
			exit(0);
		}
		else if (arestas < TAM - 1) { // minimo de arestas para criar um grafo conexo
			cout << "Impossivel criar grafo conexo com essa quantidade de arestas" << endl;
			exit(0);
		}
		else
			grafo_aleatorio_conexo_nao_direcionado(arestas);
	}
	else if (bidirecionado == '1' && conexo == '0'){
		if (arestas > max_arestas) { // limite geral de arestas direcionadas
			cout << "Impossivel criar este grafo" << endl;
			exit(0);
		}
		else if (max_nao_direcionado_desconexo(arestas)) { // limite para grafo nao virar conexo
			cout << "Impossivel criar grafo desconexo com esta quantidade de arestas" << endl;
			exit(0);
		}
		else {
			grafo_aleatorio_desconexo_nao_direcionado(arestas);
		}
	}
	//grafo direcionado e conexo
	else if (bidirecionado == '0' && conexo == '1') {
		if (arestas > max_arestas) { // limite geral de arestas direcionadas
			cout << "Impossivel criar este grafo" << endl;
			exit(0);
		}
		else if (arestas < TAM - 1) { // minimo de arestas para criar um grafo conexo
			cout << "Impossivel criar grafo conexo com essa quantidade de arestas" << endl;
			exit(0);
		}
		else
			grafo_aleatorio_conexo(arestas);
	} 

	else { // para grafos desconexos e direcionados
		if (arestas > max_arestas) { // limite geral de arestas direcionadas
			cout << "Impossivel criar este grafo" << endl;
			exit(0);
		}
		else if (max_direcionado_desconexo(arestas)) { // limite para grafo nao virar conexo
			cout << "Impossivel criar grafo desconexo com esta quantidade de arestas" << endl;
			exit(0);
		}
		else {
			grafo_aleatorio_desconexo(arestas);
		}

	}
	
}

// retorna uma instancia de grafo escolhida pelo usuario (aleatorio, pajek ou manual)
grafo * grafo::fabrica_grafo() {
	int ch, tam, arestas;
	string arquivo;
	char escolha, direcionado;
	cout << "Digite o modo de entrada:" << endl;
	cout << "1- Gerar grafo aleatorio" << endl;
	cout << "2- Carregar arquivo PAJEK (pajek.txt)" << endl;
	cout << "3- Criar grafo manualmente" << endl;
	//cout << "4 - Carregar base de dados (GENES)" << endl;
	cout << "0- Sair" << endl;
	cout << "Escolha: ";
	cin >> ch;


	switch (ch) {
	case 1: {
		cout << "Digite a quantidade de vertices: ";
		cin >> tam;
		cout << "Digite a quantidade de arestas: ";
		cin >> arestas;
		cout << "O grafo eh conexo? (1- Sim) - (0 - Nao): ";
		cin >> escolha;
		cout << "O grafo eh bidirecionado? (1- Sim) - (0 - Nao): ";
		cin >> direcionado;
		return new grafo(tam, arestas, escolha, direcionado);
		break;
	}
	case 2: {
		cout << "Digite o endereco do arquivo pajek: "; 
		cin.ignore(); // limpar buffer do teclado
		getline(cin, arquivo);
		return new grafo(arquivo); // entrada pajek
		break;
	}
	case 3: {
		cout << "Digite o tamanho do grafo: ";
		cin >> tam;
		return new grafo(tam);
		break;
	}
	
	case 0: {
		exit(0);
		break;
	}
	default:
		return new grafo(1);
	}
	
}

void grafo::grava_pajek() {
	vector<string> texto;
	int i, j;

	string linha;
	cout << "Gravando pajek..." << endl;
	
	linha = "*Vertices " + to_string(this->tam);
	texto.push_back(linha);
	cout << "linha: " << linha << endl;
	linha.clear();

	for (i = 0; i < this->tam; i++) {
		linha = to_string(i+1) + " \"" + vertices[i].get_nome() + "\"";
		//linha = to_string(i) + " " + vertices[i].get_nome();
		texto.push_back(linha);
		linha.clear();
	}

	linha = "*Arcs " + to_string(quantidade_arestas());
	texto.push_back(linha);
	linha.clear();

	for (i = 0; i < this->tam; i++) {
		for (j = 0; j < this->tam; j++) {
			if (l[i].procura(j)) {
				linha = to_string(i+1) + " " + to_string(j+1) + " " + to_string(l[i].retorna_peso(j));
				texto.push_back(linha);
				linha.clear();
			}
		}
	}
	//for (i = 0; i < texto.size(); i++) {
	//	cout << texto[i] << endl;
	//}


	ofstream output_file("./pajek.net");
	ostream_iterator<std::string> output_iterator(output_file, "\n");
	std::copy(texto.begin(), texto.end(), output_iterator);
	cout << "Gravo salvo em formato pajek! " << endl;
}



// funcionando com bidirecionado 
float grafo::centralidade_de_proximidade(int i) {
	float closeness = 0;
	int aux;
	/*
	if (!conexo()) {
		cout << "Impossivel calcular centralidade (grafo nao eh conexo)" << endl;
		return 0;
	}
	*/
	for (int x = 0; x < this->tam; x++) {
		if (x != i) {
			closeness += menor_distancia(i, x);
			//cout << "menor :" << menor_distancia(i, x) << endl;

		}
	}
	return (this->tam -1) / closeness; // retorno normalizado
}
 
// funcionando com bidirecionado
float grafo::centralidade_de_intermediacao(int x) {
	int i, j;
	float resultado = 0;
	vector<int> caminho;
	/*
	if (!conexo()) {
		cout << "Impossivel calcular centralidade (grafo nao eh conexo)" << endl;
		return 0;
	}
	*/

	//cout << "valor de x: " << x << endl;
	for (i = 0; i < this->tam; i++) {
		for (j = 0; j < this->tam; j++) {
			if (i != x && j != x) {
				caminho.clear();
				menor_distancia(i, j, caminho);
				if (caminho.size() > 0) {
					;
				//cout << "X ";
					//for (int p = 0; p < caminho.size(); p++)
							//cout << caminho[p] << " ";
				//cout << "X" << endl;
				}
				if (foi_visitado(x, caminho)) { // se x existe no caminho 
					resultado++;
				}	
			}
		}
	}
	//cout << "Resultado: " << resultado << endl;
	return resultado / ((this->tam -1) * (this->tam -2));
}

// adapter
int grafo::menor_distancia(int s, int t) {
	vector<int> caminho;
	return menor_distancia(s,t, caminho);
}

// algoritmo de dijkstra
int grafo::menor_distancia(int s, int t, vector<int> & caminho_saida) {
	if (!indice_valido(s, t))
		return -1;
	//faz_fechamento();

	//if (!fechamento[s][t])
	//	return 0;

	int* distancia = new int[tam];
	bool* perm = new bool[tam];
	int corrente, i, k = s, dc, j = 0;
	caminho_saida.clear();

	int menordist, novadist = 0;

	//inicialização
	for (i = 0; i < tam; ++i) {
		perm[i] = NAOMEMBRO;
		distancia[i] = INFINITO;
		caminho[i] = -1;
	}

	perm[s] = MEMBRO;
	distancia[s] = 0;
	corrente = s;
	while (corrente != t) {
		menordist = INFINITO;
		dc = distancia[corrente];
		for (i = 0; i < tam; i++) {
			if (!perm[i]) {
				if (!l[corrente].procura(i) && !l[i].procura(corrente))
				novadist = dc + l[corrente].retorna_peso(i);
				else
					novadist = dc + 1;
				if (novadist < distancia[i]) {
					distancia[i] = novadist;
					caminho[i] = corrente;
				}
				if (distancia[i] < menordist) {
					menordist = distancia[i];
					k = i;
				}
			}
		}
		corrente = k;

		perm[corrente] = MEMBRO;
	}



	i = caminho[t];

	if (i == -1)
		return -1;
	caminho_saida.push_back(t);
	while (i != s) {
		caminho_saida.push_back(i);
		//cout << "valor de i:" << i << endl;
		i = caminho[i];
	}
	caminho_saida.push_back(s);
	
	//imprimirDijkstra();
	//pega_caminho(s, t, caminho_saida);
	return distancia[t];
}



// tem somente 1 componente. Permite laço
void grafo::grafo_aleatorio_conexo(int arestas) {
	int origem, destino, peso = 1;
	bool primeira_vez = true;

	srand(time(NULL));
	for (int i = 0; i < arestas;) {
		origem = (rand() * rand()) % tam;
		destino = (rand() * rand()) % tam;

		if (i < this->tam - 1) {
			if (l[origem].procura(destino) || l[destino].procura(origem));
			else if (!vertice_nulo(origem) && !vertice_nulo(destino));
			else if (origem == destino);
			else if (primeira_vez) {
				cria_adjacencia(origem, destino, peso);
				//cout << " " << origem << " " << destino << endl;
				i++;
				//cout << "i: " << i << endl;
				primeira_vez = false;
			}
			else if (vertice_nulo(origem) && vertice_nulo(destino));
			else {
				cria_adjacencia(origem, destino, peso);
				//cout << " " << origem << " " << destino << endl;

				i++;
				//cout << "i: " << i << endl;
			}
		}
		else {
			if (!l[origem].procura(destino)) {
				cria_adjacencia(origem, destino, peso);
				//cout << " " << origem << " " << destino << endl;
				i++;
				//cout << "i: " << i << endl;
			}

		}
	}
}

//revisar - nao permite laco
void grafo::grafo_aleatorio_conexo_nao_direcionado(int arestas) {
	int origem, destino, peso = 1;
	bool primeira_vez = true;

	srand(time(NULL));
	for (int i = 0; i < arestas;) {
		origem = (rand() * rand()) % tam;
		destino = (rand() * rand()) % tam;

		if (i < this->tam - 1) {
			if (l[origem].procura(destino) || l[destino].procura(origem));
			else if (!vertice_nulo(origem) && !vertice_nulo(destino));
			else if (origem == destino);
			else if (primeira_vez) {
				cria_adjacencia(origem, destino, peso);;; cria_adjacencia(destino, origem, peso);  
				
				//cout << " " << origem << " " << destino << endl;
				i++;
				//cout << "i: " << i << endl;
				primeira_vez = false;
			}
			else if (vertice_nulo(origem) && vertice_nulo(destino));
			else {
				cria_adjacencia(origem, destino, peso);;; cria_adjacencia(destino, origem, peso);  
				//cout << " " << origem << " " << destino << endl;

				i++;
				//cout << "i: " << i << endl;
			}
		}
		else {
			if (!l[origem].procura(destino) && origem != destino) {
				cria_adjacencia(origem, destino, peso);;; cria_adjacencia(destino, origem, peso);  
				//cout << " " << origem << " " << destino << endl;
				i++;
				//cout << "i: " << i << endl;
			}

		}
	}
}


// NÃO permite laço. Tem no minimo 2 componentes
void grafo::grafo_aleatorio_desconexo(int arestas) {
	int origem, destino, peso = 1, i, j;
	int aleat1, aux;
	vector<int> posicoes, pt1, pt2;

	for (i = 0; i < this->tam;i++)
		posicoes.push_back(i);

	srand(time(NULL));

	for (i = 0; i < this->tam; i++) { // dando um shuffle  no vector para criacao do grafo
		aleat1 = (rand() * rand()) % this->tam;
		aux = posicoes[i];
		posicoes[i] = posicoes[aleat1];
		posicoes[aleat1] = aux;
	}

	if (this->tam % 2 == 0) { // caso numero de vertices pares
		for (i = 0; i < this->tam / 2;i++)
			pt1.push_back(posicoes[i]); // pt1 recebera primeira parte das posicoes

		for (i; i < this->tam; i++)
			pt2.push_back(posicoes[i]); //pt2 recebera segunda parte das posicoes

		for (i = 0; i < arestas / 2; ) {
			//cout << i <<  endl;
			origem = (rand() * rand()) % pt1.size();
			destino = (rand() * rand()) % pt1.size();
			origem = pt1[origem];
			destino = pt1[destino];
			if (!l[origem].procura(destino) && origem != destino) { // && origem != destino  p/ n ter laço
				cria_adjacencia(origem, destino, peso);
				i++;
			}
		}

		for (i; i < arestas; ) {
			//cout << i << endl;
			origem = (rand() * rand()) % pt2.size();
			destino = (rand() * rand()) % pt2.size();
			origem = pt2[origem];
			destino = pt2[destino];
			if (!l[origem].procura(destino) && origem != destino) {
				cria_adjacencia(origem, destino, peso);
				i++;
			}
		}

	}
	else { //caso numero de vertices impar
		for (i = 0; i < (this->tam / 2) + 1;i++)
			pt1.push_back(posicoes[i]); // pt1 recebera primeira parte das posicoes

		for (i; i < this->tam; i++)
			pt2.push_back(posicoes[i]); //pt2 recebera segunda parte das posicoes

		for (i = 0; i < arestas / 2 + 2; ) { // +1 é a unica coisa que muda
			origem = (rand() * rand()) % pt1.size();
			destino = (rand() * rand()) % pt1.size();
			origem = pt1[origem];
			destino = pt1[destino];
			if (!l[origem].procura(destino) && origem != destino) {
				cria_adjacencia(origem, destino, peso);
				i++;
			}
		}

		for (i; i < arestas; ) {
			origem = (rand() * rand()) % pt2.size();
			destino = (rand() * rand()) % pt2.size();
			origem = pt2[origem];
			destino = pt2[destino];
			if (!l[origem].procura(destino) && origem != destino) {
				cria_adjacencia(origem, destino, peso);
				i++;
			}
		}
	}
	// no final sera criado um grafo com no minimo 2 componentes tanto para vertices pares quanto para impares

	for (i = 0; i < pt1.size(); i++)
		cout << pt1[i] << " ";
	cout << endl;

	for (i = 0; i < pt2.size(); i++)
		cout << pt2[i] << " ";
	cout << endl;
}

bool grafo::max_direcionado_desconexo(int arestas) {
	int pt1, pt2, max_arestas;


	if (this->tam % 2 == 0) {
		pt1 = this->tam / 2;
		pt2 = this->tam / 2;
	}
	else {
		pt1 = (this->tam / 2) + 1;
		pt2 = this->tam / 2;
	}

	max_arestas = pt1 * (pt1 - 1) + pt2 * (pt2 - 1);
	cout << "Max arestas: " << max_arestas << endl;

	if (arestas > max_arestas)
		return true;
	else
		return false;

}


//revisar
void grafo::grafo_aleatorio_desconexo_nao_direcionado(int arestas) {
	int origem, destino, peso = 1, i, j;
	int aleat1, aux;
	vector<int> posicoes, pt1, pt2;

	for (i = 0; i < this->tam;i++)
		posicoes.push_back(i);

	srand(time(NULL));

	for (i = 0; i < this->tam; i++) { // dando um shuffle  no vector para criacao do grafo
		aleat1 = (rand() * rand()) % this->tam;
		aux = posicoes[i];
		posicoes[i] = posicoes[aleat1];
		posicoes[aleat1] = aux;
	}

	if (this->tam % 2 == 0) { // caso numero de vertices pares
		for (i = 0; i < this->tam / 2;i++)
			pt1.push_back(posicoes[i]); // pt1 recebera primeira parte das posicoes

		for (i; i < this->tam; i++)
			pt2.push_back(posicoes[i]); //pt2 recebera segunda parte das posicoes

		for (i = 0; i < arestas / 2; ) {
			//cout << i <<  endl;
			origem = (rand() * rand()) % pt1.size();
			destino = (rand() * rand()) % pt1.size();
			origem = pt1[origem];
			destino = pt1[destino];
			if (!l[origem].procura(destino) && origem != destino) { // && origem != destino  p/ n ter laço
				cria_adjacencia(origem, destino, peso);;; cria_adjacencia(destino, origem, peso);  
				i++;
			}
		}

		for (i; i < arestas; ) {
			//cout << i << endl;
			origem = (rand() * rand()) % pt2.size();
			destino = (rand() * rand()) % pt2.size();
			origem = pt2[origem];
			destino = pt2[destino];
			if (!l[origem].procura(destino) && origem != destino) {
				cria_adjacencia(origem, destino, peso);;; cria_adjacencia(destino, origem, peso);  
				i++;
			}
		}

	}
	else { //caso numero de vertices impar
		for (i = 0; i < (this->tam / 2) + 1;i++)
			pt1.push_back(posicoes[i]); // pt1 recebera primeira parte das posicoes

		for (i; i < this->tam; i++)
			pt2.push_back(posicoes[i]); //pt2 recebera segunda parte das posicoes

		for (i = 0; i < arestas / 2 + 1; ) { // +1 é a unica coisa que muda
			origem = (rand() * rand()) % pt1.size();
			destino = (rand() * rand()) % pt1.size();
			origem = pt1[origem];
			destino = pt1[destino];
			if (!l[origem].procura(destino) && origem != destino) {
				cria_adjacencia(origem, destino, peso);;; cria_adjacencia(destino, origem, peso);  
				i++;
			}
		}

		for (i; i < arestas; ) {
			origem = (rand() * rand()) % pt2.size();
			destino = (rand() * rand()) % pt2.size();
			origem = pt2[origem];
			destino = pt2[destino];
			if (!l[origem].procura(destino) && origem != destino) {
				cria_adjacencia(origem, destino, peso);;; cria_adjacencia(destino, origem, peso);  
				i++;
			}
		}
	}
	// no final sera criado um grafo com no minimo 2 componentes tanto para vertices pares quanto para impares

	for (i = 0; i < pt1.size(); i++)
		cout << pt1[i] << " ";
	cout << endl;

	for (i = 0; i < pt2.size(); i++)
		cout << pt2[i] << " ";
	cout << endl;
}

// calcula o max de arestas que um grafo desconexo pode ter e retorna true se o limite foi ultrapassado
bool grafo::max_nao_direcionado_desconexo(int arestas) {
	int pt1, pt2, max_arestas;


	if (this->tam % 2 == 0) {
		pt1 = this->tam / 2;
		pt2 = this->tam / 2;
	}
	else {
		pt1 = (this->tam / 2) + 1;
		pt2 = this->tam / 2;
	}
	//divide por 2 pois é bidirecionado
	max_arestas = (pt1 * (pt1 - 1) + pt2 * (pt2 - 1)) / 2;
	cout << "Max arestas: " << max_arestas << endl;

	if (arestas > max_arestas)
		return true;
	else
		return false;

}

// verifica se um vertice nao tem nenhum adjacente
bool grafo::vertice_nulo(int vertice) {
	for (int i = 0; i < this->tam; i++) {
		if (l[vertice].procura(i) || l[i].procura(vertice))
			return false;
	}
	return true;
}


// usada para manipular o arquivo pajek
void grafo::separador(string nome_arquivo, vector<string> &arg0, vector<string> &arg1, vector<string> &arg2, vector<string> &pajek) {
	//declaração de variaveis auxiliares
	int count1 = 0, count2 = 0, linha_atual = 1, coluna = 1, i;
	bool primeira_vez = true;
	//declaracao da tabela
	vector<int> linha; //col 0
	vector<string> aux; //col 0

						//inicio da inserção do txt numa string(final)
	ifstream file(nome_arquivo);
	if (!file) {
		cout << "erro ao abrir o arquivo:" << nome_arquivo << endl;
		exit(1);
	}

	string temp;
	string final = "";

	while (getline(file, temp)) {
			aux.push_back(temp);
			pajek.push_back(temp);
	}

	//limpa_vector(aux); // limpa linhas deixando somente operador, op1, op2

	for (i = 0; i < aux.size(); i++) {
		final += aux[i];
		final.push_back(' ');
		final.push_back('\n');
	}

	// separa final em operando, arg1, arg2
	// caso tenha somente 1 op coloca 'vazio' em arg2
	//caso não tenha nenhum op coloca 'vazio' em arg1 e arg2
	for (i = 0; i < final.size(); ++i) {
		if (final[i] == '\n') {
			linha.push_back(linha_atual++);
			if (coluna == 2) {
				arg1.push_back("");
				arg2.push_back("");
			}
			else if (coluna == 3) {
				arg2.push_back("");
			}
			coluna = 1;
		}
		else if (final[i] == ' ') {
			if (coluna == 1) {
				if (primeira_vez) {
					arg0.push_back(final.substr(count1, i - (count1)));
					primeira_vez = false;
				}
				else
					arg0.push_back(final.substr(count1 + 2, i - (count1 + 2)));
				count1 = i;
				coluna++;
			}
			else if (coluna == 2) {
				arg1.push_back(final.substr(count1 + 1, i - (count1 + 1)));
				count1 = i;
				coluna++;
			}
			else if (coluna == 3) {
				arg2.push_back(final.substr(count1 + 1, i - (count1 + 1)));
				count1 = i;
				coluna++;
			}
			else {
				aux.push_back(final.substr(count1 + 1, i - (count1 + 1)));
				count1 = i;
				coluna++;
			}
		}
	}
}


// verifica se o grafo é conexo (só tem 1 componente)
bool grafo::conexo() {
	if (componentes())
		return true;
	else
		return false;
}
// igual seta_componentes - mas retorna false quando tem mais de um componente
bool grafo::componentes() {
	vector<int> conectados;
	this->id_componente = -1; // 0 componentes inicialmente
	zera_componente();
	int i, j;
	cout << "Verificando Componentes..." << endl;
	for (i = 0; i < tam; i++) { // for para verificar se todos os vertices já estão em um componente
		if (componente[i] == -1) { // se o componente[i] for -1 significa que ele ainda nao está em um componente
			busca_sem_destino(i, conectados); // faz busca profundidade bidirecionada gerando os vertices que fazem parte desse componente
											  //fila.push_back(i);
											  //busca_sem_destino_largura(fila, conectados);
			this->id_componente++; // incrementa componente 
								   //cout << id_componente << " aa" << endl;
			for (j = 0; j < conectados.size(); j++) { // atualiza o vetor componentes com o indice de todos os conectados
				componente[conectados[j]] = this->id_componente; // que fazem parte desse componente
			}
			conectados.clear();
		}
		if (id_componente >= 1) // se for maior que 1 tem 2 componentes minimo -> falso
			return false;
	}
	cout << "Componentes montados!" << endl;
	cout << "*Quantidade componentes:" << this->id_componente + 1 << endl;
	return true;
}

// metodo mais eficiente
bool grafo::encontra_ciclo(int origem, vector<int>& visitados) {
	vector<int> adj;
	if (!visitados.empty()) {
		if (origem == visitados.at(0)) {
			visitados.push_back(origem);
			return true;
		}
	}

	if (!(foi_visitado(origem, adj))) {
		visitados.push_back(origem);
		adj.clear();
		adjacentes(origem, adj);
		for (int i = 0; i < adj.size(); i++) {
			if (bool x = encontra_ciclo(adj[i], visitados)) {
				return true;
			}
		}
	}
	return false;
}


bool grafo::ciclico() {
	bool ciclo = false;
	vector<int> visitados, copia;
	for (int i = 0; i < this->tam; i++) {
		busca_ciclico(i, visitados, &ciclo, copia);
		if (ciclo)
			return true;
		visitados.clear();
	}
	return false;
}


int grafo::busca_ciclico(int origem, vector<int> & visitados, bool * ciclico, vector<int> copia) {
	if (!foi_visitado(origem, visitados)) {
		visitados.push_back(origem);
		copia.push_back(origem);
		vector<int> adj;
		adjacentes(origem, adj);
		for (int i = 0; i < adj.size(); i++) {
			if (int x = busca_ciclico(adj[i], visitados, ciclico, copia) != 0) {
				return true;
			}
		}	
	}
	else {
		*ciclico = true; // se já estiver nos visitados forma uma ciclo
	}
	return false;
}

// busca sem destino direcionada 
int grafo::busca_sem_destino_direcionada(int origem, vector<int> & visitados) {
	if (!foi_visitado(origem, visitados)) {
		visitados.push_back(origem);
		vector<int> adj;
		adjacentes(origem, adj);
		for (int i = 0; i < adj.size(); i++) {
			if (int x = busca_sem_destino_direcionada(adj[i], visitados) != 0) {
				return true;
			}
		}
	}
	return false;
}

//busca largura sem destino bidirecionada
int grafo::busca_sem_destino_largura(list<int> & fila, vector<int> & visitados) {
	if (fila.empty())
		cout << "Destino nao existe!" << endl;
	else {
		cout << visitados.size() << endl;
		int x = fila.front();
		fila.pop_front();
		visitados.push_back(x);
		vector<int> y;
		vector<int> adj;
		adjacentes_bidirecional(x, adj); // retorna adjacentes do vertice x e coloca em um vector adj
		for (int i = 0; i < adj.size(); i++) {
			if (!foi_visitado(adj[i], visitados) && !pertence(adj[i], fila))
				y.push_back(adj[i]);
		}
		for (int i = 0; i < y.size(); i++) {
			fila.push_back(y[i]);
		}
		return busca_sem_destino_largura(fila, visitados);

	}
}

// busca profundidade sem destino bidirecionada
int grafo::busca_sem_destino(int origem, vector<int> & visitados) {
	
	if (!foi_visitado(origem, visitados)) {
		visitados.push_back(origem);
		vector<int> adj;
		adjacentes_bidirecional(origem, adj);
		for (int i = 0; i < adj.size(); i++) {
			if (int x = busca_sem_destino(adj[i], visitados) != 0) {
				return true;
			}
		}
	}
	return false;
}

//pilha nao pode ultrapassar 5000 chamadas recursivas na buca sem destino 
int grafo::seta_componentes() {
	vector<int> conectados;
	list<int> fila;
	this->id_componente = -1; // 0 componentes inicialmente
	zera_componente();
	int i, j;
	cout << "Verificando Componentes..." << endl;
	for (i = 0; i < tam; i++) { // for para verificar se todos os vertices já estão em um componente
		if (componente[i] == -1) { // se o componente[i] for -1 significa que ele ainda nao está em um componente
			busca_sem_destino(i, conectados); // faz busca profundidade bidirecionada gerando os vertices que fazem parte desse componente
			//fila.push_back(i);
			//busca_sem_destino_largura(fila, conectados);
			this->id_componente++; // incrementa componente 
			//cout << id_componente << " aa" << endl;
			for (j = 0; j < conectados.size(); j++) { // atualiza o vetor componentes com o indice de todos os conectados
				componente[conectados[j]] = this->id_componente; // que fazem parte desse componente
			}
			conectados.clear();
			fila.clear();
		}
	}
	cout << "Componentes montados!" << endl;
	cout << "*Quantidade componentes:" << this->id_componente + 1 << endl;
	imprime_componentes();
	return this->id_componente+1;
}

// imprime todos os componentes do grafo, formatado
void grafo::imprime_componentes() {
	// imprimir componentes formatados
	for (int i = 0; i <= id_componente; i++) {
		cout << "Componente " << i << ": { ";
		for (int j = 0; j < tam; j++) {
			if (i == componente[j])
				cout << j << " , ";
		}
		cout << "} " << endl;
	}
}

// retorna se um grafo tem adj com outro vertice, n importando a direcao
int grafo::adjacentes_bidirecional(int i, vector<int> & adj) {
	int j, cont = 0;

	if (!indice_valido(i, -1))
		return 0;

	for (j = 0; j < tam; j++) {
		if (l[i].procura(j) || l[j].procura(i)) { // verifica se é diferente de infinito, caso seja cont++
			cont++;
			adj.push_back(j); // coloca no vetor de adjacente somente os indices  que são adjacentes
		}
	}
	return cont;
}

//zera vetor de componentes
void grafo::zera_componente() {
	for (int i = 0;i < tam; i++) 
		componente[i] = -1;
}

//retorna quantidade de arestas do grafo
int grafo::quantidade_arestas() {
	int cont = 0;
	for (int i = 0; i < this->tam; i++)
		cont = cont + adjacentes(i);
	return cont;
}


//pra guardar o subgrafo gerado com o prim
typedef struct arestas { 
	int origem;
	int destino;
	int peso;
}Arestas;

//usado para montar uma arestar e colocar em um vector.
Arestas monta_aresta(int s, int t, int p) { // s =origem, t = destino
	Arestas  A1;
	A1.origem = s;
	A1.destino = t;
	A1.peso = p;
	return A1;
}

// algoritmo de prim para gerar subgrafo que contenha todas os vertices do grafo (tem que ser conexo)
void grafo::prim(int origem) {
	vector<Arestas> A, X; // A1 CONTERÁ O SUBGRAFO (ORIGEM-DESTINO-PESO) E X TODOS AS ARESTAS
	vector<int> S, adj;
	Arestas aux; // usado para montar aresta (origem-destino-peso)

	S.push_back(origem); // vertice de origem é add a s
	int i = origem; // i recebe o vertice de origem
	int j = 0, aresta = INFINITO, custo_minimo = 0,peso;

	while (S.size() < this->tam) { // enquanto S nao contém todos os vértices de G faça
		adjacentes(i, adj); // vetor de adjacentes pra colocar em X

		for (int k = 0; k < adj.size(); k++) { // for para adicionar a X o conjunto de arestas e vertices de adj[i]
			if (!foi_visitado(adj[k], S)) { // só coloca se nao foi visitado
				peso = l[i].retorna_peso(adj[k]);
				aux = monta_aresta(i, adj[k], peso); // monta a aresta
				X.push_back(aux); // coloca em X a aresta montada
				cout << "(X)  i: " << i << "/ k: " << adj[k] << "/aresta:" << l[i].retorna_peso(adj[k]) << endl;
			}
		}
		
		for (int k = 0; k < X.size(); k++) { // for para encontrar menor aresta e criar o conjunto (s,t,p) para adicionar na saida A1
			if (X[k].peso < aresta && !foi_visitado(X[k].destino, S)) {
				aresta = X[k].peso;
				j = X[k].destino; // j recebe o nova origem para proxima iteracao
				aux.origem = X[k].origem;
				aux.destino = X[k].destino;
				aux.peso = X[k].peso;
			}
		}
		
		A.push_back(aux); // coloca a saída com a menor aresta de x em A1
		aresta = INFINITO; // para comparar novamente depois
		i = j;
		adj.clear();
		S.push_back(j); // j contém o vertice com menor custo que ainda não foi colocado no grafo.
		cout << endl;
	}

	for (i = 0; i < S.size();i++)
		cout << "S: " << S[i] << endl;

	//saida de A está pronta para criar o subgrafo
	for (int i = 0; i < A.size();i++) {
		cout << "(A) origem: " << A[i].origem << "/destino: " << A[i].destino << "/peso: " << A[i].peso << endl;
		custo_minimo += A[i].peso;
	}

	//for (int i = 0; i < X.size();i++) 
	//	cout << "Xorigem: " << X[i].origem << "/destino: " << X[i].destino << "/peso: " << X[i].peso << endl;

	cout << endl << "Custo Minimo:" << custo_minimo << endl;

}


//verifica se um grafo eh euleriano
bool grafo::euleriano() {
	int cont = 0;
	for (int i = 0; i < this->tam;i++) {
		if ((adjacentes(i) % 2) != 0)
			cont++;
		if (cont > 2)
			return 0;
	}   

	if (cont == 2 || cont == 0)
		return 1;
	else
		return 0;

}


//_ALGORITMOS TRABALHO BIMESTRAL 
// lista as 20 emails(vertices) que tem maior grau de saida e os 20 emails(vertices)
//que tem o maior grau de entrada
// QUESTÃO 2
void grafo::top_20_sends() {
	vector<pair<int, int>> top_20; //first = id_vertice //second = peso_total (enviados por esse id_vertice(email))
	int cont_gene=0, cont_doenca=0;
	unsigned int j, i, cont = 0;

	for (i = 0; i < tam;i++) {
		cont = this->adjacentes(i);
		top_20.push_back(make_pair(i, cont));
	}

	heapsort_second(top_20); // heapsort no pair pra ordenar
	reverse(top_20.begin(), top_20.end());

	/*
	//pega as 20 últimas posições (que são as maiores)
	cout << "Top 20 individuos que possuem maior grau de saida e o valor correspondente! " << endl;

	for (i = 0; i < top_20.size() && i < 20; i++) {
		cout << i + 1 << "- Email: " << vertices[top_20[i].first].get_nome();
		cout << ", Quantidade de saidas (arestas p/ outros emails): " << top_20[i].second << endl;
	}
	*/
	cout << "\n\n\nTop 20 vertices que possuem maior grau de saida e o valor correspondente! " << endl;
	
	for (i = 0, j = 0; i < top_20.size() && j < 20; i++) {
		if (!eh_stop_word(id_to_email(top_20[i].first))) {
			cout << i + 1 << "- Rotulo: " << vertices[top_20[i].first].get_nome();
			cout << ", Quantidade de saidas : " << top_20[i].second << endl;
			j++;
		}
	}

	for (i = 0; i < top_20.size(); i++) {
		if (top_20[i].second == 0)
			break;
	}
	cont_gene = i;

	top_20.clear();

	// pegando os 20 que tem maior grau de entrada
	for (j = 0, cont = 0; j < tam; j++) {
		for (i = 0; i < tam; i++) {
			if (l[i].procura(j)) { // verifica se é diferente de infinito, caso seja cont++
				cont++; //cont = cont + l[i].retorna_peso(j);
			}
		}
		//cout << "Email: " << vertices[i].get_nome()  << ", Peso Vertice " << i << " igual a: " << cont  <<  " Emails eviandos" << endl;
		top_20.push_back(make_pair(j, cont));
		cont = 0;
	}

	heapsort_second(top_20);
	reverse(top_20.begin(), top_20.end());
	/*
	cout << "\n\n" << "Top 20 individuos que possuem maior grau de entrada e o valor correspondente! " << endl;
	for (i = 0; i < top_20.size() && i < 20; i++) {
		cout << i + 1 << "- Email: " << vertices[top_20[i].first].get_nome();
		cout << ", Quantidade de saidas (arestas p/ outros emails): " << top_20[i].second << endl;
	}
	*/
	cout << "\n\n" << "Top 20 vertices que possuem maior grau de entrada e o valor correspondente! " << endl;
	for (i = 0, j = 0; i < top_20.size() && j < 20; i++) {
		if (!eh_stop_word(id_to_email(top_20[i].first))) {
			cout << i + 1 << "- Rotulo: " << vertices[top_20[i].first].get_nome();
			cout << ", Quantidade de saidas: " << top_20[i].second << endl;
			j++;
		}
	}

	for (i = 0; i < top_20.size(); i++) {
		if (top_20[i].second == 0)
			break;
	}
	cont_doenca = i;

	cout << "Quantidade de doencas na base: " << cont_doenca << endl;
	cout << "Quantidade de genes na base: " << cont_gene << endl;

}


//QUESTÃO 3
// algoritmo busca_profundidade - algoritmo professor
int grafo::busca_profundidade(int origem, int destino, vector<int> & visitados) {
	if (origem == destino) {
		visitados.push_back(origem);
		return destino;
	}
	else if (!foi_visitado(origem, visitados)) {
		visitados.push_back(origem);
		vector<int> adj;
		adjacentes(origem, adj);
		for (int i = 0; i < adj.size(); i++) {
			if (int x = busca_profundidade(adj[i], destino, visitados) != 0) {
				return x;
			}
		}
	}
	//if (!visitados.empty())
	//	visitados.pop_back();
	return 0;
}


// verifica se um vertice já foi visitado ( está no vector visitados) (usado na busca_profundidade)

bool grafo::foi_visitado(int valor, vector<int> visitados) {
	for (int i = 0; i < visitados.size(); i++) {
		if (valor == visitados[i])
			return true;
	}
	return false;
}

//QUESTÃO 4
// algoritmo busca_largura - algoritmo professor
int grafo::largura(int destino, list<int> & fila, vector<int> & visitados) {
	if (fila.empty())
		cout << "Destino nao existe!" << endl;
	else {
		int x = fila.front();
		fila.pop_front();
		visitados.push_back(x);
		if (x == destino) {
			return x;
		}
		else {
			vector<int> y;
			vector<int> adj;
			adjacentes(x, adj); // retorna adjacentes do vertice x e coloca em um vector adj
			for (int i = 0; i < adj.size(); i++) {
				if (!foi_visitado(adj[i], visitados) && !pertence(adj[i], fila))
					y.push_back(adj[i]);
			}
			for (int i = 0; i < y.size(); i++) {
				fila.push_back(y[i]);
			}
			return largura(destino, fila, visitados);
		}
	}
}

//calcula vertices que estão a uma distancia x de um determinado vertice
int grafo::largura_distancias(int max_distancia, list<int> & fila, vector<int> & visitados, vector <pair<int, int>> & id_distancia) {
	if (fila.empty())
		cout << "Foram calculadas todas as distancias e chegou ao fim do grafo!" << endl;
	else {
		int x = fila.front();
		fila.pop_front();
		visitados.push_back(x);

			vector<int> y;
			vector<int> adj;
			adjacentes(x, adj); // retorna adjacentes do vertice x e coloca em um vector adj
			if (adj.size() > 0) {
				int nivel = busca_nivel_x(x, id_distancia);
				nivel++; // coloca os adjacentes com um nivel incrementado
				if (nivel > max_distancia) {
					return 0; // nao precisa continuar pq já pegou as distancias retornadas
				}

				for (int i = 0; i < adj.size(); i++) {
					if (!foi_visitado(adj[i], visitados) && !pertence(adj[i], fila)) {
						y.push_back(adj[i]);
						id_distancia.push_back(make_pair(adj[i], nivel)); // modificacao

					}
				}
				//insertionsort(id_distancia);
				heapsort(id_distancia); // ordena pra fazer busca binaria da distancia depois
				for (int i = 0; i < y.size(); i++) {
					fila.push_back(y[i]);
				}
			}
			
			return largura_distancias(max_distancia, fila, visitados, id_distancia);
		
	}
}

int grafo::busca_nivel_x(int x, vector <pair<int, int>> & id_distancia) {
	return busca_binaria(x, id_distancia);
}


// verifica se um valor está na fila, true se estiver, false se não estiver  (usado na largura)
bool grafo::pertence(int valor, list<int> fila) {
	list<int>::iterator it;
	for (it = fila.begin(); it != fila.end(); it++) {
		if (*it == valor)
			return true;
	}
	return false;
}


// algoritmo de warshall - material
void grafo::faz_fechamento() {
	int i, j, k;

	if (!fechamento) {
		cout << "Matriz de fechamento nao foi criada pois tamanho excedeu o limite" << endl;
		exit(0);
	}

	// inicialização da matriz de fechamento
	for (i = 0; i < tam; i++)
	{
		for (j = 0; j < tam; j++)
		{
			if (l[i].procura(j))
				fechamento[i][j] = 1;
			else
				fechamento[i][j] = 0;
		}
	}

	// algoritmo de Warshall
	for (k = 0; k < tam; k++)
	{
		for (i = 0; i < tam; i++)
		{
			if (fechamento[i][k])
				for (j = 0; j < tam; j++)
					fechamento[i][j] = fechamento[i][j] || fechamento[k][j];
		}
	}
}

// imprime a matriz de fechamento (utilizar após warshall)
void grafo::imprime_fechamento() {
	int i, j;
	cout << "Matriz de fechamento:" << endl;

	for (i = 0; i < tam; i++) cout << "\t" << i; cout << endl << endl;

	for (i = 0; i < tam; i++) {
		cout << i << "\t";
		for (j = 0; j < tam; j++) {
			cout << fechamento[i][j] << "\t";
		}
		cout << "Vertice[" << i << "]: \"" << vertices[i].get_nome() << "\"" << endl;
	}
}

// algoritmo de dijkstra
int grafo::melhorCaminho(int s, int t) {
	if (!indice_valido(s, t))
		return -1;

	faz_fechamento();

	if (!fechamento[s][t])
		return -1;

	int* distancia = new int[tam];
	bool* perm = new bool[tam];
	int corrente, i, k = s, dc, j = 0;

	int menordist, novadist = 0;

	//inicialização
	for (i = 0; i < tam; ++i) {
		perm[i] = NAOMEMBRO;
		distancia[i] = INFINITO;
		caminho[i] = -1;
	}
	perm[s] = MEMBRO;
	distancia[s] = 0;
	corrente = s;
	while (corrente != t) {
		menordist = INFINITO;
		dc = distancia[corrente];
		for (i = 0; i < tam; i++) {
			if (!perm[i]) {
				// if (l[corrente].procura(i))
				novadist = dc + l[corrente].retorna_peso(i);
				if (novadist < distancia[i]) {
					distancia[i] = novadist;
					caminho[i] = corrente;
				}
				if (distancia[i] < menordist) {
					menordist = distancia[i];
					k = i;
				}
			}
		}
		corrente = k;

		perm[corrente] = MEMBRO;
	}

	imprimirDijkstra(s, t);
	return distancia[t];
}


//mostra o caminho com mais peso de um vertice s até t
double grafo::piorCaminho2(int s, int t) {
	if (!indice_valido(s, t))
		return -1;

	faz_fechamento();

	if (!fechamento[s][t])
		return -1;

	double* distancia = new double[tam];
	double* distancia_real = new double[tam];
	bool* perm = new bool[tam];
	int corrente, i, k = s, j = 0;

	double dc, dc_real, menordist, novadist = 0, novadist_real = 0;

	//inicialização
	for (i = 0; i < tam; ++i) {
		perm[i] = NAOMEMBRO;
		distancia[i] =  INFINITO;
		distancia_real[i] = INFINITO;
		caminho[i] = -1;
	}
	perm[s] = MEMBRO;
	distancia[s] = 0;
	distancia_real[s] = 0;
	corrente = s;
	while (corrente != t) {
		menordist = INFINITO;
		dc = distancia[corrente];
		dc_real = distancia_real[corrente];
		for (i = 0; i < tam; i++) {
			if (!perm[i]) {
				// if (l[corrente].procura(i)) {
				novadist = dc + l[corrente].retorna_peso_inverso(i); // usado para calculos
				novadist_real = dc_real + l[corrente].retorna_peso(i); // armazena o peso real p/ retornar
				if (novadist < distancia[i]) {
					distancia_real[i] = novadist_real;
					distancia[i] = novadist;
					caminho[i] = corrente;
				}
				if (distancia[i] < menordist) {
					menordist = distancia[i];
					k = i;
				}
			}
		}
		corrente = k;

		perm[corrente] = MEMBRO;
	}

	imprimirDijkstra(s, t);
	return distancia_real[t];
}

// imprime o caminho gerado pelo dijkstra ( inverte o caminho p/ imprimir s -> t)
void grafo::imprimirDijkstra(int s, int t) {
	unsigned int i = caminho[t];
	vector<string> inverte;
	//cout << "Caminho detalhado: ";
	//cout << "Destino<-" << vertices[t].get_nome() << "<-";
	inverte.push_back(vertices[t].get_nome());
	while (i != s) {
		//cout << vertices[i].get_nome() << "<-";
		inverte.push_back(vertices[i].get_nome());
		i = caminho[i];
	}

	//cout << vertices[s].get_nome() << "<-Origem" << endl;
	inverte.push_back(vertices[s].get_nome());

	reverse(inverte.begin(), inverte.end());
	 
	cout << "Caminho detalhado:" << endl << "Origem: ";
	for (i = 0; i < inverte.size(); i++)
		cout << inverte[i] << " -> ";
	cout << " :Destino" << endl;

}


void vertice::set_nome(string nome) {
	this->nome = nome;
}
string vertice::get_nome() {
	return this->nome;
}

vertice::vertice() { }
vertice::~vertice() { }

// cria adj. Se já existir só incrementa o peso
void grafo::cria_adjacencia(int i, int j, int P) {

	if (indice_valido(i, j)) { // se o indice for válido
		if (!l[i].procura(j)) // se procura retorna false, nao existe adj criada
			l[i].insere_em_ordem(j, P);
		else
			l[i].atualiza_adjacencia(j);
	}
	else
		return;
}


// cria adj i j e j i. Se já existir só incrementa o peso
void grafo::cria_adjacencia_bidirecional(int i, int j, int P) {
	
	if (indice_valido(i, j)) { // se o indice for válido
		if (!l[i].procura(j)) {// se procura retorna false, nao existe adj criada
			l[i].insere_em_ordem(j, P);
			l[j].insere_em_ordem(i, P);
		}
		else {
			l[i].atualiza_adjacencia(j);
			l[j].atualiza_adjacencia(i);
		}
			
	}
	else
		return;
}

// remove adj se existir 
void grafo::remove_adjacencia(int i, int j) {
	
	if (indice_valido(i, j))
		l[i].retira_elemento(j);
	else
		return;
	
}


void grafo::remove_adjacencia_bidirecional(int i, int j) {

	if (indice_valido(i, j)) {
		l[i].retira_elemento(j);
		l[j].retira_elemento(i);
	}
		
	else
		return;

}

//imprime adjacencia (modo lista)
void grafo::imprime_adjacencia() {
	
	int i,j;
	cout << "Lista de adjacencia:" << endl;
	for (i = 0; i < tam; i++) {
		cout << "Vertice[" << i << "]: \" " << vertices[i].get_nome() << " \" : "; // depois de imprimir l[i] mostra o nome e pula linha
		l[i].imprime();
		cout << endl;
	}
	/*
	cout << endl << "Forma matricial: " << endl;
	for (i = 0; i < tam; i++) cout << "\t" << i; cout << endl << endl;


	for (i = 0; i < tam; i++) {
		cout << i << "\t";
		for (j = 0; j < tam; j++) {
			if (l[i].procura(j))
				cout << l[i].retorna_peso(j) << "\t"; // retorna o peso caso a adjacencia ij existir
			else
				cout << INFINITO << "\t"; // caso a adjacencia ij não existir o programa imprime infinito
		}
		cout << "Vertice[" << i << "]: \"" << vertices[i].get_nome() << "\"" << endl;
	}
	*/
}

//imprime adj não nulas
void grafo::imprime_adjacencia_nao_vazia() {

	int i, j, cont, total=0;
	cout << "Lista de adjacencia:" << endl;

	for (i = 0; i < tam; i++) {
		cont = adjacentes(i);
		if (cont > 0) {
			cout << "Vertice[" << i << "]: \" " << vertices[i].get_nome() << " \" : "; // depois de imprimir l[i] mostra o nome e pula linha
			l[i].imprime();
			total++;
		}
		if (cont > 0)
			cout << endl;
	}

	cout << "Quantidade de adjacencias nao vazias:" << total << endl;
}
//*****
//encontra o vertice que tem maior peso de saida
void grafo::maior_contato() {
	int peso = 0, max = 0, from, to, i, j;
	for (i = 0; i < this->tam; i++) {
		if (!l[i].vazia()) {
			for (j = 0; j < this->tam; j++) {
				peso = l[i].retorna_peso(j);
				if (peso > max && peso != INFINITO) {
					max = peso;
					from = i;
					to = j;
				}
			}
		}
	}

	cout << "Pessoa que mais enviou email para outra pessoa" << endl <<
		"From: " << id_to_email(from) << " , To: " << id_to_email(to) <<
		" Quantidade de emails: " << max << endl;
} // quem mais enviou email para uma unica pessoa

// verifica se o indice passado pelo usuario é valido
bool grafo::indice_valido(int i, int j) {
	
	if (i >= tam || j >= tam) {
		cout << "indice invalido" << endl;
		return false;
	}
	else if (i == j) {
		//cout << "diagonal principal - to == from (permitido) " << endl;
		return true;
	}
	else
		return true; 
}

// muda rótulo(emails)
void grafo::seta_informacao(int i, string V) { 
	if (indice_valido(i, -1)) // -1 para passar pelas condições de indice válido, pois aqui só utiliza o indice 'i'
		vertices[i].set_nome(V); // seta o nome do vertice i
	else
		return; 
}

// verifica quais indices são adjacences de i (pra quem x pessoa mandou email) e coloca esses indices em um vector
int grafo::adjacentes(int i, vector<int> & adj) {
	int j, cont = 0;

	if (!indice_valido(i, -1))
		return 0;

	for (j = 0; j < tam; j++) {
		if (l[i].procura(j)) { // verifica se é diferente de infinito, caso seja cont++
			cont++;
			adj.push_back(j); // coloca no vetor de adjacente somente os indices  que são adjacentes
		}
	}
	return cont;
}


// verifica quais indices são adjacences de i (pra quem x pessoa mandou email) e coloca esses indices em um vetor
int grafo::adjacentes(int i, int * adj) { 
	int j, cont = 0;

	if (!indice_valido(i, -1))
		return 0;

	for (j = 0; j < tam; j++) {
		if (l[i].procura(j)) { // verifica se é diferente de infinito, caso seja cont++
			cont++;
			adj[j] = j; // coloca no vetor de adjacente somente os indices  que são adjacentes
		}
	}
	return cont; 
	return 0;
}

//sobrecarga - usa quando só precisa da quantidade de adjacentes e não do indice
int grafo::adjacentes(int i) {
	int j, cont = 0;

	if (!indice_valido(i, -1))
		return 0;
	
	for (j = 0; j < tam; j++) {
		if (l[i].procura(j)) { // verifica se é diferente de infinito, caso seja cont++
			cont++;
		}
	}
	return cont;
}


// verifica quais indices são adjacences de i (pra quem x pessoa mandou email) e coloca esses indices em um vector
int grafo::top_adjacentes(int i, vector<pair<int, int >> & adj_peso) {
	int j, cont = 0, peso;
	//cout << "Palavra: " << id_to_email(i) << endl; 
	if (!indice_valido(i, -1))
		return 0;

	for (j = 0; j < tam; j++) {
		if (l[i].procura(j)) { // verifica se é diferente de infinito, caso seja cont++
			cont++;
			peso = l[i].retorna_peso(j);
			adj_peso.push_back(make_pair(j, peso)); // coloca no vetor de adjacente somente os indices  que são adjacentes
		}
	}

	heapsort_second(adj_peso);
	reverse(adj_peso.begin(), adj_peso.end());
	
	if (adj_peso.size() > 5) {
		for (j = 0; j < 5;j++)
			cout << "ADJ: \"" << id_to_email(adj_peso[j].first) << "\" Peso: " << adj_peso[j].second << endl;
	}
	else {
	for (j = 0; j < adj_peso.size();j++) 
		cout << "ADJ: \"" << id_to_email(adj_peso[j].first) << "\" Peso: " << adj_peso[j].second << endl;
	}

	return cont;
}

int grafo::forma_frase(int i, int tamanho_frase) {
	int j, cont = 0, peso,k;
	string final;
	vector<pair<int, int >> adj_peso;

	if (!indice_valido(i, -1))
		return 0;
	for (k = 0; k < tamanho_frase; k++) {
		cout << "Palavra: " << id_to_email(i) << endl;
		for (j = 0; j < tam; j++) {
			if (l[i].procura(j)) { // verifica se é diferente de infinito, caso seja cont++
				cont++;
				peso = l[i].retorna_peso(j);
				adj_peso.push_back(make_pair(j, peso)); // coloca no vetor de adjacente somente os indices  que são adjacentes
			}
		}
		heapsort_second(adj_peso);
		reverse(adj_peso.begin(), adj_peso.end());

		if (adj_peso.size() > 5) {
			for (j = 0; j < 5;j++)
				cout << "ADJ: \"" << id_to_email(adj_peso[j].first) << "\" Peso: " << adj_peso[j].second << endl;
		}
		else {
			for (j = 0; j < adj_peso.size();j++)
				cout << "ADJ: \"" << id_to_email(adj_peso[j].first) << "\" Peso: " << adj_peso[j].second << endl;
		}

		if (adj_peso.empty())
			break;
		final = final + " " + id_to_email(i);
		i = adj_peso[0].first;
		adj_peso.clear();
	}

	cout << "Frase final: " << final << endl;

	return cont;
}

//retorna tam do grafo (quantidade  de vertices);
int grafo::get_tam() {
	return this->tam;
}

//entra com o id do vertice e retorna o rotulo
string grafo::id_to_email(int id_vertice) {
	if (indice_valido(id_vertice, 0))
		return vertices[id_vertice].get_nome();
	return "Rotulo invalido!";
}

// entra com o rotulo e retorna o id do vertice
int grafo::email_to_id(string email) {
	//return busca_binaria(email, this->vertices);
	int max, i;
	max = this->tam;

	//opcao para rotulos ordenados
	return busca_binaria(email, vertices);
	/*
	for (i = 0; i < max; i++) {
		if (vertices[i].get_nome() == email)
			return i;
	}
		return -1;
	*/
}


bool grafo::bidirecional() {
	for (int i = 0; i < this->tam; i++) {
		for (int j = 0; j < this->tam; j++) {
			if (!l[i].procura(j) && l[j].procura(i))
				return false;

			else if (!l[j].procura(i) && l[i].procura(j))
				return false;
		}
	}
	return true;
}



// algoritmos de sort utilizados para melhorar a performance em alguns métodos 

void grafo::heapsort(vector<pair<int, int>> & pair) {
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
			if ((filho + 1 < n) && (pair[filho + 1].first > pair[filho].first))
				filho++;
			if (pair[filho].first > t1) {
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


} // ordena pelo first (id)

void grafo::heapsort_second(vector<pair<int, int>> & pair) {
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

void grafo::heapsort(int* a, int n) {

	int i = n / 2, pai, filho, t;
	for (;;) {
		if (i > 0) {
			i--;
			t = a[i];
		}
		else {
			n--;
			if (n == 0) return;
			t = a[n];
			a[n] = a[0];
		}
		pai = i;
		filho = i * 2 + 1;
		while (filho < n) {
			if ((filho + 1 < n) && (a[filho + 1] > a[filho]))
				filho++;
			if (a[filho] > t) {
				a[pai] = a[filho];
				pai = filho;
				filho = pai * 2 + 1;
			}
			else {
				break;
			}
		}
		a[pai] = t;
	}
}

void grafo::inicializa_stop_word() {
	ifstream file;
	string temp;
	int tam;
	file.open("stop_words.txt");
	

	if (!file) {
		cout << "erro ao abrir arquivo stop_words" << endl;
		exit(0);
	}

	while (getline(file, temp))
		stop_words.push_back(temp);
	
	tam = stop_words.size();
	for (int i = 0; i < tam; i++) {
		temp = toupper(stop_words[i][0]);
		temp = temp  +  stop_words[i].substr(1, stop_words[i].size() - 1);
		stop_words.push_back(temp);
	}
}

bool grafo::eh_stop_word(string palavra){
	for (int i = 0; i < stop_words.size(); i++) {
		if (stop_words[i] == palavra)
			return true;
	}
	return false;
}

int grafo::busca_binaria(string procurado, vertice * vertices) {
	int inf, media, sup;
	inf = 0; sup = this->tam - 1;
	while (inf <= sup) {
		media = (inf + sup) / 2;
		if (vertices[media].get_nome() == procurado)
			return media; // id do vertice
		if (vertices[media].get_nome() < procurado)
			inf = media + 1;
		else
			sup = media - 1;
	}
	return -1;
}

int grafo::busca_binaria(int verificador, vector<pair<int, int>> dicionario) {

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

vector<string> grafo::tokenizer(vector<string> linhas, string retirar) {
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

vector<string> grafo::tokenizer(string linhas, string retirar) {
	vector<string> str;
	str.push_back(linhas);
	return tokenizer(str, retirar);
}


grafo::~grafo() {

}

// inicializa vetor ( não utilizado )
int * grafo::inicializa_vetor() {
	int * vetor = new int[tam];
	for (int i = 0; i < tam; vetor[i] = -1, i++); // inicializa todos os indices com -1 
	return vetor;
	return 0;
}