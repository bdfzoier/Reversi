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
#ifndef linux
#include<windows.h>
#endif
#include<cstring>
#include<unordered_map>
#include<ctime>
#include<algorithm>
#define MAX_SEARCH 60
#define SIZE 8
#define NR 10
const int nxgo[8][2]={{-1,1},{-1,0},{-1,-1},{0,1},{1,-1},{1,0},{1,1},{0,-1}};
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
bool cmp1(std::pair<int, double> x, std::pair<int, double> y){
	return x.second > y.second;
}
bool cmp2(std::pair<int, double> x, std::pair<int, double> y){
	return x.second < y.second;
}
const int board_hash[10][10]={
	{0,0,0,0,0,0,0,0,0,0},
	{0,702167748,1149044463,376632294,336103763,1955888354,1981172283,1200258070,854575395,0},
	{0,1770695626,891634434,1315914244,446775943,1674990609,423196531,1618746640,1551799625,0},
	{0,1697938058,1031271398,316663619,267068920,1496174412,117465739,1781814210,315825807,0},
	{0,245216013,231532836,1911322891,1207785950,453979669,1594382150,1819508382,1976852440,0},
	{0,1791853837,32505261,1955901964,113280860,690570681,523895244,459790227,1995621976,0},
	{0,1469867151,919910822,851227755,1337858871,1816121645,996917559,583917597,470625806,0},
	{0,2047904629,653235578,514479328,1391062239,340955792,659896276,495870009,884414431,0},
	{0,1374265997,1214525556,30903131,1873004895,835701320,1777751367,1054298401,392221640,0},
	{0,0,0,0,0,0,0,0,0,0}
};
const double trained[60][3]={
	{200.000000,50.000000,100.000000},
	{210.009188,50.000000,100.000000},
	{200.000000,50.000000,100.000000},
	{184.758126,51.088705,100.000000},
	{200.000000,50.000000,100.000000},
	{252.404895,61.645532,100.000000},
	{205.045851,51.681950,100.000000},
	{255.159637,50.000000,100.000000},
	{200.000000,50.000000,100.000000},
	{381.867586,59.093379,100.000000},
	{93.641401,81.907580,100.000000},
	{536.176717,50.000000,100.000000},
	{202.222201,50.130718,100.000000},
	{765.310425,106.531042,100.000000},
	{237.922112,57.584422,100.000000},
	{870.641009,164.967030,100.000000},
	{172.471443,50.000000,100.000000},
	{824.466375,147.572871,100.000000},
	{264.647630,61.408405,100.000000},
	{778.125459,93.359409,100.000000},
	{224.256346,55.821523,100.000000},
	{663.036999,91.158844,100.000000},
	{182.618995,47.757290,100.000000},
	{460.887105,58.553676,100.000000},
	{171.559484,48.906134,100.000000},
	{304.502521,54.125099,100.000000},
	{197.597805,50.046196,100.000000},
	{216.826635,50.000000,100.000000},
	{250.005403,51.923285,100.000000},
	{252.451335,50.000000,100.000000},
	{486.510462,50.000000,91.046548},
	{344.450049,50.000000,102.329840},
	{489.098155,61.119160,100.000000},
	{266.414520,51.145078,97.709844},
	{703.452519,73.973929,100.000000},
	{236.865072,48.975970,100.000000},
	{704.795162,50.000000,100.000000},
	{235.313486,50.000000,100.000000},
	{623.079752,62.443522,100.000000},
	{217.075581,50.000000,100.000000},
	{533.103081,50.000000,103.828771},
	{200.214129,49.997837,100.002163},
	{651.899900,25.898672,100.000000},
	{199.914741,50.003911,100.000000},
	{498.647573,35.641944,97.128389},
	{156.354014,52.550739,101.700493},
	{512.253161,31.985395,90.992697},
	{214.443140,49.239835,99.493223},
	{390.674122,45.884731,98.628244},
	{222.660473,49.084425,101.373362},
	{436.307084,46.311242,114.260432},
	{194.912163,46.816628,69.294414},
	{465.553873,70.928314,121.889254},
	{569.112575,-74.118761,1039.762117},
	{1866.149853,60.466236,1051.990314},
	{1489.074057,11.062550,1025.361697},
	{1318.120319,75.245147,247.154220},
	{1412.665571,105.105599,817.957862},
	{792.400740,100.426126,631.753311},
	{-757.640624,-43.566922,2678.721224},
};
double w1=191.727187,w2=104.604102,w3=115.982689;
struct Reversi_Board{
	/*
	 * 先手  1 黑棋
	 * 后手 -1 白棋
	 * 空地  0
	 */
	int board[NR][NR],step,hash1,hash_1;
	inline bool inboard(int x,int y){return (x>0 && x<=SIZE && y>0 && y<=SIZE);}
	double w[64][3];
	std::unordered_map<long long,std::pair<int,double> > saved_w;

	//init & print
	Reversi_Board(){
		for(int i=0;i<60;i++)
			for(int j=0;j<3;j++)
				w[i][j]=trained[i][j];
		step=0;
		memset(board,0,sizeof(board));
		board[4][4]=board[5][5]=-1;
		board[4][5]=board[5][4]=1;
		hash_1=0,hash1=0;
		hash_1^=board_hash[4][4];
		hash_1^=board_hash[5][5];
		hash1^=board_hash[4][5];
		hash1^=board_hash[5][4];
		srand(time(NULL));
	}
	Reversi_Board(int arr[NR][NR]){
		hash_1=0,hash1=0;
		step=-4;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				board[i][j]=arr[i][j];
				if(arr[i][j]){
					step++;
					if(arr[i][j]==-1)hash_1^=board_hash[i][j];
					else hash1^=board_hash[i][j];
				}
			}
	}
	void init(){
		step=0;
		memset(board,0,sizeof(board));
		board[4][4]=board[5][5]=-1;
		board[4][5]=board[5][4]=1;
		hash_1=0,hash1=0;
		hash_1^=board_hash[4][4];
		hash_1^=board_hash[5][5];
		hash1^=board_hash[4][5];
		hash1^=board_hash[5][4];
	}

#ifndef linux
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
#endif
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
	inline long long curhash(){return (long long)(hash1<<31)|hash_1;}

	inline bool have_saved(){return saved_w.find(curhash())!=saved_w.end();}
	inline void save_w(int deep,double curw){
		if(!have_saved())
			saved_w[curhash()]=std::make_pair(deep,curw);
		else if(saved_w[curhash()].first<deep)
			saved_w[curhash()]=std::make_pair(deep,curw);
	}

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
	inline int eat(bool flip,int x,int y,int cur){
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
					while(inboard(tx,ty) && board[tx][ty]==-cur){
						board[tx][ty]=cur;
						hash1^=board_hash[tx][ty];
						hash_1^=board_hash[tx][ty];
						tx=tx+nxgo[pos][0];
						ty=ty+nxgo[pos][1];
					}
				}
			}
		}
		return cnt;
	}
	inline int terr(int cur){
		int cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++)
				if(board[i][j]==cur)cnt+=terrain[i][j];
		return cnt;
	}
	//返回cur可以下棋的地方个数
	inline int choice(int cur){
		int cnt=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++)
				if(board[i][j]==0 && eat(0,i,j,cur))cnt++;
		return cnt;
	}
	//计算稳定子
	inline int not_threated(int cur){
		int cnt,ans=0;
		for(int i=1;i<=SIZE;i++)
			for(int j=1;j<=SIZE;j++){
				//如果不是空白不行
				if(board[i][j]!=cur)continue;
				cnt=0;
				for(int pos=0;pos<4;pos++){
					int meet1=-2,meet2=-2;
					int tx=i+nxgo[pos][0],ty=j+nxgo[pos][1];
					//检验
					while(inboard(tx,ty) && board[tx][ty]==cur)
						tx=tx+nxgo[pos][0],ty=ty+nxgo[pos][1];
					if(inboard(tx,ty))meet1=board[tx][ty];

					tx=i+nxgo[pos+4][0],ty=j+nxgo[pos+4][1];
					//检验
					while(inboard(tx,ty) && board[tx][ty]==cur)
						tx=tx+nxgo[pos+4][0],ty=ty+nxgo[pos+4][1];
					if(inboard(tx,ty))meet2=board[tx][ty];

					if(meet1==-2 || meet2==-2 ||(meet1==-cur && meet2==-cur))cnt++;
				}
				if(cnt==4)ans++;
			}
		return ans;
	}


	/*
	 * 对于cur，棋局状态如何
	 */
	inline double assess(int cur){
		if(have_saved())return saved_w[curhash()].second;
		int iswin=win();
		double ans;
		if(iswin!=-2){
			if(iswin==cur)ans=100000;
			else if(iswin==-cur)ans=-100000;
			else ans=0;
		}
		/*return w1*(terr(cur)-terr(-cur))+
			w2*(choice(cur)-choice(-cur))+
			w3*(not_threated(cur)-not_threated(-cur));*/
		else ans=w[step][0]*(terr(cur)-terr(-cur))+
			w[step][1]*(choice(cur)-choice(-cur))+
			w[step][2]*(not_threated(cur)-not_threated(-cur));
		save_w(0,ans);
		return ans;
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
	inline bool putchess(int x,int y,int cur){
		if(!inboard(x,y) || board[x][y])return 0;
		step++;
		board[x][y]=cur;
		if(cur==1)hash1^=board_hash[x][y];
		else hash_1^=board_hash[x][y];
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
		std::pair <int, int> pr[151]; //x & y
		std::pair <int, double> pr2[151]; // id & weight
		int cur = isMax ? 1: -1;
		int cnt = 0;
		double fnlWght = isMax ? -1e9 : 1e9;
		std::pair <int, int> fnlChs = std::make_pair(-1, -1);
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				if (nowBoard.eat(0, i, j, cur) && nowBoard.board[i][j] == 0){
					pr[++cnt] = std::make_pair(i, j);
					Reversi_Board nxtBoard = nowBoard;
					nxtBoard.putchess(i, j, cur);
					pr2[cnt] = std::make_pair(cnt, nxtBoard.assess(cur));
				}
		sort(pr2 + 1, pr2 + cnt + 1, isMax ? cmp1 : cmp2);
		for (int i = 1; i <= std::min(cnt, MAX_SEARCH); i++){
			int id = pr2[i].first;
			int nx = pr[id].first;
			int ny = pr[id].second;
			flag = true;
			Reversi_Board nxtBoard = nowBoard;
			nxtBoard.putchess(nx, ny, cur);
			double weight = min_max(nxtBoard, depth - 1, !isMax, alpha, beta).second;
			if (isMax && weight > fnlWght){
				fnlChs = std::make_pair(nx, ny);
				fnlWght = weight;
				alpha = weight;
			}
			if (!isMax && weight < fnlWght){
				fnlChs = std::make_pair(nx, ny);
				fnlWght = weight;
				beta = weight;
			}
			if (beta <= alpha) break;
		}
		/*if (!flag) return std::make_pair(std::make_pair(-1, -1), min_max(nowBoard, depth - 1, !isMax, alpha, beta).second);
		return std::make_pair(fnlChs, fnlWght);*/
		if (!flag) fnlWght=min_max(nowBoard, depth - 1, !isMax, alpha, beta).second;
		nowBoard.save_w(depth, fnlWght);
		return std::make_pair(fnlChs, fnlWght);	
	}
	std::pair<int, int> auto_putchess(int cur){
		std::pair<int, int> pr;
		if(step>=49)pr=min_max(*this, 6, (cur + 1) >> 1, -1e9, 1e9).first;
		else pr=min_max(*this, 5, (cur + 1) >> 1, -1e9, 1e9).first;
		putchess(pr.first, pr.second, cur);
		return pr;
	}
};

#undef MAX_SEARCH
#undef SIZE
#undef NR

#endif
