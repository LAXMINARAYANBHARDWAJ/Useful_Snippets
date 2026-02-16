//There is a slight error in this code. If we do not enter all the required 13 decimals, or if we enter zeros instead of actual/real numbers, then the values ARE affected.

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double time;
    cout << "Time(seconds): ";
    cin >> time;

    int hour =  time / 3600;
    time = time - (hour * 3600);
    
    if (hour <= 1) {
        cout << endl << hour << "hr ";
    }
    else {
        cout << endl << hour << "hrs ";
    }

    int minute = time / 60;
    time = time - (minute * 60);
    cout << minute << "min ";

    int second = time / 1;
    time = (time - second) * 1000;
    cout << second << "sec ";

    int millisecond = time / 1;
    time = (time - millisecond) * 1000;
    cout << millisecond << "ms ";

    int microsecond = time / 1;
    time = (time - microsecond) * 1000;
    cout << microsecond << "mcs ";

    int nanosecond = time / 1;
    time = (time - nanosecond) * 1000;
    cout << nanosecond << "ns ";

    int picosecond = time / 1;
    time = (time - picosecond) * 1000;
    cout << picosecond << "ps " << endl;

    return 0;
}

