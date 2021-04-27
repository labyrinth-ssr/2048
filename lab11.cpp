#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <sstream>
#include "my_class.h"
#include <iostream>
#include <vector>
#include <string>
#include <getopt.h>
#include <unordered_map>

using namespace std;
using namespace className;

void Map::judgeWinner(){
        if (getMode() ==2){
            if (score[1]>score[2])
            cout<<username[0]<<"win!"<<endl;
            else if (score[1]==score[2])
            cout<<"draw!"<<endl;
            else
            cout<<username[1]<<"win!"<<endl;
        }
}

void Map::setUsername(){
        cout<<"Input user1's name:";
        cin>>username[0];
        cout<<"Input user2's name:";
        cin>>username[1];
        cout<<username[0]<<" "<<username[1]<<endl;
}

void Map::getTurnAddPrintScore(){
    if (playerNumber==1){
        cout<<"The score is:"<<score[0]<<endl;
    }
    else{
            cout<<"the next player is"<<username[2-player]<<endl;
            cout<<username[player-1]<<"'s score is:"<<score[player]<<endl;
    }
}

void Map::setMode(){
    cin>>playerNumber;
    cout<<"the mode is:"<<playerNumber<<endl;
}

void Map::add_score(int i){
    score[player]+=str[i];
}

void printInterface(){      
    printf("--------------game begins--------------\n\n"
    "please choose mode:\n1:one player\n2:two players\n"
    "please input the number:");
}

void Map:: printMap() const{
    for (int i=0;i<length;i++){
        for (int j=0;j<length;j++){
            cout<<"+-----";
        }
        cout<<"+"<<endl;
        for (int j=0;j<length;j++){
            if(str[i*length+j]==0)
            printf("|     ");
            else{
                printf("|%5d",str[i*length+j]);
            }
        }printf("|\n");
    }
    for (int j=0;j<length;j++){
        cout<<"+-----";
    }
    cout<<"+"<<endl;
    
}

void Map:: getRandom(){
    srand((unsigned)time(NULL));
    int x,y;
    while(str[(x=rand()%length)*length+(y=rand()%length)]!=0){
        ;
    }
    str[x*length+y]=2;
}

void Map:: iniMap(){
    getRandom();
    getRandom();
}

void Map:: merge(char c){
    for (int j=0;j<length;j++){
        for (int i=m[c][0];i>=0&&i<length;i+=m[c][1]){
            if(str[i*m[c][2]+j*m[c][3]]==str[(i+m[c][1])*m[c][2]+j*m[c][3]]){
                str[i*m[c][2]+j*m[c][3]] *=2;
                add_score(i*m[c][2]+j*m[c][3]);
                str[(i+m[c][1])*m[c][2]+j*m[c][3]] =0;
            }
        }
    }
}
    //vector<int> w={0,1,length,1},z={length,-1,length,1},a{0,1,1,length},s{length,-1,1,length};
void Map:: move(char c){//{w:}
    for (int j=0;j<length;j++){
        int k=m[c][0];
        for (int i=m[c][0];i>=0&&i<length;i+=m[c][1]){
            if(str[i*m[c][2]+j*m[c][3]]!=0){
                str[k*m[c][2]+j*m[c][3]]=str[i*m[c][2]+j*m[c][3]];
                k+=m[c][1];
            }
            else continue;
        }
        for (;k>=0&&k<length;k+=m[c][1]){
                str[k*m[c][2]+j*m[c][3]]=0;
        }
    }
}

bool Map::check_win(){
    for (int i=0;i<length*length;i++){        
            if (str[i]==winCondition)
                return true;        
    }
    return false;
}

void Map::updateWithInput(string input,int i){
    vector<int> copy=str;
    char c=input[i];
    move(c);
    cout<<"moved"<<endl;
    merge(c);
    move(c);
    if (copy!=str) getRandom();
    addCount();
}

bool Map::is_full(){
    for (int i=0;i<length;i++){
        for (int j=0;j<length;j++){
            if (str[i*length+j]==0){
                return false;
            }
        }
    }
    return true;
}

bool Map::check_lose(){
    vector<int> copy1=str;
    vector<int> saveScore=score;
    string input="wazs";
        for (int i=0;i<4;i++){
            updateWithInput(input,i);
            if (copy1==str) {
                direction[i]='\0';//the direction can't be moved.
            }
            else{
                str=copy1;
            }
        }
        score=saveScore;
        cout<<"This direction can be moved";
        for(int i=0;i<4;i++){
            cout<<direction[i]<<" ";
        }
        cout<<endl;
        for (int i=0;i<4;i++){
                if(direction[i]!='\0') {
                    return false;
                }
        }
    return true;
}

void Map::judgePlayer(){
    if (playerNumber==2){
        if(gameCount%2==1) player=1;
        else player=2;
    }
    cout<<"Now the player is:"<<player<<endl;
}

void Map::getDemand(){
    string save1;//take in direction
    for(int i=0;i<4;i++){
        if(direction[i]=='w'||direction[i]=='a'||direction[i]=='z'||direction[i]=='s'){
           save1.push_back(direction[i]);
        }  
    }
    cout<<"check:these directions can be moved"<<save1<<endl;
    cout<<"the size of the save1 is:"<<save1.size()<<endl;
    if(save1.size()==1){
        demand=save1[0];
        cout<<"get demand:"<<demand<<endl;
    }
}

void Map::checkCheated(string& input){//find the condition
    if (cheatMode&&player==cheated){
        getDemand();
        if(demand!='\0'){
            cout<<word[1]<<" if agree,please input"<<demand;
            cheatMode=false;
            haveCheated=true;
            cin>>input;
            word[0]='\0';
            while(input[0]!=demand){
                cin>>input;
            }
        }
        else{
            word[0]='\0';
            cin>>input;
        }
    }
    else{
        word[0]='\0';
        getline(cin,input);
        istringstream record(input);
        int i=0;
        while(record>>word[i]){
            cout<<word[i++]<<" "<<endl;
        }
    }
    direction[0]='w';direction[1]='a';direction[2]='z';direction[3]='s';
}

void Map::getCheat(string& input){
    if(!haveCheated){
    if(word[0]=="c"){
        cheatMode=true;
        if(player==1) cheated=2;
        else cheated=1;
        cout<<"cheat effect open"<<endl;
        cout<<cheated<<"is cheated"<<endl;
        cout<<word[1]<<"is the parameter."<<endl;
        std::fflush(stdin);
        cin>>input;
    }
    }
}

void checkParameter(int& length){
    while(length<2||length>5){
        cout<<"please input the length,no less than 3 and no more than 5:";
        cin>>length;
    }
}

int main(int argc,char* argv[]){
    Map game_map;
    int o;
    const char *optstring = "ts:";
    while ((o = getopt(argc, argv, optstring)) != -1) {
        switch (o) {
            case 't':
                game_map.setTestMode();
                break;
            case 's':
                if(atoi(optarg)<3||atoi(optarg)>5){
                    cout<<"please input the length,no less than 3 and no more than 5:";
                    return 0;
                }
                game_map.setLength(atoi(optarg));
                break;
        }
    }
    printInterface();
    game_map.setMode();
    if (game_map.getMode()==2){
        game_map.setUsername();
    }
    game_map.iniMap();
    std::fflush(stdin);
    while(1){
        game_map.printMap();
        game_map.judgePlayer();
        game_map.getTurnAddPrintScore();
        if (game_map.getCount()!=1){
            if (game_map.check_win()){
                cout<<"you win!"<<endl;
                game_map.judgeWinner();
                break;
            }
            else if(game_map.check_lose()){
                cout<<"you lose."<<endl;
                game_map.judgeWinner();
                break;
            }
        }
        string input;
        game_map.checkCheated(input);
        game_map.getCheat(input);
        game_map.updateWithInput(input,0);
        std::fflush(stdin);       
    }
    return 0;
} 
