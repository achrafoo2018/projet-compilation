#include<stdio.h>  
#include<string.h>  
#include <stdlib.h>
#include <assert.h>
#include <regex.h>


#define MAX 100

char* substring(char*, const char *, int, int);
char** str_split(char*, const char);

int main () {  
    char non_terminal;  
    int num;  
    char* production[MAX];  
    printf("Donner le nombre de production : ");  
    scanf("%d",&num);  
    printf("Donner la grammaire comme suit : NT->..|... :\n");

    for(int i=0;i<num;i++){  
        production[i] = (char*)malloc(sizeof(char) * MAX);
        scanf("%s", production[i]);  
    }

    for(int i=0;i<num;i++){  
        printf("\nGrammaire : %s",production[i]);  
        non_terminal = production[i][0];  
        substring(production[i], production[i], 3, strlen(production[i])-3);
        char** tokens = str_split(production[i], '|');
        int isLeftRecursive = 0; 
        char* betas[MAX];
        char* alphas[MAX];
        int k = 0, j = 0, n = 0, m = 0;
        if(tokens) {
            for(int t=0; *(tokens+t); t++){
                if((*(tokens + t))[0] == non_terminal){
                    isLeftRecursive = 1;
                    n++;
                    alphas[j++] = strdup(++(*(tokens + t)));

                }else{
                    m++;
                    betas[k++] = strdup(*(tokens + t));
                }
            }
        }
        if(isLeftRecursive) {  // there is left recursivity
            printf(" est recursive a gauche.\n");  
            if(m == 0){ // no Beta found 
                printf("Grammaire ne peut pas être réduit!\n");
                continue;
            }
            printf("%c->", non_terminal);
            for(int j=0; j < m; j++){
                printf("%s%c\'", betas[j], non_terminal);
                if(j < m-1)
                    printf("|");
            }
            printf("\n");
            printf("%c\'->", non_terminal);
            for(int j=0; j < n; j++){
                printf("%s%c\'|", alphas[j], non_terminal);
            }
            printf("ε\n");
        }  
        else  
            printf(" n'est pas recursive a gauche\n");  
    }  
    return 0;
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


