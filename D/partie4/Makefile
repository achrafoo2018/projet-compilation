all: bison.y flex.l
	bison -d bison.y 
	flex flex.l
	gcc bison.tab.c  