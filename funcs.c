#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include	"header.h"

void parse_key_and_property(int c,int * state, char * key_buffer, char * property_buffer, struct style_block **style_block_ptr, int * pbc, int * kbc)
{

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

    // clear buffers, reset counts
		printf("%s\n",key_buffer);
    memset(key_buffer,0,sizeof(&key_buffer));
    memset(property_buffer,0,sizeof(&key_buffer));
    key_buffer[MAX_KEY] = 0;
    property_buffer[MAX_PROPERTY] = 0;
    *pbc = *kbc = 0;
  }

}
