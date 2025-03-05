#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "TimeCode.h"

using namespace std;

// Function to extract hours and minutes from a timestamp string
TimeCode extractTime(const string &timestamp) {
    size_t colonPos = timestamp.find(':');
    int hrs = stoi(timestamp.substr(0, colonPos));
    int mins = stoi(timestamp.substr(colonPos + 1, 2));
    return TimeCode(hrs, mins, 0);
}

// Function to split a string into parts based on a delimiter
vector<string> breakIntoParts(const string &text, char delimiter) {
    vector<string> parts;
    string part;
    istringstream stream(text);
    while (getline(stream, part, delimiter)) {
        parts.push_back(part);
    }
    return parts;
}

int main() {
    ifstream dataFile("Space_Corrected.csv");

    if (!dataFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string header;
    getline(dataFile, header); // Skip the header line

    TimeCode cumulativeTime(0, 0, 0);
    int entriesProcessed = 0;

    string row;
    while (getline(dataFile, row)) {
        vector<string> columns = breakIntoParts(row, ',');

        if (columns.size() > 4 && columns[4].find("UTC") != string::npos) {
            string timeStr = columns[4].substr(5, 6); // Extract the time part
            TimeCode currentTime = extractTime(timeStr);
            cumulativeTime = cumulativeTime + currentTime;
            entriesProcessed++;
        }
    }

    if (entriesProcessed > 0) {
        TimeCode meanTime = cumulativeTime / entriesProcessed;
        cout << "Total entries analyzed: " << entriesProcessed << endl;
        cout << "Mean time: " << meanTime.ToString() << endl;
    } else {
        cout << "No valid entries found." << endl;
    }

    dataFile.close();
    return 0;
}