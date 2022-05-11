%{
#include<stdio.h>
int yylex(void);
int yyerror(char *s);
int somme, produit, sous, divis;
%}

%token NB;
%token PROD;
%token SOM;
%token SOUS;
%token DIV;
%token FIN;

%%
liste:FIN {printf("Somme=%d\nProduit=%d\nSoustraction=%d\nDivision=%d", somme, produit, sous, divis);}
|SOM listesom'.'liste
|PROD listeprod'.'liste
|SOUS listesous'.'liste
|DIV listediv'.'liste;

listesom: NB {somme += $1;}
|listesom','NB {somme += $3;};

listeprod: NB {produit *= $1;} 
|listeprod','NB {produit *= $3;};

listesous: NB {sous += $1;}
|listesous','NB {sous -= $3;};

listediv: NB {divis+=$1 ;}
|listediv','NB {$3 != 0 ? divis /= $3 : printf("division by 0, ignoring ...\n");};
%%

#include "lex.yy.c"
int yyerror(char *s)
{
printf ("%s", s);
return (0);
}
int main()
{
somme = 0;
sous = 0;
produit = 1;
divis = 0;
yyparse();
getchar();
}
