#include "game_of_life.h"
#include <iostream>

// Konstruktor
game_of_life::game_of_life() {
    // Inicijalizacija generacija
    for (int i = 0; i < REDAKA; ++i) {
        for (int j = 0; j < STUPACA; ++j) {
            _generacija[i][j] = slucajna_vrijednost();
        }
    }
}

// Metoda za ra?unanje sljede?e generacije
void game_of_life::sljedeca_generacija() {
    for (int i = 0; i < REDAKA; ++i) {
        for (int j = 0; j < STUPACA; ++j) {
            int susjedi = 0;

            // Provjera susjeda
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if ((di != 0 || dj != 0) && celija_zauzeta(i + di, j + dj)) {
                        susjedi++;
                    }
                }
            }

            // Pravila igre "Život"
            _sljedeca_generacija[i][j] = (_generacija[i][j] && (susjedi == 2 || susjedi == 3)) || (!_generacija[i][j] && susjedi == 3);
        }
    }

    // Ažuriranje trenutne generacije
    for (int i = 0; i < REDAKA; ++i) {
        for (int j = 0; j < STUPACA; ++j) {
            _generacija[i][j] = _sljedeca_generacija[i][j];
        }
    }
}

// Metoda za ispis trenutnog stanja igre
void game_of_life::iscrtaj() {
    system("cls"); // O?isti ekran (za Windows)

    for (int i = 0; i < REDAKA; ++i) {
        for (int j = 0; j < STUPACA; ++j) {
            std::cout << (_generacija[i][j] ? '#' : ' ');
        }
        std::cout << std::endl;
    }
}


bool game_of_life::slucajna_vrijednost() {
    return rand() % 4 == 0; // 25% šanse za živi organizam
}

bool game_of_life::celija_zauzeta(int i, int j) {
    return (i >= 0 && i < REDAKA&& j >= 0 && j < STUPACA&& _generacija[i][j]);
}
