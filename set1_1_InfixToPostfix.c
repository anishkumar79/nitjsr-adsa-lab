#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
char stack[MAX]; int top=-1;

void push(char c){ stack[++top]=c; }
char pop(){ return stack[top--]; }
char peek(){ return (top>=0)?stack[top]:'\0'; }
int prec(char c){ return (c=='*'||c=='/')?2:(c=='+'||c=='-')?1:0; }

void infixToPostfix(char in[], char out[]){
    int k=0;
    for(int i=0;i<strlen(in);i++){
        char c=in[i];
        if(isdigit(c)) out[k++]=c;
        else if(c=='(') push(c);
        else if(c==')'){ while(peek()!='(') out[k++]=pop(); pop(); }
        else{ while(top!=-1 && prec(peek())>=prec(c)) out[k++]=pop(); push(c); }
    }
    while(top!=-1) out[k++]=pop();
    out[k]='\0';
}

int main(){
    char in[MAX],out[MAX];
    printf("Enter infix: "); scanf("%s",in);
    infixToPostfix(in,out);
    printf("Postfix: %s\n",out);
}
