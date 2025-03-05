#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)


using namespace std;

// Struct to represent a drying batch with a name, start time, and drying duration
struct DryingSnapShot {
    string name;
    time_t startTime;
    TimeCode *timeToDry;
};

// Calculates the remaining drying time by subtracting elapsed time from total drying duration
long long int get_time_remaining(DryingSnapShot dss){
    time_t elapsed = time(0) - dss.startTime;
    long long int remaining = dss.timeToDry->GetTImeCodeAsSeconds() - elapsed;
    return (remaining > 0) ? remaining : 0;
}

// Converts a DryingSnapShot struct into a readable string format
string drying_snap_shot_to_string(DryingSnapShot dss){
    long long int remaining = get_time_remaining(dss);
    TimeCode remaining_time(0, 0, remaining);
    return dss.name + " time remaining: " + remaining_time.ToString();
}

// Calculates the surface area of a sphere given its radius
double get_sphere_sa(double rad){
    return 4 * M_PI * rad * rad;
}

// Creates a dynamically allocated TimeCode object based on the given surface area
TimeCode *compute_time_code(double surfaceArea){
    return new TimeCode(0, 0, static_cast<long long unsigned int>(surfaceArea));
}

// Test function to verify correctness of calculations
void tests(){
    DryingSnapShot dss;
    dss.startTime = time(0);
    TimeCode tc = TimeCode(0, 0, 7);
    dss.timeToDry = &tc;
    long long int ans = get_time_remaining(dss);
    assert(ans > 6 && ans < 8);

    double sa = get_sphere_sa(2.0);
    assert (50.2654 < sa && sa < 50.2655);

    TimeCode *tc2 = compute_time_code(1.0);
    assert(tc2->GetTImeCodeAsSeconds() == 1);
    delete tc2;

    cout << "ALL TESTS PASSED!" << endl;
}

// Main function to handle user interaction for tracking drying times of paint batches
int main(){
    vector<DryingSnapShot> batches;
    char choice;

    do {
        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
        cin >> choice;

        if (choice == 'A' || choice == 'a') {
            double radius;
            cout << "Enter radius: ";
            cin >> radius;
            string batch_name = "Batch-" + to_string(rand());
            DryingSnapShot batch;
            batch.name = batch_name;
            batch.startTime = time(0);
            batch.timeToDry = compute_time_code(get_sphere_sa(radius));
            batches.push_back(batch);
        }
        else if (choice == 'V' || choice == 'v') {
            for (auto it = batches.begin(); it != batches.end();) {
                if (get_time_remaining(*it) == 0) {
                    cout << it->name << " DONE!" << endl;
                    delete it->timeToDry;
                    it = batches.erase(it);
                } else {
                    cout << drying_snap_shot_to_string(*it) << endl;
                    ++it;
                }
            }
            cout << batches.size() << " batches being tracked." << endl;
        }
    } while (choice != 'Q' && choice != 'q');

    // Clean up remaining dynamically allocated memory
    for (auto &batch : batches) delete batch.timeToDry;

    return 0;
}
