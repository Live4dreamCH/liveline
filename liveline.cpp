#include "pch.h"
#include<queue>
#include <iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
//#include<Windows.h>
using namespace std;

class task
{
public:
	int ttime[4];
	char tname[100];
	char tadd[100];
	task(){}
	task(int t[], char n[], char a[])
	{
		strcpy_s(tname, n);
		strcpy_s(tadd, a);
		for (int i = 0; i < 4; i++)
		{
			ttime[i] = t[i];
		}
	}
	void show()const
	{
		cout << "time:" << endl;
		cout << "第" << ttime[0] << "周" << ends << "星期" << ttime[1] << ends;
		cout << setfill('0') << setw(2) << ttime[2] << ':' << setw(2) << ttime[3] << endl;
		cout << "name:" << endl;
		cout << tname << endl;
		cout << "address:" << endl;
		cout << tadd << endl;
	}
};

class cmp
{
public:
	bool operator()(task &x, task &y)
	{
		//return x->getwgt() > y->getwgt();
		//当前者时间更大，则true
		for (int i = 0; i < 4; i++)
		{
			if (x.ttime[i] > y.ttime[i])
				return true;
			else if (x.ttime[i] < y.ttime[i])
				return false;
		}
		return false;
	}
};

void save(priority_queue<task, vector<task>, cmp> &t)
{
	fstream myf;
	myf.open("YourFatherIs.lch", ios::out | ios::binary | ios::trunc);
	if (!myf)
		exit(55555);
	queue<task> temp;
	while (!t.empty())
	{
		//myf.write((char *)&t.top().tname, t.top().tname.length()).put(' ');
		//for (int i = 0; i < 4; i++)
		//{
		//	myf.write((char *)&t.top().ttime[i], sizeof(int)).put(' ');
		//}
		//myf.write((char *)&t.top().tadd, t.top().tadd.length()).put('\n');
		myf.write((char *)&t.top(), sizeof(task));
		temp.push(t.top());
		t.pop();
	}
	while (!temp.empty())
	{
		t.push(temp.front());
		temp.pop();
	}
	myf.close();
}

void load(priority_queue<task, vector<task>, cmp> &t)
{
	fstream myf;
	myf.open("YourFatherIs.lch", ios::in | ios::binary);
	if (myf)
	{
		task temp;
		int n;
		while (!myf.eof())
		{
			myf.read((char *)&temp, sizeof(task));
			n = myf.gcount();
			if (n == sizeof(task))
			{
				t.push(temp);
			}
		}
		//myf.getline((char *)&n, 100, ' ');
		//for (int i = 0; i < 4; i++)
		//{
		//	myf.getline((char *)&tt[i], sizeof(int), ' ');
		//}
	}
	else
	{
		cout << "open wrong,create new!" << endl;
		myf.open("YourFatherIs.lch", ios::out | ios::binary);
		if (!myf)
			exit(55555);
	}
	myf.close();
}

int main()
{
	priority_queue<task, vector<task>, cmp> myt;
	int c;
	load(myt);
	while (true)
	{
		cout << "1.add\n2.show" << endl;
		cin >> c;
		system("cls");	//清空窗口用

		if (c == 1)
		{
			int t[4];
			char n[100], a[100];
			cout << "time:(week day hour minute)" << endl;
			for (int i = 0; i < 4; i++)
			{
				cin >> t[i];
			}
			cout << "taskname:" << endl;
			cin >> n;
			cout << "address:" << endl;
			cin >> a;
			myt.push(*(new task(t, n, a)));
			save(myt);
			cout << "successfully added!" << endl;
			system("PAUSE ");	//暂停运行程序，并出现“请按任意键继续. . .”字样，进行等待
		}
		else if (c == 2)
		{
			if (myt.empty())
			{
				cout << "no task, you are free now!" << endl;
			}
			else
			{
				myt.top().show();
				cout << "finished?\n1.yes\t2.no" << endl;
				cin >> c;
				if (c == 1)
				{
					myt.pop();
					save(myt);
					cout << "successfully delete, goodjob!" << endl;
				}
				else
					cout << "just do it!" << endl;
			}
			system("PAUSE ");	//暂停运行程序，并出现“请按任意键继续. . .”字样，进行等待
		}
		system("cls");	//清空窗口用
	}
	//fstream myf;
	//myf.open("D:\\desktop\\liveline\\lchliveline.lch", ios::in | ios::out | ios::binary);
	//for (int i = 0; !myf&&i < 5; i++)
	//{
	//	cout << "open wrong,create new!";
	//	myf.open("D:\\desktop\\liveline\\lchliveline.lch", ios::out | ios::binary);
	//}
	//if (!myf)
	//	return 55555;
	//double n = 123.45;
	//myf.seekp(0, ios::end);
	//myf.write((char *)&n, sizeof(n));
	//myf.seekp(0, ios::beg);
	//myf.write("哈哈哈哈哈哈", sizeof("哈哈哈哈哈哈"));
	//myf.close();
	return 0;
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
