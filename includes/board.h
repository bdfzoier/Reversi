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
	{100.000000,0.000000,0.000000},
	{267.158747,0.000000,83.488932},
	{34.425344,-11.843484,0.000000},
	{98.927132,3.780775,29.148372},
	{78.403846,-2.007865,5.507699},
	{109.281934,36.813937,16.186147},
	{128.987361,34.514801,9.814233},
	{150.367314,68.776303,6.451874},
	{147.415906,49.993319,12.696285},
	{130.126585,86.761804,6.793682},
	{130.668943,70.542669,20.336206},
	{98.780643,114.969902,11.472099},
	{134.829105,84.945390,23.171786},
	{96.601266,127.001530,24.501587},
	{130.205915,109.696545,20.429082},
	{115.673622,148.621612,5.110190},
	{123.779576,133.534554,25.391805},
	{136.021356,178.531304,14.695885},
	{117.140598,167.560530,38.901814},
	{156.537766,202.225328,15.281767},
	{108.484495,183.901241,41.638648},
	{155.937926,222.252295,41.758230},
	{82.050324,215.683552,76.560794},
	{111.660043,259.572791,68.041831},
	{64.622603,281.743246,90.827241},
	{97.325692,306.826834,104.545791},
	{62.193611,336.391271,127.277098},
	{82.776823,337.448091,120.606421},
	{100.571854,388.411547,171.029691},
	{71.376823,412.864242,168.992425},
	{149.389354,493.274283,261.479669},
	{68.643382,484.071583,287.703602},
	{184.274908,579.361388,380.847464},
	{72.762693,599.365485,469.456956},
	{195.807312,657.298618,629.077523},
	{72.357376,833.303767,695.231552},
	{202.381381,843.032554,1077.512790},
	{153.706019,1110.563434,1221.225021},
	{224.694147,1157.202410,1818.991992},
	{305.542470,1444.017353,2093.519505},
	{140.798698,1503.305095,2864.414682},
	{283.180354,1855.784623,3201.871222},
	{126.940730,1870.722152,4087.259477},
	{539.004007,2270.121615,4331.111662},
	{144.207278,2167.454203,5089.240698},
	{858.598864,2385.893710,5047.041146},
	{154.730649,2299.968221,5520.748153},
	{328.330525,2519.278602,5373.339681},
	{143.400023,2538.261109,5778.542772},
	{-315.556126,2974.400047,5571.498654},
	{98.344797,2667.879404,5619.532873},
	{-12.156890,2427.910501,5420.092378},
	{115.393968,2617.180481,5559.547328},
	{97.635916,2945.434524,5380.693944},
	{153.434002,2949.945101,5435.757209},
	{152.939246,2904.153446,5687.681150},
	{48.791167,2736.726833,4846.949967},
	{-21.447237,2539.811158,4596.566714},
	{-64.296694,1991.193973,4515.801265},
	{175.707687,1781.059049,4291.633730}
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
