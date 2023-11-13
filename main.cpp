#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <map>
using namespace std;

class Player {
private:
    string name;
    int position; // Position on the board
    int die;

public:
    Player() : position(0) {}
    void setName(const string& n) {
        name = n;
    }

    int rollDie(){
        srand(time(NULL));
        die = rand() % 6 + 1;
        return die;
    }


    void updateLocation(int roll, const map<int, int>& snakes, const map<int, int>& ladders) {
        position += roll;
        if (position > 100) {
            position = 100; // Ensure the position doesn't go beyond 100
        }

        // Check for snakes
        if (snakes.find(position) != snakes.end()) {
            cout << name << " hit a snake! Moving from " << position << " to " << snakes.at(position) << "." << endl;
            position = snakes.at(position);
        }
            // Check for ladders
        else if (ladders.find(position) != ladders.end()) {
            cout << name << " found a ladder! Climbing from " << position << " to " << ladders.at(position) << "." << endl;
            position = ladders.at(position);
        }
    }


    int getPosition() const {
        return position;
    }

    string getName() const {
        return name;
    }
};

void getPlayerNames(Player& p1, Player& p2) {
    string name;
    cout << "Enter name for Player 1: ";
    getline(cin, name);
    p1.setName(name);

    cout << "Enter name for Player 2: ";
    getline(cin, name);
    p2.setName(name);
}

int main() {
    map<int, int> snakes; // Map of all available snakes on the board
    map<int, int> ladders; // Map of all available ladders on the board

    // Define some snakes
    snakes[32] = 10;
    snakes[36] = 6;
    snakes[48] = 26;
    snakes[62] = 18;
    snakes[88] = 24;
    snakes[95] = 56;
    snakes[97] = 78;
    // Define some ladders
    ladders[1] = 38;
    ladders[4] = 14;
    ladders[8] = 30;
    ladders[21] = 42;
    ladders[28] = 76;
    ladders[50] = 67;
    ladders[71] = 92;
    ladders[86] = 99;

    Player player1, player2;
    getPlayerNames(player1, player2);

    while (true) {
        char input; // holder for any input

        // Player 1's turn
        cout << player1.getName() << "'s turn. Enter 'y' to roll the die: ";
        cin >> input;
        if (input == 'y' || input == 'Y') {
            int roll = player1.rollDie();
            player1.updateLocation(roll, snakes, ladders);
            cout << player1.getName() << " rolled a " << roll << " and moved to " << player1.getPosition() << endl;
            if (player1.getPosition() == 100) {
                cout << player1.getName() << " wins!" << endl;
                break;
            }
        }

        // Player 2's turn
        cout << player2.getName() << "'s turn. Enter 'y' to roll the die: ";
        cin >> input;
        if (input == 'y' || input == 'Y') {
            int roll = player2.rollDie();
            player2.updateLocation(roll, snakes, ladders);
            cout << player2.getName() << " rolled a " << roll << " and moved to " << player2.getPosition() << endl;
            if (player2.getPosition() == 100) {
                cout << player2.getName() << " wins!" << endl;
                break;
            }
        }
    }
    return 0;
}
