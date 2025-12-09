#include <iostream>
#include <vector>
#include <algorithm>//algoritmo shuffle (baralhar)
#include <random>   //números aleatórios moderno
#include <iomanip>
#include <ctime>    // ler o tempo do sistema para a semente tempo atual da maquina (seed)
#include <thread>   // fazer o programa "dormir"
#include <chrono>

using namespace std;

// Limpeza de ecrã 
void LimparEcra() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Definição de Cores ANSI
const string GREEN = "\033[1;32m";
const string RED   = "\033[31m";
const string GREY  = "\033[90m";
const string RESET = "\033[0m";

int main() {
    const int totalNumbers = 90;
    const int autoInterval = 1; // Segundos entre bolas no modo automático
    
    vector<int> bingoDrum;
    vector<int> drawHistory;
    bool alreadyDrawn[totalNumbers + 1] = {false};

    // Inicialização do globo
    for (int i = 1; i <= totalNumbers; i++) {
        bingoDrum.push_back(i);
    }

    // Baralhamento
    unsigned seed = static_cast<unsigned>(time(0));
    shuffle(bingoDrum.begin(), bingoDrum.end(), default_random_engine(seed));

    // --- MENU INICIAL ---
    LimparEcra();
    cout << "============= BINGO =============" << endl;
    cout << "1. Modo Manual (Pressionar ENTER)" << endl;
    cout << "2. Modo Automatico (" << autoInterval << "s)" << endl;
    cout << "Escolha uma opcao: ";
    
    int choice;
    cin >> choice;
    cin.ignore(); // Limpa o buffer para o cin.get() não falhar depois

    // Ciclo de Sorteio
    for (int i = 0; i < totalNumbers; i++) {
        LimparEcra();

        int currentNum = bingoDrum[i];
        drawHistory.push_back(currentNum);
        alreadyDrawn[currentNum] = true;

        // Interface Visual
        cout << "========================================" << endl;
        cout << " BOLA SORTEADA: " << GREEN << currentNum << RESET << endl;
        cout << "========================================" << endl << endl;

        // Histórico recente
        cout << "Ultimos 5 sorteados: ";
        int startIndex = (drawHistory.size() > 5) ? drawHistory.size() - 5 : 0;
        for (int k = startIndex; k < drawHistory.size(); k++) {
            cout << drawHistory[k] << (k == drawHistory.size() - 1 ? "" : " | ");
        }
        cout << endl << endl;

        // Quadro Geral
        cout << "--------- QUADRO GERAL ---------" << endl;
        for (int n = 1; n <= totalNumbers; n++) {
            if (n == currentNum) cout << GREEN << setw(3) << n << RESET;
            else if (alreadyDrawn[n]) cout << RED << setw(3) << n << RESET;
            else cout << GREY << setw(3) << n << RESET;

            if (n % 10 == 0) cout << endl;
        }

        // --- LÓGICA DE CONTROLO ---
        if (choice == 1) {
            cout << endl << "Pressione [ENTER] para a proxima bola...";
            cin.get();
        } else {
            cout << endl << "Modo Automatico: Proxima bola em " << autoInterval << "s..." << endl;
            this_thread::sleep_for(chrono::seconds(autoInterval));
        }
    }

    cout << "Sorteio concluido!" << endl;
    return 0;
}
