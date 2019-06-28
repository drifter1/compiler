
/* main assembly code generation function */
void generate_code();

/* data declaration assembly code */
void generate_data_declarations(FILE *fp);

/* statements assembly code */
void generate_statements(FILE *fp);

/* Adjacency List */
typedef struct AdjList{
	int index;
	struct AdjList *next;
}AdjList;

/* Adjacency Graph */
typedef struct AdjGraph{
	AdjList **adj;
	int vertexCount;
}AdjGraph;

/* Graph Functions */
static AdjGraph *g;

void initGraph();

void insertEdge(int i, int j);

void printGraph();

int* greedyColoring();

/* Variable Array */
static char **var_name;
static int var_count = 0;
static int temp_count = 0;

/* Variable Array Functions */
void insertVar(char *name);

int getVarIndex(char *name);

void printVarArray();

/* main function register allocation */
void main_reg_allocation(AST_Node *node);
