#include <iostream>
using namespace std;

void movePlayer(int* x, int* y, char move) {
    if (move == 'w') (*y)--;
    else if (move == 's') (*y)++;
    else if (move == 'a') (*x)--;
    else if (move == 'd') (*x)++;
}

int main() {
    const int SIZE = 5;
    char map[SIZE][SIZE] = {
        {'.', '.', '.', '.', '.'},
        {'.', '#', '#', '.', '.'},
        {'.', '.', 'T', '.', '.'}, // T = Treasure (hazine)
        {'.', '#', '.', '.', '.'},
        {'.', '.', '.', '.', 'E'}  // E = Enemy (düşman)
    };

    int playerX = 0, playerY = 0;
    int health = 3;

    int* px = &playerX;
    int* py = &playerY;
    int* pHealth = &health;

    cout << "Mini Hazine Oyunu 🎮\n";
    cout << "W A S D ile hareket et. T = Hazine, E = Dusman, # = Duvar\n";

    while (true) {
        // Haritayı çiz
        cout << "\nHarita:\n";
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                if (x == *px && y == *py)
                    cout << 'P' << ' ';
                else
                    cout << map[y][x] << ' ';
            }
            cout << endl;
        }

        cout << "Can: " << *pHealth << endl;
        cout << "Hareket (w/a/s/d), cikmak icin q: ";

        char move;
        cin >> move;

        if (move == 'q') {
            cout << "Oyundan cikiliyor...\n";
            break;
        }

        int oldX = *px, oldY = *py;
        movePlayer(px, py, move);

        // Harita disina cikma kontrolu
        if (*px < 0 || *px >= SIZE || *py < 0 || *py >= SIZE) {
            cout << "Harita disina cikamazsin!\n";
            *px = oldX;
            *py = oldY;
            continue;
        }

        char tile = map[*py][*px];

        if (tile == '#') {
            cout << "Duvara carptin!\n";
            *px = oldX;
            *py = oldY;
        } 
        else if (tile == 'E') {
            cout << "Dusmana denk geldin! Can -1\n";
            (*pHealth)--;

            if (*pHealth <= 0) {
                cout << "Oldun 💀 Oyun bitti.\n";
                break;
            }
        } 
        else if (tile == 'T') {
            cout << "Hazineden buldun! Kazandin 🎉\n";
            break;
        }
    }

    return 0;
}