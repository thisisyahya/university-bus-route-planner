#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <map>
#include <random>
using namespace std;

// ===================== CLASS Stop ============================
class Stop {
public:
    int id;
    string name;
    string area;
    int students;

    Stop(int id, string name, string area, int students)
        : id(id), name(name), area(area), students(students) {}
};

// ===================== CLASS Bus =============================
class Bus {
public:
    string number;
    vector<int> stopIds;
    int capacity;
    int studentsCarried;   // NEW FEATURE

    Bus(string num, vector<int> stops, int cap, int sc)
        : number(num), stopIds(stops), capacity(cap), studentsCarried(sc) {}
};

// ===================== TIME UTILITY ==========================
string addTime(string base, int mins) {
    int h = stoi(base.substr(0, 2));
    int m = stoi(base.substr(3, 2));

    m += mins;
    h += m / 60;
    m %= 60;

    stringstream ss;
    ss << setw(2) << setfill('0') << (h % 24)
       << ":" << setw(2) << setfill('0') << m;
    return ss.str();
}

// ===================== CLASS UniversityTransport =============
class UniversityTransport {
private:
    vector<Stop> stops;
    vector<Bus> buses;

    // Generate random bus number (NEW FEATURE)
    string generateRandomBusNumber() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1000, 9999);

        int num = dist(gen);

        stringstream ss;
        ss << "RND-" << num;
        return ss.str();
    }

public:
    void addStop(Stop s) {
        stops.push_back(s);
    }

    // AUTO BUS CREATION WITH LOAD SPLITTING
    void createBusesAutomatically() {
        for (auto &s : stops) {

            int required = ceil((double)s.students / 30.0);
            int remaining = s.students;

            cout << "Stop: " << s.name
                 << " | Students: " << s.students
                 << " | Buses Needed: " << required << "\n";

            for (int i = 0; i < required; i++) {

                int load = min(30, remaining);
                remaining -= load;

                buses.push_back(
                    Bus(
                        generateRandomBusNumber(),  // NEW RANDOM NUMBER
                        {s.id},
                        30,
                        load                       // NEW student load
                    )
                );
            }
        }

        cout << "\nTotal Buses Created: " << buses.size() << "\n\n";
    }

    // BUS DETAILS
    void showBusDetails() {
        cout << "\n================ BUS DETAILS ================\n";

        for (auto &b : buses) {
            cout << "Bus " << b.number
                 << " | Capacity: " << b.capacity
                 << " | Carrying: " << b.studentsCarried << " students\n";

            for (int id : b.stopIds) {
                cout << "  - Stop: " << stops[id].name 
                     << " (" << stops[id].area << ")\n";
            }

            cout << "\n";
        }
    }

    // SUMMARY
    void studentSummary() {
        cout << "================ STUDENT SUMMARY ================\n";

        map<string, int> areaCount;
        int total = 0;

        for (auto &s : stops) {
            areaCount[s.area] += s.students;
            total += s.students;
        }

        cout << "Total University Students: " << total << "\n";
        for (auto &x : areaCount)
            cout << "  - " << x.first << ": " << x.second << "\n";

        cout << "\n";
    }

    // TIMETABLE
    void timetable(string title, string start, int gap) {
        cout << "\n================ " << title << " ================\n";

        for (auto &b : buses) {
            cout << "Bus " << b.number << " (Carrying " 
                 << b.studentsCarried << " students)\n";

            string t = start;
            for (int id : b.stopIds) {
                t = addTime(t, gap);
                cout << "  - " << stops[id].name << " at " << t << "\n";
            }

            cout << "\n";
        }
    }

    // SHOW EVERYTHING
    void showAll() {
        studentSummary();
        showBusDetails();
        timetable("MORNING ROUTE (06:30)", "06:30", 4);
        timetable("AFTERNOON ROUTE (12:30)", "12:30", 5);
        timetable("RETURN ROUTE (15:30)", "15:30", 6);
    }
};

// ========================== MAIN ============================
int main() {
    UniversityTransport uni;

    vector<double> ratio = {12,9,8,6,11,10,7};
    double sum = 0;
    for (double r : ratio) sum += r;

    vector<int> stu;
    for (double r : ratio)
        stu.push_back((int)((r/sum)*2000));

    uni.addStop(Stop(0,"Islamabad (Kashmir Hwy)","Islamabad", stu[0]));
    uni.addStop(Stop(1,"I-10 / CDA Stop","Rawalpindi", stu[1]));
    uni.addStop(Stop(2,"6th Road (Peshawar Rd)","Rawalpindi", stu[2]));
    uni.addStop(Stop(3,"Shamsabad / 502 Stop","Rawalpindi", stu[3]));
    uni.addStop(Stop(4,"Ghazali School / Dhok Kalaal","Wah Cantt", stu[4]));
    uni.addStop(Stop(5,"GT Road Westridge","Rawalpindi", stu[5]));
    uni.addStop(Stop(6,"Wah Cantt / Taxila Phase-II","Taxila", stu[6]));

    uni.createBusesAutomatically();
    uni.showAll();

    return 0;
}