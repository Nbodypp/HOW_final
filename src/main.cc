#include <stdlib.h>
#include <stdio.h>
//#include "integrator.h"
//#include "orbit_object.h"


void intro_message(char *name)
{
  printf("Usage: %s\n",name);
  printf("\n");
  exit(1);
}


int main(int argc, char *argv[])
{
  //Just a thought, maybe we can the first lines of the input file define the number of objects and such, and then the rest of the lines define the properties of the objects
  if(argc!=2)
    {
      intromessage(argv[0]);
    }
  const int n_objects = 2; //This will be accessed from command line arguments or the input file somehow

  /*Initialize the objects that will be orbiting*/

  for(int i=0; i<n_objects;i++)
    {
      //initialize an orbit_object class.
      //How are we going to do set up different instances for each object?  We have to figure out some way to define an arbitrary number of names for each instance.
    }

  
  Integrator *integrator_struct;

  integrator_struct=integrator_new(); //How to do this the OO way?

  for(int i=0;i<n_steps;i++)
    {
      check = integrator_step()
        if(check!=0)
          {
            printf("Failure on stepping for some reason.\n Now quitting...\n");
            exit(-1);
          }
      printf("The values\n");
    }

  integrator_free(integrator_struct);

}
