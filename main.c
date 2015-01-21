/*
*  CSS Alphabetizer
*  
*  usage: cssort <css file> [ > output_file]
*  purpose: sorts your css blocks alphabetically
*  todo: make a web service
*  todo: sort property blocks, too
*  todo: add minifier
*  todo: keep a count of '{' and '}'s so you can treat nested tags
*        (media queries) as a separate group.
*        Sort groups by nested level.
*/

// make a temp buffer for word and css propertys 
// create a key - property struct
// property is also a struct: name - property;
// malloc struct space for key and properties when you 
// exit reading the properties into the array

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include	"header.h"

int main(int argc, char *argv[]) 
{
  // arg check 
	if (argc != 2) 
	{
		printf("usage: cssort <css file> [ > output_file]\n");
	  exit(1); 
	}

	// open file and check for valid fp
	FILE * fp;
	fp = fopen(argv[1],"r");
	if (fp == NULL)
	{
	  printf("fp is null");
		exit(1);
	}
  
	parse_rule(fp);
  return 0;
}
