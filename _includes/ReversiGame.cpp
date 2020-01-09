/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >' "".
     | | :  `- \`.;`\ _ /`;.`/ - `  : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            佛祖保佑       永无BUG
*/


#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include "board.h"

using namespace std;

string s[2] = {"black", "white"};
int col[2] = {1, -1};

void info() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159);
	cout << "INFO";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << ' '; 
}

void prsk() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 32);
	cout << "PRSK";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << ' '; 
}

void warn() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
	cout << "WARN";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << ' '; 
}

void endg() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 111);
	cout << "ENDG";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << ' '; 
}

int main() {
	Reversi_Board myboard;
	int turn = 0;
	
	while(myboard.win() == -2) {
		myboard.prt();
		
		if(myboard.choice(col[turn]) == 0) {
			info(); cout << s[turn] << " has no moves" << endl;
			info(); cout << "Moving on to the next player" << endl;
			prsk(); cout << "Press any key to continue" << endl;
			getch();
		} else {
			info(); cout << "It's " << s[turn] << "'s turn!" << endl;
			prsk(); cout << "Input new piece coordinate :" << endl;
			info(); cout << "You can now move to: ";
			
			for(int j = 1 ; j <= 8 ; j ++) {
				for(int i = 1 ; i <= 8 ; i ++) {
					if(myboard.eat(0, i, j, col[turn])) {
						cout << "[" << char(j + 'A' - 1) << i << "] ";
					}
				}
			}
			
			cout << endl;
			
			string tmps;
			int x, y;
			
			while(cin >> tmps) {
				if(tmps[0] >= 'A' && tmps[0] <= 'Z') y = tmps[0] - 'A' + 1;
				if(tmps[0] >= 'a' && tmps[0] <= 'z') y = tmps[0] - 'a' + 1;
				
				x = tmps[1] - '0'; 
				
				if(myboard.eat(0, x, y, col[turn]) != 0)
					break; 
				else {
					system("cls");
					myboard.prt();
					warn(); cout << "Invalid coordinate!" << endl;
					prsk(); cout << "Please reinput your coordinate" << endl;
					info(); cout << "You can now move to: ";
					for(int i = 1 ; i <= 8 ; i ++) {
						for(int j = 1 ; j <= 8 ; j ++) {
							if(myboard.eat(0, i, j, col[turn])) {
								cout << "[" << char(j + 'A' - 1) << i << "] ";
							}
						}
					}
					cout << endl;
				}
			}
			myboard.putchess(x, y, col[turn]);
		}
		turn = (turn + 1) % 2;
		system("cls"); 
	}
	
	endg();
	if(myboard.win() == 1) 
		cout << "Black won!";
	else if(myboard.win() == -1)
		cout << "White won!";
	else
		cout << "Tied!";
	return 0;
}
