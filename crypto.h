#ifndef _CYPHER_H_
#define _CYPHER_H_

/* TODO: improve documentation header A.K.A. ↓
 * xor's every char of string with the value key and stores it in result. Result
 * is null-terminated, however a null character may appear earlier in result wh-
 * en string[i] and key match
 * Returns: 0, regardless
 */

int single_xor(const char *str, unsigned char key, unsigned char *res) {
	long i = 0;
	while(str[i]) {
		res[i] = str[i] ^ key;
		i++;
	}
	res[i] = '\0';
	return 0;
}

//TODO: write header:

int repeating_xor(const char *str, unsigned char *key, unsigned char *res) {
	long i = 0;
	int j = 0;
	while(str[i]) {
		if(!key[j]) {
			j = 0;
		}
		res[i] = str[i] ^ key[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return 0;
}

/* TODO: improve reliability, strictness, etc
 * scores the string based on character frequency.
 * Max score: ~845. Min score: -10 000 //TODO: update score list
 * Returns: score
 * */

int score(const char *string) {
	long i, j, lenght;
	int score = 0; 
	int higher = 0;
	long nonlatin = 0;
	long spaces = 0;
	const char reference[] = "etaoinshrdlu";
	long tmp['z' - 'a' + 1] = { 0 };
	char occurance[12] = { 0 };
	
	for(i = 0; string[i]; i++) {
		/* count occurance of A-Z characters (case independent) */
		if('a' <= tolower(string[i]) && tolower(string[i]) <= 'z') {
			tmp[tolower(string[i]) - 'a'] += 1;
		}
		/* count occurance of spaces */
		else if(string[i] == ' ' && string[i-1] != ' ') {
			spaces++;
		}
		/* count occurance of special characters */ //TODO: improve the list
		else if(string[i] != '\'' && ('a' > tolower(string[i]) || tolower(string[i] > 'z'))) {
			nonlatin++;
		}
	}

	/* use the values from first A-Z scan and fit them to match reference[]*/
	//TODO: this loop is obsolete, implement it elsewhere without the use of tmp
	for(j = 0; j < 12; j++) {
		occurance[j] = tmp[reference[j] - 'a'];
	}

	lenght = i;
	if(lenght == 0) {
		return 0;
	} 
	for(i = 0; i < 12; i++) {
		/* find the position of occurance[i] in an ascending list */
		for(j = 0; j < 12; j++) {
			if(occurance[i] > occurance[j])
				higher++;
		}
		/* compare the position of occurance[i] to the reference; margin of error = 2*/
		if(higher >= 12-2-i) { //TODO: verify
			if(higher-i+1 > 0) {
				score += int_pow(higher, 2);
			}
		}
			
		higher = 0;
	}
	
	if(spaces) {
		if(abs(lenght/spaces-5) < 6) //TODO: there is probably something wrong here
			score += int_pow(3*(5-abs(lenght/spaces-5)), 2);
	}
	return score - int_pow(100*nonlatin/(lenght), 2);
}

#endif
