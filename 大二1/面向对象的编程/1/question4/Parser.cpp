#include"Parser.h"
#include<string.h>
#include<iostream>
using namespace std;



void Parser::add_argument(string a,int b,string c){
    target[i]=a;
    num[i]=b;
    info[i]=c;
    i++;
}

int Parser::get_argument(string a){
    string h;
    h=change(a);
    for(int g=0;g<=i-1;g++)
    {
        if(target[g]==h)
        {
            return num[g];
        }
    }
    return 0;
}

void Parser::init(int a,char** b){
    for(int y=0;y<=a-1;y++)
    {
        string pp=b[y];
        if(pp=="--help")
        {
            usage();
            cout<<endl;
            cout<<"optional arguments:"<<endl;
            cout<<" --help   show this help message and exit"<<endl;
            for(int k=0;k<=i-1;k++)
            {
                cout<<" "<<target[k]<<" "<<transfer(num[k])<<"   "<<info[k]<<endl;
            }
            exit(0);
        }
    }
    for(int y=1;y<=a-1;y+=2)
    {
            int k=0;
            string po=b[y];
            for(int j=0;j<=i-1;j++)
            {
                if(target[j]==po)
                {
                    k=1;
                    if(y+1>a-1)
                    {
                        usage();
                        cout<<"./main: error: argument "<<b[y]<<": expected an argument";
                        exit(0);
                    }
                    if(ifnum(b[y+1])!=0)
                    {
                        num[j]=ifnum(b[y+1]);
                    }
                    else
                    {
                        usage();
                        cout<<"./main: error: argument "<<target[j]<<": invalid int value: '"<<b[y+1]<<"'";
                        exit(0);
                    }
                    break;
                }
            }
            if(k==0)
            {
                usage();
                cout<<"./main: error: unrecognized arguments: "<<b[y];
                exit(0);
            }
            if(y+1>a-1)
            {
                usage();
                cout<<"./main: error: argument "<<b[y]<<": expected an argument";
                exit(0);
            }
        
    }
}

void Parser::usage(){
    cout<<"usage: ./main [--help] ";
            for(int k=0;k<=i-1;k++)
            {
                cout<<"["<<target[k]<<" "<<transfer(k+1)<<"] ";
            }
            cout<<endl;
}

string Parser::transfer(int n){
    switch(n)
    {
        case 1:return "ONE";
        case 2:return "TWO";
        case 3:return "THREE";
        case 4:return "FOUR";
        case 5:return "FIVE";
        case 6:return "SIX";
        case 7:return "SEVEN";
        case 8:return "EIGHT";
        case 9:return "NINE";
        case 10:return "TEN";
    }
    return "0";
}

int Parser::ifnum(char *a){
    int l;
    l=atoi(a);
    if(l==atoi("10000000000000000000000")||l==atoi("-1000000000000000000"))
    {
        return 0;
    }
    else 
    {
        return l;
    }
}

string Parser::change(string a){
    string b;
    int u=a.length();
    char jj[100];
    jj[0]='-';
    jj[1]='-';
    for(int x=0;x<=u-1;x++)
    {
        jj[x+2]=a[x];
    }
    jj[u+2]='\0';
    b=jj;
    memset(jj,0,100*sizeof(char));
    return b;
}