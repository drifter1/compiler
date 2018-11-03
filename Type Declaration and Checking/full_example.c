// program: declarations statements RETURN SEMI functions
// main function (declarations statements)
// declarations
int i;                    // simple variable
char c = 'c';             // one with init
double val = 2.5, res[6]; // two variables, one with init and one array
double *p;                // pointer variable				  
// statements
p = &res; // assigment
for(i = 0; i < 10; i++){ // for
	if(i > 5){ // if-else
    	break;
	}
	else if(i == 5){
		i = 2 * i;
		val = func1();
		*p = add(val, i);
		print(res[i]);
		print("\n");
		continue;
	}
	else{
		*p = add(val, i);
    	val = res[i];
   	 	print(res[i]);
    	print("\n");
    	p = p + 1;
	}
	
	if(i == 2 && val == 4.5){ // if
		print("iteration: 3\n");
	}
}

while(i < 12){ // while
	print(i);
	print(" ");
	func2(c);
	i++;
}
print("\n");
return; /* RETURN SEMI */
// other functions (functions)
int func1(){ 		/* without parameters */
	// statements
	return 5;
}
void func2(char c){ /* with one parameter */
	// declarations
	char *s;
	// statements
	*s = c;
	print(*s);
}
double add (double a, int b){  /* with two parameters */
    // declarations
    double res;
    // statements
    res = a + b;
    return res;
}
