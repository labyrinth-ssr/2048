#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

void printMap(int str[][4]){//带清屏的打印
    system("cls");
    for (int i=0;i<4;i++){
        printf("+-----+-----+-----+-----+\n");
        for (int j=0;j<4;j++){
            if(str[i][j]==0)
            printf("|     ");
            else{
                printf("|%5d",str[i][j]);
            }
        }printf("|\n");
    }
    printf("+-----+-----+-----+-----+\n");
}

void getRandom(int str[4][4]){
    int x,y;
    while(str[x=rand()%4][y=rand()%4]!=0){
        ;
    }
    str[x][y]=2;
}

void iniMap(int str[4][4]){
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            str[i][j]=0;
        }
    }
    getRandom(str);
    getRandom(str);
}

void mergew(int str[4][4],int i=0,int j=0){
    for ( j=0;j<4;j++){
        for ( i=0;i<3;i++){
            if(str[i][j]==str[i+1][j]){
                str[i][j] *=2;
                str[i+1][j] =0;
            }
        }
    }
}

void mergea(int str[4][4]){
    for (int j=0;j<4;j++){
        for (int i=0;i<3;i++){
            if(str[j][i]==str[j][i+1]){
                str[j][i] *=2;
                str[j][i+1] =0;
            }
        }
    }
}

void mergez(int str[4][4]){
    for (int j=0;j<4;j++){
        for (int i=3;i>0;i--){
            if(str[i][j]==str[i-1][j]){
                str[i][j] *=2;
                str[i-1][j] =0;
            }
        }
    }
}

void merges(int str[4][4]){
    for (int j=0;j<4;j++){
        for (int i=3;i>0;i--){
            if(str[j][i]==str[j][i-1]){
                str[j][i] *=2;
                str[j][i-1] =0;
            }
        }
    }
}

void movew(int str[4][4]){
    for (int j=0;j<4;j++){
        for (int i=0;i<3;i++){
            int k=i;
            while(k<4&&str[k][j]==0){
                k++;
            }
            for (int l=i,m=k;m<4;l++,m++){
                str[l][j]=str[m][j];
            }
            for (int l=0;l<k-i;l++){
                str[3-l][j]=0;
            }
        }
    }
}

void movez(int str[4][4]){
    for (int j=0;j<4;j++){
        for (int i=3;i>=0;i--){
            int k=i;
            while(k>=0&&str[k][j]==0){
                k--;
            }
            for (int l=i,m=k;m>=0;l--,m--){
                str[l][j]=str[m][j];
            }
            for (int l=3;l>3-i+k;l--){
                str[3-l][j]=0;
            }
        }
    }
}

void movea(int str[4][4]){
    for (int j=0;j<4;j++){
        for (int i=0;i<3;i++){
            int k=i;
            while(k<4&&str[j][k]==0){
                k++;
            }
            for (int l=i,m=k;m<4;l++,m++){
                str[j][l]=str[j][m];
            }
            for (int l=0;l<k-i;l++){
                str[j][3-l]=0;
            }
        }
    }
}

void moves(int str[4][4]){
    for (int j=0;j<4;j++){
        for (int i=3;i>=0;i--){
            int k=i;
            while(k>=0&&str[j][k]==0){
                k--;
            }
            for (int l=i,m=k;m>=0;l--,m--){
                str[j][l]=str[j][m];
            }
            for (int l=3;l>3-i+k;l--){
                str[j][3-l]=0;
            }
        }
    }
}

void save_func(int str[4][4],int save[4][4]){
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            save[i][j]=str[i][j];
        }
    }
}

bool check_equal(int str[4][4],int save[4][4]){
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if(save[i][j]!=str[i][j])
                return 0;
        }
    }
    return 1;
}

bool check_win(int str[4][4],int condition){
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (str[i][j]==condition)
                return true;
        }
    }
    return false;
}

void updateWithInput(int str[4][4],char input[5],int i){
    int save[4][4]={0};
    switch (input[i]){
        case 'w':
        save_func(str,save);
        movew(str);   
        mergew(str);
        movew(str);
        if (check_equal(str,save)) break;
        getRandom(str);
        break;
        case 'z':
        save_func(str,save);
        movez(str);
        mergez(str);
        movez(str);
        if (check_equal(str,save)) break;
        getRandom(str);
        break;
        case 'a':
        save_func(str,save);
        movea(str);
        mergea(str);
        movea(str);
        if (check_equal(str,save)) break;
        getRandom(str);
        break;
        case 's':
        save_func(str,save);
        moves(str);
        merges(str);
        moves(str);
        if (check_equal(str,save)) break;
        getRandom(str);
    }
}

bool is_full(int str[4][4]){
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (str[i][j]==0) return false;
        }
    }
    return true;
}

bool check_lose(int str[4][4]){
    int save0[4][4]={0};
    save_func(str,save0);
    char input[5]={'w','a','z','s'};
    if (!is_full(str)) return false;
    else{
        for (int i=0;i<4;i++){
        updateWithInput(str,input,i);
        if (!check_equal(str,save0)) {
            save_func(save0,str);
            return false;
        }
    }
    }
    return true;
}

int main(int argc,char* argv[]){
    int str[4][4];
    int c=0;
    int s[16];
    char input[5];
    int condition=2048;
    srand((unsigned)time(NULL));
    if(argv[1]!=NULL&&!strcmp(argv[1],"-t")){
        condition=64;
        printf ("enter test mode\n");
        Sleep(500);
    }
    iniMap(str);
    printMap(str);
    while(1){
        char input[5]; 
        fflush(stdin);
        input[0]=getch();
        fflush(stdin);
        updateWithInput(str,input,0);
        printMap(str);
        if (check_win(str,condition)) {
            printf("you win!\n");
            break;
        }
        else if(check_lose(str)){
            printf("game over!\n");
            break;
        }
    }
    return 0;
}
