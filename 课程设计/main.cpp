#include "Map.h"
#include <iostream>
using namespace std;
int main() {
	Map map;
	cout << "请输入选项" << endl;
	cout << "1 存储" << endl;
	cout << "2 各个城市最短距离" << endl;
	cout << "3 两个城市最短距离" << endl;
	cout << "输入选项" << endl;
	int op;
	string begin;
	string end;
	cin >> op;
	switch (op) {
		case 1:
			map.CreateDN();
			map.fwrite();
			break;
		case 2:
			cout << "输入起点" << endl;
			cin >> begin;
			map.fread();
			map.shortest_point(begin);
			break;
		case 3:
			cout << "输入起点 终点" << endl;
			cin >> begin >> end;
			map.fread();
			map.shortest_point(begin, end);
			break;
		default:
			break;
	}
	map.fread();
}
