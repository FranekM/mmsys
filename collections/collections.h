#define LISTSIZE sizeof(list)
#define NODESIZE sizeof(node)
#define PNODESIZE sizeof(pnode)

typedef struct node {
	struct node *next;
	int value;
} node, *Node;

typedef struct pnode {
	struct pnode *next;
	int *value;
} pnode, *pNode;

typedef struct list {
	void *head;
	void *tail;
	int size;
} list, *List;

int add(List, int);
int get(List, int);
int padd(List, int *);
int *pget(List, int);
void initList(List, const char[]);
