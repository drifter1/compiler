int factorial(int n) {
    int f = 1;
    int i;
    for (i = 1; i <= n; i++) {
        f = f * i;
    }
    return f;
}
int main() {
    int n;
    input n;
    print factorial(n);
    return 0;
}