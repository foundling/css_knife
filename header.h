#define   OUT             0 
#define   IN              1 
#define   NAME            0
#define   VALUE           1
#define   MAX_KEY         500
#define   MAX_PROPERTY    1000
#define   MAX_PROP_NAME   500
#define   MAX_PROP_VALUE  1000

// top level nodes are the css style code blocks
// each style node has a key (aka html), a next pointert(to next style block), and an attached linked list of properties
// each property node inthe property node list is a key and a value

struct property_list
{
  struct property_list * next_property; // for linked list of properties
  char name[MAX_PROP_NAME];
  char value[MAX_PROP_VALUE];
};

struct rule_block
{
  char key[MAX_KEY + 1];
  struct property_list * property_list_head; // for linked lists of property_lists
  struct rule_block * next_rule_block; // for linked list of style blocks
};


int parse_key_property(FILE * fp);
int parse_name_value(char * property_buffer, struct property_list * property_list_ptr);

