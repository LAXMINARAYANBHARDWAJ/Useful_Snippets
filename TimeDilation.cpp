#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int celeritas = 299792458;

int main() {
    
    int input;
    cout << "1. Calculate dilated time (actual velocity)" << endl << "2. Calculate dilated time (percentage of Speed of light)" << endl << "3. Calculate velocity" << endl << endl << "> ";
    cin >> input;

    if (input == 1) {

        cout << "Velocity(m/s): ";
        double velocity;
        cin >> velocity;

        double velocityToCeleritas = velocity / celeritas;

        double denominator = (1 - (velocityToCeleritas * velocityToCeleritas));

        double gamma = 1 / pow(denominator, 0.5);
        
        double properTime;
        cout << "Proper time(second): ";
        cin >> properTime;
        
        double dilatedTime = gamma * properTime;

        cout << fixed << setprecision(15);
        cout << "Dilated time: " << dilatedTime << endl << "Lorentz factor: " << (gamma) << endl;

    }

    else if (input == 2) {

        cout << "Percentage compared to C: ";
        
        double percentage;
        cin >> percentage;

        double velocity = (percentage * (celeritas / 100));

        double velocityToCeleritas = velocity / celeritas;

        double denominator = (1 - (velocityToCeleritas * velocityToCeleritas));

        double gamma = 1 / pow(denominator, 0.5);
        
        double properTime;
        cout << "Proper time(second): ";
        cin >> properTime;
        
        double dilatedTime = gamma * properTime;

        cout << fixed << setprecision(15);
        cout << "Dilated time: " << dilatedTime << endl << "Lorentz factor: " << (gamma) << endl;

    }

    else if (input == 3) {

        cout << "Lorentz Factor: ";
        double gamma;
        cin >> gamma;

        double radicand = 1 - (1 / (gamma * gamma));

        double velocity = celeritas * (pow(radicand, 0.5));

        double percentage = (velocity / celeritas) * 100;
        
        cout << fixed << setprecision(15);
        cout << "Velocity: " << velocity << endl << "Percentage: " << percentage << "% the speed of light" << endl;

    }

    else {
        cout << "Invalid input. Try again." << endl;
    }

    return 0;
}