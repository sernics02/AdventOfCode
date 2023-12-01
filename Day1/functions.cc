#include "functions.h"
#include <fstream>
#include <vector>
#include <iostream>

int firstPart(std::string& inputFile) {
  std::ifstream input(inputFile); 
  if (!input.is_open()) {
    std::cerr << "Error opening file." << std::endl;
    return 1;
  }

  int sum = 0;
  std::string line; 

  while (std::getline(input, line)) {
    for (const auto c : line) {
      if (isdigit(c)) {
        int firstDigit = c - '0';
        size_t lastDigitPos = line.find_last_of("0123456789");
        int lastDigit = line[lastDigitPos] - '0';
        int calibrationValue = firstDigit * 10 + lastDigit;
        sum += calibrationValue;

        break;
      }
    }
  }
  input.close();
  return sum;
}

int secondPart(std::string& inputFile) {
  std::ifstream input(inputFile);
  if (!input.is_open())
  {
    std::cerr << "Error opening file." << std::endl;
    return 1;
  }
  std::string line;
  int result = 0;
  while(std::getline(input, line)) {
    result += detectFirstNumber(line) * 10 + detectLastNumber(line);
  }
  return result;
}

int detectFirstNumber(std::string& line) {
  int indexFirst;
  for (int i = 0; i < line.length(); i++) {
    if (line[i] == 'o' && line[i+1] == 'n' && line[i+2] == 'e') {
      indexFirst = 1;
      break;
    } else if (line[i] == 't' && line[i+1] == 'w' && line[i+2] == 'o') {
      indexFirst = 2;
      break;
    } else if (line[i] == 't' && line[i+1] == 'h' && line[i+2] == 'r' && line[i+3] == 'e' && line[i+4] == 'e') {
      indexFirst = 3;
      break;
    } else if (line[i] == 'f' && line[i+1] == 'o' && line[i+2] == 'u' && line[i+3] == 'r') {
      indexFirst = 4;
      break;
    } else if (line[i] == 'f' && line[i+1] == 'i' && line[i+2] == 'v' && line[i+3] == 'e') {
      indexFirst = 5;
      break;
    } else if (line[i] == 's' && line[i+1] == 'i' && line[i+2] == 'x') {
      indexFirst = 6;
      break;
    } else if (line[i] == 's' && line[i+1] == 'e' && line[i+2] == 'v' && line[i+3] == 'e' && line[i+4] == 'n') {
      indexFirst = 7;
      break;
    } else if (line[i] == 'e' && line[i+1] == 'i' && line[i+2] == 'g' && line[i+3] == 'h' && line[i+4] == 't') {
      indexFirst = 8;
      break;
    } else if (line[i] == 'n' && line[i+1] == 'i' && line[i+2] == 'n' && line[i+3] == 'e') {
      indexFirst = 9;
      break;
    } else if (isdigit(line[i])) {
      indexFirst = std::stoi(line.substr(i, 1));
      break;
    }
  }
  return indexFirst;
}

int detectLastNumber(std::string& line) {
  int indexLast;
  for (int i = line.length() - 1; i >= 0; i--) {
    if (line[i] == 'o' && line[i+1] == 'n' && line[i+2] == 'e') {
      indexLast = 1;
      break;
    } else if (line[i] == 't' && line[i+1] == 'w' && line[i+2] == 'o') {
      indexLast = 2;
      break;
    } else if (line[i] == 't' && line[i+1] == 'h' && line[i+2] == 'r' && line[i+3] == 'e' && line[i+4] == 'e') {
      indexLast = 3;
      break;
    } else if (line[i] == 'f' && line[i+1] == 'o' && line[i+2] == 'u' && line[i+3] == 'r') {
      indexLast = 4;
      break;
    } else if (line[i] == 'f' && line[i+1] == 'i' && line[i+2] == 'v' && line[i+3] == 'e') {
      indexLast = 5;
      break;
    } else if (line[i] == 's' && line[i+1] == 'i' && line[i+2] == 'x') {
      indexLast = 6;
      break;
    } else if (line[i] == 's' && line[i+1] == 'e' && line[i+2] == 'v' && line[i+3] == 'e' && line[i+4] == 'n') {
      indexLast = 7;
      break;
    } else if (line[i] == 'e' && line[i+1] == 'i' && line[i+2] == 'g' && line[i+3] == 'h' && line[i+4] == 't') {
      indexLast = 8;
      break;
    } else if (line[i] == 'n' && line[i+1] == 'i' && line[i+2] == 'n' && line[i+3] == 'e') {
      indexLast = 9;
      break;
    } else if (isdigit(line[i])) {
      indexLast = std::stoi(line.substr(i, 1));
      break;
    }
  }
  return indexLast;
}