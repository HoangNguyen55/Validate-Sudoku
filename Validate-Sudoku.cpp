// Validate-Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hoang Nguyen - Cmpsc 122
// check if sudoku puzzle is valid

#include <iostream>
#include <vector>
#include <string>

std::string validateRowsCols(std::vector<int>&);

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
        std::cout << validateRowsCols(row) << std::endl;
    }
}

std::string validateRowsCols(std::vector<int>& arr)
{
    std::string err[2] = { "", "" };
    std::vector<int> appeared = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (const int& arrVal : arr)
    {
        if ((arrVal < 1 || arrVal > 9) )
        {
            err[0] += " " + std::to_string(arrVal) + ",";
        }
        else
        {
            // check if repeated value is already in the string
            if (appeared[arrVal - 1] == arrVal)
            {
                err[1] += " " + std::to_string(arrVal) + ",";
            }
            else
            {
                appeared[arrVal - 1] = arrVal;
            }
        }
    }


    if (err[0].length())
    {
        err[0].pop_back();
        err[0] += " is out of range from 1 to 9.\n";
    } 
    if (err[1].length())
    {
        err[1].pop_back();
        err[1] += " is repeated.\n";
    }
    else if (!err[0].length())
    {
        err[0] += "Is valid\n";
    }

    return err[0] + err[1];
}