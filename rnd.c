/* Random number generator by the linear congruential method */
/*
 * random() and seed()
 *
 * random(int) returns an integers in the range 0 .. int-1
 * seed() sets the random number seed by using system time as seed
 *
 * Random has been taken from 'Algorithms in C', by Robert Sedgewick.
 *
 */

#include <time.h>

#ifndef NULL
#  define NULL 0L
#endif
#define m 100000000
#define m1 10000
#define b 31415821
static unsigned long int _arndno;

static unsigned long int rndmult(unsigned long int p, unsigned long int q)
{
    long int p1, p0, q1, q0;

    p1 = p / m1; p0 = p % m1;
    q1 = q / m1; q0 = q % m1;
    return (((p0 * q1 + p1 * q0) % m1) * m1 + p0 * q0) % m;
}

unsigned long int my_random(unsigned long int r)
{
    _arndno = (rndmult(_arndno, b) + 1) % m;
    return ((_arndno / m1) * r) / m1;
}

void my_seed(unsigned long int s)
{
    if (s == 0L)
	_arndno = time(NULL) /* % 231 (this % is so in DEC routines) */;
    else
	_arndno = s;
}


#ifdef DEBUG
main()
{
    int i;

    seed(0);

    printf("Random number generator test\n");
    for (i=0; i < 100; i++) {
	printf("%d\t", random(1573l));
    }
}
#endif
