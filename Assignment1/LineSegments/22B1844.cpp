#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Point {
 public:
  double x;
  double y;

 public:
  Point()
      : x(0), y(0) {}  // Default constructor initializing coordinates to (0,0)
  Point(double xVal, double yVal)
      : x(xVal), y(yVal) {}  // Parameterized constructor

  double X() const { return x; }  // Accessor for x coordinate
  double Y() const { return y; }  // Accessor for y coordinate

};

/* FINDING THE LENGTH */

double findLength(vector<pair<Point, Point> > &intervals)
{
	double curr_x_max = 0;
	double rsl = 0;
    for (int i = 0; i < intervals.size(); i++) {
        pair<Point, Point> interval = intervals[i];
		double l = interval.first.x;
		double r = interval.second.x;
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

double mFinder(pair<Point, Point> &line)
{
    return (double) (line.second.y - line.first.y) / (line.second.x - line.first.x);
}

double cFinder(pair<Point, Point> &line)
{
    return (double) ((line.first.y) * (line.second.x) - (line.first.x) * (line.second.y))/(line.second.x - line.first.x);
}

double y_coord_finder(pair<Point, Point> &line, double x_coord)
{
    double m = mFinder(line);
    double c = cFinder(line);
    return m * x_coord + c;
}

Point intersection_finder(pair<Point, Point> &line1, pair<Point, Point> &line2)
{
    double m1 = mFinder(line1);
    double m2 = mFinder(line2);
    double c1 = cFinder(line1);
    double c2 = cFinder(line2);
    if (m1 == m2) {
        return (Point(-1.000123, -1.000123));
    }
    double x_coord = (c2 - c1) / (m1 - m2);
    double y_coord = (m1 * c2 - m2 * c1) / (m1 - m2);
    return Point(x_coord, y_coord);
}

bool checkIntersection(pair<Point, Point> &line1, pair<Point, Point> &line2, Point &intersection)
{
    if (intersection.x > line1.first.x && intersection.x < line1.second.x && intersection.x > line2.first.x && intersection.x < line2.second.x) {
        return false;
    }
    return true;
}

vector<pair<Point, Point> > mergeSkylines(vector<pair<Point, Point> > &sl1, vector<pair<Point, Point> > &sl2)
{
    int p1 = 0, p2 = 0;
    vector<pair<Point, Point> > rsl;
    int size1 = sl1.size();
    int size2 = sl2.size();
    while (p1 < size1 && p2 < size2) {
        pair<Point, Point> &a = sl1[p1];
        pair<Point, Point> &b = sl2[p2];
        pair<Point, Point> &line1 = (a.first.x <= b.first.x) ? sl1[p1] : sl2[p2];
        pair<Point, Point> &line2 = (a.first.x <= b.first.x) ? sl2[p2] : sl1[p1];
        if (line1.second.x <= line2.first.x) {
                rsl.push_back(line1);
                p1++;
        } else {
            Point intersection = intersection_finder(line1, line2);
            if ((intersection.x == -1.000123 && intersection.y == -1.000123) || checkIntersection(line1, line2, intersection)) {
                if (line1.second.x < line2.second.x) {
                    if (line2.first.y > y_coord_finder(line1, line2.first.x) || (line2.first.y == y_coord_finder(line1, line2.first.x) && line1.second.y <= y_coord_finder(line2, line1.second.y))) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        Point Point2 = Point(line1.second.x, y_coord_finder(line2, line1.second.x));
                        rsl.push_back(make_pair(line2.first, Point2));
                        line2.first = Point2;
                        p1++;
                    } else {
                        rsl.push_back(line1);
                        p1++;
                        line2.first = Point(line1.second.x, y_coord_finder(line2, line1.second.x));
                    }
                } else if (line1.second.x == line2.second.x) {
                    if (line2.first.y > y_coord_finder(line1, line2.first.x) || (line2.first.y == y_coord_finder(line1, line2.first.x) && line1.second.y <= y_coord_finder(line2, line1.second.y))) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(line2);
                        p1++;
                        p2++;
                    } else {
                        rsl.push_back(line1);
                        p1++;
                        p2++;
                    }
                } else {
                    if (line2.first.y > y_coord_finder(line1, line2.first.x) || (line2.first.y == y_coord_finder(line1, line2.first.x) && line1.second.y <= y_coord_finder(line2, line1.second.y))) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(line2);
                        Point Point2 = Point(line2.second.x, y_coord_finder(line1, line2.second.x));
                        p2++;
                        line1.first = Point2;
                    } else {
                        Point Point1 = Point(line2.second.x, y_coord_finder(line1, line2.second.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        line1.first = Point1;
                        p2++;
                    }
                }
            } else {
                if (line1.second.x < line2.second.x) {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(make_pair(line2.first, intersection));
                        rsl.push_back(make_pair(intersection, line1.second));
                        p1++;
                        line2.first = Point(line1.second.x, y_coord_finder(line2, line1.second.x));
                    } else {
                        rsl.push_back(make_pair(line1.first, intersection));
                        Point Point1 = Point(line1.second.x, y_coord_finder(line2, line1.second.x));
                        rsl.push_back(make_pair(intersection, Point1));
                        p1++;
                        line2.first = Point1;
                    }
                } else if (line1.second.x == line2.second.x) {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(make_pair(line2.first, intersection));
                        rsl.push_back(make_pair(intersection, line1.second));
                        p1++;
                        p2++;
                    } else {
                        rsl.push_back(make_pair(line1.first, intersection));
                        rsl.push_back(make_pair(intersection, line2.second));
                        p1++;
                        p2++;
                    }
                } else {
                    if (line2.first.y >= y_coord_finder(line1, line2.first.x)) {
                        Point Point1 = Point(line2.first.x, y_coord_finder(line1, line2.first.x));
                        rsl.push_back(make_pair(line1.first, Point1));
                        rsl.push_back(make_pair(line2.first, intersection));
                        Point Point2 = Point(line2.second.x, y_coord_finder(line1, line2.second.x));
                        rsl.push_back(make_pair(intersection, Point2));
                        p2++;
                        line1.first = Point2;
                    } else {
                        rsl.push_back(make_pair(line1.first, intersection));
                        rsl.push_back(make_pair(intersection, line2.second));
                        p2++;
                        line1.first = Point(line2.second.x, y_coord_finder(line1, line2.second.x));
                    }
                }
            }
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

vector<pair<Point, Point> > skyline(vector<pair<Point, Point> > &intervals, int i, int j)
{
    if (i >= j) {
        vector<pair<Point, Point> > rsl;
        rsl.push_back(intervals[i]);
        return rsl;
    }
    int mid = (i + j) / 2;
    vector<pair<Point, Point> > sl1 = skyline(intervals, i, mid);
    vector<pair<Point, Point> > sl2 = skyline(intervals, mid + 1, j);
    return mergeSkylines(sl1, sl2);
}

vector<pair<Point, Point> > getSkyline(vector<pair<Point, Point> > &intervals)
{
    vector<pair<Point, Point> > rsl = skyline(intervals, 0, intervals.size()-1);
    return rsl;
}

double findArea(vector<pair<Point, Point> > &skyline)
{
    double rsl = 0;
    for (int i = 0; i < skyline.size(); i++) {
        pair<Point, Point> line = skyline[i];
        rsl += 0.5 * (line.first.y + line.second.y) * (line.second.x - line.first.x);
    }
	return rsl;
}

bool compareFirstX(const std::pair<Point, Point>& p1, const std::pair<Point, Point>& p2) {
    return p1.first.x < p2.first.x;
}

int main()
{
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	
    int n;
    cin >> n;
    double a, b, c, d;

    vector<pair<Point, Point> > posters;

    for (int i = 0; i < n; i++) {
        cin >> a >> b >> c >> d;
        posters.push_back(make_pair(Point(a, b), Point(c, d)));
    }

    std::sort(posters.begin(), posters.end(), compareFirstX);

    double lengthCovered = findLength(posters);
    vector<pair<Point, Point> > sky_line = getSkyline(posters);
    double area = findArea(sky_line);

    std::cout << static_cast<int>(lengthCovered) << endl;
    std::cout << static_cast<int>(area) << endl;

	return 0;
}