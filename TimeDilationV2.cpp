#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <limits>
#include <boost/multiprecision/cpp_dec_float.hpp>

using high_prec = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<200>>;

static const high_prec C("299792458");
static const high_prec G("6.67430e-11");
static const high_prec SOLAR_MASS("1.988475e30");
static const high_prec LIGHT_YEAR("9.4607304725808e15");

static const high_prec RS_ONE_SOLAR = (high_prec(2) * G * SOLAR_MASS) / (C * C);

inline high_prec safe_sqrt(const high_prec &x) {
    if (x < 0) {
        return high_prec(0);
    }
    using std::sqrt;
    return sqrt(x);
}

high_prec gamma_from_velocity(const high_prec &v) {
    high_prec beta2 = (v * v) / (C * C);
    if (beta2 >= 1) return std::numeric_limits<high_prec>::infinity();
    return high_prec(1) / safe_sqrt(high_prec(1) - beta2);
}

high_prec velocity_from_gamma(const high_prec &gamma) {
    if (gamma <= 1) return high_prec(0);
    high_prec invg2 = high_prec(1) / (gamma * gamma);
    high_prec beta2 = high_prec(1) - invg2;
    return C * safe_sqrt(beta2);
}

high_prec gamma_from_mass_radius(const high_prec &mass_kg, const high_prec &r_m) {
    if (r_m <= 0) return std::numeric_limits<high_prec>::infinity();
    high_prec Rs = (high_prec(2) * G * mass_kg) / (C * C);
    high_prec frac = Rs / r_m;
    if (frac >= 1) return std::numeric_limits<high_prec>::infinity();
    return high_prec(1) / safe_sqrt(high_prec(1) - frac);
}

high_prec mass_from_gamma_radius(const high_prec &gamma, const high_prec &r_m) {
    if (r_m <= 0) return high_prec(0);
    if (gamma <= 1) return high_prec(0);
    high_prec term = high_prec(1) - (high_prec(1) / (gamma * gamma));
    high_prec mass = ((C * C * r_m) / (high_prec(2) * G)) * term;
    return mass;
}

high_prec radius_from_gamma_mass(const high_prec &gamma, const high_prec &mass_kg) {
    if (mass_kg <= 0) return high_prec(0);
    if (gamma <= 1) return high_prec(0);
    high_prec gamma2 = gamma * gamma;
    high_prec base = (high_prec(2) * G * mass_kg) / (C * C);
    return base * (gamma2 / (gamma2 - high_prec(1)));
}

void print_val(const std::string &label, const high_prec &v, unsigned prec = 50) {
    std::cout << std::fixed << std::setprecision(prec) << label << v << std::endl;
}

int main() {
    std::cout << "Time Dilation V2" << std::endl;
    std::cout << "Choose mode:\n1) Relative velocity\n2) Gravitational potential (static observer)\n> ";
    int mainChoice = 0;
    if (!(std::cin >> mainChoice)) return 1;

    if (mainChoice == 1) {
        std::cout << "Velocity mode:\n1) Given velocity -> dilated time\n2) Given percentage of c -> dilated time\n3) Given Lorentz gamma -> velocity\n> ";
        int ch = 0; if (!(std::cin >> ch)) return 1;
        if (ch == 1) {
            std::cout << "Velocity (m/s): "; high_prec v; std::cin >> v;
            if (v >= C) { std::cerr << "Velocity must be less than c.\n"; return 1; }
            high_prec gamma = gamma_from_velocity(v);
            std::cout << "Proper time (seconds): "; high_prec tau; std::cin >> tau;
            high_prec dilated = gamma * tau;
            print_val("Dilated time (s): ", dilated);
            print_val("Lorentz factor: ", gamma, 20);
            return 0;
        } else if (ch == 2) {
            std::cout << "Percentage of c (0..100): "; high_prec pct; std::cin >> pct;
            if (pct <= 0 || pct >= 100) { std::cerr << "Percentage must be between 0 and 100 (exclusive).\n"; return 1; }
            high_prec v = (pct / high_prec(100)) * C;
            high_prec gamma = gamma_from_velocity(v);
            std::cout << "Proper time (seconds): "; high_prec tau; std::cin >> tau;
            high_prec dilated = gamma * tau;
            print_val("Dilated time (s): ", dilated);
            print_val("Lorentz factor: ", gamma, 20);
            return 0;
        } else if (ch == 3) {
            std::cout << "Lorentz factor (>1): "; high_prec gamma; std::cin >> gamma;
            if (gamma <= 1) { std::cerr << "Gamma must be > 1.\n"; return 1; }
            high_prec v = velocity_from_gamma(gamma);
            print_val("Velocity (m/s): ", v, 0);
            print_val("Percent of c: ", (v / C) * high_prec(100), 10);
            return 0;
        } else {
            std::cerr << "Invalid option.\n"; return 1;
        }
    }
    else if (mainChoice == 2) {
        std::cout << "Gravitational mode:\n1) Given mass (solar masses) & distance -> dilated time\n2) Given Lorentz gamma & distance -> mass (kg and solar masses)\n3) Given Lorentz gamma & mass -> distance (m and ly)\n> ";
        int ch = 0; if (!(std::cin >> ch)) return 1;
        if (ch == 1) {
            std::cout << "Mass (solar masses): "; high_prec ms; std::cin >> ms;
            std::cout << "Distance from mass (meter): "; high_prec r; std::cin >> r;
            if (r <= 0) { std::cerr << "Distance must be positive.\n"; return 1; }
            high_prec mass_kg = ms * SOLAR_MASS;
            high_prec Rs = (high_prec(2) * G * mass_kg) / (C * C);
            if (Rs >= r) { std::cerr << "Distance must be greater than Schwarzschild radius.\n"; return 1; }
            high_prec gamma = high_prec(1) / safe_sqrt(high_prec(1) - (Rs / r));
            std::cout << "Proper time (seconds): "; high_prec tau; std::cin >> tau;
            high_prec dilated = gamma * tau;
            print_val("Dilated time (s): ", dilated);
            print_val("Lorentz factor: ", gamma, 20);
            return 0;
        }
        else if (ch == 2) {
            std::cout << "Lorentz factor (>1): "; high_prec gamma; std::cin >> gamma;
            std::cout << "Distance from mass (meter): "; high_prec r; std::cin >> r;
            if (gamma <= 1 || r <= 0) { std::cerr << "Invalid inputs.\n"; return 1; }
            high_prec mass = mass_from_gamma_radius(gamma, r);
            high_prec mass_solar = mass / SOLAR_MASS;
            print_val("Mass (kg): ", mass, 0);
            print_val("Mass (solar masses): ", mass_solar, 12);
            return 0;
        }
        else if (ch == 3) {
            std::cout << "Lorentz factor (>1): "; high_prec gamma; std::cin >> gamma;
            std::cout << "Mass (solar masses): "; high_prec ms; std::cin >> ms;
            if (gamma <= 1 || ms <= 0) { std::cerr << "Invalid inputs.\n"; return 1; }
            high_prec mass_kg = ms * SOLAR_MASS;
            high_prec r = radius_from_gamma_mass(gamma, mass_kg);
            high_prec r_ly = r / LIGHT_YEAR;
            print_val("Distance (m): ", r, 0);
            print_val("Distance (light years): ", r_ly, 9);
            print_val("Mass (kg): ", mass_kg, 0);
            return 0;
        }
        else {
            std::cerr << "Invalid option.\n"; return 1;
        }
    }
    else {
        std::cerr << "Invalid main option.\n"; return 1;
    }

    return 0;
}
