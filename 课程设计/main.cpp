#include "Map.h"
#include <iostream>
int main(int argc, char *argv[]) {
	Map map_file;
	Map map_new;
	char op;
	cout << "是否从现有文件读取数据 y/n  ";
	cout << "注意现有文件必须具有数据" << endl;
	cout << "请输入";
	cin >> op;
	if (op == 'y') {
		map_file.fread();
		while (1) {
			cout << "请输入选项" << endl;
			cout << "1 某个城市到各个城市的最小路径" << endl;
			cout << "2 两个城市最短距离" << endl;
			cout << "3 清除文件" << endl;
			cout << "4 退出" << endl;
			cout << "输入选项";
			cin >> op;
			string begin;
			string end;
			switch (op) {
				case '1':
					cout << "输入起始点" << endl;
					cin >> begin;
					map_file.shortest_point(begin);
					break;
				case '2':
					cout << "输入起始点 终点" << endl;
					cin >> begin >> end;
					map_file.shortest_point(begin, end);
					break;
			case '3':
					map_file.fclear();
					break;
				case '4':
					return 0;
			}
		}
	} else if (op == 'n') {
		while (1) {
			cout << "请输入选项" << endl;
			cout << "1 存储" << endl;
			cout << "2 某个城市到各个城市的最小路径" << endl;
			cout << "3 两个城市最短距离" << endl;
			cout << "4 退出" << endl;
			cin >> op;
			string begin;
			string end;
			switch (op) {
				case '1':
					map_new.CreateDN();
					map_new.fwrite();
					break;
				case '2':
					cout << "输入起始点" << endl;
					cin >> begin;
					map_new.shortest_point(begin);
					break;
				case '3':
					cout << "输入起始点 终点" << endl;
					cin >> begin >> end;
					map_new.shortest_point(begin, end);
					break;
				case '4':
					return 0;
			}
		}
	}
}
