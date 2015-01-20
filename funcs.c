#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include	"header.h"

char property_buffer[MAX_PROPERTY + 1];
char key_buffer[MAX_KEY + 1];

static struct table
{
  struct style_block * next;
} _table;


static struct style_block
{
  char * selector;
  struct property * property_list;
} _style_block;

// linked list of properties
static struct property
{
  struct property * next;
  char * name;
  char * value; // wrong?
} _property;

int parse_key_property(FILE * fp)
{
  int c;
  int state = OUT;
  int pbc = 0, kbc = 0;

  while ( (c=getc(fp)) != EOF)
  {
		// accumulate key name while outside of code block
		if ( (state == OUT) && (c != '{') )
		{
			key_buffer[kbc++] = c;
		}
		// switch to IN on opening brace
		else if ( (state == OUT) && (c == '{') )
		{
			state = IN;
		}
		// store the property data in buf while not closing brace
		else if ( (state == IN) && (c != '}') && (c != '\n') )
		{
			property_buffer[pbc++] = c;
		}
		// exit process key property data on closing brace
		else if ( (state == IN) && (c == '}') )
		{
			state = OUT;
      printf("%s\n",key_buffer);
      pbc = 0, kbc = 0;
      memset(key_buffer,0,sizeof(key_buffer));
      memset(property_buffer,0,sizeof(key_buffer));
		}
  }
  return 0;
}
