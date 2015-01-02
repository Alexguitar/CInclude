#ifndef _ALTMATH_H_
#define _ALTMATH_H_

/* 
 * Simple alternative to double pow() that works on integers. Does not allow
 * negative exponents
 * Returns: base^exp
 */

int int_pow(int x, unsigned int pow)
{
    int ret = 1;
    while ( pow != 0 )
    {
        if ( (pow & 1) == 1 )
            ret *= x;
        x *= x;
        pow >>= 1;
    }
    return ret;
}

#endif
