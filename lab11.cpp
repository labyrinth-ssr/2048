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

void Map::add_score(int i,int j){
    score[player]+=str[i][j];
}

void printInterface(){      
    printf("--------------game begins--------------\n\n"
    "please choose mode:\n1:one player\n2:two players\n"
    "please input the number:");
}

void Map:: printMap() const{//带清屏的打印
    for (int i=0;i<length;i++){
        for (int j=0;j<length;j++){
            cout<<"+-----";
        }
        cout<<"+"<<endl;
        for (int j=0;j<length;j++){
            if(str[i][j]==0)
            printf("|     ");
            else{
                printf("|%5d",str[i][j]);
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
    while(str[x=rand()%length][y=rand()%length]!=0){
        ;
    }
    str[x][y]=2;
}

void Map:: iniMap(){
    for (int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            str[i][j]=0;
        }
    }
    getRandom();
    getRandom();
}

void Map:: mergew(){
    for (int j=0;j<length;j++){
        for (int i=0;i<length-1;i++){
            if(str[i][j]==str[i+1][j]){
                str[i][j] *=2;
                add_score(i,j);
                str[i+1][j] =0;
            }
        }
    }
}

void Map:: mergea(){
    for (int j=0;j<length;j++){
        for (int i=0;i<length-1;i++){
            if(str[j][i]==str[j][i+1]){
                str[j][i] *=2;
                add_score(j,i);
                str[j][i+1] =0;
            }
        }
    }
}

void Map:: mergez(){
    for (int j=0;j<length;j++){
        for (int i=length-1;i>0;i--){
            if(str[i][j]==str[i-1][j]){
                str[i][j] *=2;
                add_score(i,j);
                str[i-1][j] =0;
            }
        }
    }
}

void Map:: merges(){
    for (int j=0;j<length;j++){
        for (int i=length-1;i>0;i--){
            if(str[j][i]==str[j][i-1]){
                str[j][i] *=2;
                add_score(j,i);
                str[j][i-1] =0;
            }
        }
    }
}

void Map:: movew(){
    for (int j=0;j<length;j++){
        for (int i=0;i<length-1;i++){
            int k=i;
            while(k<length&&str[k][j]==0){
                k++;
            }
            for (int l=i,m=k;m<length;l++,m++){
                str[l][j]=str[m][j];
            }
            for (int l=0;l<k-i;l++){
                str[length-1-l][j]=0;
            }
        }
    }
}

void Map:: movez(){
    for (int j=0;j<length;j++){
        for (int i=length-1;i>=0;i--){
            int k=i;
            while(k>=0&&str[k][j]==0){
                k--;
            }
            for (int l=i,m=k;m>=0;l--,m--){
                str[l][j]=str[m][j];
            }
            for (int l=length-1;l>length-1-i+k;l--){
                str[length-1-l][j]=0;
            }
        }
    }
}

void Map:: movea(){
    for (int j=0;j<length;j++){
        for (int i=0;i<length-1;i++){
            int k=i;
            while(k<length&&str[j][k]==0){
                k++;
            }
            for (int l=i,m=k;m<length;l++,m++){
                str[j][l]=str[j][m];
            }
            for (int l=0;l<k-i;l++){
                str[j][length-1-l]=0;
            }
        }
    }
}

void Map:: moves(){
    for (int j=0;j<length;j++){
        for (int i=length-1;i>=0;i--){
            int k=i;
            while(k>=0&&str[j][k]==0){
                k--;
            }
            for (int l=i,m=k;m>=0;l--,m--){
                str[j][l]=str[j][m];
            }
            for (int l=length-1;l>length-1-i+k;l--){
                str[j][length-1-l]=0;
            }
        }
    }
}

bool Map::check_win(){
    for (int i=0;i<length;i++){
        for (int j=0;j<length;j++){
            if (str[i][j]==winCondition)
                return true;
        }
    }
    return false;
}

void Map::updateWithInput(string input,int i){
    vector<vector<int>> copy=str;
    switch (input[i]){
        case 'w':
        movew();   
        mergew();
        movew();
        if (copy==str) break;
        getRandom();
        break;
        case 'z':
        movez();
        mergez();
        movez();
        if (copy==str) break;
        getRandom();
        break;
        case 'a':
        movea();
        mergea();
        movea();
        if (copy==str) break;
        getRandom();
        break;
        case 's':
        moves();
        merges();
        moves();
        if (copy==str) break;
        getRandom();
    }
    addCount();
    
}

bool Map::is_full(){
    for (int i=0;i<length;i++){
        for (int j=0;j<length;j++){
            if (str[i][j]==0){
                return false;
            }
        }
    }
    return true;
}

bool Map::check_lose(){
    vector<vector<int>> copy1=str;
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
        fflush(stdin);
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
            label:case '?':
                printf("error optopt: %c\n", optopt);
                printf("error opterr: %d\n", opterr);
                return 0;
                break;
        }
    }
    printInterface();
    game_map.setMode();
    if (game_map.getMode()==2){
        game_map.setUsername();
    }
    game_map.iniMap();
    fflush(stdin);
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
        fflush(stdin);       
    }
    return 0;
} 
