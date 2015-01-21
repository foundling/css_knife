#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include	"header.h"

char property_buffer[MAX_PROPERTY + 1];
char key_buffer[MAX_KEY + 1];


int parse_rule_block(FILE * fp)
{
  int c;
  int state = OUT;
  int pbc = 0, kbc = 0;
  struct rule_block head_rule_block = { {0},0,0 };
  
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
      strncpy(head_rule_block.key,key_buffer,MAX_KEY);
			printf("%s",property_buffer);
			
			struct rule_block *new_rule_node = malloc(sizeof(struct rule_block));
			new_rule_node->next_rule_block = &head_rule_block;
			head_rule_block.next_rule_block = NULL;

      parse_property(property_buffer, new_rule_node);

      pbc = 0, kbc = 0;
      memset(key_buffer,0,sizeof(key_buffer));
      memset(property_buffer,0,sizeof(key_buffer));
		}
  }
  return 0;
}

int parse_property(char * property_block, struct rule_block * new_rule_blockp) 
{

  int i;
  int state = NAME;
  int block_len = strlen(property_block);
  char name[MAX_PROP_NAME + 1] = {0};
  char value[MAX_PROP_VALUE + 1] = {0};
  int nc, vc;
	nc = vc = 0;

  for (i=0;i<block_len;i++)
  {
	  // in name area
    if ( (state == NAME) && (property_block[i] != ':'))
    {
      name[nc++] = property_block[i];     
    }    
		// we see a colon
    else if ( (state == NAME) && (property_block[i] == ':'))
    {
      state = VALUE;
    }
		// in value area
    else if ( (state == VALUE) && (property_block[i] != ';') )
    {
      value[vc++] = property_block[i];
    }
		// end of value area, process name,value pair
		else if ( (state == VALUE) && (property_block[i] == ';') )
		{
			
		  state = NAME;
			struct property_list _property_list = {0,{0},{0}};
			strncpy(_property_list.name, name, MAX_PROP_NAME);
			strncpy(_property_list.value, value, MAX_PROP_VALUE);

			// give the pointer on rule block the address for list above
      rule_block->property_list_head = &_property_list;
			// create property_list
			// 
			printf("%s",value);
			printf("%s",name);
			// create new property node

			// new node gets put first
			// point new node's next to property list
			// point property list ptr to NULL so it's at the end
      // copy data to new propery_node's name and val fields


      // reset buffers, counts
			vc = nc = 0;
      memset(name,0,sizeof(name));
			memset(value,0,sizeof(value));

		}
  }
  return 0;
}
