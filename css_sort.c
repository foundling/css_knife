/*
*  CSS Alphabetizer
*  
* accumulate {/}'s and each number of current {/}'s 
* is sorted as a separate group
*
*/

// make a temp buffer for word and css values 
// create a key - property struct
// property is also a struct: name - value;
// malloc struct space for key and properties when you 
// exit reading the properties into the array

struct property 
{
  char * name;
	char * value;
} _property;

struct selector 
{
  char * name;
	struct property * prop; // wrong?
} _selector; 

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#define   OUT    0 
#define   IN     1 

// get filename
int main(int argc, char *argv[]) 
{
  // 
	if (argc != 2) 
	{
		printf("Please specify one filename\n");
	  exit(1); 
	}
	// open file
	FILE * fp;
	fp = fopen(argv[1],"r");
	if (fp == NULL)
	{
	  printf("fp is null");
		exit(1);
	}

  int c;
	int state = OUT;
	char key_buffer[1001];
	key_buffer[1000] = 0;
	int kbc = 0;
	char value_buffer[5001];
	value_buffer[5000] = 0;
	int vbc = 0;

  
	// two states: out of attribute block and in one
  while ( (c=getc(fp)) != EOF )
	{
	  if ( (state == OUT) && (c != '{') && (c != ' '))
		{
					key_buffer[kbc++] = c;
		}
	  else if ( (state == OUT) && (c == '{') )
		{
			  state = IN;
		}
		else if ( (state == IN) && (c != '}') )
		{
		    value_buffer[vbc++] = c;
		}
		else if ( (state == IN) && (c == '}') )
		{
			   state = OUT;
				 // value buffer gets parsed into colon separated data
				 // it must be able to handle not having a value
				 // or property name
				 printf("%s\n\n",key_buffer);
				 /*render(key_buffer,value_buffer);*/
				 printf("VALUE BUFFER:%s\n",value_buffer);
		}
		else
		{
		  printf("error!\n");
		//	printf("key: %s\n,value: %s\nstate: %d\n", key_buffer, value_buffer, state);
			exit(1);
		}

	}
  return 0;
}
