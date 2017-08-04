/*
Steven Waterhouse
Cwc.c
Description: This c program is meant to mimic the linux cp command to allow
the command to be used regardless of OS.
Input: A file with lines of text and space/newline char delimited tokens. Also a file
to be populated with the contents of the first file.
Output: The second file passed becomes a copy of the first file. There is no console output
*/


#include <stdio.h>
#include <string.h>


int main( int argc, const char *argv[] )

{
	
	FILE * fileB=fopen(argv[2], "w");
	FILE *fileA=fopen( argv[1], "r" );
	char line;
  
  while ((line =fgetc(fileA))!=EOF)
    { 
      fputc(line,fileB);   //not much to say, it this line
      //of the while loop copies file A to fileB char by char 
    }
  	fclose (fileB); 
  	fclose (fileA);       

	  

}