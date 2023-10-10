/*
   CSCI1120 Assignment 2
   Name         : LEE Shing Hei
   Student ID   : 1155183712
   E-mail       : 1155183712@link.cuhk.edu.hk
*/

#include <iostream>
#include <random>
using namespace std;

int main() {
    int seed, n;
    cout << "Enter seed and board size: ";
    cin >> seed >> n;

    mt19937 rps(seed), die(seed);           // random number generators
    uniform_int_distribution<> play(1, 3);  // random int in [1, 3]
    uniform_int_distribution<> roll(1, 6);  // random int in [1, 6]

    int roundNum = 1;                       // indicating round number
    int humanChoice, compChoice;	        // indicating human and computer choice
    int humanCounter = 0, compCounter = 0;  // indicating current number of moves for human/computer
    int totalMove = 2 * n + (n - 3);        // total number of moves for human/computer
    bool gameEnd = false;

    int hi = 1, hj = 1;
    int ci = n, cj = 1;


    while (!gameEnd) {
        int roundWinner = 0;                            // indicating round winner (0 = draw, 1 = human, 2 = computer)
        cout << "Round " << roundNum << ":" << endl;    // print round number
        roundNum++;
        // print board
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == ci && j == cj) {
                    if (j != n)                         // check if it is the last column, if not, print space
                        cout << "C ";
                    else
                        cout << "C";
                }
                else if (i == hi && j == hj) {
                    if (j != n)                         // check if it is the last column, if not, print space
                        cout << "H ";
                    else
                        cout << "H";
                }
                else if (j != n) {
                    if (i == j || i == 1 || i == n || j == 1 || i + j == n + 1)     // j == n is omitted in here
                        cout << "* ";
                    else
                        cout << "  ";
                }
                else
                    cout << "*";                        // j == n
            }
            cout << endl;                               // print new line after each row finished counting columns
        }
        do {
            roundWinner = 0;
            cout << "Choose (1=R, 2=P, 3=S): ";
            cin >> humanChoice;                         // intake human choice
            compChoice = play(rps);                     // generate computer choice 

            // print human picks
            cout << "Human picks ";
            if (humanChoice == 1)
                cout << "Rock." << endl;
            else if (humanChoice == 2)
                cout << "Paper." << endl;
            else
                cout << "Scissors." << endl;

            // print computer picks
            cout << "Computer picks ";
            if (compChoice == 1)
                cout << "Rock." << endl;
            else if (compChoice == 2)
                cout << "Paper." << endl;
            else
                cout << "Scissors." << endl;

            // print result
            if (humanChoice - compChoice == 1 || humanChoice - compChoice == -2) {
                cout << "Human wins and moves ";
                roundWinner = 1;                        // indicating human wins
            }
            else if (compChoice - humanChoice == 1 || compChoice - humanChoice == -2) {
                cout << "Computer wins and moves ";
                roundWinner = 2;                        // indicating computer wins 
            }
            else {
                cout << "Draw!" << endl;
            }

            if (roundWinner != 0) {                     // if there is a winner
                int rollNum = roll(die);	            // generate random number of steps
                cout << rollNum << " step(s)." << endl;
                if (roundWinner == 1) {				    // if human wins   
                    while (rollNum > 0) {               // while there are still steps to move
                        if (humanCounter < n - 1) {     // if human is still moving in the first row
                            hj++;                       // move right
                            humanCounter++; 		    // add 1 to human total moves 
                            rollNum--;				    // minus 1 to steps to move
                        }
                        else if ((humanCounter >= n - 1) && (humanCounter < totalMove - (n - 1))) {     // if human is moving diagonally 
							hi++;                       // move down
                            hj--;					    // move left 
                            humanCounter++;             // add 1 to human total moves
                            rollNum--;  		        // minus 1 to steps to move     
						}
                        else if (humanCounter >= totalMove - (n - 1)) {	 // if human is moving in the last row
                            hj++;   		            // move right    
                            humanCounter++; 		    // add 1 to human total moves
                            rollNum--;  		        // minus 1 to steps to move
                        }
					}
                }
                else {								    // if computer wins
                    while (rollNum > 0) {			    // while there are still steps to move
                        if (compCounter < n - 1) {      // if computer is still moving in the last row
							cj++;                       // move right
							compCounter++;			    // add 1 to computer total moves
							rollNum--;				    // minus 1 to steps to move
						}
                        else if ((compCounter >= n - 1) && (compCounter < totalMove - (n - 1))) {   // if computer is moving diagonally
                            ci--;					    // move up
                            cj--;   		            // move left
                            compCounter++;			    // add 1 to computer total moves
                            rollNum--;				    // minus 1 to steps to move
                        }
                        else if (compCounter >= totalMove - (n - 1)) {
							cj++;					    // move right
							compCounter++;			    // add 1 to computer total moves
							rollNum--;				    // minus 1 to steps to move
						}     
                    }
                }
            }
        } while (roundWinner == 0);	                    // if there is no winner, repeat the round

        if (humanCounter >= totalMove) {                // if human reaches the end
			cout << "Game over!" << endl << "Human wins the game!";
			gameEnd = true;
		}
        else if (compCounter >= totalMove) {            // if computer reaches the end
            cout << "Game over!" << endl << "Computer wins the game!";
			gameEnd = true;
		}
    }
}