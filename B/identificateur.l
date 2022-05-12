lettre [A-Za-z]
chiffre [0-9]
identificateur {lettre}({lettre}|{chiffre})*
%%
{identificateur} printf ("%s: Est un identificateur \n", yytext);
. printf ("%s: Ce n'est pas un identificateur \n", yytext);
%%
int yywrap() 
{ 
return 1 ; 
}
int main()
{
yylex();
}