#ifndef ZUDIROGRID_H
#define ZUDIROGRID_H
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class ZudiroGrid
{
public:
    ZudiroGrid();
    ZudiroGrid(string filename, int level, int subLevel);
    void ZudiroGridSecond(string filename, int level, int subLevel);
    void stringToVector(string text, vector <int> &attribute);
    vector<int> isDoneHere(int i, int j);

    vector <int> atg, lotg;
    vector <int> Fatg, Flotg;
    vector <vector <int> > grid;
    int dim, level, subLevel;
};

#endif // ZUDIROGRID_H
