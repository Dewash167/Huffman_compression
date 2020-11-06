#define treeheight 100
typedef struct node
{
	char data;
	unsigned freq;
	struct node *left, *right;
} node;
struct minheap
{
	unsigned size;
	unsigned capacity;
	node **arr;
};

typedef struct codes
{
	char ch;
	char str[64];
} codes;

node *newnode(char data, unsigned freq);
struct minheap *createminheap(unsigned capacity);
void swapnode(node **a, node **b);
void heapify(struct minheap *mheap, int index);
int issone(struct minheap *mheap);
node *minimum(struct minheap *mheap);
void insert(struct minheap *mheap, node *t);
void makeheap(struct minheap *mheap);
struct minheap *cbm(char data[], int freq[], int size);
node *bht(char data[], int freq[], int size);
int isleaf(node *root);
void printcodes(node *root, int arr[], int top);
void code(char data[], int freq[], int size);
void printarr(int arr[], int n);
