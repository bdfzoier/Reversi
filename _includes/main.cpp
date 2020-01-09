#include <iostream>
#include <cstdio>
#include "board.h"
using namespace std;
pair<pair<int, int>, double> min_max(Reversi_Board nowBoard, int depth, bool isMax, double alpha, double beta){ //返回一个坐标 和 最大/最小权值
	if (depth == 0){
		return make_pair(make_pair(-1, -1), nowBoard.assess(1));
	}
	int winn = nowBoard.win();
	if (winn != -2){
		return make_pair(make_pair(0, 0), winn * 1e9);
	}
	int cur = isMax ? 1: -1;
	double fnlWght = isMax ? -1e9 : 1e9;
	pair <int, int> fnlChs;
	for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
			if (nowBoard.eat(0, i, j, cur) && nowBoard.board[i][j] == 0){
				Reversi_Board nxtBoard = nowBoard;
				nxtBoard.putchess(i, j, cur);
				double weight = min_max(nxtBoard, depth - 1, isMax ^ 1, alpha, beta).second;
				if (isMax && weight > fnlWght){
					fnlChs = make_pair(i, j);
					fnlWght = weight;
					alpha = weight;
				}
				if (!isMax && weight < fnlWght){
					fnlChs = make_pair(i, j);
					fnlWght = weight;
					beta = weight;
				}
				if (beta <= alpha) break;
			}
		}
	}
	return make_pair(fnlChs, fnlWght);
}
int main(){
	Reversi_Board myboard;
	int cur=1;
	while(myboard.win()==-2){
		myboard.raw_prt();
		getchar();
		pair<pair<int,int>,double> res=min_max(myboard,2,(cur+1)>>1,-1e9,1e9);
		myboard.putchess(res.first.first,res.first.second,cur);
		cout<<cur<<endl;
		cout<<res.second<<endl;
		cout<<myboard.step<<endl;
		cur=-cur;
	}
	if(myboard.win())printf("%d wins!!!",myboard.win());
	else printf("Draw");
	return 0;
}
