#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;

#define DEV_MODE false

int main() {
	srand(time(NULL));

	int option, senha_dig_1, senha_dig_2, senha_dig_3, senha_dig_4, senha_usr_1, senha_usr_2, senha_usr_3, senha_usr_4, tent = 10, pos_err = 0, pos_cer = 0, cod_tent = 0;
	bool continuar = true;

	do {
	    option = 0;
		// solicita ao usuario a variavel option que definira em qual case do switch
		// entraremos.
		cout << "+==============================+" << endl;
		cout << "|         MENU PRINCIPAL       |" << endl;
		cout << "+==============================+" << endl;
		cout << "|           (1) Jogar          |" << endl;
		cout << "|           (2) Sobre          |" << endl;
		cout << "|           (3) Sair           |" << endl;
		cout << "+==============================+" << endl;
		cout << "        Escolha uma opção: ";
		cin >> option;

		cout << "\033c";

		switch (option) {  // Menu do jogo

		case 1: /*Jogar*/

			//   Reseta variáveis
			tent = 10;
			pos_err= 0;
			pos_cer= 0;

			/*Algoritimo para gerar os digitos aleatorios da senha e verificar se
			 * todos os digitos da senha sao diferentes*/
			do {
				senha_dig_1 = (rand() % 6) + 1;
				senha_dig_2 = (rand() % 6) + 1;
				senha_dig_3 = (rand() % 6) + 1;
				senha_dig_4 = (rand() % 6) + 1;
			} while (senha_dig_1 == senha_dig_2 || senha_dig_1 == senha_dig_3 || senha_dig_1 == senha_dig_4 || senha_dig_2 == senha_dig_3 ||
			         senha_dig_2 == senha_dig_4 || senha_dig_3 == senha_dig_4);

			do {  // LOOP DA TENTATIVA

				/*Exibe a quantidade de números certos na posição certa e números
				certos na posição errada para 0. essas variáveis serão usadas como
				contadores dentro desse loop a cada tentativa*/

				if(DEV_MODE) {
					cout << endl
					     << "|[DEBUG] SENHA GERADA: " << senha_dig_1 << senha_dig_2 << senha_dig_3 << senha_dig_4
					     << "         |" << endl;
				}

				cout << "+==============================+" << endl;
				cout << "|   TENTATIVAS RESTANTES: ";
				if (tent < 10) cout << " ";
				cout << tent << "   |" << endl;
				cout << "+==============================+" << endl;
				cout << "|          SENHA: ****         |" << endl;
				cout << "|Corretos na posição errada: " << pos_err << " |" << endl;
				cout << "|Corretos na posição certa:  " << pos_cer << " |" << endl;
				cout << "+==============================+" << endl;
				cout << "Digite um código (4 dígitos): ";
				cin >> cod_tent;
				
				/*Verifica se o número digitado pelo jogador tem 4 dígitos*/
				if (cod_tent < 1000 || cod_tent > 9999) {
					cout << "\033c";
					cout << endl << "Você digitou uma senha inválida! " << endl;
					cout << endl << "- O número precisa ter 4 dígitos." << endl;
					continue;
				}

				/* Separa o número de 4 dígitos digitado pelo jogador em dígitos
				individuais e joga dentro do vetor senha_dig. A operação é feita do
				último para o primeiro dígito usando módulo e divisão:*/

				senha_usr_4 = cod_tent % 10;  // - `cod_tent % 10` obtém o último dígito
				cod_tent /= 10;  // - `cod_tent /= 10` remove o último dígito já extraído
				senha_usr_3 = cod_tent % 10;
				cod_tent /= 10;
				senha_usr_2 = cod_tent % 10;
				cod_tent /= 10;
				senha_usr_1 = cod_tent % 10;
				cod_tent /= 10;

				if (senha_usr_1 == senha_usr_2 || senha_usr_1 == senha_usr_3 || // confere se os digitos são diferente entre eles utilazando "ou"/"or"/"||"
				        senha_usr_1 == senha_usr_4 || senha_usr_2 == senha_usr_3 ||
				        senha_usr_2 == senha_usr_4 || senha_usr_3 == senha_usr_4) {
					cout << "\033c";
					cout << endl << "Você digitou uma senha inválida! ";
					cout << endl << "- Os números precisam ser diferentes entre si." << endl;

				} else if (senha_usr_1 < 1 || senha_usr_1 > 6 || senha_usr_2 < 1 ||
				           senha_usr_2 > 6 || senha_usr_3 < 1 || senha_usr_3 > 6 || // delimita com maior e menor o valor minimo digitado =1 e máximo =6
				           senha_usr_4 < 1 || senha_usr_4 > 6) {
					cout << "\033c";
					cout << endl
					     << "Você digitou uma senha inválida! Verifique as seguintes regras: ";
					cout << endl << "- Os números precisam estar entre 1 e 6." << endl;

				} else {
					pos_err = 0;
					pos_cer = 0;

					//se o usuario acertar o digito da senha na posição certa o contador de posição certa soma +1
					if (senha_usr_1 == senha_dig_1) pos_cer++;
					if (senha_usr_2 == senha_dig_2) pos_cer++;
					if (senha_usr_3 == senha_dig_3) pos_cer++; 
					if (senha_usr_4 == senha_dig_4) pos_cer++;

					//se o usuario acertar a digito da senha na posição errada o contador de posição errada soma +1
					if (senha_usr_1 == senha_dig_2 || senha_usr_1 == senha_dig_3 || senha_usr_1 == senha_dig_4) pos_err++;
					if (senha_usr_2 == senha_dig_1 || senha_usr_2 == senha_dig_3 || senha_usr_2 == senha_dig_4) pos_err++; 
					if (senha_usr_3 == senha_dig_1 || senha_usr_3 == senha_dig_2 || senha_usr_3 == senha_dig_4) pos_err++; 
					if (senha_usr_4 == senha_dig_1 || senha_usr_4 == senha_dig_2 || senha_usr_4 == senha_dig_3) pos_err++;

					// se o usuario erra a senha a tentaiva diminui para ele tentar novamente até acabarem
					if (senha_usr_1 != senha_dig_1 || senha_usr_2 != senha_dig_2 || 
						senha_usr_3 != senha_dig_3 || senha_usr_4 != senha_dig_4) {
						tent--;
					}
					cout << "\033c";
				}
			} while ((senha_usr_1 != senha_dig_1 || senha_usr_2 != senha_dig_2 ||
				senha_usr_3 != senha_dig_3 || senha_usr_4 != senha_dig_4) && tent > 0);
				 //repetição para continar as tentatiivas enquanto elas não chegarem a 0

				if (tent == 0) {
					cout << "\033c";
					cout << endl
					     << "Que pena, suas tentativas acabaram! Você perdeu! " // mensagem de derrota após as tentativas acabarem
					     << endl
					     << endl;   
					cin.ignore();
					cout << "Aperte ENTER para voltar ao Menu Principal...";
					cin.ignore();
					cout << "\033c";
				} else {
					cout << "\033c";
					cout << endl << "Parabéns! Você acertou todos os números!" << endl;
					cout << endl << "Você venceu!" << endl; // mensagem de vitoria após acertar a senha
					cin.ignore();
					cout << "Aperte ENTER para voltar ao Menu Principal...";
					cin.ignore();
					cout << "\033c";
				}
			break;

		case 2: /*Sobre*/

			// Menu do case 2 que leva a opção "sobre"

			cout << "\033c";
			cout << endl;
			cout << "+==============================+" << endl;
			cout << "|            SOBRE             |" << endl;
			cout << "+==============================+" << endl;
			cout << "|       Desenvolvedores:       |" << endl;
			cout << "| - Matheus Alexandre Santos   |" << endl;
			cout << "| - Luiz Miguel Silvino        |" << endl;  
			cout << "| - Luiz Borba                 |" << endl;
			cout << "| - Carlos Henrique Deucher    |" << endl;
			cout << "|                              |" << endl;
			cout << "+==============================+" << endl;
			cin.ignore();
			cout << "Aperte ENTER para voltar ao Menu Principal...";
			cin.ignore();
			cout << "\033c";

			break;
		case 3: /*Sair*/
			continuar = false; 
			break;
		}

	} while (continuar);
}