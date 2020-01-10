#include<iostream>
#include<cstdio>
#include "./includes/board.h"
using namespace std;
char first;
int main(){
	Reversi_Board myboard;
	printf("you go first?[y/n]:");
	scanf("%c",&first);
	int cur=int(first=='y')*2-1;
#ifdef linux
		system("clear");
#endif
#ifndef linux
		system("cls");
#endif
	while(myboard.win()==-2){
		printf("Please enter the coordinate where you want to put your chess\n");
		printf("e.g. D3,C6\n");
		myboard.raw_prt();
		if(cur==1 && myboard.choice(first=='y'?1:-1)){
			char s[3];
			scanf("%s",s);
			int y=s[0]-'A'+1,x=s[1]-'0';
			while(myboard.board[x][y] || !myboard.eat(0,x,y,first=='y'?1:-1)){
				printf("Invalid!! Please enter again\n");
				scanf("%s",s);
				y=s[0]-'A'+1,x=s[1]-'0';
			}
			myboard.putchess(x,y,first=='y'?1:-1);
		}
		else
			myboard.auto_putchess(first=='y'?-1:1);
#ifdef linux
		system("clear");
#endif
#ifndef linux
		system("cls");
#endif
		cur=-cur;
	}
	printf("%d wins",myboard.win());
	return 0;
}
