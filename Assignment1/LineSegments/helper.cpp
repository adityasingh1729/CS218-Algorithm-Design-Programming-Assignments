#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

class Point {
 public:
  float x;
  float y;

 public:
  Point()
      : x(0), y(0) {}  // Default constructor initializing coordinates to (0,0)
  Point(float xVal, float yVal)
      : x(xVal), y(yVal) {}  // Parameterized constructor

  float X() const { return x; }  // Accessor for x coordinate
  float Y() const { return y; }  // Accessor for y coordinate

};


int main(){
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	
	for (int fileIndex = 1; fileIndex <= 2; fileIndex++) {
        string inputFileName = "inputs/input" + to_string(fileIndex) + ".txt";
        string outputFileName = "myoutput/out" + to_string(fileIndex) + ".txt";

        ifstream inputFile(inputFileName);
        ofstream outputFile(outputFileName);

        if (!inputFile.is_open() || !outputFile.is_open()) {
            cerr << "Error opening input or output file!" << endl;
            return 1;
        }

        int n;
        inputFile >> n;
        float a, b, c, d;

        vector<pair<Point, Point>> posters;

        for (int i = 0; i < n; i++) {
            inputFile >> a >> b >> c >> d;
            posters.push_back(make_pair(Point(a, b), Point(c, d)));
        }

        float lengthCovered = 0;
        float area = 0;

        outputFile << static_cast<int>(lengthCovered) << endl;
        outputFile << static_cast<int>(area) << endl;

        inputFile.close();
        outputFile.close();
    }

	return 0;
}

