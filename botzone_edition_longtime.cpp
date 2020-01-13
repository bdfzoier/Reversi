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
#include<cstring>
#include<unordered_map>
#include<ctime>
#include<algorithm>
#define MAX_SEARCH 7
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
	{100.000000,100.000000,170.000000},
	{104.884154,100.000000,170.000000},
	{97.615873,99.437972,170.000000},
	{100.057607,99.374590,170.000000},
	{91.764403,100.108723,170.000000},
	{87.323293,100.790683,170.000000},
	{80.429914,100.501996,170.003320},
	{70.616784,100.464134,169.991935},
	{72.053596,100.211694,170.001298},
	{56.288489,100.585974,169.987694},
	{67.250512,100.448316,170.023042},
	{42.727369,101.444895,169.958344},
	{63.796180,101.182854,170.001367},
	{35.657432,101.776243,170.042894},
	{59.964472,101.350162,170.009773},
	{33.329978,100.950617,170.019717},
	{52.136953,100.637911,170.008109},
	{32.950547,101.425769,170.002053},
	{43.540129,101.493724,170.100824},
	{32.178475,100.895884,170.098219},
	{37.767861,100.722262,170.216163},
	{32.779879,101.573993,170.276521},
	{36.026347,100.052478,170.581426},
	{35.089194,100.497492,170.335376},
	{36.475016,101.225639,170.979660},
	{36.981943,101.330119,170.523600},
	{36.966541,101.726514,171.146249},
	{38.469569,102.500546,170.781711},
	{37.402215,103.465229,171.183062},
	{39.495562,102.609484,171.044789},
	{37.541648,103.621135,171.943866},
	{40.146071,101.701010,171.909881},
	{38.546978,103.934053,173.443466},
	{41.076977,102.861013,172.594955},
	{40.595433,103.550160,172.851263},
	{43.428649,103.330118,174.501889},
	{43.334363,101.703772,173.727289},
	{45.953212,107.946683,178.276944},
	{45.601103,106.438398,180.962825},
	{48.140089,105.775793,176.935580},
	{48.788002,105.324405,185.374369},
	{50.366302,104.685857,170.691547},
	{50.186884,108.533460,187.332595},
	{51.104301,112.879774,173.904655},
	{50.267841,109.710334,188.702475},
	{50.858117,114.945284,176.263241},
	{50.193052,113.872413,169.661592},
	{49.795848,106.929531,192.736453},
	{48.856670,114.882970,179.841160},
	{47.461187,120.897585,214.844166},
	{44.870913,123.373679,240.003389},
	{43.151742,132.230414,257.567057},
	{43.495296,131.748830,208.259210},
	{41.096648,118.854611,176.392630},
	{46.417038,111.186443,292.301704},
	{48.541083,127.853350,315.145880},
	{63.462561,141.675383,479.716850},
	{71.511331,141.196492,632.637470},
	{100.569168,149.148674,1783.703095},
	{64.566356,159.769552,2416.965968}
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
	std::unordered_map<long long,std::pair<std::pair<int,int>,double> > saved_w;

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
	inline void save_w(std::pair<std::pair<int,int>,double> curw){
		if(!have_saved())
			saved_w[curhash()]=curw;
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
		if(nowBoard.have_saved())return nowBoard.saved_w[nowBoard.curhash()];
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
		if(depth>=4)nowBoard.save_w(std::make_pair(fnlChs, fnlWght));
		return std::make_pair(fnlChs, fnlWght);	
	}
	std::pair<int, int> auto_putchess(int cur){
		std::pair<int, int> pr;
		if(step>=52)pr=min_max(*this, 7, (cur + 1) >> 1, -1e9, 1e9).first;
		else pr=min_max(*this, 6, (cur + 1) >> 1, -1e9, 1e9).first;
		putchess(pr.first, pr.second, cur);
		return pr;
	}
};

int n;
int tx,ty;
int cur=1;
int player=1;
Reversi_Board myboard;
int main(){
	scanf("%d",&n);n*=2,n--;
	scanf("%d%d",&ty,&tx);
	if(tx!=-1 && ty!=-1){
		ty++,tx++;
		myboard.putchess(tx,ty,1);
		cur=-cur;
	}
	while(1){
		if(player==1){
			std::pair<int, int> pr = myboard.auto_putchess(cur);
			if(!myboard.inboard(pr.first,pr.second))printf("-1 -1\n");
			else printf("%d %d\n",pr.second-1,pr.first-1);
			printf(">>>BOTZONE_REQUEST_KEEP_RUNNING<<<\n");
			fflush(stdout);
			
		}
		else{
			scanf("%d%d",&ty,&tx);
			ty++,tx++;
			myboard.putchess(tx,ty,cur);
		}
		cur=-cur;
		player=-player;
	}

	
	return 0;
}
