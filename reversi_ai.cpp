# include <iostream>
# include <cstdio>
# include "./includes/board.h" 

using namespace std;

int cur;
char first, hq;
Reversi_Board myboard;

void cl() {
#ifndef _WIN32
	system("clear");
#endif
#ifdef _WIN32
	system("cls");
#endif
}

void pr() {
	if(hq == 'n') {
		myboard.raw_prt();
	} else {
		myboard.prt();
	}
}

int main(){
	printf("Do you want high quality graphics? (high quality graphics might not work on some computers) [y/n]:");
	scanf("%c", &hq); getchar();
	
	printf("Are you going to go first? [y/n]:");
	scanf("%c", &first);
	cur=int(first=='y')*2-1;
	
	cl();

	while (myboard.win() == -2) {
		printf("Current player's valid moves are: ");
		for(int j = 1 ; j <= 8 ; j ++) 
			for(int i = 1 ; i <= 8 ; i ++) 
				if(myboard.eat(0, i, j, first == 'y' ? 1 : -1) && myboard.board[i][j] == 0) 
					printf("[%c%d] ", char(j + 'A' - 1), i);
		printf("\n");
		printf("Please enter the the new piece's coordinate\n");
		printf("Format e.g.: E4, D6\n");
		pr();
		
		if(cur == 1 && myboard.choice(first == 'y' ? 1 : -1)) {
			char s[3];
			scanf("%s",s);
			int x = s[1] - '0', y = s[0] - 'A' + 1;
			while(myboard.board[x][y] || !myboard.eat(0, x, y, first == 'y' ? 1 : -1)) {
				printf("Invalid coordinate! Please enter again\n");
				scanf("%s", s);
				x = s[1] - '0', y = s[0] - 'A' + 1;
			}
			myboard.putchess(x, y, first == 'y' ? 1 : -1);
		}
		else
			myboard.auto_putchess(first == 'y' ? -1 : 1);
		cl();
		cur = -cur;
	}
	if(myboard.win())printf(myboard.win()==1?"black wins":"white wins");
	else printf("draw");
	return 0;
}
