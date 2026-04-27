int main() {
    int x;

    while (1) {

        print "Input a number (enter negative to quit): ";
        input x;

        if (x < 0) {
            break;
        }

        if (x % 2 == 0) {
            print "The number is even.\n";
        } else {
            print "The number is odd.\n";
        }
    }

    return 0;
}