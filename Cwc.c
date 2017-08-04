/*
Steven Waterhouse
Cwc.c
Description: This c program is meant to mimic the linux wc command to allow
the command to be used regardless of OS.
Input: A file with lines of text and space/newline char delimited tokens. 
Output: The number of words, lines and characters in the file, and a newline.
Irks me when functions make the console look weird by not doing a newline at the end.
*/



#include <stdio.h>
#include <string.h>


int main( int argc, const char *argv[] )

{
	
	
	FILE *file=fopen( argv[1], "r" );
	char line;
	int characters=0;
	int words=0;
	int linesNum=0;
	char lastChar=' '; //set beforehand to trigger the first word

   
  
  while ((line =fgetc(file))!=EOF) //go through character by character,
    //which bypasses the need to grab chunks of mem in the form of string buffers

    { 
    	 
         characters++;
         if (line=='\n')
         {
         	linesNum++;
         } 
         if (lastChar==' ' || lastChar=='\n') //last char was a delimeter
         {
         	if (line!=' ' && line !='\n') //current char isn't
         	{
         		words++; //therfore this must be the start of a new word
         	}
         }
         lastChar=line;
    }


    printf("%d lines, %d words and %d bytes \n", linesNum, words, characters);
  	fclose (file); 
  	     

	}
    
