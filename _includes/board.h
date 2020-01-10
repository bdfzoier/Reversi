#ifndef BOARD_H
#define BOARD_H

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

#include<iostream>
#include<cstdio>
#include<windows.h>
#include<cstring>
#include<ctime>

#define SIZE 8
#define NR 10
const int nxgo[8][2]={{-1,1},{-1,0},{-1,-1},{0,1},{0,-1},{1,1},{1,0},{1,-1}};
double train_speed=1;
const int terrain[10][10]={
	{  0,   0,   0,  0,  0,  0,  0,   0,   0},
	{  0, 100, -50, 20, 10, 10, 20, -50, 100},
	{  0, -50, -75, 10,  5,  5, 10, -75, -50},
	{  0,  20,  10,  5,  2,  2,  5,  10,  20},
	{  0,  10,   5,  2,  0,  0,  2,   5,  10},
	{  0,  10,   5,  2,  0,  0,  2,   5,  10},
	{  0,  20,  10,  5,  2,  2,  5,  10,  20},
	{  0, -50, -75, 10,  5,  5, 10, -75, -50},
	{  0, 100, -50, 20, 10, 10, 20, -50, 100},
	{  0,   0,   0,  0,  0,  0,  0,   0,   0}
};
const double trained[60][3]={
	{100.000000,100.000000,100.000000},
	{100.361768,100.000000,100.180884},
	{99.584864,99.867397,100.000000},
	{100.052040,99.813727,100.123644},
	{100.508281,99.990285,100.000114},
	{99.980930,99.837283,99.834116},
	{100.392281,99.991115,100.025741},
	{101.700082,100.014420,100.237165},
	{100.319654,100.195803,100.046840},
	{98.551383,99.879870,100.250361},
	{99.056466,100.658859,100.945670},
	{96.171441,100.636101,100.093181},
	{84.689848,100.251655,100.043888},
	{93.722519,100.032442,100.025845},
	{74.551304,100.306106,99.175692},
	{79.050164,100.089955,100.377848},
	{65.501229,98.998674,99.914575},
	{61.750032,98.855593,101.484934},
	{82.364053,100.248548,100.418696},
	{84.644159,100.114286,100.373809},
	{92.271047,98.723173,100.251926},
	{91.356030,99.206406,100.281395},
	{93.946307,98.843857,100.304727},
	{88.638031,98.631199,100.405774},
	{89.239438,97.776317,100.626685},
	{90.279200,99.373917,101.318744},
	{75.154937,98.854079,100.724124},
	{88.095642,99.578796,100.951991},
	{59.871079,99.490190,99.888563},
	{86.556520,101.446131,103.139242},
	{61.036956,98.932327,98.550705},
	{91.364970,99.735812,99.725901},
	{69.717369,99.801442,100.536428},
	{92.720623,101.302991,99.832103},
	{70.018037,100.269868,99.760472},
	{73.636113,99.308187,99.908963},
	{66.383039,100.529246,100.029636},
	{75.789401,100.079043,98.827350},
	{79.383997,100.277526,98.765728},
	{87.237933,100.803887,100.558349},
	{93.098684,98.368412,101.996210},
	{87.053517,99.893426,101.401589},
	{95.069497,100.212388,101.089259},
	{75.506549,100.996672,98.794895},
	{102.271143,99.739296,99.760543},
	{30.164496,100.558540,100.759110},
	{110.221976,99.724882,100.420185},
	{-6.572154,101.048376,99.236292},
	{68.025292,99.406431,98.780108},
	{30.467266,103.413578,106.310126},
	{-32.713665,99.614116,97.440799},
	{-9.095210,108.138533,95.376254},
	{-236.204362,103.873654,96.617861},
	{-421.479201,105.974136,95.041996},
	{-634.374948,110.186536,123.848831},
	{-534.744391,115.026140,241.512005},
	{-651.583349,97.423774,133.513773},
	{448.755769,119.649926,50.595185},
	{142.247264,115.653295,106.607771},
	{111.284104,117.282423,86.280741},
};


struct Reversi_Board{
	/*
	 * 先手  1 黑棋
	 * 后手 -1 白棋
	 * 空地  0
	 */
	int board[NR][NR],step;
	inline bool inboard(int x,int y){return (x>0 && x<=SIZE && y>0 && y<=SIZE);}
	double w[64][3];

	//init & print
	Reversi_Board(){
		for(int i=0;i<60;i++)
			for(int j=0;j<3;j++)
				w[i][0]=trained[i][j];
		step=0;
		memset(board,0,sizeof(board));
		board[4][4]=board[5][5]=-1;
		board[4][5]=board[5][4]=1;
		srand(time(NULL));
	}
	Reversi_Board(int arr[NR][NR]){
		step=-4;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				board[i][j]=arr[i][j];
				if(arr[i][j])step++;
			}
	}
	void init(){
		step=0;
		memset(board,0,sizeof(board));
		board[4][4]=board[5][5]=-1;
		board[4][5]=board[5][4]=1;
	}
	void prt(){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
		std :: cout << "    A   B   C   D   E   F   G   H   ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std :: cout << std :: endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
		std :: cout << "  ┌───┬───┬───┬───┬───┬───┬───┬───┐ ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std :: cout << std :: endl;
		for(int i=1;i<=SIZE;i++){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
			std :: cout << ' ' << i;
			for(int j=1;j<=SIZE;j++){
				std :: cout << "│ ";
				if(board[i][j] == 0) {
					std :: cout << "  ";
				} else if(board[i][j] == 1) {
					std :: cout << "■";
				} else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 111);
					std :: cout << "■";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
			std :: cout << "│ ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std :: cout << "\n";
			if(i != SIZE) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
				std :: cout << "  ├───┼───┼───┼───┼───┼───┼───┼───┤ ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				std :: cout << "\n";
			} else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
				std :: cout << "  └───┴───┴───┴───┴───┴───┴───┴───┘ " << std :: endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				std :: cout << "\n";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	void raw_prt(){
		puts("    A B C D E F G H");
		puts("  +----------------+");
		for(int i=1;i<=SIZE;i++){
			putchar('0'+i);
			putchar(' ');
			putchar('|');
			for(int j=1;j<=SIZE;j++){
				putchar(' ');
				putchar(board[i][j]?(board[i][j]==1?'#':'o'):' ');
			}
			putchar('|');
			putchar('\n');
		}
		puts("  +----------------+");
	}
	

	//Calculation

	/*
	 * 判断是否有输赢
	 *  1是黑赢
	 * -1是白赢
	 *  0是平局
	 * -2是尚未分出胜负
	 */
	int win(){
		int black=0,white=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				if(board[i][j]==1)black++;
				else if(board[i][j]==-1)white++;
			}
		if(step==60 || (!choice(1) && !choice(-1))){
			if(black>white)return 1;
			else if(white>black)return -1;
			else return 0;
		}
		else{
			if(!white)return 1;
			else if(!black)return -1;
			else return -2;
		}
	}
	/*
	 * (可以用这个函数计算合理的走棋位置)
	 * 计算吃子的函数
	 * flip 表示是否翻转棋子
	 * cur 表示当前是哪方
	 * 返回值表示能反转多少个
	 */
	int eat(bool flip,int x,int y,int cur){
		int cnt=0;
		for(int pos=0;pos<8;pos++){
			int tx=x+nxgo[pos][0],ty=y+nxgo[pos][1],tcnt=0;
			//检验
			while(inboard(tx,ty) && board[tx][ty]==-cur)
				tx=tx+nxgo[pos][0],ty=ty+nxgo[pos][1],tcnt++;
			//符合翻的要求
			if(inboard(tx,ty) && board[tx][ty]==cur){
				cnt+=tcnt;
				if(flip){
					tx=x+nxgo[pos][0],ty=y+nxgo[pos][1];
					while(inboard(tx,ty) && board[tx][ty]==-cur)
						board[tx][ty]=cur,tx=tx+nxgo[pos][0],ty=ty+nxgo[pos][1];
				}
			}
		}
		cnt+=flip;
		return cnt;
	}
	int terr(int cur){
		int cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++)
				if(board[i][j]==cur)cnt+=terrain[i][j];
		return cnt;
	}
	//返回cur可以下棋的地方个数
	int choice(int cur){
		int cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++)
				if(board[i][j]==0 && eat(0,i,j,cur))cnt++;
		return cnt;
	}
	//计算稳定子
	int not_threated(int cur){
		cur=-cur;
		bool threat[NR][NR];
		memset(threat,0,sizeof(threat));
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				//如果不是空白不行
				if(board[i][j])continue;
				for(int pos=0;pos<8;pos++){
					int tx=i+nxgo[pos][0],ty=j+nxgo[pos][1];
					//检验
					while(inboard(tx,ty) && board[tx][ty]==-cur)
						tx=tx+nxgo[pos][0],ty=ty+nxgo[pos][1];
					//符合翻的要求
					if(inboard(tx,ty) && board[tx][ty]==cur){
						tx=i+nxgo[pos][0],ty=j+nxgo[pos][1];
						while(inboard(tx,ty) && board[tx][ty]==-cur)
							threat[tx][ty]=1,tx=tx+nxgo[pos][0],ty=ty+nxgo[pos][1];
					}
				}
			}
		int cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++)
				cnt+=(!threat[i][j] && board[i][j]==-cur);
		return cnt;
	}


	/*
	 * 对于cur，棋局状态如何
	 */
	double assess(int cur){
		int iswin=win();
		if(iswin!=-2){
			if(iswin==cur)return 100000;
			else if(iswin==-cur)return -100000;
			else return 0;
		}
		return w[step][0]*(terr(cur)-terr(-cur))+
			w[step][1]*(choice(cur)-choice(-cur))+
			w[step][2]*(not_threated(cur)-not_threated(-cur));
	}
	void train(double o,double t,int cur){
		w[step][0]+=train_speed*(terr(cur)-terr(-cur))*(t-o);
		w[step][1]+=train_speed*(choice(cur)-choice(-cur))*(t-o);
		w[step][2]+=train_speed*(not_threated(cur)-not_threated(-cur))*(t-o);
	}


	//API
	

	/*
	 * 下一个子
	 * 坐标及身份
	 * 失败返回0
	 */
	bool putchess(int x,int y,int cur){
		if(!inboard(x,y) || board[x][y])return 0;
		step++;
		board[x][y]=cur;
		eat(1,x,y,cur);
		return 1;
	}
	void rand_putchess(int cur){
		int curchoice=choice(cur);
		if(!curchoice)return;
		int choice_num=rand()%curchoice,cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				if(board[i][j]==0 && eat(0,i,j,cur)){
					if(cnt==choice_num){
						putchess(i,j,cur);
						return;
					}
					cnt++;
				}
			}
	}
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
	void auto_putchess(int cur){
		pair<int, int> pr = min_max(*this, 5, (cur + 1) >> 1, -1e9, 1e9).first;
		putchess(pr.first, pr.second, cur);
	}
};

#undef SIZE
#undef NR

#endif
