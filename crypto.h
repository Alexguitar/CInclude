#ifndef _CYPHER_H_
#define _CYPHER_H_

int single_xor(const char *, char , char *, int);
int repeating_xor(const char *, unsigned char *, unsigned char *, int);
int score(const char *, int);

char attack_single_byte_xor(const char *, int);

#endif
