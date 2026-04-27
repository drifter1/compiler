double bmi(double weight, double height) {
    return weight / (height * height); 
}
void category(double value) {
    if (value < 18.5) {
        print "Underweight\n";
    } else if (value < 25.0) {
        print "Healthy Weight\n";
    } else if (value < 30.0) {
        print "Overweight\n";
    } else {
        print "Obesity\n";
    }
}
int main() {
    double weight, height;
    double value;

    print "Please enter your weight in kg: ";
    input weight;

    print "Pleae enter your height in meters: ";
    input height;

    value = bmi(weight, height);

    print "Your BMI is: ";
    print value;
    print "\n";

    category(value);

    return 0;
}