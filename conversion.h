#ifndef _CONVERSION_H_
#define _CONVERSION_H_

//TODO: write header

int bin_to_hex(const char *string, char *hexstr) {
	int i = 0;
		
	while(1) {
		/* terminate string */
		if(!string[i]) {
			hexstr[2*i] = '\0';
			return 2*i;
		}
		/* deal with first 4 bits */
		if(string[i] / 16 < 10) {
			/* 358u = binary(11110000) */
			hexstr[2*i] = '0' + string[i] / 16;
		} else {
			hexstr[2*i] = 'a' + string[i] / 16 - 10;
		}
		/* deal with last 4 bits */
		if((string[i] & 15u) < 10) {
			/* 15u = binary(00001111) */
			hexstr[2*i+1] = '0' + (string[i] & 15u);
		} else {
			hexstr[2*i+1] = 'a' + (string[i] & 15u) - 10;
		}
		i++;	
	}
}

/*
 * decrypt base 16 into base 2 (in char wide packs), returns when a character 
 * that is not 0-9 or a-f (case sensitive) is hit upon. Is null-terminated
 * Returns: lenght in chars, 0-indexed
 */
int hex_to_bin(const char *string, char *binary) {
	int i = 0;
	int j = 0;
	
	while(1) {
		if('0' <= string[i] && string[i] <= '9') {
			binary[j] = (string[i] - '0') << 4;	
		} else
		if('a' <= string[i] && string[i] <= 'f') {
			binary[j] = (string[i] - 'a' + 10) << 4;
		} else {
			binary[j] = '\0';
			return j;
		}
		i++;


		if('0' <= string[i] && string[i] <= '9') {
			binary[j] |= string[i] - '0';	
		} else
		if('a' <= string[i] && string[i] <= 'f') {
			binary[j] |= string[i] - 'a' + 10;
		} else {
			binary[j+1] = '\0';
			return j;
		}
		i++;
		j++;
	}
}

/* TODO: make it a sane function, terminate, return, etc.
 * decypts base 16 into base 64. assumes b64 is long enough 
 * assumes b16 is null-terminated, does not terminate b64
 * Returns: 0, regardless
 */

int hex_to_b64(const char *b16, char *b64) {
	long i, j, k;
	char pad = 0;
	char tmp[3];

	i = 0;
	j = 0;
	
	/* connect 3 4-bits into 2 6-bits for as long as posible */
	while(1) {
		/* decypt 3 hex chars and store them in tmp */
		for(k = 0; k < 3; k++) {
			if(!b16[i]) {
				goto padding;
			}

			if('0' <= b16[i] && b16[i] <= '9') {
				tmp[k] = b16[i] - '0';
				i++;
				continue;
			}
			tmp[k] = b16[i] - 'a' + 10;
			i++;
			
			
		}
		//TODO: document
		/* magical bonding process */
		b64[j] = tmp[0] << 2 | tmp[1] >> 2;
		j++;
		b64[j] = ((tmp[1] << 4) & ~192u) | tmp[2];
		j++;

	}

	padding:
	/* deal with leftover 4-bit groups */
	switch(k) {
		case 1:
			b64[j] = tmp[0];
			j++;
			
			pad = 1;
			break;
		case 2:
			b64[j] = tmp[0] << 2 | tmp[1] >> 2;
			j++;
			
			b64[j] = tmp[1] << 4 & ~192u;
			j++;
			
			pad = 2;
			break;
		default:
			break;
	}

	/* binary to base 64 */
	i = 0;
	while(i != j) {
		//TODO: replace numerical values with 'F', etc
		if(0 <= b64[i] && b64[i] <= 25) {
			b64[i] += 'A';
			i++;
			continue;
		}
		if(26 <= b64[i] && b64[i] <= 51) {
			b64[i] += 'a' - 26;
			i++;
			continue;
		}
		if(52 <= b64[i] && b64[i] <= 61) {
			b64[i] += '0' - 52;
			i++;
			continue;
		}
		if(b64[i] == 62) {
			b64[i] = '+';
			i++;
			continue;
		}
		b64[i] = '/';
		i++;
	}
	/* terminate string */
	b64[i] = '\0';

	return 0;
}

#endif
