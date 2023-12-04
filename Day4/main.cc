#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>

int main() {
  std::string line, num;
  std::ifstream file("input.txt");
  int p1 = 0;
  while (std::getline(file, line)) {
    std::string win = line.substr(line.find(":") + 2, line.find("|") - line.find(":") - 3);
    std::set<int> winNums;
    for (int i = 0; i < win.size(); i += 3) {
      winNums.insert(stoi(win.substr(i, 2)));
    }

    std::string pull = line.substr(line.find("|") + 2, line.size() - line.find("|"));
    std::set<int> pullNums;
    for (int i = 0; i < pull.size(); i += 3) {
      pullNums.insert(stoi(pull.substr(i, 2)));
    }

    std::vector<int> isect;
    std::set_intersection(winNums.begin(), winNums.end(), pullNums.begin(), pullNums.end(), back_inserter(isect));
    if (isect.size() > 0)
      p1 += 1 << (isect.size() - 1);
  }
  std::cout << p1 << std::endl;
  file.close();
  return 0;
}