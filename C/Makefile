CFLAGS := -Wall -g
all: left_recursivity LL1_parser
lr: left_recursivity.c
	gcc $(CFLAGS) left_recursivity.c -o left_recursivity
TLL1: LL1_parser.c
	gcc $(CFLAGS) LL1_parser.c -o LL1_parser

