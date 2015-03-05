/*

A command-line utility that takes a CSS file via stdin, alphabetizes it, and sends the newly sorted file to stdout or to an output file that is not the same as the source file. Sorry, but no in-place sorting of css files is supported at this time.
 
Usage: knife [-DZ ] [ -f target_file_name] [ -o output_file ] 
-D, find duplicate selectors
-f, target filename
-o, send stdout to a file. cannot be the name of the source file
-p, sort properties within a rule block only, do not sort css rules
-Z, include leading non-alphabetic characters like '.' and '#' in sort procedure

Features under consideration:

+ Implementing it as a web service
+ Structural requirements for the inclusion of comments
+ Nested block logic ( I.E., Keep a count of brace nesting level so you can treat nested tags (.e.g. media query style rules) as a separate sort group if needed.)

*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  "header.h"

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
