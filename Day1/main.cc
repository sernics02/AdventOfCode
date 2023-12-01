#include <iostream>
#include "functions.h"

int main() {
  std::string inputFile = "input.txt";
  std::cout << "Total sum of calibration values: " << firstPart(inputFile) << std::endl;
  std::cout << "Total sum of calibration values: " << secondPart(inputFile) << std::endl;
  return 0;
}