#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// --- ANSI Color Codes for the Bonus Requirement ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

// --- Base Abstract Class ---
class Player {
protected:
    string name;
    int score;

public:
    Player(string n) : name(n), score(0) {}
    virtual char makeChoice() = 0; // Pure virtual function for Polymorphism

    void addPoint() { score++; }
    int getScore() { return score; }
    void resetScore() { score = 0; }
    string getName() { return name; }
};

// --- Human Player Class ---
class HumanPlayer : public Player {
public:
    HumanPlayer() : Player("Human") {}

    char makeChoice() override {
        char choice;

        while (true) {
            cout << YELLOW << "Your move (R/P/S): " << RESET;
            cin >> choice;
            choice = toupper(choice);
            if (choice == 'R' || choice == 'P' || choice == 'S') {
                return choice;
            }
            cout << RED << "Invalid input! Please enter R, P, or S.\n" << RESET;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
};

// --- Abstract Computer Class ---
class ComputerPlayer : public Player {
public:
    ComputerPlayer(string n) : Player(n) {}
    virtual char makeChoice() = 0;
};

// --- Level 1: Easy (Always Rock) ---
class EasyComputer : public ComputerPlayer {
public:
    EasyComputer() : ComputerPlayer("Easy Computer") {}
    char makeChoice() override { return 'R'; }
};

// --- Level 2: Medium (Random) ---
class MediumComputer : public ComputerPlayer {
public:
    MediumComputer() : ComputerPlayer("Medium Computer") {}
    char makeChoice() override {
        char moves[] = { 'R', 'P', 'S' };
        return moves[rand() % 3];
    }
};

// --- Level 3: Hard (Beats last move) ---
class HardComputer : public ComputerPlayer {
private:
    char lastHumanMove;
    bool firstMove;
public:
    HardComputer() : ComputerPlayer("Hard Computer"), firstMove(true) {}

    // We need a way to tell the computer what the human did last
    void updateLastMove(char m) {
        lastHumanMove = m;
        firstMove = false;
    }

    char makeChoice() override {
        if (firstMove) {
            char moves[] = { 'R', 'P', 'S' };
            return moves[rand() % 3];
        }
        // Logic: Beats player's last move
        if (lastHumanMove == 'R') return 'P';
        if (lastHumanMove == 'P') return 'S';
        return 'R'; // If last was S
    }
};

// --- Game Manager Class ---
class Game {
private:
    HumanPlayer human;
    ComputerPlayer* computer;
    int level;

public:
    Game() : computer(nullptr) {
        srand(time(0)); // Seed for randomness
    }

    void showMenu() {
        cout << CYAN << "========================================" << RESET << endl;
        cout << "  ROCK PAPER SCISSORS - 3 LEVEL CHALLENGE" << endl;
        cout << CYAN << "========================================" << RESET << endl;
        cout << "Choose Computer Level:" << endl;
        cout << "1. Easy (Always Rock)" << endl;
        cout << "2. Medium (Random)" << endl;
        cout << "3. Hard (Beats your last move)" << endl;
        cout << "Your choice: ";
        cin >> level;

        if (level == 1) computer = new EasyComputer();
        else if (level == 2) computer = new MediumComputer();
        else computer = new HardComputer();
    }

    void playMatch() {
        human.resetScore();
        computer->resetScore();

        cout << GREEN << "\nLevel " << level << ": " << computer->getName() << RESET << endl;

        for (int round = 1; round <= 3; round++) {
            cout << "\nRound " << round << " of 3" << endl;
            char hMove = human.makeChoice();
            char cMove = computer->makeChoice();

            cout << "Computer chose: " << cMove << endl;

            // Logic for Hard Computer's memory
            if (level == 3) {
                ((HardComputer*)computer)->updateLastMove(hMove);
            }

            if (hMove == cMove) {
                cout << YELLOW << "IT'S A TIE!" << RESET << endl;
            }
            else if ((hMove == 'R' && cMove == 'S') ||
                (hMove == 'P' && cMove == 'R') ||
                (hMove == 'S' && cMove == 'P')) {
                cout << GREEN << "YOU WIN THIS ROUND!" << RESET << endl;
                human.addPoint();
            }
            else {
                cout << RED << "COMPUTER WINS THIS ROUND!" << RESET << endl;
                computer->addPoint();
            }
            cout << "Score: You " << human.getScore() << " - Computer " << computer->getScore() << endl;
        }

        // Final Winner
        cout << "\n----------------------------" << endl;
        if (human.getScore() > computer->getScore())
            cout << GREEN << "YOU WIN THE MATCH " << human.getScore() << "-" << computer->getScore() << "!" << RESET << endl;
        else if (computer->getScore() > human.getScore())
            cout << RED << "COMPUTER WINS THE MATCH " << computer->getScore() << "-" << human.getScore() << "!" << RESET << endl;
        else
            cout << YELLOW << "THE MATCH IS A DRAW!" << RESET << endl;
    }

    ~Game() { delete computer; } // Cleanup memory
};

int main() {
    char playAgain;
    do {
        Game myGame;
        myGame.showMenu();
        myGame.playMatch();

        cout << "\nPlay again? (Y/N): ";
        cin >> playAgain;
    } while (toupper(playAgain) == 'Y');

    cout << "Thanks for playing!" << endl;
    return 0;
}
