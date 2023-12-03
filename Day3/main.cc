#include <iostream>
#include <fstream>

std::vector<std::string> getInput(std::string inputPath) {
  std::vector<std::string> data;
  std::ifstream infile(inputPath);
  std::string line;

  if(infile.is_open()) {
    while(std::getline(infile, line)) {
      data.push_back(line);
    }
    infile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  return data;
}

bool isSymbol(const std::vector<std::string>& grid, int x, int y) {
  if (y < 0 || y >= grid.size() || x < 0 || x >= grid[0].length())
    return false;
  return !isdigit(grid[y][x]) && grid[y][x] != '.';
}

int isGear(const std::vector<std::string>& grid, int x, int y) {
  if (grid[y][x] != '*')
    return false;
  int firstAdjecentDigit = 0;
  int startY = y > 0 ? y - 1 : y;
  int startX = x > 0 ? x - 1 : x;
  int endY = y < grid.size() - 1 ? y + 1 : y;
  int endX = x < grid[0].length() - 1 ? x + 1 : x;
  for (int i = startY; i <= endY; i++) {
    for (int j = startX; j <= endX; j++) {
      if (isdigit(grid[i][j])) {
        int number = 0;
        int decimal = 1;
        for (int lookLeft = j; lookLeft >= 0; lookLeft--) // Read left part of number with temp index
          if (isdigit(grid[i][lookLeft])) {
            number += decimal * (grid[i][lookLeft] - '0');
            decimal *= 10;
          } else
            break;
        for (++j; j < grid[0].length(); j++) // Read right part of number with j index (Don't want to check it in outer loop again)
          if (isdigit(grid[i][j])) {
            number *= 10;
            number += grid[i][j] - '0';
          } else
            break;
        if (firstAdjecentDigit)
          return firstAdjecentDigit * number;
        else
          firstAdjecentDigit = number;
      }
    }
  }
  return 0;
}

int main() {
  int part1 = 0;
  int part2 = 0;

  std::vector<std::string> input = getInput("input.txt");

  int x, y = 0;
  for (const std::string& line : input) {
    x = 0;
    for (int x = 0; x < line.length(); x++) {
      if (int gearRatio = isGear(input, x, y)) {
        part2 += gearRatio;
        continue;
      }
      
      //Skip any non-gear, non-digit:
      if (!isdigit(line[x]))
        continue;
      
      bool isPartNumber = false;
      int number = 0;
      //If its a digit, check if it has symbol left to it
      for (int leftY = y - 1; leftY <= y + 1; leftY++)
        if (isSymbol(input, x-1, leftY))
          isPartNumber = true;
      //Read the whole number
      while (isdigit(line[x])) {
        number *= 10;
        number += line[x] - '0';
        // Check if digit has symbol above or below
        if (!isPartNumber)
          if (isSymbol(input, x, y-1) || isSymbol(input, x, y+1))
            isPartNumber = true;
        x++;
      }
      x--; // x is incremented one to much in while loop
      //Check if digit has symbol right to it
      if (!isPartNumber)
        for (int rightY = y - 1; rightY <= y + 1; rightY++)
          if (isSymbol(input, x+1, rightY))
            isPartNumber = true;
      
      if (isPartNumber)
        part1 += number;
    }
    y++;
  }

  std::cout << "Part 1: " << part1 << std::endl; 
  std::cout << "Part 2: " << part2 << std::endl; 
}
