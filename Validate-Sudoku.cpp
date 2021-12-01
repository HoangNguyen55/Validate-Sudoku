// Validate-Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hoang Nguyen - Cmpsc 122
// check if sudoku puzzle is valid

#include <iostream>
#include <vector>
#include <string>

std::string check(std::vector<int>&);

int main()
{
    std::string out;
    std::vector<int> rowsToTest[] = {
      {2, 2, 2, 5, 47, 7, 8, 9, 10},
      {0, 0, 0, 0},
      {1, 5, 6, 7, 8, 4, 2, 3, 9},
      {1, 1, 2, 4, 7, 2},
      {9, 6, 5, 4, 7, 2, 3, 4, 4, 18},
      {100, 2636, 24, 288, 3, 9, 7, 89},
      {98, 1, 3, 0, 7, 5, 9, 7, 2, 3},
      {1, 5, 6, 7, 8, 69, 73, 3, 69},
    };

    for (std::vector<int> row : rowsToTest)
    {
        out = "\nCurrent testing row: [";
        for (int val : row)
            out += " " + std::to_string(val) + ",";
        out.pop_back();
        std::cout << out << " ]\n";
        std::cout << check(row) << std::endl;
    }
}

std::string check(std::vector<int> &arr)
{
    std::string err = "";
    std::vector<int> appeared = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    bool happened = false;
    bool outOfRange = false;
    int x;
    if (arr.size() != 9)
        err += "The length of the row is not 9\n";

    for (int i = 0; i < arr.size(); i++)
    {
        x = arr[i];
        if ((x < 1 || x > 9) && !outOfRange)
        {
            err += "There is a number that is out of range from 1 to 9\n";
            outOfRange = true;
        }
        else if (x > 0 && x < 9)
        {
            if (appeared[x - 1] == x && !happened)
            {
                err += "There is a number in range that is repeated\n";
                happened = true;
            }
            else
                appeared[x - 1] = x;
        }
    }

    if (!err.length())
        err = "The row is valid";

    return err;
}