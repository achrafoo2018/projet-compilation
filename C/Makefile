CFLAGS := -Wall -g
all: left_recursivity premier suivant table_LL1
lr: left_recursivity.c
	gcc $(CFLAGS) left_recursivity.c -o left_recursivity
pr: premier.c
	gcc $(CFLAGS) premier.c -o premier
sv: suivant.c 
	gcc $(CFLAGS) suivant.c -o suivant
TLL1: table_LL1.c
	gcc $(CFLAGS) table_LL1.c -o table_LL1

