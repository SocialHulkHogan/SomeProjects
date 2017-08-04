/*
Steven Waterhouse
Csort.c
Description: This c program is meant to mimic the linux sort command to allow
the command to be used regardless of OS.
Input: A file of numbers or strings to be sorted. The flexibility of input
is actually superior to the linux sort command, as that command requires the strings to be line seperated.
For this program, the strings can be line or space seperated. The options are
default, reversed, numbers, reversed numbers, and no consecutive repeats given by
no option inputeed, -r, -n, -nr and -u respectively.
Output: Output to the console a line by line sorted list of the tokens 
from the input file, sorted according to the options used.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int cstring_cmp(const void *a, const void *b)
{
   const char *ia = a;
   const char *ib = b;
   return strcasecmp(ia, ib);
}

int floatcomp(const void* elem1, const void* elem2)
{
    if(*(const float*)elem1 < *(const float*)elem2)
        return -1;
    return *(const float*)elem1 > *(const float*)elem2;
}

int main( int argc, const char *argv[] )
{
 
  int words=0;
  char lastChar=' ';
  int curword=0;
  int maxword=0;
  int inword=0; 
  char c; 
  int i=0,j=0;
  float tfloat;
  static FILE* file;  
  static char mode;                    
  //The first three variables must be static, or else c will forget them after 
  //the if statements they are defined in.
  //The first thing the code does is figure out which option and what file
  //the user is using  

  if(argc==2)
  {
    file=fopen( argv[1], "r" );
    
    const char *option="-x";
    mode='x';
   
  }

  if(argc==3)
  {
    
    file=fopen( argv[2], "r" );
    const char *option= argv[1];
    if (strcmp(option,"-n")!=0 && strcmp(option,"-r")!=0 && strcmp(option,"-nr")!=0 && strcmp(option,"-u")!=0)
    {
      printf("optional argument not recognized, must be -b or -n, exiting now \n");
      exit(0);
    }
    if (strcmp(option,"-nr")==0)
    {
      mode='g';
    }
    else
    {
      mode=argv[1][1];
    }
    
  }

  if (argc>3 || argc==1)
  {
    printf("incorrect number of arguments, exiting now \n");
    exit(0);
  }


//buffer size getter, it goes through and finds the longest word
//and the number of words

while ((c =fgetc(file))!=EOF)
    { 
         if (inword==1 )
            {
              curword++;
              if (curword>maxword)
                {
                  maxword=curword;
                }
            }
         if (c=='\n' || c==' ')
          {
            inword=0;
            curword=0;
          }
         
         if (lastChar==' ' || lastChar=='\n')
          {
            
            if (c!=' ' && c !='\n')
              {
                words++;
                inword=1;
              }
           
          }
         lastChar=c;
    }


   // The following close and re-open is to reset the file index
    fclose (file); 

    if(argc==2)
      {
        file=fopen( argv[1], "r" );
      }
    else
      {
        file=fopen( argv[2], "r" );
      }

    
    //declaring new variables based on the now available
    //words and maxword. Words represents the number of words
    //in the file and maxword is the smallest buffer size that will fit all
    //the words
    
    char array2[words][maxword];
    char temp[maxword];
    memset(&array2[0], 0, sizeof(array2));
    memset(&temp[0], 0, maxword);
    int start=0;
    int end =words-1;
    

    //puts all the words from the file into array2
    while ((c =fgetc(file))!=EOF)
    {
        
        if (c!='\n' && c!=' ') //if in a word
          {
            array2[i][j]=c;
            j++;

          }

        if(c=='\n' || c==' ') //if a space is found
        {
          
            j=0;
            if (lastChar!='\n' && lastChar!=' ') //check for consecutive spaces
            {
              i++; //start storing the next word   
            }
        }

        lastChar=c;
  
    }

    fclose(file);

// if the file isn't a number option, sort by strings
if(mode=='x' || mode=='r' || mode=='u')
  {
    
    qsort(array2, words, maxword, cstring_cmp);
  }
    

// if mode is r, reverse array2
if(mode=='r') 
  {
    while(start<end)
    {
      for(i=0;i<maxword;i++)
      {
        temp[i]=array2[start][i];
        array2[start][i]=array2[end][i];
        array2[end][i]=temp[i];
      }
      start++;
      end--;
    }
  }

//if the mode should normally print array 2, then it does
  if(mode!='g' && mode!='n' && mode!='u')
    {
      for(i=0;i<words;i++)
        {
          for(j=0;j<maxword;j++)
            {
              printf("%c", array2[i][j]);
            }
      printf("\n");
        }
    }
// if the mode is a numeric mode, populate a float array with the
//tokens from array2

  if (mode=='n' || mode=='g')
    {
      float array1[words];
      float newnum;
      char src[maxword]; //temp buffer for easy conversion
      //strcpy(src,  "");
      memset(&src[0], 0, maxword);

      for(i=0;i<words;i++)
        {
          strcat(src, &array2[i][0]);
          
          if (strlen(src)>maxword) //sometimes an extra digit is tacked on to the biggest number
            //This revereses that if it happens
          {
              src[strlen(src)-1] = 0; 
          }
          newnum=atof(src);
          newnum= roundf(newnum * 100.0)/100.0; //go to two decimal places
          array1[i]=newnum;
         // strcpy(src,  ""); //clear temp buffer
          memset(&src[0], 0, maxword);
        }
    

    qsort(&array1[0], words, sizeof(float), floatcomp); //sort by numeric value

    //if the option is -nr, reverse the sorted array
    if(mode=='g') 
      {
        while(start<end)
          {
            tfloat = array1[start];   
            array1[start] = array1[end];
            array1[end] = tfloat;
            start++;
            end--;
          }
      } 
    //print all the floats
    for(i=0;i<words;i++)
    {
      printf("%g\n", array1[i]);
    }

  }
//end of numeric option code

//The following code describes the u case
if (mode=='u')
  {
    char buff[maxword];
    memset(&buff[0], 0, maxword); 
    char lastword[maxword];
    for(i=0;i<words;i++)
      { 
        strcat(buff, &array2[i][0]); //give buff the word
     
        if (strcmp(buff,lastword)!=0) //print if not a duplicate
          {
            printf("%s\n", buff);
          }
          //the following needed to be done via loop unless 
          //the library functions memset and strcat are used, 
          //but those both loop under the hood anyway so this is faster
        for(j=0;j<maxword;j++) //set lastword to be the word that was just finished
          {
            lastword[j]=buff[j];
          }
       
        memset(&buff[0], 0, maxword); //clear the buffer

      }    
  }
  //end of u mode code
    
}
    
