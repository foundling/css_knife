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

	// pointer is head of rule_blocks
	struct rule_block * rule_block_headp;
  
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
			// get pointer to new rule_block struct
		  struct rule_block * new_rule_block = malloc(sizeof(struct rule_block));
			// point head to new rule_block
			rule_block_headp = new_rule_block;
			// set next ptr to null
			new_rule_block->next_rule_block=NULL;
			// copy key into new_rule_block
			strncpy(new_rule_block->key,key_buffer,MAX_KEY);
			printf("%s\n",new_rule_block->key);
      
      // now take new rule block and append the parsed property stuff to it as linked list
			parse_property(property_buffer,new_rule_block);
      pbc = 0, kbc = 0;
      memset(key_buffer,0,sizeof(key_buffer));
      memset(property_buffer,0,sizeof(property_buffer));
			state = OUT;
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
			
			// create new property list node
			struct property_list _property_list = {0,{0},{0}};
			// copy data into it
			strncpy(_property_list.name, name, MAX_PROP_NAME);
			strncpy(_property_list.value, value, MAX_PROP_VALUE);

			// new property list gets a next value of what new rule block pointer's head pointed to
			_property_list.next_property = new_rule_blockp->property_list_head;
			// new rule block's head points to property_list address
			new_rule_blockp->property_list_head = &_property_list; 
			printf("%s\n",_property_list.name);
			printf("%s\n",_property_list.value);

      // reset buffers, counts, change state
			vc = nc = 0;
      memset(name,0,sizeof(name));
			memset(value,0,sizeof(value));
		  state = NAME;
		}
  }
  return 0;
}
