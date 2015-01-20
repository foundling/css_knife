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
void parse_key_and_property(FILE * css_file, char * property_buffer, char * key_buffer);

// each style block has a selector string
// and it points to a linked list of properties

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



// get filename
int main(int argc, char *argv[]) 
{
  char key_buffer[MAX_KEY + 1];
  key_buffer[MAX_KEY] = 0;
  char property_buffer[MAX_PROPERTY + 1];
  property_buffer[MAX_PROPERTY] = 0;


  _property.next = NULL;
	_property.name = "width:";
	_property.value = "100%;"; 
  _style_block.selector = "html";
	_style_block.property_list = &_property;

  printf("%s\n",_style_block.selector);
  printf("%s\n",_style_block.property_list->name);
  printf("%s\n",_style_block.property_list->value);

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

  parse_key_and_property(fp,key_buffer,property_buffer);

  return 0;
}

void parse_key_and_property(FILE * css_file, char * property_buffer, char * key_buffer)
{
  int c;
  int state = OUT;
  int pbc = 0, kbc = 0;
  while ( (c=getc(css_file)) != EOF )
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
    else if ( (state == IN) && (c != '}') && (c != '\n') )
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
//         printf("%s\n",key_buffer);
//         printf("%s\n\n",property_buffer);
         memset(key_buffer,0,sizeof(&key_buffer));
         memset(property_buffer,0,sizeof(&key_buffer));
         pbc = kbc = 0;
    }

  } 
}
