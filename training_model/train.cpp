#include <iostream>
#include <cstdio>
#include "board.h"
using namespace std;
pair<pair<int, int>, double> min_max(Reversi_Board nowBoard, int depth, bool isMax, double alpha, double beta){ //返回一个坐标 和 最大/最小权值
	bool flag = false;
	if (depth == 0){
		return make_pair(make_pair(-1, -1), nowBoard.assess(1));
	}
	int winn = nowBoard.win();
	if (winn != -2){
		return make_pair(make_pair(0, 0), winn * 100000);
	}
	int cur = isMax ? 1: -1;
	double fnlWght = isMax ? -1e9 : 1e9;
	pair <int, int> fnlChs = make_pair(-1, -1);
	for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
			if (nowBoard.eat(0, i, j, cur) && nowBoard.board[i][j] == 0){
				flag = true;
				Reversi_Board nxtBoard = nowBoard;
				nxtBoard.putchess(i, j, cur);
				double weight = min_max(nxtBoard, depth - 1, !isMax, alpha, beta).second;
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
	if (!flag) return make_pair(make_pair(-1, -1), min_max(nowBoard, depth - 1, !isMax, alpha, beta).second);
	return make_pair(fnlChs, fnlWght);
}
int main(){
	Reversi_Board myboard;
	for(int i=1;i<=10000;i++){
		if(i%10==0)printf("%d\n",i);
		train_speed=(double)1/((double)10000*i*i);
		//printf("%lf\n",train_speed);
		int cur=1;
		myboard.init();
		while(myboard.win()==-2){
			double nxpoint=min_max(myboard,2,(cur+1)>>1,-1e9,1e9).second;
			double curpoint=myboard.assess(1);
			myboard.train(curpoint,nxpoint,1);

			//myboard.raw_prt();
			myboard.rand_putchess(cur);
			cur=-cur;
		}
	}
	for(int i=0;i<60;i++)
		printf("%f %f %f\n",myboard.w[i][0],myboard.w[i][1],myboard.w[i][2]);
	return 0;
}
