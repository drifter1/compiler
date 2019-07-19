
/* main assembly code generation function */
void generate_code();

/* data declaration assembly code */
void generate_data_declarations(FILE *fp);

/* statements assembly code */
void generate_statements(FILE *fp);

/* get register name from color */
char * GetRegisterName(int color, int isFloat);

/* various generation functions */
void generate_arithm(FILE *fp, AST_Node_Arithm *node);
void generate_bool(FILE *fp, AST_Node_Bool *node);
void generate_rel(FILE *fp, AST_Node_Rel *node, int invLogic, char* Label);
void generate_equ(FILE *fp, AST_Node_Equ *node, int invLogic, char* Label);
void generate_load(FILE *fp, AST_Node_Ref *node);
void generate_func_call_res(FILE *fp, AST_Node_Func_Call *node);
void generate_simple(FILE *fp, char* Label);
void generate_incr_decr(FILE *fp, AST_Node_Incr *node);

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

/* main function tree traversal */
void main_func_traversal(FILE *fp, AST_Node *node);
