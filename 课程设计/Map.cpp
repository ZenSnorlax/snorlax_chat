//
// Created by abs on 12/24/23.
//

#include "Map.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#define MaxVex 100
using namespace std;
Map::Map() : vex(100, ""), arc(100, vector<int>(100, MaxInt)) {
	vexnum = 100;
	arcnum = 100;
}

void Map::CreateDN() {
	cout << "输入总城市" << endl;
	scanf("%d", &vexnum);
	cout << "输入总路线" << endl;
	scanf("%d", &arcnum);
	cout << "输入顶点参数" << endl;
	cout << "例如 地点名 地点名 距离" << endl;
	for (int i = 0; i < arcnum; ++i) {
		cout << ": ";
		string vb;
		string ve;
		int distance;
		cin >> vb >> ve >> distance;
		const int begin = LocateInt(vb);
		const int end = LocateInt(ve);
		arc[begin][end] = distance;
	}
	for (int i = 0; i < vexnum; ++i) {
		if (vex[i].empty()) {
			cout << "请输入剩余顶点" << endl;
			cout << ": ";
			cin >> vex[i];
		}
	}

}


void Map::shortest_point(const string &v) {
	vector<int> path = ShortestPath(v);
	int index = LocateInt(v);
	for (int i = 0; i < vexnum; ++i) {
		if (i == index)
			continue;
		int j = i;
		if (path[j] == -1)
			cout << vex[j] << "不能到达" << endl;
		else {
			while (j != index) {
				cout << vex[j] << "<-";
				j = path[j];
			}
			cout << vex[index] << "<-" << endl;
		}
	}
}

void Map::shortest_point(const string &vb, const string &ve) {
	if (vb == ve) {
		cout << "起点和终点相同，无需计算最短路径。" << endl;

		return;
	}

	vector<int> path = ShortestPath(vb);
	int b = LocateInt(vb);
	int e = LocateInt(ve);
	if (path[e] == -1) {
		cout << ve << "不能到达" << endl;
	} else {
		int j = e;
		while (j != b) {
			cout << vex[j] << "<-";
			j = path[j];
		}
		cout << vex[b] << "<-" << endl;
	}
}

vector<int> Map::ShortestPath(const string &v) {
	int index = LocateInt(v);
	vector<bool> S(vexnum, false);
	vector<int> D(vexnum);
	vector<int> Path(vexnum);
	for (int i = 0; i < vexnum; ++i) {
		D[i] = arc[index][i];
		if (D[i] < MaxInt)
			Path[i] = index;
		else
			Path[i] = -1;
	}
	S[index] = true;
	D[index] = 0;
	for (int i = 1; i < vexnum; ++i) {
		int min = MaxInt;
		for (int w = 0; w < vexnum; ++w)
			if (!S[w] && D[w] < min) {
				index = w;
				min = D[w];
			}
		S[index] = true;
		for (int w = 0; w < vexnum; ++w)
			if (!S[w] && (D[index] + arc[index][w]) < D[w]) {
				D[w] = D[index] + arc[index][w];
				Path[w] = index;
			}
	}
	return Path;
}

int Map::LocateInt(const string &v) {
	int i;
	for (i = 0; !vex[i].empty() && i < MaxVex; ++i)
		if (vex[i] == v)
			return i;
	vex[i] = v;
	return i;
}

void Map::fwrite() {
	ofstream test_write;
	test_write.open("test.csv", ios::out);
	assert(test_write.is_open());	
	test_write.clear();
	for (int i = 0; i < vexnum; ++i) {
		for (int j = 0; j < vexnum; ++j) {
			if (arc[i][j] == MaxInt)
				continue;
			test_write << vex[i] << "," << vex[j] << "," << arc[i][j] << '\n';
		}
	}
	test_write.close();
}
void Map::fread() {
	ifstream test_read;
	test_read.open("test.csv");
	assert(test_read.is_open());
	string s;
	vexnum = 0;
	while (getline(test_read, s)) {
		string vb;
		string ve;
		int distance;
		int count = 0;
		int first;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == ',') {
				++count;
				if (count == 1) {
					vb = s.substr(0, i);
					first = i;
				}
				if (count == 2) {
					ve = s.substr(first + 1, i - first - 1);
					distance = s[i + 1] - '0';
					break;
				}
			}
		}
		int b = locateint(vb);
		int e = locateint(ve);
		arc[b][e] = distance;
	}
	test_read.close();
}
int Map::locateint(const string &v) {
	int i;
	for (i = 0; !vex[i].empty() && i < MaxVex; ++i)
		if (vex[i] == v)
			return i;
	++vexnum;
	vex[i] = v;
	return i;
}
void Map::fclear() {
	ofstream file;
	file.open("test.csv");
	file.clear();
	file.close();
}
