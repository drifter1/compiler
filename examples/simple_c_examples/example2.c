double operation(double value, int i) {
    double res;
    res = value * i + i;
    return res;
}
int main() {
    int i;
    double val = 2.5, res;
    for (i = 0; i < 10; i++) {
        res = operation(val, i);
        val = res;
        print res;
        print "\n";
    }
    return 0;
}