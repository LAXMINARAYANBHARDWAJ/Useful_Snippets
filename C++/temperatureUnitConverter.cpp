#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    
    double inputTemperature;
    std::cout << "Magnitude >> " << std::fixed;
    std::cin >> inputTemperature; 

    std::string unit;
    std::cout << "Unit >> ";
    std::cin >> unit;
    std::cout << std::endl;

    if (unit == "C" || unit == "c") {
        double fahrenheit = (inputTemperature * 1.8) + 32;
        double kelvin = (inputTemperature + 273.15);

        std::cout << fahrenheit << " F" << std::endl << kelvin << " K" << std::endl;
    }

    else if (unit == "F" || unit == "f") {
        double celsius = (inputTemperature - 32) / 1.8;
        double kelvin = (celsius + 273.15);

        std::cout << celsius << " C" << std::endl << kelvin << " K" << std::endl;
    }

    else if (unit == "K" || unit == "k") {
        double celsius = inputTemperature - 273.15;
        double fahrenheit = (celsius * 1.8) + 32;

        std::cout << celsius << " C" << std::endl << fahrenheit << " F" << std::endl;
    }

    else {
        std::cout << "INVALID INPUT" << std::endl;
    }
    
    return 0;

}
