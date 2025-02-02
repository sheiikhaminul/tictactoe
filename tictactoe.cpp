#include <iostream>
#include <limits>
using namespace std;

char space[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
string player1, player2;
char token1, token2;
int digit, row, col;
bool tie = false;
char current_token;

void displayBoard() {
    cout << "          |         |            \n";
    cout << "     " << space[0][0] << "    |    " << space[0][1] << "    |    " << space[0][2] << "\n";
    cout << "   _______|_________|_______     \n";
    cout << "          |         |            \n";
    cout << "     " << space[1][0] << "    |    " << space[1][1] << "    |    " << space[1][2] << "\n";
    cout << "   _______|_________|_______     \n";
    cout << "          |         |            \n";
    cout << "     " << space[2][0] << "    |    " << space[2][1] << "    |    " << space[2][2] << "\n";
    cout << "          |         |            \n";
}

void takeInput() {
    cout << (current_token == token1 ? player1 : player2) << " please enter a digit for position (" << current_token << "): ";

    while (!(cin >> digit) || digit < 1 || digit > 9) {
        cin.clear(); // clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number between 1-9: ";
    }

    row = (digit - 1) / 3;
    col = (digit - 1) % 3;

    if (space[row][col] != 'x' && space[row][col] != 'o') {
        space[row][col] = current_token;
    } else {
        cout << "This space is already occupied! Try again." << endl;
        takeInput();
    }
}

bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (space[i][0] == space[i][1] && space[i][1] == space[i][2]) return true;
        if (space[0][i] == space[1][i] && space[1][i] == space[2][i]) return true;
    }

    // Check diagonals
    if (space[0][0] == space[1][1] && space[1][1] == space[2][2]) return true;
    if (space[0][2] == space[1][1] && space[1][1] == space[2][0]) return true;

    return false;
}

bool checkTie() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (space[i][j] != 'x' && space[i][j] != 'o') return false;
        }
    }
    return true;
}

int main() {
    cout << "Player 1, enter your name: ";
    getline(cin, player1);
    do {
        cout << player1 << " enter your symbol (x/o): ";
        cin >> token1;
        if (token1 == 'x' || token1 == 'o') {
            token2 = (token1 == 'x') ? 'o' : 'x';
            break;
        } else {
            cout << "Invalid symbol. Please enter 'x' or 'o'." << endl;
        }
    } while (true);

    cout << "Player 2, enter your name: ";
    cin.ignore();
    getline(cin, player2);
    cout << player2 << " your symbol is " << token2 << endl;

    current_token = token1;

    cout << "GAME START!!" << endl;

    while (true) {
        displayBoard();
        takeInput();

        if (checkWin()) {
            displayBoard();
            cout << (current_token == token1 ? player1 : player2) << " wins!!" << endl;
            break;
        }

        if (checkTie()) {
            displayBoard();
            cout << "It's a tie!" << endl;
            break;
        }

        // Switch player
        current_token = (current_token == token1) ? token2 : token1;
    }

    return 0;
}
