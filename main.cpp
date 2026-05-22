// Spring '26
// Instructor: Diba Mirza
// Student name: Andrew Li
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <map>
#include <queue>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies

    map<string , double> movieList;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        movieList[movieName] = movieRating;
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
    }

    movieFile.close();

    if (argc == 2){
        for (auto& movie : movieList) {
            cout << movie.first << ", " << movie.second << endl;
        }
            //print all the movies in ascending alphabetical order of movie names
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message


    for (auto prefix : prefixes) {

        bool match = false;

        vector<pair<string, double>> matchMovies;

        vector<pair<string, double>> bestMovies;


        for (auto& movie : movieList) {
            if (movie.first.find(prefix) == 0) {
                matchMovies.push_back(movie);
                match = true;
            }
        }

        if (match == false) {
            cout << "No movies found with prefix "<< prefix << "." << endl;
        }

        sort(matchMovies.begin(), matchMovies.end(), compare);

        for (auto& movie: matchMovies) {
            bestMovies.push_back({movie.first, movie.second});
        }

        for (auto& bestMovie : bestMovies) {
            cout << "Best movie with prefix " << prefix << " is: " << bestMovie.first << " with rating " << std::fixed << std::setprecision(1) << bestMovie.second << endl;

        }
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.

    return 0;
    }

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}