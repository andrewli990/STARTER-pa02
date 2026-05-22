#include "movies.h"

using namespace std;

bool compare(const pair<string, double>& a,
                const pair<string, double>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    }
    return a.first < b.first;
}