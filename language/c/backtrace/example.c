//  http://www.gnu.org/software/libc/manual/html_node/Backtraces.html
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

/* Obtain a backtrace and print it to @code{stdout}. */
void print_trace (void)
{
	void    * array[10];
	size_t  size;
	char    ** strings;
	size_t  i;

	size = backtrace(array, 10);
	strings = backtrace_symbols (array, size);
	if (NULL == strings)
	{
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	printf ("Obtained %zd stack frames.\n", size);

	for (i = 0; i < size; i++)
		printf ("%s\n", strings[i]);

	free (strings);
	strings = NULL;
}

/* A dummy function to make the backtrace more interesting. */
void dummy_function (void)
{
	print_trace();
}

int main (int argc, char *argv[])
{
	dummy_function();
	return 0;
}
