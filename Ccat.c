/*
Steven Waterhouse
Ccat.c
Description: This c program is meant to mimic the linux cat command to allow
the command to be used regardless of OS.
Input: A file with lines of text and space delimited tokens. The options -n and -b
number the output and number the non blank lines of output respectively.
Output: The contents of the input file, and potential line numbers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, const char *argv[] )

{
  static FILE* file;
  //static int forks;
  static char mode;
  //The first three variables must be static, or else c will forget them after 
  //the if statements they are defined in.
  char line;

  if(argc==2) //if no options selected
  {
    file=fopen( argv[1], "r" );
    
    const char *option="-x";
    mode='x';
   
  }

  if(argc==3) //if option selected
  {
    
    file=fopen( argv[2], "r" );
    const char *option= argv[1];
    
    
    if (strcmp(option,"-n")!=0 && strcmp(option,"-b")!=0 )
    {
      printf("optional argument not recognized, must be -b or -n, exiting now \n");
      exit(0);
    }
    mode=argv[1][1]; //sets mode if there is an option
  }

  if (argc>3 || argc==1) //if the input makes no sense
  {
    printf("incorrect number of arguments, exiting now \n");
    exit(0);
  }
  
  
  //printf("%d\n", argc);
  //printf("%c\n",mode );
  int boolean=1;
  int counter=0;
  


    //the following is mostly to print numberes lines
   if (mode!='x')
    {
      
      while ((line=fgetc(file))!=EOF) //characters are fetched one by one, no wasting mem on string buffers
        { 
          if (line!='\n' && boolean==1) //new text for a line
            {
              counter++;
              printf("%d %s", counter,"   ");
            }
           
          
          if(!(boolean==1 && line=='\n')) //print the fetched character
            {
              printf("%c", line);
            
            }
          else if(mode=='b') //don't number the blank lines if mode is b
            {
              printf("\n"); 
            }
            else
              {
                counter++;
                printf("%d %s \n", counter,"   ");
              }
              //just checks to see if the last char was a new line
              //basically doing the same thing as comparing a last char
              //and making sure its not a newline
          if(line=='\n')
            {
              boolean=1;
            }
          else
            {
              boolean=0;
            }
          
             
        }
        
    }

    else //all that gets called with no option
    {
      while ((line =fgetc(file))!=EOF)
        { 
          printf("%c", line);    
        }

    }
    printf("\n");

 }