float amount = 5.5;
int main() {
    float card;
    float cash;
    float remainder;

    print "Input card balance: ";
    input card;

    print "Input cash: ";
    input cash;

    // pay with card only
    if (card >= amount) {
        card = card - amount;
        print "Paid fully with card.\n";
        print "Card Remainder is ";
        print card;
        print "\n";
    }
    // pay part in cash
    else {
        remainder = amount - card;

        // cash sufficient
        if (cash >= remainder) {
            print "Paid ";
            print card;
            print " with card.\n";

            card = 0;
            print "Card is now empty!\n";

            print "Paid ";
            print remainder;
            print " in cash.\n";

            print "Remaining cash is ";
            cash = cash - remainder;
            print cash;
            print "\n";
        }
        // cash unsufficient
        else {
            print "Card + Cash balance is insufficient!\n";
            print "You need ";
            print remainder - cash;
            print " more!\n";
        }
    }

    return 0;
}