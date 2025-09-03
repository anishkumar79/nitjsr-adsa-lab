#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 100
int val[N], vtop=-1; char op[N]; int otop=-1;

void pushv(int x){ val[++vtop]=x; }
int popv(){ return val[vtop--]; }
void pusho(char c){ op[++otop]=c; }
char popo(){ return op[otop--]; }
char topo(){ return (otop>=0)?op[otop]:'\0'; }
int prec(char c){ return (c=='*'||c=='/')?2:(c=='+'||c=='-')?1:0; }

int apply(int a,int b,char c){
    if(c=='+') return a+b;
    if(c=='-') return a-b;
    if(c=='*') return a*b;
    return a/b;
}

int eval(char *s){
    for(int i=0;i<strlen(s);i++){
        if(isspace(s[i])) continue;
        if(isdigit(s[i])){
            int num=0;
            while(i<strlen(s)&&isdigit(s[i]))
                num=num*10+(s[i++]-'0');
            pushv(num); i--;
        } else if(s[i]=='(') pusho(s[i]);
        else if(s[i]==')'){
            while(topo()!='('){
                int b=popv(),a=popv(); pushv(apply(a,b,popo()));
            } popo();
        } else {
            while(otop!=-1 && prec(topo())>=prec(s[i])){
                int b=popv(),a=popv(); pushv(apply(a,b,popo()));
            } pusho(s[i]);
        }
    }
    while(otop!=-1){
        int b=popv(),a=popv(); pushv(apply(a,b,popo()));
    }
    return popv();
}

int main(){
    char expr[200];
    printf("Enter expression: ");
    fgets(expr,200,stdin);  
    printf("Result = %d\n", eval(expr));
    return 0;
}
