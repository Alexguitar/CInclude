#ifndef _CYPHER_H_
#define _CYPHER_H_

#include <ctype.h>
#include "altmath.h"
/* TODO: improve documentation header A.K.A. ↓
 * xor's every char of string with the value key and stores it in result. Result
 * is null-terminated, however a null character may appear earlier in result wh-
 * en string[i] and key match
 * Returns: lenght
 */
int single_xor(const char *str, char key, char *res, int lenght)
{
	long i = 0;
	while(lenght--) {
		res[i] = str[i] ^ key;
		i++;
	}
	res[i] = '\0';
	return i;
}



//TODO: write header:

int repeating_xor(const char *str, unsigned char *key, unsigned char *res, int lenght)
{
	long i = 0;
	int j = 0;
	while(lenght) {
		if(!key[j]) {
			j = 0;
		}
		res[i] = str[i] ^ key[j];
		i++;
		j++;
		lenght--;
	}
	res[i] = '\0';
	return 0;
}

int ENGLISH_FREQUENCY[] = {
// value is frequency in 10 000 characters
	/* A */	817,
	/* B */	149,
	/* C */	276,
	/* D */	425,
	/* E */	1270,
	/* F */	223,
	/* G */	202,
	/* H */	609,
	/* I */	697,
	/* J */	15,
	/* K */	77,
	/* L */	403,
	/* M */	241,
	/* N */	675,
	/* O */	751,
	/* P */	193,
	/* Q */	10,
	/* R */	599,
	/* S */	633,
	/* T */	906,
	/* U */	278,
	/* V */	98,
	/* W */	236,
	/* X */	15,
	/* Y */	197,
	/* Z */	7
};
const char etaoin[] = { 'e', 't', 'a', 'o', 'i', 'n',
			's', 'h', 'r', 'd', 'l', 'u',
			'c', 'm', 'w', 'f', 'g', 'y',
			'p', 'b', 'v', 'k', 'j', 'x',
			'q', 'z' };

int score(const char *string, int lenght)
{
	int stat[26];
	int spaces, punct, symbols, numbers;
	int garbage;

	/* initialize current statistic */
	memset(&stat, 0, 26*sizeof(int));
	spaces = punct = symbols = numbers = garbage = 0;

	int i;
	for(i = 0; i < lenght; i++) {
		/* letters */
		if('a' <= tolower(string[i]) && tolower(string[i]) <= 'z') {
			stat[tolower(string[i]) - 'a'] += 1;
		}
		/* count numbers */
		else if('0' <= string[i] && string[i] <= '9')
			continue;
		else switch(string[i]) {
			/* spaces */
			case ' ': case '\n': case '\t':
				spaces++;
				break;
			/* punctioation */
			case '.': case ',': case '\'': case '\"': case ':':
			case ';': case '`': case '!': case '?': case '&':
			case '(': case ')': case '[': case ']': case '{':
			case '}': case '-': case '|':
				punct++;
				break;
			/* symbols */
			case '@': case '#': case '$': case '%': case '^':
			case '*': case '+': case '<': case '>': case '~':
			case '_': case '=': case '/': case '\\':
				symbols++;
				break;
			/* garbage */
			default:
				garbage++;
				break;
		}
	}
	/* if tolarance% is garbage, return 0 */
	int tolerance = 10;
		if((100 * garbage * tolerance) / lenght >= 100)
			return 1;
	int letters = lenght - spaces - punct - symbols - numbers - garbage;
	/* calculate character frequency per 10 000 chars */
	/* based on the Bhattacharyya coefficient */
	for(i = 0; i < 26; i++) {
		stat[i] = (double) stat[i] / (double) letters * 10000.0;
//		printf("%c: %d\n", 'a' + i, stat[i] - ENGLISH_FREQUENCY[i]);
	}

	/* this stage awards up to 10 000 points */
	int score = 0;
	for(i = 0; i < 26; i++) {
		score += sqrt(ENGLISH_FREQUENCY[i] * stat[i]);
	}
	return score;

}


char attack_single_byte_xor(const char *string, int lenght)
{
	int i;
	unsigned char key = 0;
	unsigned char bestkey;
	int bestscore = 1;
	int tmpscore;
	char *tmp = malloc(sizeof(char) * lenght);

	do{
		single_xor(string, key, tmp, lenght);
		tmpscore = score(tmp, lenght);
//		printf("__%c:%d\n", key, tmpscore);
		if(tmpscore > bestscore) {
			bestscore = tmpscore;
			bestkey = key;
		}
		next:
		key++;
	} while(key != 0);
	printf("Key: %c score: %d\n", bestkey, bestscore);
	return bestkey;
}

#endif
