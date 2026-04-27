double bracket1 = 10000.0;
double bracket2 = 30000.0;
double rate2 = 0.2;
double rate3 = 0.3;

double calculatetax(double income) {
    double tax = 0.0;
    double taxable;

    if (income > bracket1) {
        if (income > bracket2) {
            taxable = bracket2 - bracket1;
        } else {
            taxable = income - bracket1;
        }
        tax = tax + taxable * rate2;
    }

    if (income > bracket2) {
        taxable = income - bracket2;
        tax = tax + taxable * rate3;
    }

    return tax;
}

int main() {
    double income;
    input income;
    print calculatetax(income);
    return 0;
}