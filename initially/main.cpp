#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

/* -------------------- DATA STRUCTURES -------------------- */

struct Stop {
    int id;
    string name;
    string area;
    int students;
};

struct Bus {
    int number;                 // ❌ Random number, can collide
    int capacity;
    int studentsCarried;
    vector<int> stopIds;
};

/* -------------------- GLOBAL DATA -------------------- */

vector<Stop> stops;
vector<Bus> buses;

/* -------------------- RANDOM BUS NUMBER (BUGGY) -------------------- */

int generateRandomBusNumber() {
    // ❌ No uniqueness check
    return rand() % 9000 + 1000;
}

/* -------------------- STUDENT DISTRIBUTION -------------------- */

void distributeStudents() {
    vector<float> ratios = {1.5, 2.0, 1.0, 2.5};
    float sum = 0;

    for (float r : ratios)
        sum += r;

    for (int i = 0; i < stops.size(); i++) {
        stops[i].students = (int)((ratios[i] / sum) * 2000);
    }
}

/* -------------------- BUS ALLOCATION -------------------- */

void allocateBuses() {
    for (auto& stop : stops) {
        int remaining = stop.students;

        while (remaining > 0) {
            Bus b;
            b.number = generateRandomBusNumber();
            b.capacity = 30;
            b.studentsCarried = min(30, remaining);
            b.stopIds.push_back(stop.id);

            remaining -= b.studentsCarried;
            buses.push_back(b);
        }
    }
}

/* -------------------- DISPLAY FUNCTIONS -------------------- */

void showBusDetails() {
    cout << "\n===== BUS DETAILS =====\n";

    for (auto& b : buses) {
        cout << "Bus " << b.number
             << " | Capacity: " << b.capacity
             << " | Carrying: " << b.studentsCarried << " students\n";

        for (int id : b.stopIds) {
            // ❌ BUG: assumes stop.id == index in vector
            cout << "  - Stop: " << stops[id].name << "\n";
        }
        cout << "----------------------\n";
    }
}

/* -------------------- MAIN FUNCTION -------------------- */

int main() {
    srand(time(0));

    // Stops with NON-SEQUENTIAL IDs (causes bug)
    stops.push_back({101, "Main Gate", "North Campus", 0});
    stops.push_back({205, "Library", "Central Campus", 0});
    stops.push_back({309, "Hostel", "East Wing", 0});
    stops.push_back({412, "Sports Complex", "South Zone", 0});

    distributeStudents();
    allocateBuses();
    showBusDetails();

    return 0;
}