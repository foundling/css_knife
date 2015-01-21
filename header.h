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

// css property node
struct pnode
{
  char name[MAX_PROP_NAME];
  char value[MAX_PROP_VALUE];
  struct pnode * next; 
};

// css rule node
struct rnode
{
  char key[MAX_KEY + 1];
  struct pnode phead; 
  struct rnode * next; 
};


int parse_rule(FILE * fp);
int parse_property(char * property_block, struct rnode * new_rnode);
