// functions
double operation(double value, int i) { /* function declaration */
    // declarations
    double res;
    // statements
    res = value * i + i;
    return res;
}
// main function
int main() {
    // declarations
    int i;
    double val = 2.5, res;
    // statements
    for (i = 0; i < 10; i++) {
        res = operation(val, i);
        val = res;
        print res;
        print "\n";
    }
    return 0;
}