/*
Trabalho Bimestral de Grafos
Nome: Edson Monteiro, Lucca Portes
*/
#include "Grafo.h"
#include "lista_encadeada.h"
#include "trata_arquivo.h"
#include "gera_endereco.h"
#include <iostream>
using namespace std;


int main() {
	int i, j, ch, P, valor, from, to, tam, cont, origem, destino, distancia;
	char escolha, direcionado;
	string email, V, _from, _to;
	int arestas;

	//teste

	grafo * G = grafo::fabrica_grafo();


	//Modo super rapido
	/*
	vector<string> enderecos;
	gera_endereco * GE = new gera_endereco("base_genes");
	enderecos = GE->gerador();
	GE->~gera_endereco();

	trata_arquivo * A = new trata_arquivo(enderecos);
	grafo * G = A->armazena_adjacencias();
	G->grava_pajek();
	
	*/
	/*
	grafo * G = new grafo(7);

	G->cria_adjacencia_bidirecional(0,1 , 1);
	G->cria_adjacencia_bidirecional(0,2 , 1);
	G->cria_adjacencia_bidirecional(0,3 , 1);
	G->cria_adjacencia_bidirecional(0,4 , 1);
	G->cria_adjacencia_bidirecional(0,5 , 1);
	G->cria_adjacencia_bidirecional(0,6 , 1);
	G->cria_adjacencia_bidirecional(3,4 , 1);
	G->cria_adjacencia_bidirecional(5,6 , 1);
	*/
	/*
	for (i = 0; i < G->get_tam(); i++)
		cout << "CLoseness de " << i << " : " << G->centralidade_de_proximidade(i) << endl;

	for (i = 0; i < G->get_tam(); i++)
		cout << "Betweeness de " << i << " : " << G->centralidade_de_intermediacao(i) << endl;
	*/
	

	
	 
	
	
	do {
		cout << "\nO que deseja fazer?\n";
		cout << "1- Criar adjacencia\n";
		cout << "2- Remover adjacencia\n";
		cout << "3- Imprimir matriz de adjacencia\n";
		cout << "4- Setar informacao\n";
		cout << "5- Verificar adjacentes\n";
		cout << "6- (Warshall) Fazer e imprimir matriz de fechamento \n";
		cout << "7- (Dijkstra) Calcular menor caminho entre dois vertices(que tem menor peso)\n";
		//cout << "____________Trabalho Bimestral___________" << endl;
		cout << "8- quantidade de VERTICES, ARESTAS e top 20 entrada e saida" << endl;
		cout << "9- Busca Profundidade" << endl;
		cout << "10- Busca Largura " << endl;
		cout << "11- Busca com distancia especifica (LARGURA Modificado) " << endl;
		cout << "12- (Dijkstra INVERSO)Calcular MAIOR caminho entre dois vertices(que tem maior peso)\n";
		cout << "13- Gerar arvore geradora minima (PRIM)" << endl;
		cout << "14- Verificar quantidade de componentes Fracamente conectados" << endl;
		cout << "____________Trabalho Bimestral 2___________" << endl;
		cout << "15- Gravar pajek em arquivo TXT" << endl;
		cout << "16- Carregar pajek de um arquivo TXT" << endl;
		cout << "17- Verificar se o grafo eh CONEXO" << endl;
		cout << "18- Verificar se o grafo eh EULERIANO" << endl;
		cout << "19- Verificar se o grafo eh CICLICO" << endl;
		cout << "20- Verificar centralidade de POSICIONAMENTO de um determinado vertice" << endl;
		cout << "21- Verificar centralidade de INTERMEDIACAO de um determinado vertice" << endl;
		cout << "30- Verificar se o grafo eh BIDIRECIONADO" << endl;
		cout << "31- Verificar top adjacentes e o peso" << endl;
		cout << "32- Verificar adjacentes bidirecionado" << endl;
		//cout << "32- Formar frase a partir dos adj" << endl; */
		cout << "0- Sair\n\n";
		cout << "Escolha: ";
		cin >> ch;

		switch (ch) {
		case 1: {
			system("CLS");
			cout << "\nDigite a posicao i, e j e o valor P do vertice que deseja criar: " << endl << "i: ";
			cin >> i;
			cout << "j: ";
			cin >> j;
			cout << "P: ";
			cin >> P;
			G->cria_adjacencia(i, j, P);
			break;
		}
		case 2: {
			system("CLS");
			cout << "\nDigite a posicao i, e j que deseja remover: " << endl << "i: ";
			cin >> i;
			cout << "j: ";
			cin >> j;
			G->remove_adjacencia(i, j);
			break;
		}
		case 3: {
			system("CLS");
			G->imprime_adjacencia();
			break;
		}
		case 4: {
			system("CLS");
			cout << "Digite o id do vertice 'i' e o rotulo/nome do vertice: " << endl << "i: ";
			cin >> i;
			cin.ignore(); // limpa o buffer do teclado
			cout << "Rotulo: ";
			getline(cin, V); // pra pegar nomes com espaço
			G->seta_informacao(i, V);
			break;
		}
		case 5: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite o rotulo que deseja verificar: " << endl << "ROTULO: ";
				cin.ignore();
				getline(cin, _from);
				//cin >> _from;
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				if (i == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "Digite a ID do vertice que deseja verificar: ";
				cin >> i;
			}

			vector<int> adj;

			cout << "quantidade de adjacentes: " << G->adjacentes(i, adj) << endl;
			cout << "Indices do Vetor de adjacentes: [ ";
			for (i = 0; i < adj.size(); i++) {
				
				cout << adj[i] << " " << G->id_to_email(adj[i]) << " / ";
			}
			cout << "]" << endl;

			adj.clear();
			break;
		}
		case 6: {
			system("CLS");
			G->faz_fechamento();
			G->imprime_adjacencia();
			G->imprime_fechamento();
			break;

		}
		case 7: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite FROM , e TO pra verificar o menor caminho entre eles: " << endl << "FROM: ";
				cin.ignore(); getline(cin, _from);
				cout << "To: ";
				getline(cin, _to);
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				j = G->email_to_id(_to);
				if (i == -1 || j == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "\nDigite a posicao i, e j pra verificar o menor caminho entre eles: " << endl << "i: ";
				cin >> i;
				cout << "j: ";
				cin >> j;
			}
			valor = G->melhorCaminho(i, j); 
			
			if (valor == -1) { // caso nao exista caminho
				cout << "O peso do menor caminho entre " << i << " e " << j << " eh: INFINITO" << endl;
				break;
			}

			cout << "O peso do menor caminho entre " << i << " e " << j << " eh: " << valor << endl;
			break;
		}
		case 8: {
			system("CLS");
			cont = 0;
			cout << "Quantidade de vertices: " << G->get_tam() << endl;
			
			for (i = 0; i < G->get_tam(); i++)
				cont = cont + G->adjacentes(i);
			cout << "quantidade de arestas: " << cont << endl;
			
			G->top_20_sends();

			break;
		}
		case 9: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite FROM , e TO pra fazer a busca PROFUNDIDADE entre eles: " << endl << "FROM: ";
				cin.ignore(); getline(cin, _from);
				cout << "To: ";
				getline(cin, _to);
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				j = G->email_to_id(_to);
				if (i == -1 || j == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!" << endl;
					break;
				}
			}
			else {	
				cout << "\nDigite a origem: ";
				cin >> i;
				cout << "Digite o destino: ";
				cin >> j;
			}
			if (G->indice_valido(i, j)) {
				vector<int> aux;
				G->busca_profundidade(i, j, aux);

					cout << "Caminho: ";
					for (i = 0; i < aux.size(); i++) {
						cout << aux[i] << " - ";
					
				}

			}
			
			break;
		}
		case 10: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite FROM , e TO pra fazer a busca por LARGURA entre eles: " << endl << "FROM: ";
				cin.ignore(); getline(cin, _from);
				cout << "To: ";
				getline(cin, _to);
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				destino = G->email_to_id(_to);
				if (i == -1 || destino == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "\nDigite a origem: ";
				cin >> i;
				cout << "Digite o destino: ";
				cin >> destino;
			}
			
			vector<int> aux;
			list<int> fila;
			fila.push_back(i);

			G->largura(destino, fila, aux);

			if (aux[aux.size() - 1] != destino)
				cout << "Nao e possivel alcancar esse destino!" << endl;
			else {
				cout << "Caminho: ";
				for (i = 0; i < aux.size(); i++) {
					cout << aux[i] << " - ";
				}
			}
			fila.clear();
			aux.clear();
			break;
		}
		case 11: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite FROM , e a distancia para verificar quais vertices estão a essa distancia: " << endl << "FROM: ";
				cin.ignore(); getline(cin, _from); 

				cout << "distancia: ";
				cin >> distancia;
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				if (i == -1 || distancia < 0) {
					cout << "Erro: Rotulo Digitado incorretamente ou distancia negativa!";
					break;
				}
			}
			else {
				cout << "\nDigite a origem: ";
				cin >> i;
				cout << "Digite a distancia: ";
				cin >> distancia;
			}
			vector<int> aux;
			list<int> fila;
			vector < pair<int, int>> id_distancia; // recebera id e distancia correspondente;

			fila.push_back(i);
			id_distancia.push_back(make_pair(i, 0)); // 0 pq e a propria origem e está a distancia 0 
			
			G->largura_distancias(distancia, fila, aux, id_distancia);


			for (i = 0; i < id_distancia.size(); i++) {
				if ( id_distancia[i].second == distancia)
					cout << "Vertice: " << id_distancia[i].first << ": " << G->id_to_email(id_distancia[i].first)
					<< " Distancia: " << id_distancia[i].second << endl;

			}
			aux.clear();
			fila.clear();
			id_distancia.clear();

			break;
		}
		case 12: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite FROM , e TO pra verificar o MAIOR caminho entre eles: : " << endl << "FROM: ";
				cin.ignore(); getline(cin, _from);
				cout << "To: ";
				getline(cin, _to);
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				j = G->email_to_id(_to);
				if (i == -1 || j == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "\nDigite a posicao i, e j pra verificar o MAIOR caminho entre eles: " << endl << "i: ";
				cin >> i;
				cout << "j: ";
				cin >> j;
			}
			
			double maior_valor= 0;
			maior_valor = G->piorCaminho2(i, j);

			if (maior_valor == -1) { // caso nao exista caminho
				cout << "O peso do MAIOR caminho entre " << i << " e " << j << " eh: INFINITO" << endl;
				break;
			}

			cout << "O peso do MAIOR caminho entre " << i << " e " << j << " eh: " << maior_valor << endl;
			break;
		}
		case 13: {
			system("CLS");
			cout << "Digite o vertice de origem ";
			cin >> i;
			G->prim(i);
		
			break;
		}
		case 14: {
			system("CLS");
			G->seta_componentes();
			break;
		}
		case 15: {
			system("CLS");
			G->grava_pajek();
			break;
		}
		case 16: {
			system("CLS");
			G->~grafo();
			delete (G);// recria o grafo
			grafo * G = grafo::fabrica_grafo();
			break;
		}
		case 17: {
			system("CLS");
			if (G->conexo())
				cout << "Grafo eh conexo ( existe somente 1 componente) " << endl;
			else
				cout << "Grafo nao eh conexo ( + de 1 componente) " << endl;
			break;
		}
		case 18: {
			system("CLS");
			if (G->euleriano())
				cout << "O grafo eh EULERIANO ( possui 0 ou 2 adj impares" << endl;
			else 
				cout << "O grafo nao eh EULERIANO" << endl;
			break;
		}
		case 19: {
			system("CLS");
			vector<int> adj;
			if (G->encontra_ciclo(0, adj))
				cout << "O grafo eh ciclico!" << endl;
			else
				cout << "O grafo nao eh ciclico" << endl;
			break;
		}
		case 20: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite o nome Vertice que deseja verificar: " << endl << "NOME: ";
				cin.ignore(); getline(cin, _from);
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				if (i == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "Digite a ID do vertice que deseja verificar: ";
				cin >> i;

				cout << "Valor: " << G->centralidade_de_proximidade(i) << endl;
				break;
			}
		}
		case 21: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite o nome Vertice que deseja verificar: " << endl << "NOME: ";
				cin.ignore(); getline(cin, _from);
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				if (i == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "Digite a ID do vertice que deseja verificar: ";
				cin >> i;
			}
			cout << "Valor: " << G->centralidade_de_intermediacao(i) << endl;
			break;
		}
		
		case 30: {
			if (G->bidirecional())
				cout << "O grafo e Bidirecionado" << endl;
			else
				cout << "O grafo NAO e Bidirecionado (eh direcionado)" << endl;
			break;
		}
		case 31: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite o Nome que deseja verificar: " << endl << "NOME: ";
				cin.ignore(); getline(cin, _from);
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				if (i == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "Digite a ID do vertice que deseja verificar: ";
				cin >> i;
			}
			vector<pair<int, int>> saida;
			G->top_adjacentes(i, saida);
			break;
		}
		case 32: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite o rotulo que deseja verificar: " << endl << "ROTULO: ";
				cin.ignore();
				getline(cin, _from);
				//cin >> _from;
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				if (i == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "Digite a ID do vertice que deseja verificar: ";
				cin >> i;
			}

			vector<int> adj;

			cout << "quantidade de adjacentes: " << G->adjacentes_bidirecional(i, adj) << endl;
			cout << "Indices do Vetor de adjacentes: [ ";
			for (i = 0; i < adj.size(); i++) {

				cout << adj[i] << " " << G->id_to_email(adj[i]) << " / ";
			}
			cout << "]" << endl;

			adj.clear();
			break;
		}
		/*
		case 32: {
			system("CLS");
			cout << "Pesquisar por rotulo(1) ou por ID(0)?" << endl << "Escolha: ";
			cin >> escolha;
			if (escolha == '1') {
				cout << "\nDigite o Nome que deseja verificar: " << endl << "NOME: ";
				cin.ignore(); getline(cin, _from);
				i = G->email_to_id(_from); // retorna -1 se email nao existir
				if (i == -1) {
					cout << "Erro: Rotulo Digitado incorretamente!";
					break;
				}
			}
			else {
				cout << "Digite a ID do vertice que deseja verificar: ";
				cin >> i;
			}
			cout << "Digite a quantidade de palavras da frase: ";
			cin >> j;
			G->forma_frase(i, j);
			break;
		}
		*/

		case 0: {
			system("CLS");
			//exit(0);
			break;
		}
		}
	} while (ch != 0);


	return 0;
}

/*
grafo * G = new grafo(6);
G->cria_adjacencia_bidirecional(0,1 , 1);
G->cria_adjacencia_bidirecional(0,3 , 4);
G->cria_adjacencia_bidirecional(1,2 , 5);
G->cria_adjacencia_bidirecional(1,3 , 7);
G->cria_adjacencia_bidirecional(1, 5, 6);
G->cria_adjacencia_bidirecional(2,5 , 6);
G->cria_adjacencia_bidirecional(3,4 , 8);
G->cria_adjacencia_bidirecional(4,5 , 2);
G->prim(0);
*/
/*
G->cria_adjacencia(3,0 ,1 );
G->cria_adjacencia(3,1 , 1);
G->cria_adjacencia(3,2 , 1);
G->cria_adjacencia(3,4 , 1);
G->cria_adjacencia(3,5 , 1);
G->cria_adjacencia(1, 2, 1);
*/
/*
G->cria_adjacencia(3, 2, 1);
G->cria_adjacencia(3, 3, 1);
G->cria_adjacencia(3, 4, 1);
G->cria_adjacencia(3, 5, 10000);
G->cria_adjacencia(2, 1, 1);
G->cria_adjacencia(2, 3, 1);
G->cria_adjacencia(4, 2, 15000);
G->cria_adjacencia(0, 1, 15000);
G->cria_adjacencia(0, 3, 15000);
G->cria_adjacencia(0, 5, 15000);
*/
/*
G->cria_adjacencia(0,1 ,10 );
G->cria_adjacencia(1,2 ,20 );
G->cria_adjacencia(0,2 , 5000);
G->cria_adjacencia(2, 3, 5000);
*/

/*
for (i=0; i < G->get_tam(); i++)
cout << "***centralidade: " << i << ": " << G->centralidade_de_proximidade(i) << endl;

for (i = 0; i < G->get_tam(); i++)
cout << "***intermediacao: " << i << ": " << G->centralidade_de_intermediacao(i) << endl << "___" << endl;
*/




//primeira vez
/*
vector<string> enderecos;
gera_endereco * GE = new gera_endereco("base_genes");
enderecos = GE->gerador();
GE->~gera_endereco(); // destrói o classe, pois já fez o que tinha que fazer e retornou o vector<enderecos>
trata_arquivo * A = new trata_arquivo(enderecos); // SE CHAMAR CONSTRUTOR COM 1 PARAMETRO (VECTOR) ENTRA NO MODO
//PARA INDEXAR TUDO (DEMORA MAIS)

tam = A->quantidade_vertices();
cout << "O numero de vertices do grafo eh: " << tam << endl;

cout << endl << "Criando  Grafo..." << endl;
grafo * G = new grafo(tam);

for (i = 0; i < tam; i++) {
email = A->nome_vertice(i);
G->seta_informacao(i, email);
}

for (i = 0; i < A->quantidade_adj(); i++) {
from = A->retorna_from(i);
to = A->retorna_to(i);
G->cria_adjacencia(from, to, 1); // cria adj from _ to com peso 1
}
cout << "Grafo Criado!" << endl;
G->grava_pajek();
*/

/*
cout << "Carregando Arquivos..." << endl;
trata_arquivo * A = new trata_arquivo("id_vertices.txt", "adj.txt");// SE CHAMAR CONSTRUTOR SEM NENHUM PARAMETROS VAI NO MODO RÁPIDO
cout << "Arquivos Carregados!" << endl; // carrega arquivo "id_vertices" e "adj" e coloca em pair


tam = A->quantidade_vertices();
cout << "O numero de vertices do grafo eh: " << tam << endl;

cout << endl << "Criando  Grafo..." << endl;
grafo * G = new grafo(tam);

for (i = 0; i < tam; i++) {
email = A->nome_vertice(i);
G->seta_informacao(i, email);
}

for (i = 0; i < A->quantidade_adj(); i++) {
from = A->retorna_from(i);
to = A->retorna_to(i);
G->cria_adjacencia(from, to, 1); // cria adj from _ to com peso 1
}
cout << "Grafo Criado!" << endl;

G->grava_pajek();
*/





// teste PAJEK
/*
grafo * G = new grafo(8);

G->cria_adjacencia(0, 1, 1);
G->cria_adjacencia(1, 2, 3);
G->cria_adjacencia(3, 4, 4);
G->cria_adjacencia(5, 6, 2);
G->cria_adjacencia(6, 0, 2);

G->cria_adjacencia(5, 2, 1);
G->cria_adjacencia_bidirecional(1, 3, 1);
*/

// grafo exercicio 1b //TESTE GRAFO ÁRVORES GERADORAS MINIMAS
/*
grafo * G = new grafo(6);
G->cria_adjacencia(0,3 ,1 );
G->cria_adjacencia(3,0 ,1 );
G->cria_adjacencia(0,4 ,2 );
G->cria_adjacencia(4,0 ,2 );
G->cria_adjacencia(0,5 ,3 );
G->cria_adjacencia(5,0 ,3 );
G->cria_adjacencia(1,3 ,6 );
G->cria_adjacencia(3,1 ,6 );
G->cria_adjacencia(1,4 ,2 );
G->cria_adjacencia(4,1 ,2 );
G->cria_adjacencia(1,5 ,1 );
G->cria_adjacencia(5,1 ,1 );
G->cria_adjacencia(2,3 ,5 );
G->cria_adjacencia(3,2 ,5 );
G->cria_adjacencia(2,4 ,3 );
G->cria_adjacencia(4,2 ,3 );
G->cria_adjacencia(2,5 ,4 );
G->cria_adjacencia(5,2 ,4 );
*/


// grafo exercicio 1a //TESTE GRAFO ÁRVORES GERADORAS MINIMAS
/*
grafo * G = new grafo(5);

G->cria_adjacencia(0,1 ,7 );
G->cria_adjacencia(1,0 ,7 );
G->cria_adjacencia(0,2 , 1);
G->cria_adjacencia(2, 0, 1);
G->cria_adjacencia(0,3 ,2 );
G->cria_adjacencia(3,0 ,2 );
G->cria_adjacencia(0,4 ,3 );
G->cria_adjacencia(4, 0,3 );
G->cria_adjacencia(1,2 ,3 );
G->cria_adjacencia(2,1 ,3 );
G->cria_adjacencia(1,3 ,4 );
G->cria_adjacencia(3,1 ,4 );
G->cria_adjacencia(1,4 ,5 );
G->cria_adjacencia(4,1 ,4 );
G->cria_adjacencia(2,3 ,1 );
G->cria_adjacencia(3,2 ,1 );
G->cria_adjacencia(2,4 ,2 );
G->cria_adjacencia(4,2 ,2 );
G->cria_adjacencia(3,4 ,3 );
G->cria_adjacencia(4,3 ,3 );
G->prim(0);
*/

//TESTE GRAFO ÁRVORES GERADORAS MINIMAS
/*
grafo * G = new grafo(6);

G->cria_adjacencia(0,1 ,1 );
G->cria_adjacencia(1,0 ,1 );
G->cria_adjacencia(0,2 ,7 );
G->cria_adjacencia(2,0 ,7 );
G->cria_adjacencia(0, 5 ,10 );
G->cria_adjacencia(5,0 ,10 );
G->cria_adjacencia(1,2 ,2 );
G->cria_adjacencia(2,1 ,2 );
G->cria_adjacencia(1,3 ,8 );
G->cria_adjacencia(3,1 ,8 );
G->cria_adjacencia(2,3 ,4 );
G->cria_adjacencia(3,2 ,4 );
G->cria_adjacencia(2,4 ,3 );
G->cria_adjacencia(4,2 ,3 );
G->cria_adjacencia(3,4 ,1 );
G->cria_adjacencia(4,3 , 1);
G->cria_adjacencia(3,5 , 2);
G->cria_adjacencia(5,3 ,2 );
G->cria_adjacencia(4,5 ,5 );
G->cria_adjacencia(5,4 ,5 );
G->prim(0);
*/

//TESTE PARA GRAFO - PROFUNDIDADE - exercicio
/*
grafo * G = new grafo(11);
G->cria_adjacencia(0,1 ,1 );
G->cria_adjacencia(1,4 , 1);
G->cria_adjacencia(1,5 , 1);
G->cria_adjacencia(0,2 , 1);
G->cria_adjacencia(2, 6,1 );
G->cria_adjacencia(6, 9, 1);
G->cria_adjacencia(0,3 , 1);
G->cria_adjacencia(3,7 , 1);
G->cria_adjacencia(7,10 , 1);
G->cria_adjacencia(3,8 , 1);
G->cria_adjacencia(5, 2, 1);
G->cria_adjacencia(2, 3, 1);
*/
//G->cria_adjacencia(5, 2, 1);
//G->cria_adjacencia(2, 0, 1);
//G->cria_adjacencia(2, 3, 1);

//TESTE PARA GRAFO - LARGURA G2
/*
grafo * G = new grafo(7);
G->cria_adjacencia(3,1 , 1);
G->cria_adjacencia(3,2 , 1);
G->cria_adjacencia(3,4 , 1);
G->cria_adjacencia(1,0 , 1);
G->cria_adjacencia(0, 1, 1);
G->cria_adjacencia(2,1 , 1);
G->cria_adjacencia(2,3, 1);
G->cria_adjacencia(4,5 , 1);
G->cria_adjacencia(5,6 , 1);
G->cria_adjacencia(4,6 , 1);
G->cria_adjacencia(6,4 , 1);
*/
//TESTE PARA GRAFO - LARGURA G3
/*
grafo * G = new grafo(9);
G->cria_adjacencia(6,8 , 1);
G->cria_adjacencia(8,6 , 1);
G->cria_adjacencia(6,3 , 1);
G->cria_adjacencia(3,6 , 1);
G->cria_adjacencia(3,0 , 1);
G->cria_adjacencia(0,3 , 1);
G->cria_adjacencia(3,5 , 1);
G->cria_adjacencia(5,3 , 1);
G->cria_adjacencia(5, 2, 1);
G->cria_adjacencia(2, 5, 1);
G->cria_adjacencia(0,1 , 1);
G->cria_adjacencia(1,0 , 1);
G->cria_adjacencia(0,2 , 1);
G->cria_adjacencia(2,0 , 1);
G->cria_adjacencia(5,7 , 1);
G->cria_adjacencia(7, 5, 1);
G->cria_adjacencia(4, 7, 1);
G->cria_adjacencia(5,1 , 1);
G->cria_adjacencia(1, 4, 1);
G->cria_adjacencia(5, 8, 1);
G->cria_adjacencia(8, 5, 1);
*/
