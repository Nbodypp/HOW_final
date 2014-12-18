#include <stdio.h>
#include <stdlib.h>
#include "intro.h"


void intromessage(char* name)
{
  printf("Usage: %s particle_file_name\n", name);
  printf("     particle_file_name:  name of the .ini file which defines particle parameters\n");
    exit(0);
}
