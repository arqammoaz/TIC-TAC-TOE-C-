#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void playSound(int freq, int dur) {
#ifdef _WIN32
    Beep(freq, dur);
#endif
}

void saveHighScores(string p1, int s1, string p2, int s2) {
    ofstream outFile("scores.txt", ios::app);   
    if (outFile.is_open()) {
        outFile << p1 << " " << s1 << endl;
        outFile << p2 << " " << s2 << endl;
        outFile << "----------------------" << endl;
        outFile.close();
    }
}

void clearScoreFile() {
    ofstream outFile("scores.txt", ios::trunc); // DELETE ALL DATA
    outFile.close();
}


//void saveHighScores(string p1, int s1, string p2, int s2) {
//    ofstream outFile("scores.txt");
//    if (outFile.is_open()) {
//        outFile << p1 << " " << s1 << endl;
//        outFile << p2 << " " << s2 << endl;
//        outFile.close();
//    }
//}

void loadHighScores(string &p1, int &s1, string &p2, int &s2) {
    ifstream inFile("scores.txt");
    if (inFile.is_open()) {
        inFile >> p1 >> s1 >> p2 >> s2;
        inFile.close();
    }
}

void displayScoreboard(string p1, int s1, string p2, int s2) {
    cout << "\n\t==============================\n";
    cout << "\t          SCOREBOARD          \n";
    cout << "\t==============================\n";
    cout << "\t Player Name        Score\n";
    cout << "\t------------------------------\n";
    cout << "\t " << left << setw(18) << p1 << setw(5) << s1 << endl;
    cout << "\t " << left << setw(18) << p2 << setw(5) << s2 << endl;
    cout << "\t==============================\n\n";
}


class Board {
private:
    char grid[3][3];

public:
    // Constructor
    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                grid[i][j] = ' ';
            }
        }
    }

    void display() {
        cout << "\t\t      1   2   3\n";
        cout << "\t\t    \xDA\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xBF\n";
        for (int i = 0; i < 3; i++) {
            cout << "\t\t  " << i + 1 << " \xB3 ";
            for (int j = 0; j < 3; j++) {
                cout << grid[i][j] << " \xB3 ";
            }
            if (i < 2)
                cout << "\n\t\t    \xC3\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xB4\n";
        }
        cout << "\n\t\t    \xC0\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xD9\n";
    }
    bool makeMove(int r, int c, char s) {
        if (r < 0 || r > 2 || c < 0 || c > 2 || grid[r][c] != ' ') return false;
        grid[r][c] = s;
        playSound(800, 50);
        return true;
    }
    bool checkWin(char s) {
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] == s && grid[i][1] == s && grid[i][2] == s) {
			
			return true;
		}
            if (grid[0][i] == s && grid[1][i] == s && grid[2][i] == s) return true;
        }
        return (grid[0][0] == s && grid[1][1] == s && grid[2][2] == s) ||
               (grid[0][2] == s && grid[1][1] == s && grid[2][0] == s);
    }
};

int main() {
    string p1Name = "Player1", p2Name = "Player2";
    int p1Score = 0, p2Score = 0;
    

    loadHighScores(p1Name, p1Score, p2Name, p2Score);

while (true) {
    clearScreen();
    cout << "\n\t======= TIC TAC TOE ULTIMATE =======\n\n";
    cout << "\t1. New Game (Set Names)\n";
    cout << "\t2. Quick Play (Use Saved/Default)\n";
    cout << "\t3. View Scoreboard\n";
    cout << "\t4. Reset Scores\n";
    cout << "\t5. Exit\n\n";
    cout << "\t Enter your choice: ";
    
    int choice;
    cin >> choice;

        if (choice == 5){
        	clearScoreFile();
			 break;
			 }

        if (choice == 1) {
            cout << "\t Enter Player 1 Name: "; cin >> p1Name;
            cout << "\t Enter Player 2 Name: "; cin >> p2Name;
            p1Score = 0; p2Score = 0;
        } else if (choice == 3) {
            clearScreen();
            displayScoreboard(p1Name, p1Score, p2Name, p2Score);
            cout << "\t Press Enter to return...";
            cin.ignore(); cin.get();
            continue;
        } else if (choice == 4) {
            p1Score = 0; p2Score = 0;
            saveHighScores(p1Name, p1Score, p2Name, p2Score);
            cout << "\t Scores Reset!\n";
            Sleep(1000);
            continue;
        }


        char playAgain = 'y';
        while (playAgain == 'y' || playAgain == 'Y') {
            Board b;
            bool turnX = true;
            bool gameOver = false;
            int moves = 0;

            while (!gameOver) {
                clearScreen();
                displayScoreboard(p1Name, p1Score, p2Name, p2Score);
                b.display();
                
                int r, c;
                cout << "\t " << (turnX ? p1Name : p2Name) << "'s turn (" << (turnX ? 'X' : 'O') << ")\n";
                cout << "\t Enter row: ";
                cin >> r ;
                cout << "\t Enter column: ";
                cin >> c ;
                

                if (b.makeMove(r - 1, c - 1, turnX ? 'X' : 'O')) {
                    moves++;
                    if (b.checkWin(turnX ? 'X' : 'O')) {
                        clearScreen();
                        displayScoreboard(p1Name, p1Score, p2Name, p2Score);
                        b.display();
                        cout << "\n\t \xDB\xDB\xDB " << (turnX ? p1Name : p2Name) << " WINS! \xDB\xDB\xDB\n";
                        playSound(1000, 300);
                        if (turnX) 
						p1Score++; else p2Score++;
                        gameOver = true;
                    } else if (moves == 9) {
                        clearScreen();
                        b.display();
                        cout << "\n\t IT'S A DRAW!\n";
                        gameOver = true;
                    }
                    turnX = !turnX;
                } else {
                    cout << "\t Invalid move! Try again.\n";
                    Sleep(800);
                }
            }
            
            saveHighScores(p1Name, p1Score, p2Name, p2Score);
            cout << "\n\t Play another round? (y/n): ";
            cin >> playAgain;
        }
    }

    return 0;
}