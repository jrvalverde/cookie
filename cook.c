/** 
 * @file cookie.c
 *
 * @brief A program to print cookies.
 *
 *  By:
 *	J. R. Valverde
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef vms
#  include <file.h>
#else
#  include <sys/file.h>
#endif
#include <math.h>
#include <ctype.h>
#ifdef vms
#ifndef GNU
#  include <unixio.h>
#endif
#  include <types.h>
#endif
#include <time.h>

#ifdef vms
    char default_bakery[] = "SYS$LIBRARY:COOKIE.FILE";
#   define LOGICAL_BAKERY	"COOKIES"
#else
    char default_bakery[] = "/usr/local/lib/cookie.file";
#   define LOGICAL_BAKERY	"cookies"
#endif

#if defined(GNU) || defined(ultrix)
#define FALSE 0
#define TRUE  1
#endif

/* MAGIC NUMBERS */

#define MAXLINE 	256
#define MAXRANDOM   4294967295

/* Forward */

FILE *open_cookie_file(int argc,char *argv[]);
long get_file_length(FILE *fptr);
void print_cookie(FILE *bakery, long length);
long fit_to_length(long rno, long length);

/* External */ 

extern void my_seed(unsigned long int s);
extern unsigned long int my_random(unsigned long int r);


main(argc, argv)
int argc;
char *argv[];
{
    static FILE *bakery;	/** The cookie database file */
    static char *auxname;
    static char done;
    static long length;
    static char line[MAXLINE];
    static int firstchar;

/*    if (isatty(stdout) != 1) exit(0);	/ * we won't be able to show */

    bakery = open_cookie_file(argc, argv);
    if (bakery == NULL)
	exit(0);

    length = get_file_length(bakery);
    if (length == 0l)
	exit(0);

    print_cookie(bakery, length);

    exit(0);
}

/**
 *	@fn FILE *open_cookie_file(int argc, char *argv[])
 *	@brief Open the cookie database
 *	@param int argc the count ouf arguments
 *	@param char *argv[] ans array of argument strings
 *	@return a pointer to the database file or NULL if failure.
 */
FILE *open_cookie_file(argc, argv)
int argc;
char *argv[];
{
    static char *auxname;
    static FILE *bakery;

    /* 1. Open specified file if arguments are available */
    if (argc > 1) {
	/* loop for all arguments: args are alternative files */
	while (--argc) {
	    if ((bakery = fopen(argv[argc], "r")) != NULL)
		return bakery;
	    else {
		if ((auxname = getenv(argv[argc])) != NULL)
		    if ((bakery = fopen(auxname, "r")) != NULL)
			return bakery;
	    }
	}
    }

    /* 2. If that failed, then try with default file name */
    if ((bakery = fopen(default_bakery, "r")) != NULL)
	return bakery;
    else {
	if ((auxname = getenv(LOGICAL_BAKERY)) != NULL)
	    if ((bakery = fopen(auxname, "r")) != NULL)
		return bakery;
    }

    /* 3. If this also failed, then forget about this */
#ifdef vms
    fprintf(stderr,
	"%%COOKIE-E-OPENIN, error opening cookie file as input\n");
#endif
    return NULL;
}

long get_file_length(fptr)
FILE *fptr;
{
    static long pos;

    fseek(fptr, 0L, 2);   /* go to end of file */
    if ((pos = ftell(fptr)) == EOF) {
	fprintf(stderr, "%%COOKIE-E-NOLEN, error getting cookie file length\n");
	return 0l;
    }
    return pos;
}

void print_cookie(bakery, length)
FILE *bakery;
long length;
{
    static unsigned long pos;
    static char line[MAXLINE];
    static int done;

    /* 5. Now get a random number between 0 and file length */
    my_seed(0L);
    pos = my_random(length);

    /* 6. Locate the first cookie */
    done = FALSE;
    fseek(bakery, pos, 0);  /* seek from beginning of file */
    fgets(line, MAXLINE, bakery); /* discard first line */
    for (;;) {
	if (fgets(line, MAXLINE, bakery) == NULL) {
	    if (done) {
		fprintf(stderr, 
	"%%COOKIE-E-NOCOOK, There are no cookies (sigh)\n");
		return;	    /* there are no cookies */
	    }
	    fseek(bakery, 0L, 0);
	    done = TRUE;	    /* we have passed EOF */
	    continue;
	}
	if (line[0] != ' ') break;	/* we have found a cookie */
    }

    /* 7. print the cookie */
    fprintf(stdout, "%s", line);
    while (fgets(line, MAXLINE, bakery) != NULL) {
	if (line[0] == '\0') {
	    fprintf(stdout, "\n");
	    continue;
	}
	if (line[0] != ' ') return;	          /* we are done */
	fprintf(stdout, "%s", &line[1]);
    }

    return;
}

long fit_to_length(rno, length)
long rno, length;
{
    static double drno, dlen, dno;

    drno = rno; dlen = length;
    dno = rno * dlen;
    dno /= MAXRANDOM;
    return floor(dno);
}
