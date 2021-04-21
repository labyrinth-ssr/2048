#include <vector>
#include <string>
#include <iostream>

using namespace std;

#ifndef MY_CLASS_H // include guard
#define MY_CLASS_H
namespace className{
    class Map{
    //after examining,the only directon can be moved will be the demand.
    char demand='\0';
    char direction[4]={'w','a','z','s'};
    string word[2];//parameters for cheat
    int cheated=0;//who is cheated
    bool haveCheated=false;
    int winCondition=2048;
    int playerNumber =1;
    int gameCount=1;//gameCount
    int player=0;
    int length=4;
    vector<int> score={0,0,0};
    string username[2];
    vector<vector<int>> str={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    bool cheatMode=false;
    void getRandom(); 
    void mergew();
    void mergea();
    void mergez();
    void merges();
    void movew();
    void movea();
    void movez();
    void moves();
    void add_score(int ,int);
    void addCount(){
        gameCount++;
    }
    bool is_full();
    void getDemand();//only one direction to go
    public:
    int getCount(){
        return gameCount;
    }
    void setTestMode(char*);
    Map()=default;
    Map(int i){
        length=i;
        vector<int> temp(i);
        str.resize(i,temp);      
    }
    void iniMap();
    void printMap() const;
    void getTurnAddPrintScore();
    void setUsername();
    void setMode();
    void updateWithInput(string,int);
    int getMode(){
        return playerNumber;
    };
    bool check_win();
    bool check_lose();
    void judgeWinner();
    void getCheat(string&);
    void judgePlayer();
    void checkCheated(string&);
    void analyzeArgv(int,char*[]);
    void setTestMode(){
        winCondition=64;
        cout<<"win condition is:"<<winCondition<<endl;
    }
    void setLength(int i){
        length=i;
        vector<int> temp(i);
        str.resize(i,temp);
    }
};

}

#endif
