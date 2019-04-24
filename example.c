/*
 * example.c
 *
 * 		Example test case for fault injection
 *		into open()
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void) {
	const char * filepath = "README.md";
	int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);

	if (fd < 0)
    	exit(EXIT_FAILURE);

	return 0;
}
