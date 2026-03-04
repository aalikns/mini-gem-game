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

    cout << "Mini Gem Game 🎮\n";
    cout << "Move with W,A,S,D . T = Gem, E = Enemy, # = Obstackle\n";

    while (true) {
        cout << "\nMap:\n";
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                if (x == *px && y == *py)
                    cout << 'P' << ' ';
                else
                    cout << map[y][x] << ' ';
            }
            cout << endl;
        }

        cout << "Health: " << *pHealth << endl;
        cout << "Move (w/a/s/d), press q for quit: ";

        char move;
        cin >> move;

        if (move == 'q') {
            cout << "Exiting the game...\n";
            break;
        }

        int oldX = *px, oldY = *py;
        movePlayer(px, py, move);

        // Harita disina cikma kontrolu
        if (*px < 0 || *px >= SIZE || *py < 0 || *py >= SIZE) {
            cout << "You can't go outside the map!\n";
            *px = oldX;
            *py = oldY;
            continue;
        }

        char tile = map[*py][*px];

        if (tile == '#') {
            cout << "You hit the obstackle!\n";
            *px = oldX;
            *py = oldY;
        } 
        else if (tile == 'E') {
            cout << "You came across with you enemy! Health -1\n";
            (*pHealth)--;

            if (*pHealth <= 0) {
                cout << "You dead 💀 Game is finished.\n";
                break;
            }
        } 
        else if (tile == 'T') {
            cout << "You found the gem! You won 🎉\n";
            break;
        }
    }

    return 0;
}