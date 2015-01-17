#ifndef _BITWISE_H_
#define _BITWISE_H_


// WARNING: do _NOT_ try to understand this
int hamming_weight(int i)
{
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int hamming_distance(const char *A, const char *B,unsigned int lenght)
{
	long distance = 0;
	while(lenght > 0) {
		distance += hamming_weight((*A)^(*B));
		A++;
		B++;
		lenght--;
	}
	return distance;
}

int single_hamming_distance(const char A, const char B)
{
	return hamming_weight(A^B);
}

double norm_hamming_distance(char *string, long lenght, long keysize)
{
	if(!keysize || !string || !lenght)
		return -1;
	int block_num = lenght / keysize;
	int hamming = 0;

	char *tmp1 = malloc(sizeof(char) * (keysize + 1));
	char *tmp2 = malloc(sizeof(char) * keysize);
	tmp1[keysize] = '\0';

	int i, j;
	/* compare every block to other block */
	for(i = 0; i < block_num; i++) {
		for(j = 0; j < keysize; j++) {
			tmp1[j] = string[j + i * keysize];
			tmp2[j] = string[(j + (i + 1) * keysize) % lenght];
		}
		hamming += hamming_distance(tmp1, tmp2, keysize);
	}
	return (double) hamming / (double) keysize / (double) block_num;
}

#endif
