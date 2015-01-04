#ifndef _MATH_H_
#define _MATH_H_
#include <math.h>

int is_prime(unsigned int number)
{
	unsigned int i;
	if(number <= 1)
		return 0; // 1, 0 are not prime
	if(number < 4)
		return 1; // 2, 3 are prime
	int r = floor(sqrt(number));
	if(number % 2 == 0)
		return 0;
	if(number < 9)
		return 1; // 4, 6, 8 are exluded
	if(number % 3 == 0)
		return 0;
	for(i = 5; i <= r; i += 6) {
		if(number % i == 0)
			return 0;
		if(number % (i+2) == 0)
			return 0;
	}
	return 1;
}


//TODO: veryify
int divisors(unsigned int number)
{
	if(number < 2)
		return 1;
	if(number < 4)
		return 2;

	unsigned int i, r, count;
	count = 0;
	r = floor(sqrt(number));
	for(i = 1; i <= r; i++)	{
		if(number % i == 0)
			count++;
	}
	if(r*r == number) 
		return 2*count -1;
	return 2*count;

}

#endif
