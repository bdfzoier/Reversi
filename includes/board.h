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
	{106.375910,100.000000,103.187955},
	{97.050554,99.196969,100.000000},
	{102.164780,98.753066,100.706313},
	{91.146547,99.946768,100.144025},
	{72.945467,100.847627,100.094617},
	{62.788817,101.127856,100.016856},
	{46.919999,100.802598,99.724930},
	{38.263935,99.991282,99.991834},
	{34.129771,99.830914,99.444124},
	{27.247263,99.651057,99.761252},
	{30.048667,99.430968,99.426648},
	{26.066177,99.782008,99.414017},
	{28.693513,100.372157,99.448155},
	{25.833633,100.203817,99.220213},
	{27.588226,101.221354,99.034913},
	{26.413727,100.893623,99.731604},
	{27.817417,100.506559,99.474670},
	{28.459878,101.326419,99.835357},
	{29.894287,100.810378,98.979393},
	{31.271216,100.799871,99.309207},
	{32.803589,100.515737,98.880995},
	{34.239211,100.789443,99.444919},
	{36.155931,102.913401,99.704200},
	{36.426354,101.720107,99.782936},
	{39.078931,104.290986,100.425001},
	{38.125275,101.513342,100.782384},
	{41.396562,96.639651,111.940588},
	{39.672708,101.066446,100.943719},
	{43.210211,102.731063,99.976140},
	{41.272454,101.896015,101.125665},
	{44.834575,104.642285,100.856896},
	{42.956239,101.794427,102.551759},
	{45.594121,103.328821,99.822596},
	{45.033504,103.100862,103.038145},
	{47.047332,107.521681,101.450738},
	{46.843403,104.751306,102.816695},
	{48.118311,110.596712,103.008006},
	{49.440749,109.948771,105.027616},
	{50.046390,103.400207,102.579965},
	{53.041466,109.780026,104.655556},
	{52.860310,106.113628,110.628094},
	{57.046193,109.875817,101.919517},
	{57.453349,106.300757,107.309651},
	{61.925939,111.883997,107.403047},
	{64.161106,108.576579,112.276873},
	{68.123229,116.863735,110.776358},
	{71.127275,112.471587,119.479615},
	{74.229876,108.906725,116.795937},
	{77.538477,116.398221,129.071565},
	{78.945769,117.901417,132.475071},
	{83.481027,122.691526,143.277702},
	{80.725749,122.943335,173.931017},
	{86.676793,125.787318,181.433439},
	{82.401170,135.688004,296.228846},
	{86.334710,129.063971,292.108434},
	{81.527307,149.007958,680.207850},
	{80.079822,139.173009,812.550987},
	{71.452234,177.293015,2215.092827},
	{44.347594,185.563423,2731.973488}
};
double w1=191.727187,w2=104.604102,w3=115.982689;


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
				w[i][j]=trained[i][j];
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
					std :: cout << "■ ";
				} else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 111);
					std :: cout << "■ ";
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
		/*return w1*(terr(cur)-terr(-cur))+
			w2*(choice(cur)-choice(-cur))+
			w3*(not_threated(cur)-not_threated(-cur));*/
		return w[step][0]*(terr(cur)-terr(-cur))+
			w[step][1]*(choice(cur)-choice(-cur))+
			w[step][2]*(not_threated(cur)-not_threated(-cur));
	}
	void train(double o,double t,int cur){
		w[step][0]+=train_speed*(terr(cur)-terr(-cur))*(t-o);
		w[step][1]+=train_speed*(choice(cur)-choice(-cur))*(t-o);
		w[step][2]+=train_speed*(not_threated(cur)-not_threated(-cur))*(t-o);
		//w1+=train_speed*(terr(cur)-terr(-cur))*(t-o);
		//w2+=train_speed*(choice(cur)-choice(-cur))*(t-o);
		//w3+=train_speed*(not_threated(cur)-not_threated(-cur))*(t-o);
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
	std::pair<std::pair<int, int>, double> min_max(Reversi_Board nowBoard, int depth, bool isMax, double alpha, double beta){ //返回一个坐标 和 最大/最小权值
		bool flag = false;
		if (depth == 0){
			return std::make_pair(std::make_pair(-1, -1), nowBoard.assess(1));
		}
		int winn = nowBoard.win();
		if (winn != -2){
			return std::make_pair(std::make_pair(0, 0), winn * 100000);
		}
		int cur = isMax ? 1: -1;
		double fnlWght = isMax ? -1e9 : 1e9;
		std::pair <int, int> fnlChs = std::make_pair(-1, -1);
		for (int i = 1; i <= 8; i++){
			for (int j = 1; j <= 8; j++){
				if (nowBoard.eat(0, i, j, cur) && nowBoard.board[i][j] == 0){
					flag = true;
					Reversi_Board nxtBoard = nowBoard;
					nxtBoard.putchess(i, j, cur);
					double weight = min_max(nxtBoard, depth - 1, !isMax, alpha, beta).second;
					if (isMax && weight > fnlWght){
						fnlChs = std::make_pair(i, j);
						fnlWght = weight;
						alpha = weight;
					}
					if (!isMax && weight < fnlWght){
						fnlChs = std::make_pair(i, j);
						fnlWght = weight;
						beta = weight;
					}
					if (beta <= alpha) break;
				}
			}
		}
		if (!flag) return std::make_pair(std::make_pair(-1, -1), min_max(nowBoard, depth - 1, !isMax, alpha, beta).second);
		return std::make_pair(fnlChs, fnlWght);
	}
	void auto_putchess(int cur){
		std::pair<int, int> pr = min_max(*this, 6, (cur + 1) >> 1, -1e9, 1e9).first;
		putchess(pr.first, pr.second, cur);
	}
};

#undef SIZE
#undef NR

#endif
