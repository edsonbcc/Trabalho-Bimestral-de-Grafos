#include "gera_endereco.h"

gera_endereco::gera_endereco() { 
}

gera_endereco::gera_endereco(string _caminho) {
	this->caminho = _caminho;
	//gerador();
}


void gera_endereco::lista_pastas(string _caminho) {
	DIR *dir;

	struct dirent *lsdir;

	dir = opendir(_caminho.c_str()); //  caminho.c_str() conversao de string caminho para char * caminho
							// guarda todos os caminhos possiveis no vector pastas
	while ((lsdir = readdir(dir)) != NULL) {
		this->pastas.push_back(lsdir->d_name);
	}

	closedir(dir);
}

vector<string> gera_endereco::gerador() {
	int i, j, k;

	lista_pastas(caminho); // maildir->todas as pastas (nomes ficam guardados em vector "pastas")

	for (int i = 2; i < pastas.size(); i++) { // ignora os 2 primeiros que não sao & válidos
		sub_pastas.push_back(caminho + "\\" + pastas[i]); // faz concatenacao de pastas + subpasta maildir\\brawner
	}
	imprime(sub_pastas); // os dois primeiro são ignorados pois não são enderecos válidos ". .."

	salva_arquivo();

	cout << "Operacao concluida com sucesso!" << endl;
	cout << "quantidade de arquivos para abrir: " << sub_pastas.size() << endl;

	return sub_pastas;

	//imprime(pastas); // os dois primeiro são ignorados pois não são enderecos válidos ". .."
	//imprime(sub_pastas); // os dois primeiro são ignorados pois não são enderecos válidos ". .."
	/*
	pastas.clear();

	for (int i = 0; i < sub_pastas.size(); i++) {
		lista_pastas(sub_pastas[i]);

		for (j = 2; j < pastas.size(); j++) { // ignorando os dois primeiros
			if (existe("_sent_mail", pastas)) {
				pastas[j] = sub_pastas[i] + "\\" + "_sent_mail";
				final.push_back(pastas[j]);
				break;
			}
			else if (existe("sent", pastas)) {
				pastas[j] = sub_pastas[i] + "\\" + "sent";
				final.push_back(pastas[j]);
				break;
			}
			else {
				pastas[j] = sub_pastas[i] + "\\" + pastas[j];
				cout << "***nao tem _sent_email e sent : " << sub_pastas[i] << endl;
				break;
			}
		}
		pastas.clear();
	}

	//cout << "**Endereco /sent/sent_mail" << endl;
	//imprime(final);

	pastas.clear();

	for (i = 0; i < final.size(); i++) {
		lista_pastas(final[i]); // lista os arquivos
		for (j = 2; j < pastas.size(); j++) {
			pastas[j] = final[i] + "\\" + pastas[j];
			endereco_final.push_back(pastas[j]);
		}
		pastas.clear();
	}
	*/
	//cout << "***Endereco Final:" << endl;
	//imprime(endereco_final);
	
} //fim métodos



bool gera_endereco::existe(string verificador, vector<string> pastas) {
	for (int i = 0; i < pastas.size(); i++) {
		if (verificador == pastas[i])
			return true;
	}
	return false;
}
void gera_endereco::imprime(vector<string> vector) {
	cout << endl;
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i] << endl;
	}
}

void gera_endereco::salva_arquivo() {
	ofstream output_file("./enderecos.txt");
	ostream_iterator<std::string> output_iterator(output_file, "\n");
	std::copy(endereco_final.begin(), endereco_final.end(), output_iterator);
}

gera_endereco::~gera_endereco(){
	pastas.clear();
	sub_pastas.clear();
	final.clear();
	endereco_final.clear();
	caminho.clear();
}
