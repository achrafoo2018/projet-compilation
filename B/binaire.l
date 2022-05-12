%%
(0|1)+ printf (" %s : c'est un nombre binaire \n",yytext);
.* printf ("%s : ce n'est pas un nombre binaire \n",yytext);
%%
int yywrap()
{
return 1 ;
}
int main(int argc, char *argv[]) 
{ 
   ++argv, --argc; 
   if ( argc > 0 )
       yyin = fopen( argv[0], "r" ); 
   else {
       yyin = stdin;
       
   }
   yylex() ; 
} 

