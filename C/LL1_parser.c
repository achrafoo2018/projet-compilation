#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 100

int in_array(char *, char, int);

char *substring(char *, const char *, int, int);
char **str_split(char *, const char);
void str_append(char *, char);
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

void followFirst(char, int, int);
void findFirst(char, int, int);
void follow(char c);

int count, n = 0;
char calc_first[MAX][MAX];
char calc_follow[MAX][MAX];
int m = 0;
char first[MAX];
char *productions[MAX];
char *production[MAX];
char f[MAX];
int k;
char nt;
int e;

int main(int argc, char **argv)
{
	int jm = 0;
	int km = 0;
	int i;
	char c, ch;
	count = 8;

	printf("Donner le nombre de production : ");
	scanf("%d", &count);
	printf("Donner la grammaire comme suit (epsilon = #) : NT->..|... :\n");
	int num = 0;
	for (int i = 0; i < count; i++)
	{
		productions[i] = (char*) malloc(sizeof(char) *MAX);
		scanf("%s", productions[i]);
		char non_terminal = productions[i][0];
		if(!isupper(non_terminal) || productions[i][1] != '-' || productions[i][2] != '>' ){
			printf("Grammaire '\033[1m%s\033[0m' est invalide !!\n", productions[i]);
			return 0;
		}
		char *tmp = (char *) malloc(sizeof(char) *MAX);
		strcpy(tmp, productions[i]);
		substring(tmp, productions[i], 3, strlen(productions[i]) - 3);
		char **tokens = str_split(tmp, '|');
		if (tokens)
		{
			for (int t = 0; *(tokens + t); t++)
			{
				char *tmp = (char*) malloc(sizeof(char) *MAX);
				tmp[0] = non_terminal;
				str_append(tmp, '=');
				strcat(tmp, *(tokens + t));
				production[num] = (char*) malloc(sizeof(char) *MAX);
				strcpy(production[num++], tmp);
				if(non_terminal == tmp[2]){
					printf("Grammaire '\033[1m%s\033[0m' est récursive a gauche!!\n", productions[i]);
					return 0;
				}

			}
		}
	}
	count = num;
	char done[count];
	int ptr = -1;
	for (k = 0; k < count; k++)
	{
		for (int j = 0; j < 100; j++)
		{
			calc_first[k][j] = '!';
		}
	}
	int ptr1 = 0, ptr2, flag;
	for (k = 0; k < count; k++)
	{
		c = production[k][0];
		ptr2 = 0;
		flag = 0;
		for (int j = 0; j <= ptr; j++)
			if (c == done[j])
				flag = 1;
		if (flag == 1)
			continue;
		findFirst(c, 0, 0);
		ptr += 1;
		done[ptr] = c;
		printf("\n\033[1m Premier(%c)\033[0m= { ", c);
		calc_first[ptr1][ptr2++] = c;
		for (i = 0 + jm; i < n; i++)
		{
			int j = 0, chk = 0;
			for (j = 0; j < ptr2; j++)
			{
				if (first[i] == calc_first[ptr1][j])
				{
					chk = 1;
					break;
				}
			}
			if (chk == 0)
			{
				printf("%c, ", first[i]);
				calc_first[ptr1][ptr2++] = first[i];
			}
		}
		printf("}\n");
		jm = n;
		ptr1++;
	}
	printf("\n");
	printf("--------------------------------------------\n\n");
	char donee[count];
	ptr = -1;
	for (k = 0; k < count; k++)
	{
		for (int j = 0; j < 100; j++)
		{
			calc_follow[k][j] = '!';
		}
	}
	ptr1 = 0;
	int nb_non_terminals = 0;
	for (e = 0; e < count; e++)
	{
		nt = production[e][0];
		ptr2 = 0;
		flag = 0;
		for (int j = 0; j <= ptr; j++)
			if (nt == donee[j])
				flag = 1;
		if (flag == 1)
			continue;
		nb_non_terminals += 1;
		follow(nt);
		ptr += 1;
		donee[ptr] = nt;
		printf("\033[1m Suivant(%c)\033[0m = { ", nt);
		calc_follow[ptr1][ptr2++] = nt;
		for (i = 0 + km; i < m; i++)
		{
			int j = 0, chk = 0;
			for (j = 0; j < ptr2; j++)
			{
				if (f[i] == calc_follow[ptr1][j])
				{
					chk = 1;
					break;
				}
			}
			if (chk == 0)
			{
				printf("%c, ", f[i]);
				calc_follow[ptr1][ptr2++] = f[i];
			}
		}
		printf(" }\n\n");
		km = m;
		ptr1++;
	}
	char terminals[MAX];
	for (k = 0; k < MAX; k++)
	{
		// initialize terminal array
		terminals[k] = '!';
	}
	int nb_terminals = 0;
	for (k = 0; k < count; k++)
	{
		for (int kk = 0; kk < strlen(production[k]); kk++)
		{
			if (!isupper(production[k][kk]) && production[k][kk] != '#' &&
				 production[k][kk] != '=' && production[k][kk] != '\0')
			{
				flag = 0;
				for (int pp = 0; pp < nb_terminals; pp++)
				{
					if (production[k][kk] == terminals[pp]){ // check if terminal already exists
						flag = 1;
						break;
					}
				}
				if (!flag)	// if not add it to the terminal array
					terminals[nb_terminals++] = production[k][kk];
			}
		}
	}
	terminals[nb_terminals++] = '$';
	printf("\n\t+===================================================================================================================+\n");
	printf("\t|\t\t\t\t\t\t\033[1mTable LL(1)\033[0m  \t\t\t\t\t\t\t    |");
	printf("\n\t+===================================================================================================================+\n");
	printf("\t\t|\t");
	for (k = 0; k < nb_terminals; k++)
	{
		printf("\033[1m%c\033[0m\t\t", terminals[k]);
	}
	printf("\n\t--------+------------------------------------------------------------------------------------------------------------\n");
	char first_prod[count][nb_terminals];
	for (int j = 0; j < count; j++)
	{
		int destiny = 0;
		k = 2;
		int ct = 0;
		char tem[100];
		while (production[j][k] != '\0')
		{
			if (!isupper(production[j][k]))
			{
				tem[ct++] = production[j][k];
				tem[ct++] = '_';
				tem[ct++] = '\0';
				k++;
				break;
			}
			else
			{
				int kk = 0;
				int pp = 0;
				for (kk = 0; kk < count; kk++)
				{
					if (calc_first[kk][0] == production[j][k])
					{
						for (pp = 1; pp < 100; pp++)
						{
							if (calc_first[kk][pp] != '!')
								tem[ct++] = calc_first[kk][pp];
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
		int kk = 0, pp;
		for (pp = 0; pp < ct; pp++)
		{
			if (tem[pp] == '#')
				kk = 1;
			else if (tem[pp] == '_')
			{
				if (kk == 1)
					kk = 0;
				else
					break;
			}
			else
				first_prod[j][destiny++] = tem[pp];
		}
	}
	char table[nb_non_terminals][nb_terminals + 1];
	ptr = -1;
	for (k = 0; k < nb_non_terminals; k++)
	{
		for (int j = 0; j < (nb_terminals + 1); j++)
		{
			table[k][j] = '!';
		}
	}
	for (k = 0; k < count; k++)
	{
		nt = production[k][0];
		flag = 0;
		for (int j = 0; j <= ptr; j++)
			if (nt == table[j][0])
				flag = 1;
		if (flag == 1)
			continue;
		else
		{
			ptr = ptr + 1;
			table[ptr][0] = nt;
		}
	}
	for (k = 0; k < count; k++)
	{
		int pp = 0;
		while (first_prod[k][pp] != '\0')
		{
			int to, ni = 0;
			for (to = 0; to < nb_terminals; to++)
			{
				if (first_prod[k][pp] == terminals[to])
				{
					ni = 1;
				}
			}
			if (ni == 1)
			{
				char xz = production[k][0];
				int cz = 0;
				while (table[cz][0] != xz)
				{
					cz = cz + 1;
				}
				int vz = 0;
				while (terminals[vz] != first_prod[k][pp])
				{
					vz = vz + 1;
				}
				table[cz][vz + 1] = (char)(k + 65);
			}
			pp++;
		}
	}
	for (k = 0; k < nb_terminals; k++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (calc_first[k][j] == '!')
			{
				break;
			}
			else if (calc_first[k][j] == '#')
			{
				int fz = 1;
				while (calc_follow[k][fz] != '!')
				{
					char xz = production[k][0];
					int cz = 0;
					while (table[cz][0] != xz)
					{
						cz = cz + 1;
					}
					int vz = 0;
					while (terminals[vz] != calc_follow[k][fz])
					{
						vz = vz + 1;
					}
					table[k][vz + 1] = '#';
					fz++;
				}
				break;
			}
		}
	}
	for (k = 0; k < nb_non_terminals; k++)
	{
		printf("\t   %c\t|\t", table[k][0]);
		for (int kk = 1; kk < (nb_terminals + 1); kk++)
		{
			if (table[k][kk] == '!')
				printf("\t\t");
			else if (table[k][kk] == '#')
				printf("%c->#\t\t", table[k][0]);
			else{
				char nt = production[table[k][kk] - 65][0];
				char *tmp = (char *)malloc(sizeof(char) * MAX);
				substring(tmp, production[table[k][kk] - 65], 2, strlen(production[table[k][kk] - 65]) - 1);
				printf("%c->%s\t\t",nt , tmp);
			}
		}
		printf("\n");
		printf("\t--------+------------------------------------------------------------------------------------------------------------");
		printf("\n");
	}
	int j;
	printf("\n\nDonner un mot : ");
	char input[MAX];
	scanf("%s%c", input, &ch);
	printf("\n\t+=========================================================================+\n");
	printf("\t|\t\033[1mPile\033[0m\t\t\t\033[1mEntrée\033[0m\t\t\t\033[1mAction\033[0m\t\t  |");
	printf("\n\t+=========================================================================+\n");
	int i_ptr = 0, s_ptr = 1;
	char stack[MAX];
	stack[0] = '$';
	stack[1] = table[0][0];
	while (s_ptr != 0)
	{
		printf("\t\t");
		int sp = 0;
		for (sp = 0; sp <= s_ptr; sp++)	// print stack values
			printf("%c", stack[sp]);
		printf("\t\t\t");
		sp = i_ptr;
		while (input[sp] != '\0')
			printf("%c", input[sp++]);
		printf("\t\t\t");
		char inp = input[i_ptr];
		char stk = stack[s_ptr--];
		if (!isupper(stk))
		{
			if (inp == stk)
			{
				// if input and stack head are same
				i_ptr++;
				printf("Dépilement\n");
			}
			else
			{
				printf("\n\t+=========================================================================+\n");
				printf("\t|\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\t\t\t|\n", input);
				printf("\t+=========================================================================+\n\n\n");
				exit(0);
			}
		}
		else if (inp != '\0')
		{
			// if input is not empty
			for (i = 0; i < nb_terminals; i++)
			{
				if (terminals[i] == inp)
					break;
			}
			if (i == nb_terminals)
			{
				// if input is not found in terminals
				printf("\n\t===========================================================================\n");
				printf("\t\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\n", input);
				printf("\t===========================================================================\n\n\n");
				exit(0);
			}
			char produ[MAX];
			for (j = 0; j < nb_non_terminals; j++)
			{
				if (stk == table[j][0])
				{
					if (table[j][i + 1] == '#')
					{
						printf("%c->#\n", table[j][0]);
						produ[0] = '#';
						produ[1] = '\0';
					}
					else if (table[j][i + 1] != '!')
					{
						int mum = table[j][i + 1] - 'A';
						strcpy(produ, production[mum]);
						char *tmp = (char *)malloc(sizeof(char) * MAX);
						substring(tmp, produ, 2, strlen(produ) - 1);
						printf("%c->%s\n", produ[0], tmp);
					}
					else
					{
						printf("\n\t===========================================================================\n");
						printf("\t\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\n", input);
						printf("\t===========================================================================\n\n\n");
						exit(0);
					}
				}
			}
			int le = strlen(produ);
			le--;
			if (le == 0)
			{
				printf("\t---------------------------------------------------------------------------\n");
				continue;
			}
			for (j = le; j >= 2; j--)
				stack[++s_ptr] = produ[j];
		}
		else
		{
			char produ[MAX];
			for (j = 0; j < count; j++)
			{
				if (stk == production[j][0] && production[j][2] == '#')
				{
					printf("%c->#\n", production[j][0]);
					produ[0] = '#';
					produ[1] = '\0';
					break;
				}
			}
			if (j == count)
			{
				printf("\n\t===========================================================================\n");
				printf("\t\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\n", input);
				printf("\t===========================================================================\n\n\n");
				exit(0);
			}
			int le = strlen(produ);
			le--;
			if (le == 0)
			{
				printf("\t---------------------------------------------------------------------------\n");
				continue;
			}
			for (j = le; j >= 2; j--)
				stack[++s_ptr] = produ[j];
		}
		printf("\t---------------------------------------------------------------------------\n");
	}
	if (input[i_ptr] == '\0')
	{
		printf("\t\t$");
		printf("\n\t===========================================================================\n");
		printf("\t\t\t\tLe mot \033[1m'%s'\033[0m est accepté !!\n", input);
		printf("\t===========================================================================\n\n\n");
	}
	else
	{
		printf("\n\t===========================================================================\n");
		printf("\t\t\t\tLe mot \033[1m'%s'\033[0m n'est pas accepté !!\n", input);
		printf("\t===========================================================================\n\n\n");
	}
}

void follow(char c)
{
	int i, j;
	if (production[0][0] == c)
	{
		f[m++] = '$';
	}
	for (i = 0; i < count; i++)
	{
		for (j = 2; j < strlen(production[i]); j++)
		{
			if (production[i][j] == c)
			{
				if (production[i][j + 1] != '\0')
				{
					followFirst(production[i][j + 1], i, (j + 2));
				}
				if (production[i][j + 1] == '\0' && c != production[i][0])
				{
					follow(production[i][0]);
				}
			}
		}
	}
}


void findFirst(char c, int q1, int q2)
{
	int j;
	if (!(isupper(c)))
	{
		first[n++] = c;
	}
	for (j = 0; j < count; j++)
	{
		if (production[j][0] == c)
		{
			if (production[j][2] == '#')
			{
				if (production[q1][q2] == '\0')
					first[n++] = '#';
				else if (production[q1][q2] != '\0' && (q1 != 0 || q2 != 0))
				{
					findFirst(production[q1][q2], q1, (q2 + 1));
				}
				else
					first[n++] = '#';
			}
			else if (!isupper(production[j][2]))
			{
				first[n++] = production[j][2];
			}
			else
			{
				findFirst(production[j][2], j, 3);
			}
		}
	}
}


void followFirst(char c, int c1, int c2)
{
	if (!(isupper(c)))
		f[m++] = c;
	else
	{
		int i = 0, j = 1;
		for (i = 0; i < count; i++)
		{
			if (calc_first[i][0] == c)
				break;
		}
		while (calc_first[i][j] != '!')
		{
			if (calc_first[i][j] != '#')
			{
				f[m++] = calc_first[i][j];
			}
			else
			{
				if (production[c1][c2] == '\0')
				{
					follow(production[c1][0]);
				}
				else
				{
					followFirst(production[c1][c2], c1, c2 + 1);
				}
			}
			j++;
		}
	}
}


char *substring(char *destination, const char *source, int beg, int n)
{
	while (n > 0)
	{
		*destination = *(source + beg);
		destination++;
		source++;
		n--;
	}
	*destination = '\0';
	return destination;
}


char **str_split(char *a_str, const char a_delim)
{
	char **result = 0;
	size_t count = 0;
	char *tmp = a_str;
	char *last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;
	/*Count how many elements will be extracted. */
	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/*Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/*Add space for terminating null string so caller
	   knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) *count);

	if (result)
	{
		size_t idx = 0;
		char *token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}
	return result;
}


void str_append(char *s, char c)
{
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
}


int in_array(char *array, char c, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (array[i] == c)
			return 1;
	}
	return 0;
}

