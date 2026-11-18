#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void SetColor(int textColor){
    cout << "\033[" << textColor << "m";
}
void ResetColor(){
    cout << "\033[0m";
}

//declaration
int number=3;
bool blow=false;
bool first=true;
int identical=0;
int wrong=0;
static const int hight=(10+2);
static const int length=(10+2);
char board[hight][length];
bool wisible[hight][length];
char flag[hight][length];

int main(){
    setlocale(LC_ALL,"");
    srand(time(0));

    //base initialization
    for(int i=0;i<hight;i++){
        for(int j=0;j<length;j++){
            board[i][j]='0';
            wisible[i][j]=false;
            flag[i][j]='0';
        }
    }

    //placeing the mines
    cout << "Goal: flag all mines and ONLY the mines\n";
    cout << "pieces of mines: \n";
    first=true;
    do{
        if(first==false){
            cout << "Something went wrong....\nTry again.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        first=false;
    }while((!(cin >> number)) || number > ((length-2)*(hight-2)));
    first=true;
    int x, y, a=0;
    do{
        x=rand()%(hight-2)+1;
        y=rand()%(hight-2)+1;
        if(board[x][y]=='X'){
        }
        else if(board[x][y]=='0'){
            board[x][y]='X';
            a++;
        }
    }while(a<number);

    //counting the mines
    int b=48;
    for(int k=1;k<(hight-1);k++){
        for(int l=1;l<(length-1);l++){
            if(board[k][l]!='X'){
                for(int m=(k-1);m<=(k+1);m++){
                    for(int n=(l-1);n<=(l+1);n++){
                        if(board[m][n]=='X'){
                            b++;
                        }
                    }
                }
                board[k][l]=b;
                b=48;
            }
        }
    }

    //first gess
    int line=0/*sor*/, column=0/*oszlop*/, action=0, last=0;/*[oszlop][sor]*/
    char ch, chs;

do{

    for(int aa=1;aa<(hight-1);aa++){
        //cout << "test";
        for(int ab=1;ab<(length-1);ab++){
            //cout << "tset";
            if(wisible[aa][ab]==true && flag[aa][ab]!='P'){
                cout << board[aa][ab] << " ";
            }
            else if(flag[aa][ab]=='P'){
                SetColor(31);
                cout << "P ";
                ResetColor();
            }
            else{
                cout << "- ";
            }
        }
        cout <<"\n";
    }

        first=true;
        do{
            if(first==false){
                cout << "Something went wrong....\nTry again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            first=false;
            chs=(length-3+65);
            cout << "A-" << chs << ":";
            cin >>  ch;
        }while(!((ch>=65 && ch<=(length-3+65)) || (ch>=97 && ch<=(length-3+97))));
        first=true;
        if(ch>90){
            line=ch-96;
        }
        else{
            line=ch-64;
        }
        //cout << "line" << line;
        do{
            if(first==false){
                cout << "Something went wrong....\nTry again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "line(sor): ";
            first=false;
        }while((!(cin >> column)) || ((column > (length-2)) || (column<=0)));
        first=true;

        do{
            if(first==false){
                cout << "Something went wrong....\nTry again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "action(1-> mine; 2-> flag; 3-> remove flag): ";
            cin >> action;
            first=false;
        }while(!(action<4 && action>0));
        cout << "\n";

if(action==1){
    if(board[column][line]=='X'){
        blow=true;
    }
    else if(board[column][line]!='X' && wisible[column][line]==true){
        identical=0;
        for(int ai=-1;ai<2;ai++){
            for(int aj=-1;aj<2;aj++){
                if(board[column+ai][line+aj]=='X' && flag[column+ai][line+aj]=='P'){
                    identical++;
                }
            }
        }
        if(identical==board[column][line]-48){
            for(int ak=-1;ak<2;ak++){
                for(int al=-1;al<2;al++){
                    if(board[column][line]!='X'){
                        wisible[column+ak][line+al]=true;
                    }
                }
            }
        }
    }
    wisible[column][line]=true;
    int sum=1, sum_pre=0;

    do{
        for(int o=1;o<(hight-1);o++){
            for(int p=1;p<(length-1);p++){
                if(wisible[o][p]==true){
                    if(board[o][p]=='0'){
                        for(int q=(-1);q<2;q++){
                            for(int r=(-1);r<2;r++){
                                wisible[o+q][p+r]=true;
                            }
                        }
                    }
                }
                else if(board[o][p]!='0' && board[o][p]!='X'){
                    for(int u=(-1);u<2;u++){
                        for(int v=(-1);v<2;v++){
                            if(board[o][p]=='0' && board[o][p]!='X'){
                                wisible[o+u][p+v]=true;
                            }
                        }
                    }
                }
            }
        }

        sum_pre=sum;
        sum=0;
        for(int w=1;w<(hight-1);w++){
            for(int z=1;z<(length-1);z++){
                if(wisible[w][z]==true){
                    sum++;
                }
            }
        }
    }while(sum_pre!=sum);

    if(blow==true){
        cout << "BBlown up!\nYou have lost.\n";
            for(int ag=1;ag<(hight-1);ag++){
                for(int ah=1;ah<(length-1);ah++){
                    if(board[ag][ah]=='X'){
                        SetColor(31);
                        cout << board[ag][ah] << " ";
                        ResetColor();
                    }
                    else{
                        cout << board[ag][ah] << " ";
                    }
            }
            cout << "\n";
            }
        break;
    }
}

else if(action==2){
    identical=0;
    wrong=0;
    flag[column][line]='P';
    for(int ac=1;ac<(hight-1);ac++){
        for(int ad=1;ad<(length-1);ad++){
            if(board[ac][ad]=='X' && flag[ac][ad]=='P'){
                identical++;
            }
            else if(flag[ac][ad]=='P' && board[ac][ad]!='X'){
                wrong++;
            }
        }
    }
    if(identical==number && wrong==0){
        cout << "You have won!\n";
        for(int ae=1;ae<(hight-1);ae++){
            for(int af=1;af<(length-1);af++){
                if(board[ae][af]=='X'){
                        SetColor(31);
                        cout << board[ae][af] << " ";
                        ResetColor();
                    }
                    else{
                        cout << board[ae][af] << " ";
                    }
            }
            cout << "\n";
        }
        break;
    }
}
else if(action==3){
    identical=0;
    wrong=0;
    flag[column][line]='0';
    for(int ac=1;ac<(hight-1);ac++){
        for(int ad=1;ad<(length-1);ad++){
            if(board[ac][ad]=='X' && flag[ac][ad]=='P'){
                identical++;
            }
            else if(flag[ac][ad]=='P' && board[ac][ad]!='X'){
                wrong++;
            }
        }
    }
    if(identical==number && wrong==0){
        cout << "You have won!\n";
        for(int ae=1;ae<(hight-1);ae++){
            for(int af=1;af<(length-1);af++){
                if(board[ae][af]=='X'){
                        SetColor(31);
                        cout << board[ae][af] << " ";
                        ResetColor();
                    }
                    else{
                        cout << board[ae][af] << " ";
                    }
            }
            cout << "\n";
        }
        break;
    }
}

}while(blow==false);

return 0;
}
