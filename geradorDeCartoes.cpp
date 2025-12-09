#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Verifica se o valor gerado já existe na coluna atual para evitar duplicados
bool isValueRepeated(int value, int column[], int limit) {
    for (int i = 0; i < limit; i++) {
        if (column[i] == value) return true;
    }
    return false;
}

// Cria os ficheiros .txt com a grelha formatada
void GenerateGridTicket(int quantity) {
    int ticketMatrix[5][5];

    for (int n = 1; n <= quantity; n++) {
        string fileName = "Bingo_Ticket_" + to_string(n) + ".txt";
        ofstream file(fileName);

        // Preenche cada coluna (B, I, N, G, O) respeitando os intervalos
        for (int c = 0; c < 5; c++) {
            int baseValue = (c * 20) + 1; // Define 1-20, 21-40, etc.
            for (int r = 0; r < 5; r++) {
                int randomNumber;
                do {
                    randomNumber = rand() % 20 + baseValue;
                } while (isValueRepeated(randomNumber, ticketMatrix[c], r));

                ticketMatrix[c][r] = randomNumber;
            }
        }

        // Cabeçalho visual
        file << "-------------------------------" << endl;
        file << "|  B  |  I  |  N  |  G  |  O  |" << endl;
        file << "-------------------------------" << endl;

        // Desenha a tabela com os números alinhados e o centro livre (XXX)
        for (int r = 0; r < 5; r++) {
            file << "| ";
            for (int c = 0; c < 5; c++) {
                if (r == 2 && c == 2) {
                    file << "XXX"; 
                } else {
                    if (ticketMatrix[c][r] < 10) file << "0"; 
                    file << ticketMatrix[c][r] << " ";
                }
                file << " | ";
            }
            file << endl;
            file << "-------------------------------" << endl;
        }
        file.close();
    }
}

// Função principal que lê os argumentos da linha de comandos (argc/argv)
int main(int argc, char* argv[]) {
    // Verifica se o utilizador passou o argumento de quantidade
    if (argc < 2) {
        cout << "Erro: Indica a quantidade de cartoes!" << endl;
        cout << "Uso: " << argv[0] << " [quantidade]" << endl;
        return 1; 
    }

    int totalTickets;
    try {
        // Converte o texto do argumento (argv[1]) para número inteiro
        totalTickets = stoi(argv[1]);
    } catch (...) {
        cout << "Erro: O valor inserido nao e um numero valido." << endl;
        return 1;
    }

    // Valida o limite de segurança de 500 cartões
    if (totalTickets > 500) {
        cout << "Erro: O limite maximo permitido e de 500 cartoes." << endl;
        return 1;
    }

    // Inicializa a semente aleatória baseada no tempo do sistema
    srand(static_cast<unsigned>(time(NULL)));

    if (totalTickets > 0) {
        GenerateGridTicket(totalTickets);
        cout << "Sucesso: " << totalTickets << " cartoes gerados." << endl;
    } else {
        cout << "Erro: Insira um numero positivo." << endl;
    }

    return 0;
}
