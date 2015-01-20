/*
*  CSS Alphabetizer
*  
*  usage: cssort <css file> [ > output_file]
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
  int c;
	int state = OUT;
  char key_buffer[MAX_KEY + 1];
  char property_buffer[MAX_PROPERTY + 1];
  key_buffer[MAX_KEY] = 0;
  property_buffer[MAX_PROPERTY] = 0;
  int pbc = 0, kbc = 0;


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

  while ( (c=getc(fp)) != EOF)
	{
	  struct style_block * _style_block = parse_key_and_property(c, &state, key_buffer,property_buffer, &pbc, &kbc);
		if (_style_block) 
		{
		  printf("%s\n",_style_block->selector);
		}
  }
  return 0;
}


