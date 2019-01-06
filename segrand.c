#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <stddef.h>

/* for C89 */
#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)(-1))
#endif

void seg_catch(int);
static void overwrite_memory(void);

static jmp_buf jmp;
volatile static size_t i;

int main(void)
{

	signal(SIGSEGV, seg_catch);

	switch (setjmp(jmp))
	{
		case 0:
			overwrite_memory();
			break;
		default:
			break;
	}

	printf("%zu\n", i);
}

/* using volatile so that the optimizer won't
 * remove this array entirely */
static volatile char victim[2];

static void overwrite_memory(void)
{
	for (i = 0; i < SIZE_MAX-1; i++)
		victim[i] = '!';
}

void seg_catch(int sig)
{
	(void)sig;

	longjmp(jmp, 1);

	return;
}
