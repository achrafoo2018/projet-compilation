#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Retourne vrai si le character est un d�limteur
bool estUnDelimiteur(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}')
		return (true);
	return (false);
}

// Retourne vrai si le character est un op�rateur
bool estUnOperateur(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' ||
		ch == '=')
		return (true);
	return (false);
}

// Retourne vrai si le character est un character valide pour un identificateur
bool identificateurValide(char* str)
{
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
		str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		str[0] == '6' || str[0] == '7' || str[0] == '8' ||
		str[0] == '9' || estUnDelimiteur(str[0]) == true)
		return (false);
	return (true);
}

// Retourne vrai si le character est un mot-cl�
bool estMotCle(char* str)
{
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "do") ||
		!strcmp(str, "break") ||
		!strcmp(str, "continue") || !strcmp(str, "int")
		|| !strcmp(str, "double") || !strcmp(str, "float")
		|| !strcmp(str, "return") || !strcmp(str, "char")
		|| !strcmp(str, "sizeof") || !strcmp(str, "long")
		|| !strcmp(str, "short") || !strcmp(str, "typedef")
		|| !strcmp(str, "void") || !strcmp(str, "static"))

		return (true);
	return (false);
}

// Retourne vrai si le character est un entier
bool isInteger(char* str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// Retourne vrai si le character est un r�el
bool isRealNumber(char* str)
{
	int i, len = strlen(str);
	bool contientUnDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.' ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			contientUnDecimal = true;
	}
	return (contientUnDecimal);
}

// pour extratire une sous-chaine.
char* subString(char* str, int left, int right)
{
	int i;
	char* subStr = (char*)malloc(
				sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

// analyser l'input.
void analyseur(char* str)
{
	int left = 0, right = 0;
	int len = strlen(str);

	while (right <= len && left <= right) {
		if (estUnDelimiteur(str[right]) == false)
			right++;

		if (estUnDelimiteur(str[right]) == true && left == right) {
			if (estUnOperateur(str[right]) == true)
				printf("'%c' C'est un operateur\n", str[right]);

			right++;
			left = right;
		} else if (estUnDelimiteur(str[right]) == true && left != right
				|| (right == len && left != right)) {
			char* subStr = subString(str, left, right - 1);

			if (estMotCle(subStr) == true)
				printf("'%s' C'est un mot cle\n", subStr);

			else if (isInteger(subStr) == true)
				printf("'%s' C'est un entier\n", subStr);

			else if (isRealNumber(subStr) == true)
				printf("'%s' C'est un reel\n", subStr);

			else if (identificateurValide(subStr) == true
					&& estUnDelimiteur(str[right - 1]) == false)
				printf("'%s' C'est un identificateur valide\n", subStr);

			else if (identificateurValide(subStr) == false
					&& estUnDelimiteur(str[right - 1]) == false)
				printf("'%s' Ce n'est pas un identificateur valide\n", subStr);
			left = right;
		}
	}
	return;
}

int main(int argc, char **argv)
{
	// longueur maximale de str est 100
	while(true){
		char str [100];	
        printf("donner une instruction: ");
		fgets(str,100,stdin);
		str[strcspn(str, "\n")] = 0; // supprimer \n
		analyseur(str); //appel de l'analyseur
	}
	return (0);
}
