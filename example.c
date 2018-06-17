#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int
main()
{

  const char * filepath = "README.md";

  int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);

  if (fd == -1)
  {
      perror("Error opening file for writing");
      exit(EXIT_FAILURE);
  }

  return 0;
}
