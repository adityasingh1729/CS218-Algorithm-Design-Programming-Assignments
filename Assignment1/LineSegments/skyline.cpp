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

/* FINDING THE LENGTH */

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

/* FINDING THE AREA */

vector<pair<Point, Point>> mergeSkylines(vector<pair<Point, Point>> &sl1, vector<pair<Point, Point>> &sl2)
{
    
}

vector<pair<Point, Point>> skyline(vector<pair<Point, Point>> &intervals, int i, int j)
{
    if (i >= j) {
        vector<pair<Point, Point>> rsl;
        rsl.push_back(intervals[i]);
        return rsl;
    }
    int mid = (i + j) / 2;
    vector<pair<Point, Point>> sl1 = skyline(intervals, i, mid);
    vector<pair<Point, Point>> sl2 = skyline(intervals, mid + 1, j);
    return mergeSkylines(sl1, sl2);
}

float findArea(vector<pair<Point, Point>> &skyline)
{
    float rsl = 0;
    for (auto &line : skyline) {
        rsl += 0.5 * (line.first.y + line.second.y) * (line.second.x - line.first.x);
    }
	return rsl;
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
        vector<pair<Point, Point>> sky_line = skyline(posters, 0, posters.size()-1);
        float area = findArea(sky_line);

        outputFile << static_cast<int>(lengthCovered) << endl;
        outputFile << static_cast<int>(area) << endl;

        inputFile.close();
        outputFile.close();
    }

	return 0;
}