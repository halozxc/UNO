// UNO.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<vector>
#include<cmath>
#include<time.h> 
using namespace std;
void printcard(int x);
bool issamefunctioncard(int x, int y );
int nextgiver(int x, int y, int z);


int main()
{
	
	srand((unsigned)time(NULL));
	cout << "Hi,这是一个UNO卡牌游戏"<<endl;
	int book[108] = { 0 };
	vector<int> cardlib;//这是牌库
	vector<int> cardbin;//存放打出去的牌
	vector<int> card_player;
	auto cb = cardlib.begin();
	auto  cn = cardbin.end();
	auto cp = card_player.begin();
	 int i = 0,j=1;
	while (cardlib.size()!=108 ) {//随机排列卡牌，并存入牌库中
		
		int n = rand()%108;
		if (book[n] == 0) {
			cardlib.push_back(n);
			book[n] = 1;
			i ++;
		}
	}
	cout << "请告诉我一共有多少个玩家" << endl;
		int playernum;
	cin >> playernum;
	const int pla = playernum;
	
	int npc;
	cout << "请告诉我需要几人是NPC" << endl;
	cin >> npc;
	while(npc>playernum)
	{
		cout << "NPC个数不可以超过玩家数哦，请再输入一次" << endl;
		cin >> npc;
	}
	int pointer[10];
	pointer[0] = -1;
	cout << "游戏开始咯！！！" << endl;
	
	for (i = 1; (int)i <= playernum; i++)
	{//分配并管理每位玩家的牌
		int first = 1;
		while (j <= 7) {
			card_player.push_back(cardlib[0]);
			if (cardlib[0]<=107 && cardlib[0]>=104 && first==1)//每人取牌7张，其余当作牌库，然后从牌堆中取出首张牌(若是"wild draw 4"需再取)
			{
				cardlib.erase(cardlib.begin());
				first = 0;
			}
			else {
				cardlib.erase(cardlib.begin());
				j++;
				first = 0;
			}
		}
		j = 1;
		
		pointer[i] =card_player.size()-1;
		//cout << "卡牌调出总数：" << card_player.size()<<endl;
		//cout << "pointer" << i << "指向位置" << pointer[i] << endl;
		
	}
	//用一个变量来控制玩家出牌顺序
	int nextplayer = 1;
	int giver = 1;
	
	
	
	bool keepon = true;
	int card,colorasked;
	while (keepon==true)
    {
		if (giver <= playernum - npc) 
		{
			cout << "现在是玩家" << giver << "出牌" << endl;
			cout << "请过目你的牌" << endl;
			for (i = pointer[giver - 1]+1, j = 1; (int)i <= pointer[giver]; i++, j++)
			{
				cout << "卡牌" << j << endl;
				printcard(card_player[i]);
			}
				cout << "请选择你要出的牌,现在输入-1还允许摸一张新牌" << endl;
				cin >> card;
				if (card > 0)
				{//从自己的牌中打出一张
					if (cardbin.size() == 0)
					{//第一次出牌，无需指定颜色
						cardbin.push_back(card_player[card + pointer[giver - 1]]);
						if(cardbin[cardbin.size() - 1]>99){
							colorasked = rand() % 4;
						}
						else {
							colorasked = cardbin[cardbin.size() - 1] / 25;
						}
					}
					else//不是第一位玩家的第一次出牌，考虑其出牌的类型与颜色
					{
						if (card_player[card + pointer[giver - 1]] > 99) 
						{
							cardbin.push_back(card_player[card + pointer[giver - 1]]);
						}
						else 
						{
							while (card_player[card + pointer[giver - 1]]/ 25 != colorasked && !issamefunctioncard(card + pointer[giver - 1], cardbin[cardbin.size() - 1])&& card_player[card + pointer[giver - 1]] < 99)
							{
								//如果出的牌不是与上张同色或者同功能，则要求重新输入
								cout << "不可以出这张牌，请再次选择" << endl;
								cin >>card;
							}
							
							cardbin.push_back(card_player[card + pointer[giver - 1]]);
						}
					}
					cout << "玩家" << giver << "打出了这张牌" << endl;
					printcard(card_player[card + pointer[giver - 1]]);
					cp = card_player.begin();
					card_player.erase(cp+card + pointer[giver - 1]);
					colorasked = cardbin[cardbin.size() - 1] / 25;
					//打出新牌后更新pointer内各元素指向的新位置
					for (int i = giver; i <= playernum; i++) {
						pointer[i]=pointer[i]-1;
						

					}
				}
				else
				{//摸一张新牌，如果颜色或功能符合要求，则打出，否则放入自己的牌中
					if (cardlib[0] / 25 == colorasked || !issamefunctioncard(cardlib[0], cardbin[cardbin.size() - 1]) || cardlib[0] > 99) {
						cardbin.push_back(cardlib[0]);
						    cardlib.erase(cardlib.begin());
							cout << "玩家" << giver << "摸牌并打出了这张牌:"<<endl;
							printcard(cardlib[0]);
					}
					else {
						cout << "你摸到的牌为" << endl;
						printcard(cardlib[0]);
						cp = card_player.begin();
					       card_player.insert(cp+pointer[giver],cardlib[0]);
							for (int i = giver; i <= playernum; i++) {
								pointer[i]++;
							
							}
					}
				}
		}
		else
        {//机器人出牌
			int k = 0;//检测是否打出了牌
			for (int i = pointer[giver - 1] + 1; i <= pointer[giver]; i++)
			{
				if (card_player[i]/25 ==colorasked || issamefunctioncard(card_player[i],cardbin[cardbin.size() - 1]) || card_player[i] > 99) {
					cout << "玩家" << giver << "打出了这张牌" << endl;
						printcard(card_player[i]);
						card_player.erase(card_player.begin()+i-1);
						for (i = giver; i <= playernum; i++) {
							pointer[i]--;
						}
				 k=1;
					break;
				}
			}
			     if (k == 0) {
					 if (cardlib[0] / 25 ==colorasked || issamefunctioncard(cardlib[0],cardbin[cardbin.size() - 1]) || cardlib[0] > 99) {
						 cout << "玩家" << giver << "打出了这张牌" << endl;
							 printcard(cardlib[0]);
							 cardbin.push_back(cardlib[0]);
							 cardlib.erase(cardlib.begin());
					 }
					 else {
						 cp = card_player.begin();
						 card_player.insert(cp+pointer[giver], cardlib[0]);
							 cardlib.erase(cardlib.begin());
							 cout << "玩家" << giver << "摸牌";
							 for (int i = giver; i <= playernum; i++) {
								 pointer[i]++;
							 }
					 }
				 }
		}
		for (i = playernum; i >= 1; i--) 
		{
			if (pointer[i] - pointer[i - 1] == 1) {
				cout << "玩家" << i << "喊出了UNO" << endl;
			}
		}
		for (i = playernum; i >= 1; i--)
		{
			if (pointer[i] - pointer[i - 1] == 0) 
			{
				cout << "玩家" << i << "赢了" << endl;
				keepon = false;
			}
		}
		if (cardbin[cardbin.size() - 1] > 99)
		{
			if (cardbin[cardbin.size() - 1] > 103)
			{
				colorasked = rand() % 4;
				giver = nextgiver(giver, nextplayer, playernum);
				for (int i = 1; i <= 4; i++) {
					cp = card_player.begin();
					card_player.insert(cp + pointer[giver] - 1, cardlib[0]);
					cardlib.erase(cardlib.begin());
					cout << "玩家" << giver << "摸牌*"<<i<<endl;
					for (j = giver; (int)j <= playernum; j++) {
						pointer[j]++;
					}
				}
				giver = nextgiver(giver, nextplayer, playernum);
			}
			else if (cardbin[cardbin.size() - 1] > 99 && cardbin[cardbin.size() - 1] <= 103)
			{
				colorasked = rand() % 4;
				giver = nextgiver(giver, nextplayer, playernum);
			}
		}
			else 
			{
				if (cardbin[cardbin.size()-1] % 25 >= 19 && cardbin[cardbin.size()-1] % 25 <= 20)
				{
					colorasked = cardbin[cardbin.size() - 1] / 25;//跳过
					giver = nextgiver(giver, nextplayer, playernum);
					giver = nextgiver(giver, nextplayer, playernum);
				}
				else if (cardbin[cardbin.size()-1] % 25 >= 21 && cardbin[cardbin.size()-1] % 25 <= 22)
				{
					colorasked = cardbin[cardbin.size() - 1] / 25;//翻转
					if (nextplayer = 1)
						nextplayer = -1;
					else
						nextplayer = 1;
					giver = nextgiver(giver, nextplayer, playernum);
				}
				else if (cardbin[cardbin.size()-1] % 25 >= 23 && cardbin[cardbin.size()-1] % 25 <= 24) {
					colorasked = cardbin[cardbin.size() - 1] / 25;//draw+2
					giver = nextgiver(giver, nextplayer, playernum);
					for (i = 1; i <= 2; i++) {
						cp = card_player.begin();
						card_player.insert(cp + pointer[giver] - 1, cardlib[0]);
						cardlib.erase(cardlib.begin());
						cout << "玩家" << giver << "摸牌*"<<i<<endl;
						for (i = giver; (int)i <= playernum; i++) {
							pointer[i]++;
						}
					}
					giver = nextgiver(giver, nextplayer, playernum);
				}
				else
				{
					giver = nextgiver(giver, nextplayer, playernum);
				}
			}
		

    }
	
     return 0;
}
void printcard(int x)
{
	if (x > 99) {
		if (x > 104) {
			cout << "手牌类型：万能牌" << endl;
			cout << "手牌名称：wild draw +4" << endl;
			cout << "功能：不论上一张出牌者打出的是什么颜色，而可以随意指定下家出牌的颜色，同时下家需从牌堆中罚摸4张牌，且不能再出牌。" << endl;
		}
		else
		{
			cout << "手牌类型：万能牌" << endl;
			cout << "手牌名称：wild" << endl;
			cout << "功能：不论上一张出牌者打出的是什么颜色，而可以随意指定下家出牌的颜色" << endl;
		}
	}
	else
	{
		int color = x / 25, lei = x % 25;
		if (lei >= 19) {
			cout << "出牌类型：功能牌" << endl;
			switch (lei) {
			case 19:
				cout << "功能：跳过" << endl;
				break;
			case 20:
				cout << "功能：跳过" << endl;
				break;
			case 21:
				cout << "功能：翻转" << endl;
				break;
			case 22:
				cout << "功能：翻转" << endl;
				break;
			case 23:
				cout << "功能：+2" << endl;
				break;
			case 24:
				cout << "功能：+2" << endl;
				break;
			}
		}
		else
		{
			if (lei > 9) {
				cout << "牌面数字：" << lei - 9 << endl;

			}

			else {
				cout << "牌面数字：" << lei << endl;
			}
		}
		switch (color) {
		case 0:
			cout << "牌面颜色：红" << endl;
			break;
		case 1:
			cout << "牌面颜色：黄" << endl;
			break;
		case 2:
			cout << "牌面颜色：蓝" << endl;
			break;
		case 3:
			cout << "牌面颜色：绿" << endl;
			break;

		}
	}
}
bool issamefunctioncard(int x, int y) {
	bool result = false;
	int a = x % 25;
	int b = y % 25;
	if (a <= 20 && a >= 19 && b <= 20 && b >= 19)
		result = true;
	if (a <= 22 && a >= 21 && b <= 22 && b >= 21)
		result = true;
	if (a <= 24 && a >= 23 && b <= 24 && b >=23)
		result = true;
	return result;
}
int nextgiver(int x, int y,int z) {
	int result;
	if (x + y > z)
		result = 1;
	else if (x + y < 1)
		result = z;
	else
		result = x + y;
	return result;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
