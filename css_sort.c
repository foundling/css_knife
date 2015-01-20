/*
*  CSS Alphabetizer
*  
* accumulate {/}'s and each number of current {/}'s 
* is sorted as a separate group
*
*/

// make a temp buffer for word and css propertys 
// create a key - property struct
// property is also a struct: name - property;
// malloc struct space for key and properties when you 
// exit reading the properties into the array

struct property 
{
  char * name;
	char * property;
} _property;

struct selector 
{
  char * name;
	struct property * prop; // wrong?
} _selector; 

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#define   OUT        0 
#define   IN         1 
#define   MAX_KEY    500
#define		MAX_PROPERTY  1000

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
	char key_buffer[MAX_KEY + 1];
	key_buffer[MAX_KEY] = 0;
	char property_buffer[MAX_PROPERTY + 1];
	property_buffer[MAX_PROPERTY] = 0;
	int pbc = 0, kbc = 0;

  //html{ width: 400px; background: red;}
	//body{ width: 400px; background: red;}
  
	// two states: out of attribute block and in one
  while ( (c=getc(fp)) != EOF )
	{
	  // store key name
	  if ( (state == OUT) && (c != '{') && (c != ' ') && (c != '\n') && (c != '\t') )
		{
				key_buffer[kbc++] = c;
		}
		// switch to IN
	  else if ( (state == OUT) && (c == '{') )
		{
			  state = IN;
		}
		// store the property data
		else if ( (state == IN) && (c != '}') && (c != ' ') && (c != '\n') && (c != '\t') )
		{
		    property_buffer[pbc++] = c;
		}
		// exit - this is where the printing and buffer clear happens
		else if ( (state == IN) && (c == '}') )
		{
			   state = OUT;
				 // property buffer gets parsed into colon separated data
				 // it must be able to handle not having a property
				 // or property name
				 printf("%s\n",key_buffer);
				 printf("%s\n\n",property_buffer);
				 memset(key_buffer,0,sizeof(key_buffer));
				 memset(property_buffer,0,sizeof(key_buffer));
				 pbc = kbc = 0;
		}

	}
	fclose(fp);
  return 0;
}
