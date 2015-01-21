#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include	"header.h"

char property_buffer[MAX_PROPERTY + 1];
char key_buffer[MAX_KEY + 1];


int parse_key_property(FILE * fp)
{
  int c;
  int state = OUT;
  int pbc = 0, kbc = 0;
  struct rule_block Rule_Block;
  struct rule_block * sp = &Rule_Block;
  
	while ( (c=getc(fp)) != EOF)
  {
		// pointer to a container for a style block. init to null

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
		else if ( (state == IN) && (c != '}') )
		{
			property_buffer[pbc++] = c;
    }
		// exit process key property data on closing brace
		else if ( (state == IN) && (c == '}') )
		{
			state = OUT;
			strncpy(sp->key,key_buffer,MAX_KEY);
      printf("%s\n",sp->key); 
      pbc = 0, kbc = 0;
      memset(key_buffer,0,sizeof(key_buffer));
      memset(property_buffer,0,sizeof(key_buffer));
		}
  }
  return 0;
}

int parse_name_value(char * property_block, struct property_list * property_list_head_ptr) 
{

  int i;
  int state = NAME;
  int block_len = strlen(property_block);
  char name[MAX_PROP_NAME + 1] = {0};
  char value[MAX_PROP_VALUE + 1] = {0};
  int nc, vc;
	nc = vc = 0;

  for (i=0;block_len;i++)
  {
    if ( (state == NAME) && (property_block[i] != ':'))
    {
      name[nc++] = property_block[i];     
    }    
    else if ( (state == NAME) && (property_block[i] == ':'))
    {
      state = VALUE;
    }
    else if ( (state == VALUE) && (property_block[i] != ';') )
    {
      value[vc++] = property_block[i];
    }
		else if ( (state == VALUE) && (property_block[i] == ';') )
		{
		  state = NAME;
			// create new property node
			// new node gets put first
			// point new node's next to property list
			// point property list ptr to NULL so it's at the end

      // copy data to new propery_node's name and val fields

			vc = nc = 0;
      memset(name,0,sizeof(name));
			memset(value,0,sizeof(value));

		}
  }
  return 0;
}
