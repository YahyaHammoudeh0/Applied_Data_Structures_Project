
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

class SnakeAndLadderGame {
private:
    int numPlayers;
    vector<int> playerPositions;
    vector<string> playerNames;
    int board[100];

public:
    SnakeAndLadderGame(int players) : numPlayers(players) {
        playerPositions.resize(numPlayers, 0);
        initializeBoard();
        getPlayersNames();
    }

    void initializeBoard() {
        for (int i = 0; i < 100; ++i) {
            board[i] = i + 1;
        }

        board[16] = 6;
        board[47] = 26;
        board[49] = 11;
        board[56] = 53;
        board[62] = 19;
        board[64] = 60;
        board[87] = 24;

        board[1] = 38;
        board[4] = 14;
        board[9] = 31;
        board[21] = 42;
        board[28] = 84;
        board[36] = 44;
        board[51] = 67;
        board[71] = 91;
        board[80] = 99;
    }

    void getPlayersNames() {
        for (int i = 0; i < numPlayers; ++i) {
            string name;
            cout << "Enter the name for Player " << i + 1 << ": ";
            cin >> name;
            playerNames.push_back(name);
        }
    }

    int rollDie() {
        return rand() % 6 + 1;
    }

    int getNextPosition(int currentPosition, int dieRoll) {
        int newPosition = currentPosition + dieRoll;
        if (newPosition <= 99) {
            newPosition = board[newPosition - 1];
            cout << "Move to position " << newPosition << ". ";
            handleSpecialPositions(newPosition);
        } else {
            cout << "Cannot move beyond position 100. ";
        }
        return newPosition;
    }

    void handleSpecialPositions(int position) {
        if (position == 99) {
            cout << "Congratulations! You reached the WINNING position!" << endl;
        } else if (position == 6 || position == 26 || position == 11 || position == 53 || position == 19 || position == 60 || position == 24) {
            cout << "Oops! You encountered a snake. Move back to position " << position << "." << endl;
        } else if (position == 38 || position == 14 || position == 31 || position == 42 || position == 84 || position == 44 || position == 67 || position == 91 || position == 99) {
            cout << "Great! You found a ladder. Climb up to position " << position << "." << endl;
        }
    }

    void displayBoard() {
        cout << setw(6) << " ";
        for (int i = 1; i <= 10; ++i) {
            cout << setw(6) << i;
        }
        cout << endl;

        int count = 0;
        for (int i = 9; i >= 0; --i) {
            if (i % 2 == 0) {
                for (int j = 1; j <= 10; ++j) {
                    cout << setw(6) << board[count++];
                }
            } else {
                for (int j = 10; j >= 1; --j) {
                    cout << setw(6) << board[count++];
                }
            }
            cout << endl;
        }
    }

    void play() {
        srand(time(0));
        int currentPlayer = 0;

        while (true) {
            cout << playerNames[currentPlayer] << "'s turn. Press enter to roll the die.";
            cin.get();
            int dieRoll = rollDie();
            cout << playerNames[currentPlayer] << " rolled a " << dieRoll << ". ";
            playerPositions[currentPlayer] = getNextPosition(playerPositions[currentPlayer], dieRoll);
            displayBoard();

            if (playerPositions[currentPlayer] == 99) {
                cout << playerNames[currentPlayer] << " wins!" << endl;
                break;
            }

            currentPlayer = (currentPlayer + 1) % numPlayers;
        }
    }
};

int main() {
    cout << "Welcome to the Snake and Ladder Game!" << endl;

    int numPlayers;
    cout << "Enter the number of players (2 or more): ";
    cin >> numPlayers;

    if (numPlayers < 2) {
        cout << "Invalid number of players. Exiting the game." << endl;
        return 1;
    }

    SnakeAndLadderGame game(numPlayers);
    game.play();

    return 0;
}
