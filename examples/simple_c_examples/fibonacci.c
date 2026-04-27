int main() {
    int n, i, t0 = 0, t1 = 1, t2;

    input n;

    print t0;
    print "\n";
    print t1;
    print "\n";

    for (i = 1; i <= n - 2; i++) {
        t2 = t0 + t1;

        print t2;
        print "\n";

        t0 = t1;
        t1 = t2;
    }

    return 0;
}