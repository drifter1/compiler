/*
 * a leap year is any year that meets the below conditions:
 * is a multiple of 4 but not of 100, or
 * is a multiple of 400.
 */
int isleapyear(int year) {
    int flag;

    if (year % 400 == 0) {
        flag = 1;
    } else if (year % 100 == 0) {
        flag = 0;
    } else if (year % 4 == 0) {
        flag = 1;
    } else {
        flag = 0;
    }

    return flag;
}

int main() {
    int year;

    print "Enter year: ";
    input year;

    if (isleapyear(year)) {
        print "Leap Year.\n";
    } else {
        print "Not a Leap Year.\n";
    }

    return 0;
}