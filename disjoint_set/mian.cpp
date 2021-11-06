#include<graphics.h>
#include<iostream>
#include<ctime>
using namespace std;
#define random(x) rand()%x
#define PROP 15//设置方格的边长
#define fx(x) 49+PROP*((x-1)%w+1)
#define fy(x) 50+PROP*((x-1)/w) 


unsigned int w = 0, h = 0, sum = 0;
int s[1000000] = { 0 };

int Find(int);
void unionSet_N(int, int);
void unionSet(int, int);

void rander_map();
void Border_erase(int, int);
int chief_Fun();
void init_ar();
void unionSet_N(int, int);
void init_img();
void erase_D(int);
void erase_R(int);

int main()
{
	srand((int)time(NULL));
	cout << "请分别输入行和列，用空格隔开：" << endl;
	cin >> w >> h;
	sum = w * h;
	init_ar();
	init_img();
}


/*-------具体函数实现--------*/

//按高度合并两个不相交集合
void unionSet(int root1, int root2)
{
	if (s[root2] < s[root1])
	{
		s[root1] = root2;
	}
	else
	{
		if (s[root1] == s[root2]) --s[root1];
		s[root2] = root1;
	}
}

//普通合并
void unionSet_N(int root1, int root2)
{
	s[root2] = root1;
}

//查找根节点，返回根节点下标
int Find(int index)
{
	if (s[index] == index) return index;
	return s[index] = Find(s[index]);
}


void init_ar()
{
	int count = 0;
	for (int i = 1; i <= sum; i++)
	{
		s[count] = ++count;
	}
}

void init_img()
{
	initgraph(w * PROP + 100, h * PROP + 100);
	setbkmode(TRANSPARENT);
	setbkcolor(RGB(255, 248, 220));//设置背景颜色
	cleardevice();//使用当前背景色清空绘图设备
	setlinestyle(PS_SOLID, 1, NULL, 0);
	setlinecolor(RGB(0, 0, 0));
	line(49, 49, 49 + w * PROP, 49);
	line(48, 49, 48, 49 + h * PROP);

	setlinecolor(RGB(255, 248, 220));
	line(48, 49, 48, 49 + PROP);

	rander_map();
	chief_Fun();
	while (1);
}

void rander_map()
{
	setlinestyle(PS_SOLID, 1, NULL, 0);
	setlinecolor(RGB(0, 0, 0));
	int count = 0;
	for (int i = 1; i <= w * h; i++)
	{
		count++;
		if (count < sum)
			line(fx(count), fy(count), fx(count), fy(count) + PROP - 1);
		line(fx(count), fy(count) + PROP - 1, fx(count) - PROP - 1, fy(count) + PROP - 1);
	}
}

void erase_D(int x)
{
	setlinestyle(PS_SOLID, 1, NULL, 0);
	setlinecolor(RGB(255, 248, 220));
	line(fx(x), fy(x) + PROP - 1, fx(x) - PROP - 1, fy(x) + PROP - 1);
}

void erase_R(int x)
{
	setlinestyle(PS_SOLID, 1, NULL, 0);
	setlinecolor(RGB(255, 248, 220));
	line(fx(x), fy(x), fx(x), fy(x) + PROP - 1);
}
void Border_erase(int a, int b)
{
	if (a < b) swap(a, b);
	if (a == b + w)erase_D(b);
	if (a == b - 1)erase_R(a);
	if (a == b - w)erase_D(a);
	if (a == b + 1)erase_R(b);
}

int celect(int x)
{
	int temp = random(5);
	if (temp == 1 && (x - w) > 1 && (x - w) < w * h) return x - w;
	if (temp == 2 && (x + 1) > 1 && (x + 1) % w != 1) return x + 1;
	if (temp == 3 && (x + w) > 1 && (x + w) < w * h) return x + w;
	if (temp == 4 && (x - 1) > 1 && (x - 1) % w != 0) return x - 1;
	return celect(x);
}


int chief_Fun()
{
	while (1)
	{
		int a, b;
		a = random(sum + 1);
		b = celect(a);
		if (Find(a) != Find(b))
		{
			unionSet_N(Find(a), Find(b));
			Border_erase(a, b);
		}
		int i = 10000;
		while (i--);
	}
}
