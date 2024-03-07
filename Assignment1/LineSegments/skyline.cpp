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

float findLength(vector<pair<Point, Point>> &intervals)
{
	float curr_x_max = 0;
	float rsl = 0;
	for (auto &interval: intervals) {
		float l = interval.first.x;
		float r = interval.second.x;
		if (r > curr_x_max) {
			if (l > curr_x_max) {
				rsl += (r - l);
			} else {
				rsl += r - curr_x_max;
			}
			curr_x_max = r;
		}
	}
	return rsl;
}

float findArea(vector<pair<Point, Point>> &intervals)
{
	if (intervals[0].first.x == 0) {
        
	}
	return 0;
}

int main()
{
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	
	for (int fileIndex = 1; fileIndex <= 10; fileIndex++) {
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

		std::sort(posters.begin(), posters.end(), [](const auto& p1, const auto& p2) {
    	    return p1.first.x < p2.first.x;
	    });


        float lengthCovered = findLength(posters);
        float area = findArea(posters);

        outputFile << static_cast<int>(lengthCovered) << endl;
        outputFile << static_cast<int>(area) << endl;

        inputFile.close();
        outputFile.close();
    }

	return 0;
}