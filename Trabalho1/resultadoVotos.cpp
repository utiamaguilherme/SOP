#include "include/resultadoVotos.hpp"

resultadoVotos::resultadoVotos();

void resultadoVotos::resultado(unsigned int number, vector<Candidato>& candidatos){
	cout << "Resultado final:\n";
	cout << "Numero\tNome\t\t Votos validos\t %\n";
	for(int i=0; i<number; i++){
		cout << candidatos[i].number << "\t";
		cout << candidatos[i].name << "\t\t";
		cout << candidatos[i].votos << "\t";
		cout << (candidatos[i].votos*100)/quantTotal << endl;
	}
}