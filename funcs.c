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
	struct rule_block * rule_block_head;
  
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
		  struct rule_block * new_rule_block_p = malloc(sizeof(struct rule_block));
			// point new rule block p to address that head ptr had - puts it at front
			new_rule_block_p->next = rule_block_head;
			// point head to new rule_block
			rule_block_head = new_rule_block_p;
			// copy key into new_rule_block
			strncpy(new_rule_block_p->key,key_buffer,MAX_KEY);
		//	printf("%s\n",new_rule_block_p->key);
      
      // now take new rule block and append the parsed property stuff to it as linked list
			parse_property(property_buffer,new_rule_block_p);
			//printf("%s\n",new_rule_block_p->property_list_head->name);

      pbc = 0, kbc = 0;
      memset(key_buffer,0,sizeof(key_buffer));
      memset(property_buffer,0,sizeof(property_buffer));
			state = OUT;
		}
  }
		printf("%s\n",rule_block_head->property_list_head);

/*
	struct rule_block * current_rule_p = rule_block_head->next;
	while (current_rule_p != NULL)
	{
	  printf("%s\n",current_rule_p->key);	
	}
	*/
  return 0;
}

// parses property and appends linked list of properties to newly created rule block
int parse_property(char * property_block, struct rule_block * new_rule_block_p) 
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
			_property_list.next = new_rule_block_p->property_list_head;
			// new rule block's head points to property_list address
			new_rule_block_p->property_list_head = &_property_list; 

      // reset buffers, counts, change state
			vc = nc = 0;
      memset(name,0,sizeof(name));
			memset(value,0,sizeof(value));
		  state = NAME;
		}
  }
  return 0;
}


