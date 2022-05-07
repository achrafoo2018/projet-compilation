#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 100


// Functions to calculate Follow
void followfirst(char, int, int);
void follow(char c);

// Function to calculate First
void findfirst(char, int, int);
char* substring(char*, const char *, int, int);
char** str_split(char*, const char);
void str_append(char*, char);
int count, n = 0;

// Stores the final result
// of the First Sets
char calc_first[MAX][MAX];

// Stores the final result
// of the Follow Sets
char calc_follow[MAX][MAX];
int m = 0;

// Stores the production rules
char *productions[MAX];
char *production[MAX];
char f[MAX], first[MAX];
int k;
char ck;
int e;

int main(int argc, char **argv){
	int jm = 0;
	int km = 0;
	int i;
	char c;
	count = 8;
	// The Input grammar
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
	
	// Initializing the calc_first array
	for(k = 0; k < count; k++){
		for(kay = 0; kay < 100; kay++){
			calc_first[k][kay] = '!';
		}
	}
	int point1 = 0, point2, flag;
	
	for(k = 0; k < count; k++){
		c = production[k][0];
		point2 = 0;
		flag = 0;
		
		// Checking if First of c has
		// already been calculated
		for(kay = 0; kay <= ptr; kay++)
			if(c == done[kay])
				flag = 1;
				
		if (flag == 1)
			continue;
		
		// Function call
		findfirst(c, 0, 0);
		ptr += 1;
		
		// Adding c to the calculated list
		done[ptr] = c;
		calc_first[point1][point2++] = c;
		
		// Printing the First Sets of the grammar
		for(i = 0 + jm; i < n; i++) {
			int lark = 0, chk = 0;
			
			for(lark = 0; lark < point2; lark++) {
				if (first[i] == calc_first[point1][lark]){
					chk = 1;
					break;
				}
			}
			if(chk == 0){
				calc_first[point1][point2++] = first[i];
			}
		}
		jm = n;
		point1++;
	}
	char donee[count];
	ptr = -1;
	
	// Initializing the calc_follow array
	for(k = 0; k < count; k++){
		for(kay = 0; kay < 100; kay++){
			calc_follow[k][kay] = '!';
		}
	}
	point1 = 0;
	int land = 0;
	for(e = 0; e < count; e++){
		ck = production[e][0];
		point2 = 0;
		flag = 0;
		
		// Checking if Follow of ck
		// has already been calculated
		for(kay = 0; kay <= ptr; kay++)
			if(ck == donee[kay])
				flag = 1;
				
		if (flag == 1)
			continue;
		land += 1;
		
		// Function call
		follow(ck);
		ptr += 1;
		
		// Adding ck to the calculated list
		donee[ptr] = ck;
		printf("\nSuivant(%c) = { ", ck);
		calc_follow[point1][point2++] = ck;
		
		// Printing the Follow Sets of the grammar
		for(i = 0 + km; i < m; i++) {
			int lark = 0, chk = 0;
			for(lark = 0; lark < point2; lark++)
			{
				if (f[i] == calc_follow[point1][lark])
				{
					chk = 1;
					break;
				}
			}
			if(chk == 0){
				printf("%c", f[i]);
				if(i < n-1)
                    printf(", ");
                else
                    printf(" ");
				calc_follow[point1][point2++] = f[i];
			}
		}
		printf(" }\n");
		km = m;
		point1++;
	}
	printf("\n");
}


void follow(char c){
	int i, j;
	
	// Adding "$" to the follow
	// set of the start symbol
	if(production[0][0] == c){
		f[m++] = '$';
	}

	for(i = 0; i < count; i++){
		for(j = 2; j < strlen(production[i]); j++){
			if(production[i][j] == c){
				if(production[i][j+1] != '\0'){
					// Calculate the first of the next
					// Non-Terminal in the production
					followfirst(production[i][j+1], i, (j+2));
				}
				if(production[i][j+1]=='\0' && c!=production[i][0]){
					// Calculate the follow of the Non-Terminal
					// in the L.H.S. of the production
					follow(production[i][0]);
				}
			}
		}
	}
}

void findfirst(char c, int q1, int q2){
	int j;
	
	// The case where we
	// encounter a Terminal
	if(!(isupper(c))){
		first[n++] = c;
	}
	for(j = 0; j < count; j++)
	{
		if(production[j][0] == c)
		{
			if(production[j][2] == '#')
			{
				if(production[q1][q2] == '\0')
					first[n++] = '#';
				else if(production[q1][q2] != '\0'
						&& (q1 != 0 || q2 != 0))
				{
					// Recursion to calculate First of New
					// Non-Terminal we encounter after epsilon
					findfirst(production[q1][q2], q1, (q2+1));
				}
				else
					first[n++] = '#';
			}
			else if(!isupper(production[j][2]))
			{
				first[n++] = production[j][2];
			}
			else
			{
				// Recursion to calculate First of
				// New Non-Terminal we encounter
				// at the beginning
				findfirst(production[j][2], j, 3);
			}
		}
	}
}

void followfirst(char c, int c1, int c2){	
	// The case where we encounter
	// a Terminal
	if(!(isupper(c)))
		f[m++] = c;
	else
	{
		int i = 0, j = 1;
		for(i = 0; i < count; i++)
		{
			if(calc_first[i][0] == c)
				break;
		}
		
		//Including the First set of the
		// Non-Terminal in the Follow of
		// the original query
		while(calc_first[i][j] != '!')
		{
			if(calc_first[i][j] != '#')
			{
				f[m++] = calc_first[i][j];
			}
			else
			{
				if(production[c1][c2] == '\0')
				{
					// Case where we reach the
					// end of a production
					follow(production[c1][0]);
				}
				else
				{
					// Recursion to the next symbol
					// in case we encounter a "#"
					followfirst(production[c1][c2], c1, c2+1);
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
        if (a_delim == *tmp)
        {
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
