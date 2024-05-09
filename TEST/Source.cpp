#include <iostream>
#include <cstdlib>
#include <ctime>

// Dimenzije polja
const int REDAKA = 20;
const int STUPACA = 40;

class GameOfLife {
private:
    bool _generacija[REDAKA][STUPACA];
    bool _sljedeca_generacija[REDAKA][STUPACA];

    // Pomo?ne metode
    bool slucajna_vrijednost() {
        return rand() % 4 == 0; // 25% šanse za živi organizam
    }

    bool celija_zauzeta(int i, int j) {
        return (i >= 0 && i < REDAKA&& j >= 0 && j < STUPACA&& _generacija[i][j]);
    }

public:
    // Konstruktor
    GameOfLife() {
        // Inicijalizacija generatora slu?ajnih brojeva
        srand(time(nullptr));

        // Inicijalizacija po?etne generacije
        for (int i = 0; i < REDAKA; ++i) {
            for (int j = 0; j < STUPACA; ++j) {
                _generacija[i][j] = slucajna_vrijednost();
            }
        }
    }

    // Metoda za ra?unanje sljede?e generacije
    void sljedeca_generacija() {
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
    void iscrtaj() {
        system("cls"); // O?isti ekran (za Windows)

        for (int i = 0; i < REDAKA; ++i) {
            for (int j = 0; j < STUPACA; ++j) {
                std::cout << (_generacija[i][j] ? '#' : ' ');
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    GameOfLife igra;

    bool dalje;
    do {
        igra.iscrtaj();
        igra.sljedeca_generacija();

        std::cout << "Dalje (1/0): ";
        std::cin >> dalje;
    } while (dalje);

    return 0;
}
