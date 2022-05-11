%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror (char*);
%}

%%

mot : S '\n' {printf("mot correct\n"); exit(0);}
;
S : 'a'S'c'
| 'a''b''c'
| B
;

B : 
| 'b'B
;

%%
int yylex()
{
char c=getchar();
return(c);
}

int yyerror(char *s){
printf("%s \n",s);
return 0;
}
int main(){
yyparse();
printf("\n");
return 0;
}
