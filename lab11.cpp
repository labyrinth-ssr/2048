#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

void printMap(char* str){
    for (int i=0;i<4;i++){
        printf("+-----+-----+-----+-----+\n");
        for (int j=0;j<4;j++){
            printf("|  %c  ",str[i*4+j]);
        }printf("|\n");
    }
    printf("+-----+-----+-----+-----+\n");
}

void iniMap(char* str){
    for (int i=0;i<16;i++){
        str[i]=' ';
    }
    printMap(str);
}

int getRandom(short* s,int c){
    int j=(int) ((float) ((16-c)*rand())/(RAND_MAX+1.0));
    int n=s[j];
    s[j]=s[16-1-c];
    return n;
}

short getpos(short* s,int c){
    short x,y,n;
    n=getRandom(s,c);//不重复，一次一个，循环内不变的s与n返回n后给出xy
    //printf ("%d\n",n);
    return n;
}

void updateWithInput(int c,short* s,char* str){
    char input[5];
    scanf("%s",input);
    if (!strcmp(input,"n")){
        str[getpos(s,c)]='2';
    }
    printMap(str);
}

void prepareRandom(short* s){
for (int i=0;i<16;i++){
        s[i]=i;
    }
}

int main(){
    char str[17];
    int c=0;
    short s[16];
    iniMap(str);
    prepareRandom(s);
    srand((unsigned)time(NULL));
    while(c<16){
        updateWithInput(c,s,str);
        c++;
    }
    printf("game over\n");
    return 0;
}