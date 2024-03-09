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

float mFinder(pair<Point, Point> &line)
{
    return (float) (line.second.y - line.first.y) / (line.second.x - line.first.x);
}

float cFinder(pair<Point, Point> &line)
{
    return (float) ((line.first.y) * (line.second.x) - (line.first.x) * (line.second.y))/(line.second.x - line.first.x);
}

float y_coord_finder(pair<Point, Point> &line, float x_coord)
{
    float m = mFinder(line);
    float c = cFinder(line);
    return m * x_coord + c;
}

Point intersection_finder(pair<Point, Point> &line1, pair<Point, Point> &line2)
{
    float m1 = mFinder(line1);
    float m2 = mFinder(line2);
    float c1 = cFinder(line1);
    float c2 = cFinder(line2);
    if (m1 == m2) {
        return (Point(-1.000123, -1.000123));
    }
    float x_coord = (c2 - c1) / (m1 - m2);
    float y_coord = (m1 * c2 - m2 * c1) / (m1 - m2);
    return Point(x_coord, y_coord);
}

bool checkIntersection(pair<Point, Point> &line1, pair<Point, Point> &line2, Point &intersection)
{
    if (intersection.x > line1.first.x && intersection.x < line1.second.x && intersection.x > line2.first.x && intersection.x < line2.second.x) {
        return false;
    }
    return true;
}

void whileLoopTask(pair<Point, Point> &line1, pair<Point, Point> &line2, vector<pair<Point, Point>> &rsl, int *p1, int *p2)
{
    if (line1.second.x <= line2.first.x) {
                rsl.push_back(line1);
                *p1++;
        } else {
            Point intersection = intersection_finder(line1, line2);
            if ((intersection.x == -1.000123 && intersection.y == -1.000123) || checkIntersection(line1, line2, intersection)) {
                if (line1.second.x < line2.second.x) {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        Point Point2 = Point(line1.second.x, y_coord_finder(line2, line1.second.x));
                        rsl.push_back(make_pair(line2.first, Point2));
                        line2.first = Point2;
                        *p1++;
                    } else {
                        rsl.push_back(line1);
                        *p1++;
                        line2.first = Point(line1.second.x, y_coord_finder(line2, line1.second.x));
                    }
                } else if (line1.second.x == line2.second.x) {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(line2);
                        *p1++;
                        *p2++;
                    } else {
                        rsl.push_back(line1);
                        *p1++;
                        *p2++;
                    }
                } else {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(line2);
                        Point Point2 = Point(line2.second.x, y_coord_finder(line1, line2.second.x));
                        *p2++;
                        line1.first = Point2;
                    } else {
                        Point Point1 = Point(line2.second.x, y_coord_finder(line1, line2.second.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        line1.first = Point1;
                        *p2++;
                    }
                }
            } else {
                if (line1.second.x < line2.second.x) {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(make_pair(line2.first, intersection));
                        rsl.push_back(make_pair(intersection, line1.second));
                        *p1++;
                        line2.first = Point(line1.second.x, y_coord_finder(line2, line1.second.x));
                    } else {
                        rsl.push_back(make_pair(line1.first, intersection));
                        Point Point1 = Point(line1.second.x, y_coord_finder(line2, line1.second.x));
                        rsl.push_back(make_pair(intersection, Point1));
                        *p1++;
                        line2.first = Point1;
                    }
                } else if (line1.second.x == line2.second.x) {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(make_pair(line2.first, intersection));
                        rsl.push_back(make_pair(intersection, line1.second));
                        *p1++;
                        *p2++;
                    } else {
                        rsl.push_back(make_pair(line1.first, intersection));
                        rsl.push_back(make_pair(intersection, line2.second));
                        *p1++;
                        *p2++;
                    }
                } else {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(make_pair(line2.first, intersection));
                        Point Point2 = Point(line2.second.x, y_coord_finder(line1, line2.second.x));
                        rsl.push_back(make_pair(intersection, Point2));
                        *p2++;
                        line1.first = Point2;
                    } else {
                        rsl.push_back(make_pair(line1.first, intersection));
                        rsl.push_back(make_pair(intersection, line2.second));
                        *p2++;
                        line1.first = Point(line2.second.x, y_coord_finder(line1, line2.second.x));
                    }
                }
            }
        }
}

vector<pair<Point, Point>> mergeSkylines(vector<pair<Point, Point>> &sl1, vector<pair<Point, Point>> &sl2)
{
    int p1 = 0, p2 = 0;
    vector<pair<Point, Point>> rsl;
    int size1 = sl1.size();
    int size2 = sl2.size();
    while (p1 < size1 && p2 < size2) {
        if (sl1[p1].first.x <= sl2[p2].first.x) {
            whileLoopTask(sl1[p1], sl2[p2], rsl, &p1, &p2);    
        } else {
            whileLoopTask(sl2[p2], sl1[p1], rsl, &p1, &p2);
        }
    }
    if (p1 == size1) {
        while (p2 < size2) {
            rsl.push_back(sl2[p2]);
            p2++;
        }
    } else {
        while (p1 < size1) {
            rsl.push_back(sl1[p1]);
            p1++;
        }
    }
    return rsl;
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

vector<pair<Point, Point>> getSkyline(vector<pair<Point, Point>> &intervals)
{
    vector<pair<Point, Point>> rsl = skyline(intervals, 0, intervals.size()-1);
    for (auto &elem : rsl) {
        cout << elem.first.x << "," << elem.first.y << " " << elem.second.x << "," << elem.second.y << endl;
    }
    return rsl;
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
	
	for (int fileIndex = 1; fileIndex <= 1; fileIndex++) {
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
        vector<pair<Point, Point>> sky_line = getSkyline(posters);
        float area = findArea(sky_line);

        outputFile << static_cast<int>(lengthCovered) << endl;
        outputFile << static_cast<int>(area) << endl;

        inputFile.close();
        outputFile.close();
    }
	return 0;
}