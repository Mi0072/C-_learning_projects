#include <iostream>
#include <string>
#define NOMINMAX
#include <windows.h>
#include <cmath>
#include <iomanip> //  Adicionado para controlo de precisão decimal

void IMC(double peso, double altura_m) {
	double imc_valor = peso / (std::pow(altura_m, 2));

	if (imc_valor < 18.5) {
		std::cout<< "Baixo Peso ("<< imc_valor<<")";
	}
	else if (imc_valor <= 24.9) {
		std::cout << "Peso Adequado(" << imc_valor << ")";
	}
	else if (imc_valor <= 29.9) {
		std::cout << "Pré-obesidade(" << imc_valor << ")";
	}
	else if (imc_valor <= 34.9) {
		std::cout << "Obesidade Classe I(" << imc_valor << ")";
	}
	else if (imc_valor <= 39.9) {
		std::cout << "Obesidade Classe II(" << imc_valor << ")";
	}
	else {
		std::cout << "Obesidade Classe III(" << imc_valor << ")";
	}
}

void PP(int PAS, int PAD) {
	int PP = PAS - PAD;

	if (PP < 30 || PP > 50) {
		std::cout << "\nPressão de Pulso NÃO se encontra nos valores de referência: " << PP << std::endl;
	}
	else {
		std::cout << "\nPressão de Pulso encontra-se nos valores de referência: " << PP << std::endl;
	}
}

void PAM(int PAS, int PAD) {
	double PAM = (PAS + 2 * PAD) / 3.0;

	if (PAM < 70 || PAM > 105) {
		std::cout << "Pressão Arterial Média NÃO se encontra nos valores de referência: " << PAM << std::endl;
	}
	else {
		std::cout << "Pressão Arterial Média encontra-se nos valores de referência: " << PAM << std::endl;
	}
}

void eGFR(char sexo, double creatinina, int idade) { // Alterado tipos para double para evitar perdas de precisão em expoentes
	if (sexo == 'H' || sexo == 'h') {
		double temp = creatinina / 0.9;
		double eGFR_result = 142.0 * std::pow(std::min(temp, 1.0), -0.302) * std::pow(std::max(temp, 1.0), -1.200) * std::pow(0.9938, idade) * 1.00;
		std::cout << "Taxa de Filtração Glomerular Estimada (eGFR - CKD-EPI): " << eGFR_result << std::endl;
	}
	else {
		double temp = creatinina / 0.7;
		double eGFR_result = 142.0 * std::pow(std::min(temp, 1.0), -0.241) * std::pow(std::max(temp, 1.0), -1.200) * std::pow(0.9938, idade) * 1.012; 
		std::cout << "Taxa de Filtração Glomerular Estimada (eGFR - CKD-EPI): " << eGFR_result << std::endl;
	}
}

int main()
{
	int idade = 0;
	double peso = 0.0;
	int altura = 0;
	int mmHg_sys = 0;
	int mmHg_dys = 0;
	double creatinina = 0.0;
	char sexo = 'H';

	SetConsoleOutputCP(65001);
	int op = 0;

	do {

		std::cout << "\n\n\n";
		//Idade
		do {
			std::cout << "Idade: ";
			std::cin >> idade;
			if (idade <= 0) std::cout << "Valor inválido. Tenta novamente.\n";
		} while (idade <= 0);
		std::cout << std::endl;


		//Sexo

		do {
			std::cout << "Sexo (H ou F): ";
			std::cin >> sexo;
			if (sexo != 'H' && sexo != 'F' && sexo != 'h' && sexo != 'f') std::cout << "Valor inválido. Tenta novamente.\n";
		} while (sexo != 'H' && sexo != 'F' && sexo != 'h' && sexo != 'f');
		std::cout << std::endl;

		//Peso
		do {
			std::cout << "Peso (Kg): ";
			std::cin >> peso;
			if (peso <= 0) std::cout << "Valor inválido. Tenta novamente.\n";
		} while (peso <= 0);
		std::cout << std::endl;

		//Altura

		do {
			std::cout << "Altura (cm): ";
			std::cin >> altura;
			if (altura <= 0) std::cout << "Valor inválido. Tenta novamente.\n";
		} while (altura <= 0);


		std::cout << std::endl;

		do {
			std::cout << "Pressão Arterial Sistólica: ";
			std::cin >> mmHg_sys;
			if (mmHg_sys <= 0) std::cout << "Valor inválido. Tenta novamente.\n";
		} while (mmHg_sys <= 0);
		do{
			std::cout << "Pressão Arterial Diastólica: ";
			std::cin >> mmHg_dys;
			if (mmHg_dys <= 0) std::cout << "Valor inválido. Tenta novamente.\n";
		} while ( mmHg_dys <= 0);

		std::cout << std::endl;

		//Creatinina sérica

		do {
			std::cout << "Creatinina Sérica: ";
			std::cin >> creatinina;
			if (creatinina <= 0) std::cout << "Valor inválido. Tenta novamente.\n";

		} while (creatinina <= 0);
		std::cout << std::endl;

		//Verificar Dados
		std::cout << "Confirmar dados:\n" << "1. Idade: " << idade << "\n2. Peso: " << peso << "\n3. Altura: " << altura << "\n4. Pressão Arterial: " << "\n - Sys: " << mmHg_sys << "\n - Dys: " << mmHg_dys << "\n5. Creatinina Sérica: " << creatinina << std::endl;
		std::cout << "0 - Mudar Dados | 1- Prosseguir \n";
		std::cin >> op;
	} while (op !=1);

	system("cls");

	// Configurar formatação decimal no terminal
	std::cout << std::fixed << std::setprecision(1);

	// Converter a altura de cm para metros garantindo divisão em float
	double altura_metros = altura / 100.0;
	std::cout << "\n=== RESUMO CLÍNICO (MedCalc CLI) ===\n\n";

	// Chamada e impressão dos resultados
	std::cout << "Classificação IMC: ";
	IMC(peso, altura_metros);
	std::cout<<std::endl;
	eGFR(sexo, creatinina, idade);
	PP(mmHg_sys, mmHg_dys);
	PAM(mmHg_sys, mmHg_dys);

	return 0;
}
