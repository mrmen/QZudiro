#include "zudirogrid.h"

#include <iostream>
#include <tinyxml.h>
#include <string>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <algorithm>

using namespace std;
using namespace boost;

ZudiroGrid::ZudiroGrid(){};

// Constructeur de grille
ZudiroGrid::ZudiroGrid(string filename, int level, int subLevel){

    TiXmlDocument doc(filename.c_str());

    if(!doc.LoadFile()){
        cout << "Document name : " << filename.c_str() << endl;
    }

    // get a copy of document
    TiXmlHandle hdl(&doc);
    // get the first element
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();
    if(!elem){
        cout << "element not good" << endl;
    }

    this->level = level;
    this->subLevel = subLevel;

    // create jump
    int jump = (level-1)*10 + subLevel-1;
//    cout << jump << endl;
    for(int i=0;i<jump;i++){
        elem = elem->NextSiblingElement();
    }

    string tempAtg = elem->Attribute("atg");
    stringToVector(tempAtg, this->atg);
    string tempLotg = elem->Attribute("lotg");
    stringToVector(tempLotg, this->lotg);
    this->dim = this->atg.size();

    vector<int> temp(this->dim);
    for (int i=0; i<this->dim; i++){
        for(int j=0; j<this->dim; j++){
            temp[j] = 0;
        }
        this->grid.push_back(temp);
    }
}

// Constructeur de grille
void ZudiroGrid::ZudiroGridSecond(string filename, int level, int subLevel){

    TiXmlDocument doc(filename.c_str());

    if(!doc.LoadFile()){
        cout << "Document name : " << filename.c_str() << endl;
    }

    // get a copy of document
    TiXmlHandle hdl(&doc);
    // get the first element
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();
    if(!elem){
        cout << "element not good" << endl;
    }

    this->level = level;
    this->subLevel = subLevel;

    // create jump
    int jump = (level-1)*10 + subLevel-1;
//    cout << jump << endl;
    for(int i=0;i<jump;i++){
        elem = elem->NextSiblingElement();
    }

    string tempAtg = elem->Attribute("atg");
    this->atg.clear();
    this->atg.resize(0);
    this->Fatg.clear();
    this->Fatg.resize(0);
    std::cout << tempAtg << std::endl;
    stringToVector(tempAtg, this->atg);
    string tempLotg = elem->Attribute("lotg");
    this->lotg.clear();
    this->Flotg.clear();
    this->Flotg.resize(0);
    stringToVector(tempLotg, this->lotg);
    this->dim = this->atg.size();

    for(int i=0;i<this->dim;i++){
        this->Fatg.push_back(0);
        this->Flotg.push_back(0);
    }

    vector<int> temp(this->dim);
    this->grid.clear();
    this->grid.resize(0);
    for (int i=0; i<this->dim; i++){
        for(int j=0; j<this->dim; j++){
            temp[j] = 0;
        }
        this->grid.push_back(temp);
    }
}



void ZudiroGrid::stringToVector(string text, vector<int> &attribute){
    char_separator<char> sep(",");
    tokenizer<char_separator<char> > tokens(text, sep);
    BOOST_FOREACH(string t, tokens)
    {
        attribute.push_back(lexical_cast<int>(t));
    }
}

vector<int> ZudiroGrid::isDoneHere(int i, int j){
    vector<int> returnValue;
    // get grid part
    vector<int> column;
    vector<int> line;

    //std::cout << ">>>>>>>>>>>>>>>>>>>" << std::endl;
    for(int count=0; count<this->dim; count++){
        line.push_back(this->grid[i][count]);
        column.push_back(this->grid[count][j]);
        //std::cout << grid[count][j];
    }
    //std::cout << " " << std::endl;

    // parse column
    //
    // FIXME: ne fonctionne pas dans certains cas
    //
    //
    //
    int reg = 0;
    int value = 1;
    int count = 0;
    int nonzero = 0;
    while (count<this->dim){
        if (column[count]==1){
            reg = reg + 1;
            nonzero = 1;
        }
        if (column[count]==0){
            if (reg!=0)
                value = value * reg;
            reg = 0;
        }
        count++;
    }
    if (reg!=0)
        value = value * reg;
    if (nonzero==0)
        value = 0;

    this->Fatg[j] = value;
    returnValue.push_back(value);
    //
    //
        //parse line
    reg = 0;
    value = 1;
    count = 0;
    nonzero = 0;
    while (count<this->dim){
        if (line[count]==1){
            reg = reg + 1;
            nonzero = 1;
        }
        if (line[count]==0){
            if (reg!=0)
                value = value * reg;
            reg = 0;
        }
        count++;
    }
    if (reg!=0)
        value = value * reg;
    if (nonzero==0)
        value=0;
    this->Flotg[i] = value;
    returnValue.push_back(value);

    return returnValue;
}


