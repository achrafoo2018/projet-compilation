lettre [A-Za-z]
chiffre [0-9]
identificateur ({lettre}|_)({lettre}|{chiffre}|_)*
entier ("+"|"-")?{chiffre}+
%%
{identificateur} printf ("%s: Est un identificateur \n", yytext);
{entier} printf ("%s: Est un entier naturel \n",yytext);
.* printf ("%s: Ni un identificateur Ni un nombre \n", yytext);
%%
int yywrap() 
{ 
return 1 ; 
}
int main()
{
yylex() ; 
} 

