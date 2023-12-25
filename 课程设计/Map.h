//
// Created by abs on 12/24/23.
//

#ifndef MAP_H
#define MAP_H
#include<string>
#include<vector>
#define MaxInt 32765
using namespace std;

class Map {
public:
    Map();

    void CreateDN();

    void shortest_point(const string&);

    void shortest_point(const string&, const string&);
    void fwrite();
    void fread();

private:
    vector<string> vex;
    vector<vector<int>> arc;
    int vexnum;
    int arcnum;

    vector<int> ShortestPath(const string&);

    int LocateInt(const string&);
    int locateint(const string&);
};

#endif //MAP_H

