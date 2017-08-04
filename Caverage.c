/* Hello World program */
/* Hello World program */

#include<stdio.h>

int main( int argc, const char *argv[] )
{
  FILE *file=fopen( argv[1], "r" );
   int i;
   int counter=0;
   float sum=0;

  int line=fscanf (file, "%d", &i);    
  while (line !=EOF)
    { counter++;
      sum+=i; 
      //printf ("%d ", i);
      line=fscanf (file, "%d", &i);      
    }
    fclose (file);        

    float average=sum/counter;
    printf("The average is %.3g\n", average);

}