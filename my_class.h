#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

#ifndef MY_CLASS_H // include guard
#define MY_CLASS_H
namespace className{
    class Map{
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
    vector<int> w={0,1,length,1},z={length-1,-1,length,1},a{0,1,1,length},s{length-1,-1,1,length};
    unordered_map<char,vector<int>> m{{'w',w},{'z',z},{'a',a},{'s',s}};
    vector<int> score={0,0,0};
    string username[2];
    vector<int> str{vector<int>(16,0)};
    bool cheatMode=false;
    void getRandom(); 
    void merge(char);
    void move(char);
    void add_score(int);
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
        str.resize(i*i);
        m['w']={0,1,length,1};m['z']={length-1,-1,length,1};m['a']={0,1,1,length},m['s']={length-1,-1,1,length};

    }
};

}

#endif
