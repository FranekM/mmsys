#ifndef COLLECTIONS
#define COLLECTIONS

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

#define TNODESIZE sizeof(tnode)
#define TREESIZE sizeof(tree)

typedef struct tnode {
	struct tnode *left;
	struct tnode *right;
	int key;
	int value;
} tnode, *tNode;

typedef struct tree {
	tNode root;
	int size;
} tree, *Tree;

int tput(Tree, int, int);
int tget(Tree, int);
void initTree(Tree);
int isexact();

#endif
