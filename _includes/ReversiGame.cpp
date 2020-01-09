#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>;
#include "board.h"

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


using namespace std;

string s[2] = {"black", "white"};
int col[2] = {1, -1};

int main() {
	Reversi_Board myboard;
	int turn = 0;
  
	while(myboard.win() == -2) {
		if(myboard.choice(col[turn]) == 0) {
			cout << s[turn] << " has no choice left to move!" << endl;
			cout << "Move to the next player!" << endl;
			cout << "Press any key to continue" << endl;
			getch();
		} else {
			cout << "It's " << s[turn] << "'s turn!" << endl;
			cout << "Please input the coordinate you want to put your piece :" << endl;
			cout << "e.g. : C3, D6" << endl;
      
			myboard.prt();
      
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
					cout << "Invalid coordinate!" << endl;
					cout << "Please reinput your coordinate" << endl;
					cout << "e.g. : C3, D6" << endl;
					myboard.prt();
				}
			}
			myboard.putchess(x, y, col[turn]);
		}
		turn = (turn + 1) % 2;
		system("cls"); 
	}
	if(myboard.win() == 1)
		cout << "Black won!";
	else if(myboard.win() == -1)
		cout << "White won!";
	else
		cout << "Tied!";
	return 0;
}
