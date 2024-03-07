#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <cmath>

using namespace std;

void safePush(vector<vector<int>> &rsl, vector<int> &vec)
{
  if (rsl.size() == 0) {
    rsl.push_back(vec);
    return;
  }
  if (rsl[rsl.size() - 1][1] != vec[1] && rsl[rsl.size() - 1][0] != vec[0]) {
    rsl.push_back(vec);
  }
}

vector<vector<int>> mergeSkylines(vector<vector<int>> &sl1, vector<vector<int>> &sl2)
{
  int height1 = 0, height2 = 0;
  int p1 = 0, p2 = 0;
  vector<vector<int>> rsl;
  while (p1 < sl1.size() && p2 < sl2.size()) {
    vector<int> buil1 = sl1[p1];
    vector<int> buil2 = sl2[p2];
    int x = 0;
    if (buil1[0] < buil2[0] || (buil1[0] == buil2[0] && buil1[1] == buil2[1] && height1 < height2) || (buil1[0] == buil2[0] && buil1[1] > buil2[1])) {
      x = buil1[0];
      p1++;
      height1 = buil1[1];
    } else {
      x = buil2[0];
      p2++;
      height2 = buil2[1];
    }
    int y = max(height1, height2);
    vector<int> newPoint {x,y};
    safePush(rsl, newPoint);
  }
  if (p1 == sl1.size()) {
    while (p2 < sl2.size()) {
      safePush(rsl, sl2[p2]);
      p2++;
    }
  } else {
    while (p1 < sl1.size()) {
      safePush(rsl, sl1[p1]);
      p1++;
    }
  }
  return rsl;
}

vector<vector<int>> skyline(vector<vector<int>>& buildings, int i, int j)
{
  if (i >= j) {
    vector<vector<int>> rsl;
    vector<int> building = buildings[i];
    rsl.push_back(vector<int>{building[0], building[2]});
    rsl.push_back(vector<int>{building[1], 0});
    return rsl;
  }
  int mid = (i + j) / 2;
  vector<vector<int>> sl1 = skyline(buildings, i, mid);
  vector<vector<int>> sl2 = skyline(buildings, mid + 1, j);
  return mergeSkylines(sl1, sl2);
}

vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
{
  return skyline(buildings, 0, buildings.size()-1);
}

int main()
{
  vector<vector<int>> buildings {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
  vector<vector<int>> rsl = getSkyline(buildings);
  for (auto &elem : rsl) {
    for (auto &num : elem) {
      cout << num << " ";
    }
    cout << endl;
  }
  return 0;
}
