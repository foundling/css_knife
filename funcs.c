#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include	"header.h"

char property_buffer[MAX_PROPERTY + 1];
char key_buffer[MAX_KEY + 1];

struct table
{
  struct style_block * next;
};


struct style_block
{
  char selector[MAX_KEY + 1];
  struct property * property_list;
};

// linked list of properties
struct property
{
  struct property * next;
  char name[MAX_PROP_NAME];
  char value[MAX_PROP_VALUE];
};

int parse_key_property(FILE * fp)
{
  int c;
  int state = OUT;
  int pbc = 0, kbc = 0;
  struct table Table = {0};
  //struct style_block *style_block_ptr = malloc(sizeof(struct style_block));
  
	while ( (c=getc(fp)) != EOF)
  {
		// create style_block on heap
    struct style_block *style_block_ptr = malloc(sizeof(struct style_block));
		// create property_list on heap
		struct property * property_ptr = malloc(sizeof(struct property));
		// style_block gets the address of property list just allocated
		style_block_ptr->property_list = property_ptr; 

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
      //printf("%s\n",key_buffer);
			// copy key_buffer into style_block_ptr's selector field
      strcpy(style_block_ptr->selector,key_buffer);
      strcpy(style_block_ptr->property_list->name,property_buffer);
			printf("%s\n",style_block_ptr->selector);
			printf("%s\n",style_block_ptr->property_list->name);

      //printf("%s\n",style_block_ptr->selector);
      pbc = 0, kbc = 0;
      memset(key_buffer,0,sizeof(key_buffer));
      memset(property_buffer,0,sizeof(key_buffer));
		}
  }
  return 0;
}
