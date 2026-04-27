int gcd(int x, int y) {
    while (x != y) {
        if (x > y) {
            x = x - y;
        } else {
            y = y - x;
        }
    }
    return x;
}

int main() {
    int x = 60;
    int y = 48;
    print "GCD is ";
    print gcd(x, y);
    print "\n";
    return 0;
}