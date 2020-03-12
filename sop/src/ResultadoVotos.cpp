#include "includes/ResultadoVotos.hpp"


void ResultadoVotos::resultado(vector<Candidato> &candidatos, unsigned int lidos, unsigned int validos, unsigned int max){


	//cout << "Resultado final:\n";

	printf("Total de votos processados: %u\n", lidos);
	printf("Votos validos: %u (%.2f%%)\n", validos, ((double)validos/(double)lidos)*100.0);
	printf("Tamanho maximo da fila: %d nos\n\n", max);

	cout << fmtcabvoto;
	for(auto i : candidatos){
		printf(fmtvoto, i.getNumber(), i.getName().c_str(), i.getVotos(), (double)((double)i.getVotos()*100.0)/(double)validos);
	}
	// cout << candidatos[i].number << "\t";
	// cout << candidatos[i].name << "\t\t";
	// cout << candidatos[i].votos << "\t";
	// cout << (candidatos[i].votos*100)/quantTotal << endl;
}
