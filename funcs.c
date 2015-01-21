#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include	"header.h"

char property_buffer[MAX_PROPERTY + 1];
char key_buffer[MAX_KEY + 1];


int parse_rule(FILE * fp)
{
  int c;
  int state = OUT;
  int pbc = 0, kbc = 0;

  struct rnode RNODE = {{0}};
  struct pnode PNODE = {{0},{0}};
	RNODE.phead = PNODE;

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
			struct rnode * NEW_RNODE = malloc(sizeof(struct rnode));
			strncpy(NEW_RNODE->key,key_buffer,MAX_KEY);
			NEW_RNODE->next = RNODE.next;
			RNODE.next = NEW_RNODE;
			printf("%p\n%p\n",NEW_RNODE->next,RNODE.next);


			// reset, clean up
      pbc = 0, kbc = 0;
      memset(key_buffer,0,sizeof(key_buffer));
      memset(property_buffer,0,sizeof(property_buffer));
			state = OUT;
		}
  }

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
int parse_property(char * property_block, struct rnode * new_rnode)
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
			

      // reset buffers, counts, change state
			vc = nc = 0;
      memset(name,0,sizeof(name));
			memset(value,0,sizeof(value));
		  state = NAME;
		}
  }
  return 0;
}


