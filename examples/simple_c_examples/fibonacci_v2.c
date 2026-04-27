int fibonacci(int n) {
    int i;
    int t0 = 0, t1 = 1, t2;

    for (i = 1; i <= n - 2; i++) {
        t2 = t0 + t1;
        t0 = t1;
        t1 = t2;
    }

    return t2;
}
int main() {
    int n;
    input n;
    print fibonacci(n);
    return 0;
}