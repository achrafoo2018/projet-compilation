#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 100


int in_array(char *, char, int);

char* substring(char*, const char *, int, int);
char** str_split(char*, const char);
void str_append(char*, char);

#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define MAX 100

void followFirst(char , int , int);
void findFirst(char , int , int);
void follow(char c);

int count,n=0;
char calc_first[MAX][MAX];
char calc_follow[MAX][MAX];
int m=0;
char first[MAX];
char *productions[MAX];
char *production[MAX];
char f[MAX];
int k;
char ck;
int e;

int main(int argc,char **argv)
{
	int jm=0;
	int km=0;
	int i;
	char c,ch;
	count = 8;
	
    printf("Donner le nombre de production : ");  
    scanf("%d",&count);  
    printf("Donner la grammaire comme suit (epsilon = #) : NT->..|... :\n");
    int num = 0;
    for(int i=0;i<count;i++){  
        productions[i] = (char*)malloc(sizeof(char) * MAX);
        scanf("%s", productions[i]);  
        char *non_terminal = (char *)malloc(sizeof(char) * 3);
        str_append(non_terminal, productions[i][0]);
        if(productions[i][1] != '-')
            str_append(non_terminal, productions[i][1]);
        substring(productions[i], productions[i], 3, strlen(productions[i])-3);
        char **tokens = str_split(productions[i], '|');
        if(tokens){
            for(int t=0; *(tokens+t); t++){
                char *tmp = (char*)malloc(sizeof(char) * MAX);
                strcpy(tmp, non_terminal);
                str_append(tmp, '=');
                strcat(tmp, *(tokens+t));
                production[num] = (char *)malloc(sizeof(char) * MAX);
                strcpy(production[num++], tmp);
            }
        }
    }
    count = num;
	int kay;
	char done[count];
	int ptr = -1;
	for(k=0;k<count;k++){
		for(kay=0;kay<100;kay++){
			calc_first[k][kay] = '!';
		}
	}
	int point1 = 0,point2,flag;
	for(k=0;k<count;k++){
		c=production[k][0];
		point2 = 0;
		flag = 0;
		for(kay = 0; kay <= ptr; kay++)
			if(c == done[kay])
				flag = 1;
		if (flag == 1)
			continue;
		findFirst(c,0,0);
		ptr+=1;
		done[ptr] = c;
		printf("\n\033[1m Premier(%c)\033[0m= { ",c);
		calc_first[point1][point2++] = c;
		for(i=0+jm;i<n;i++){
			int j = 0,chk = 0;
  			for(j=0;j<point2;j++){
  				if (first[i] == calc_first[point1][j]){
  					chk = 1;
  					break;
				}
			}
			if(chk == 0){
  		 		printf("%c, ",first[i]);
  				calc_first[point1][point2++] = first[i];
			}
		}
		printf("}\n");
		jm=n;
		point1++;
	}
	printf("\n");
	printf("--------------------------------------------\n\n");
	char donee[count];
	ptr = -1;
	for(k=0;k<count;k++){
		for(kay=0;kay<100;kay++){
			calc_follow[k][kay] = '!';
		}
	}
	point1 = 0;
	int land = 0;
	for(e=0; e < count; e++){
		ck=production[e][0];
		point2 = 0;
		flag = 0;
		for(kay = 0; kay <= ptr; kay++)
			if(ck == donee[kay])
				flag = 1;
		if (flag == 1)
			continue;
  		land += 1;
		follow(ck);
  		ptr+=1;
		donee[ptr] = ck;
  		printf("\033[1m Suivant(%c)\033[0m = { ",ck);
  		calc_follow[point1][point2++] = ck;
  		for(i=0+km;i<m;i++){
  			int j = 0,chk = 0;
  			for(j=0;j<point2;j++){
  				if (f[i] == calc_follow[point1][j]){
  					chk = 1;
  					break;
				}
			}
			if(chk == 0){
  		 		printf("%c, ",f[i]);
  				calc_follow[point1][point2++] = f[i];
  			}
  		}
  		printf(" }\n\n");
		km=m;
		point1++; 
	}
	char ter[MAX];
	for(k=0;k < MAX;k++){
		ter[k] = '!';
	}
	int ap,vp,sid = 0;
	for(k=0;k < count;k++){
		for(kay=0;kay < count;kay++){
			if(!isupper(production[k][kay]) && production[k][kay]!= '#' && production[k][kay] != '=' && production[k][kay] != '\0'){
				vp = 0;
				for(ap = 0;ap < sid; ap++){
					if(production[k][kay] == ter[ap]){
						vp = 1;
						break;
					}
				}
				if(vp == 0)
					ter[sid++] = production[k][kay];
			}
		}
	}
	ter[sid] = '$';
	sid++;
	printf("\n\t+===================================================================================================================+\n");	
	printf("\t|\t\t\t\t\t\t\033[1mTable LL(1)\033[0m  \t\t\t\t\t\t\t    |");
	printf("\n\t+=======+===========================================================================================================+\n");
	printf("\t|\t|\t");
	for(ap = 0;ap < sid; ap++){
		printf("\033[1m%c\033[0m\t\t",ter[ap]);
	}
	printf("\n\t--------+------------------------------------------------------------------------------------------------------------\n");
	char first_prod[count][sid];
	for(ap=0;ap<count;ap++){
		int destiny = 0;
		k = 2;
		int ct = 0;
		char tem[100];
		while(production[ap][k] != '\0'){
			if(!isupper(production[ap][k])){
				tem[ct++] = production[ap][k];
				tem[ct++] = '_';
				tem[ct++] = '\0';
				k++;
				break;
			}
			else{
				int zap=0;
				int tuna = 0;
				for(zap=0;zap<count;zap++){
					if(calc_first[zap][0] == production[ap][k]){
						for(tuna=1;tuna<100;tuna++){
							if(calc_first[zap][tuna] != '!'){
								tem[ct++] = calc_first[zap][tuna];
							}
							else
								break;
						}
					break;
					}
				}
				tem[ct++] = '_';
			}
			k++;
		}
		int zap = 0,tuna;		
		for(tuna = 0;tuna<ct;tuna++){
			if(tem[tuna] == '#'){
				zap = 1;
			}
			else if(tem[tuna] == '_'){
				if(zap == 1){
					zap = 0;
				}
				else
					break;
			}
			else{
				first_prod[ap][destiny++] = tem[tuna];
			}
		}
	}
	char table[land][sid+1];
	ptr = -1;
	for(ap = 0; ap < land ; ap++){
		for(kay = 0; kay < (sid + 1) ; kay++){
			table[ap][kay] = '!';
		}
	}
	for(ap = 0; ap < count ; ap++){
		ck = production[ap][0];
		flag = 0;
		for(kay = 0; kay <= ptr; kay++)
			if(ck == table[kay][0])
				flag = 1;
		if (flag == 1)
			continue;
		else{
			ptr = ptr + 1;
			table[ptr][0] = ck;
		}
	}
	for(ap = 0; ap < count ; ap++){
		int tuna = 0;
		while(first_prod[ap][tuna] != '\0'){
			int to,ni=0;
			for(to=0;to<sid;to++){
				if(first_prod[ap][tuna] == ter[to]){
					ni = 1;
				}
			}
			if(ni == 1){
				char xz = production[ap][0];
				int cz=0;
				while(table[cz][0] != xz){
					cz = cz + 1;
				}
				int vz=0;
				while(ter[vz] != first_prod[ap][tuna]){
					vz = vz + 1;
				}
				table[cz][vz+1] = (char)(ap + 65);
			}
			tuna++;
		}
	}
	for(k=0;k<sid;k++){
		for(kay=0;kay<100;kay++){
			if(calc_first[k][kay] == '!'){
				break;
			}
			else if(calc_first[k][kay] == '#'){
				int fz = 1;
				while(calc_follow[k][fz] != '!'){
					char xz = production[k][0];
					int cz=0;
					while(table[cz][0] != xz){
						cz = cz + 1;
					}
					int vz=0;
					while(ter[vz] != calc_follow[k][fz]){
						vz = vz + 1;
					}
					table[k][vz+1] = '#';
					fz++;	
				}
				break;
			}
		}
	}
	for(ap = 0; ap < land ; ap++){
		printf("\t   %c\t|\t",table[ap][0]);
		for(kay = 1; kay < (sid + 1) ; kay++){
			if(table[ap][kay] == '!')
				printf("\t\t");
			else if(table[ap][kay] == '#')
				printf("%c=#\t\t",table[ap][0]);
			else{
				printf("%s\t\t",production[table[ap][kay]-'A']);
			}
		}
		printf("\n");
		printf("\t--------+------------------------------------------------------------------------------------------------------------");
		printf("\n");
	}
	int j;
	printf("\n\nDonner un mot : ");
	char input[MAX];
	scanf("%s%c",input,&ch);
	printf("\n\t+=========================================================================+\n");
	printf("\t|\t\033[1mPile\033[0m\t\t\t\033[1mEntrée\033[0m\t\t\t\033[1mAction\033[0m\t\t  |");
	printf("\n\t+=========================================================================+\n");
	int i_ptr = 0,s_ptr = 1;
	char stack[MAX];
	stack[0] = '$';
	stack[1] = table[0][0];
	while(s_ptr != 0){
		printf("\t\t");
		int vamp = 0;
		for(vamp=0;vamp<=s_ptr;vamp++) // print stack values
			printf("%c",stack[vamp]);
		printf("\t\t\t");
		vamp = i_ptr;
		while(input[vamp] != '\0')
			printf("%c",input[vamp++]);
		printf("\t\t\t");
		char inp = input[i_ptr];
		char stk = stack[s_ptr--];
		if(!isupper(stk)){
			if(inp == stk){ // if input and stack head are same
				i_ptr++;
				printf("Dépilement\n");
			}
			else{
				printf("\n\t+=========================================================================+\n");
				printf("\t|\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\t\t\t|\n", input);
				printf("\t+=========================================================================+\n\n\n");
				exit(0);
			}
		}
		else if(inp != '\0'){ // if input is not empty
			for(i=0; i < sid; i++){
				if(ter[i] == inp)
					break;
			}
			if(i == sid){ // if input is not found in terminals
				printf("\n\t===========================================================================\n");
				printf("\t\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\n", input);
				printf("\t===========================================================================\n\n\n");
				exit(0);
			}
			char produ[MAX];
			for(j=0;j < land; j++){
				if(stk == table[j][0]){
					if (table[j][i+1] == '#'){
						printf("%c=#\n",table[j][0]);
						produ[0] = '#';
						produ[1] = '\0';
					}
					else if(table[j][i+1] != '!'){
						int mum = table[j][i+1] - 'A';
						strcpy(produ, production[mum]);
						printf("%s\n",produ);
					}
					else{
						printf("\n\t===========================================================================\n");
						printf("\t\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\n", input);
						printf("\t===========================================================================\n\n\n");
						exit(0);
					}
				}
			}
			int le = strlen(produ);
			le--;
			if(le == 0){
				printf("\t---------------------------------------------------------------------------\n");
				continue;
			}
			for(j=le;j>=2;j--)
				stack[++s_ptr] = produ[j];
		}else{
			char produ[MAX];
			for(j=0;j < count; j++){
				if(stk == production[j][0] && production[j][2] == '#'){
					printf("%c=#\n",production[j][0]);
					produ[0] = '#';
					produ[1] = '\0';
					break;
				}
			}
			if(j == count){
				printf("\n\t===========================================================================\n");
				printf("\t\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\n", input);
				printf("\t===========================================================================\n\n\n");
				exit(0);
			}
			int le = strlen(produ);
			le--;
			if(le == 0){
				printf("\t---------------------------------------------------------------------------\n");
				continue;
			}
			for(j=le;j>=2;j--)
				stack[++s_ptr] = produ[j];
		}
		printf("\t---------------------------------------------------------------------------\n");
	}
	if (input[i_ptr] == '\0'){
		printf("\t\t$");
		printf("\n\t===========================================================================\n");
		printf("\t\t\t\tLe mot \033[1m'%s'\033[0m est accepté !!\n", input);
		printf("\t===========================================================================\n\n\n");
	}
	else{
		printf("\n\t===========================================================================\n");
		printf("\t\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\n", input);
		printf("\t===========================================================================\n\n\n");

	}
}

void follow(char c){
	int i ,j;
	if(production[0][0]==c){
 		f[m++]='$';
 	}
	for(i = 0; i < count; i++){
		for(j = 2; j < strlen(production[i]); j++){
   			if(production[i][j]==c)
   			{
    			if(production[i][j+1]!='\0'){
					followFirst(production[i][j+1],i,(j+2));
 				}
    			if(production[i][j+1]=='\0'&&c!=production[i][0]){
     				follow(production[i][0]);
				}
   			}   
  		}
 	}
}

void findFirst(char c ,int q1 , int q2)
{
	int j;
	if(!(isupper(c))){
		first[n++]=c;
	}
	for(j=0;j<count;j++)
	{
		if(production[j][0]==c)
		{
			if(production[j][2]=='#'){
				if(production[q1][q2] == '\0')
					first[n++]='#';
				else if(production[q1][q2] != '\0' && (q1 != 0 || q2 != 0))
				{
					findFirst(production[q1][q2], q1, (q2+1));
				}
				else
					first[n++]='#';
			}
			else if(!isupper(production[j][2])){
				first[n++]=production[j][2];
			}
			else {
				findFirst(production[j][2], j, 3);
			}
		}
	}	
}

void followFirst(char c, int c1 , int c2){
    if(!(isupper(c)))
		f[m++]=c;
	else{
		int i=0,j=1;
		for(i=0;i<count;i++)
		{
			if(calc_first[i][0] == c)
				break;
		}
		while(calc_first[i][j] != '!')
		{
			if(calc_first[i][j] != '#'){
				f[m++] = calc_first[i][j];
			}
			else{
				if(production[c1][c2] == '\0'){
					follow(production[c1][0]);
				}
				else{
					followFirst(production[c1][c2],c1,c2+1);
				}
			}
			j++;
		}
	}
}


char* substring(char *destination, const char *source, int beg, int n){
    while (n > 0){
        *destination = *(source + beg);
        destination++;
        source++;
        n--;
    }
    *destination = '\0';
    return destination;
}

char** str_split(char* a_str, const char a_delim){
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    /* Count how many elements will be extracted. */
    while (*tmp){
        if (a_delim == *tmp){
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result){
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token){
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}

void str_append(char* s, char c){
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

int in_array(char *array, char c, int n){
	for(int i=0; i < n; i++){
		if(array[i] == c)
			return 1;
	}
	return 0;
}
