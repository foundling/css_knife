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

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#define   OUT           0 
#define   IN            1 
#define   MAX_KEY       500
#define   MAX_PROPERTY  1000

// each style block has a selector string
// and it points to a linked list of properties

struct table
{
  struct style_block * next;
} _table;


struct style_block 
{
  char * selector;
  struct property * property_list;
} _style_block;

// linked list of properties
struct property 
{
  struct property * next;
  char * name;
	char * value; // wrong?
} _property; 


void parse_key_and_property(int c,int * state, char * key_buffer, char * property_buffer, struct style_block * style_block_ptr, int * pbc, int * kbc);

// get filename
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
		printf("Please specify a single filename\n");
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
	  struct style_block * style_block_ptr = malloc(sizeof(struct style_block));
	  parse_key_and_property(c, &state, key_buffer,property_buffer,style_block_ptr, &pbc, &kbc);
  }
  return 0;
}

void parse_key_and_property(int c,int * state, char * key_buffer, char * property_buffer, struct style_block * style_block_ptr, int * pbc, int * kbc)
{

  printf("%c",c);

  // store key name
  if ( (*state == OUT) && (c != '{') && (c != ' ') && (c != '\n') && (c != '\t') )
  {
      key_buffer[(*kbc)++] = c;
  }
  // switch to IN
  else if ( (*state == OUT) && (c == '{') )
  {
      *state = IN;
  }
  // store the property data
  else if ( (*state == IN) && (c != '}') && (c != '\n') )
  {
    property_buffer[(*pbc)++] = c;
  }
  // exit - this is where the printing and buffer clear happens
  else if ( (*state == IN) && (c == '}') )
  {
    *state = OUT;

		// create style_block struct on heap
		// copy key_field into its selector field

    //printf("%s",key_buffer);
		// clear buffers, reset counts
    memset(key_buffer,0,sizeof(&key_buffer));
    memset(property_buffer,0,sizeof(&key_buffer));
    *pbc = *kbc = 0;
  }

}
/*
struct table
{
  struct style_block * next;
	} _table;


	struct style_block
	{
	  char * selector;
	  struct property * property_list;
	} _style_block;

*/

