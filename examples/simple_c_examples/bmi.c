int main() {
    double weight, height, bmi;

    print "Please enter your weight in kg: ";
    input weight;

    print "Pleae enter your height in meters: ";
    input height;

    bmi = weight / (height * height);

    print "Your BMI is: ";
    print bmi;
    print "\n";

    return 0;
}