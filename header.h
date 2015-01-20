#define   OUT           0 
#define   IN            1 
#define   MAX_KEY       500
#define   MAX_PROPERTY  1000

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


void parse_key_and_property(int c,int * state, char * key_buffer, char * property_buffer, struct style_block **style_block_ptr, int * pbc, int * kbc);
