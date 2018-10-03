// main function
// declarations
int i;
double val = 2.5, res[10];
// statements
for(i = 0; i < 10; i++){
    res[i] = operation(val, i);
    val = res[i]; 
    print(res[i]);
    print('\n');
}
return;
// functions
double operation (double value, int i){    /* function declaration */
    // declarations
    double res;
    // statements
    res = value*i + i;
    return res;
}
