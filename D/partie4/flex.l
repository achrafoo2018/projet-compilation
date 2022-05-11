%{
#include<stdio.h>
#include<math.h>
#include"bison.tab.h"
%}
%%
[0-9]+ {yylval=atoi(yytext); return NB;}
produit {return PROD;}
somme {return SOM;}
soustraction {return SOUS;}
division {return DIV;}
[,|.] {return yytext[0];}
[$] {return FIN;}
[ \t\n] {}
. {printf("Erreur lexicale\n"); exit(0);}
%%
int yywrap()
{return 1;}
