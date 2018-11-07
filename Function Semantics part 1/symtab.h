/* maximum size of hash table */
#define SIZE 211

/* maximum size of tokens-identifiers */
#define MAXTOKENLEN 40

/* how parameter is passed */
#define BY_VALUE 1
#define BY_REFER 2

/* parameter struct */
typedef struct Param{
	// parameter type and name
	int par_type;
	char param_name[MAXTOKENLEN];
	
	// to store the value
	int ival; double fval; char *st_sval;
	int passing; // value or reference
}Param;

/* a linked list of references (lineno's) for each variable */
typedef struct RefList{ 
    int lineno;
    struct RefList *next;
}RefList;

// struct that represents a list node
typedef struct list_t{
	// name, size of name, scope and occurrences (lines)
	char st_name[MAXTOKENLEN];
    int st_size;
    int scope;
    RefList *lines;
    
	// to store value and sometimes more information
	int st_ival; double st_fval; char st_sval;
	
	// type
    int st_type;
    
    // for arrays (info type), for pointers (pointing type)
	// and for functions (return type)
	int inf_type;
	
	// array stuff
	int *i_vals; double *f_vals; char *s_vals;
	int array_size;
	
	// function parameters
	Param *parameters;
	int num_of_pars;
	
	// pointer to next item in the list
	struct list_t *next;
}list_t;

/* hash table */
static list_t **hash_table;


// Symbol Table Functions
void init_hash_table(); // initialize hash table
unsigned int hash(char *key); // hash function 
void insert(char *name, int len, int type, int lineno); // insert entry
list_t *lookup(char *name); // search for entry
void symtab_dump(FILE *of); // dump file

// Type Functions
void set_type(char *name, int st_type, int inf_type); // set the type of an entry (declaration)
int get_type(char *name); // get the type of an entry

// Scope Management Functions
void hide_scope(); // hide the current scope
void incr_scope(); // go to next scope

// Function Declaration and Parameters
Param def_param(int par_type, char *param_name, int passing); // define parameter
int func_declare(char *name, int ret_type, int num_of_pars, Param *parameters); // declare function
int func_param_check(char *name, int num_of_pars, Param *parameters); // check parameters
