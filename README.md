![](https://i.loli.net/2020/01/09/elHK2zmAindw3ZX.jpg)
# Reversi
基于minmax搜索实现的黑白棋AI，支持linux，windows下编译运行

## 战斗力
打赢了目前找到的所有AI，具体[战况](https://github.com/bdfzoier/Reversi/blob/master/战况.md)（该战况已过期，已经打败了更多ai（10余个））。

## 如何使用

```
$ git clone https://github.com/bdfzoier/Reversi.git
$ cd Reversi/
$ g++ reversi_ai.cpp -o reversi_ai -Wall
$ ./reversi_ai
```

## 程序框架

```cpp
struct Reversi_Board:
	//分别存储棋盘，总棋子个数，黑方哈希，白方哈希
	int board[NR][NR],step,hash1,hash_1;
	//存储每一步的评估权值
	double w[64][3];
	//历史表
	std::unordered_map<long long,std::pair<int,double> > saved_w;


	//检查坐标是否在合法范围内
	inline bool inboard(int x,int y)

	//初始化
	Reversi_Board()
	//从数组导入
	Reversi_Board(int arr[NR][NR])
	//重新初始化，但不重置记录评估权值的数组
	void init()

	//彩色输出，已经适配windows和linux
	void prt()
	//字符输出
	void raw_prt()

	//根据hash1,hash_1计算棋盘总哈希
	inline long long curhash()
	//存储历史表，记录当前搜索过的层数和搜索得到的权值
	inline void save_w(int deep,double curw)

	/*
	 * 判断是否有输赢
	 *  1是黑赢
	 * -1是白赢
	 *  0是平局
	 * -2是尚未分出胜负
	 */
	int win()
	/*
	 * (可以用这个函数计算合理的走棋位置)
	 * 计算吃子的函数
	 * flip 表示是否翻转棋子
	 * x,y,表示下子位置
	 * cur 表示当前是哪方
	 * 返回值表示能反转多少个
	 */
	inline int eat(bool flip,int x,int y,int cur)
	//计算cur方的地势分数
	inline int terr(int cur)
	//计算cur方的行动力
	inline int choice(int cur)
	//计算cur方的稳定子
	inline int not_threated(int cur)
	//当前棋局cur方的优势估计
	inline double assess(int cur)
	//训练估价权值
	void train(double o,double t,int cur)

	//cur方在坐标(x,y)处下一个子
	inline bool putchess(int x,int y,int cur)
	//电脑随机下一个cur的子
	void rand_putchess(int cur)
	/*
	 * minmax搜索
	 * 返回一个坐标 和 最大/最小权值
	 */
	std::pair<std::pair<int, int>, double> min_max(Reversi_Board nowBoard, int depth, bool isMax, double alpha, double beta)
	//电脑根据minmax搜索结果给cur方下一个子
	std::pair<int, int> auto_putchess(int cur)
```

