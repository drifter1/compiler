int max(int x, int y) {
    int z;
    if (x > y) {
        z = x;
    } else {
        z = y;
    }
    return z;
}

int lcm(int x, int y) {
    int val;
    val = max(x, y);
    while (1) {
        if ((val % x == 0) && (val % y == 0)) {
            break;
        }
        val++;
    }
    return val;
}

int main() {
    int x = 15;
    int y = 25;
    print "LCM is ";
    print lcm(x, y);
    print "\n";
    return 0;
}