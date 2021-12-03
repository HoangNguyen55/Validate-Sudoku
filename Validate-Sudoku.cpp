// Validate-Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hoang Nguyen - Cmpsc 122
// check if sudoku puzzle is valid

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

std::string validateRowsCols(std::vector<int>&);
void get_from_file(int(&sudoku)[9][9]);

int main()
{
    int sudoku[9][9];
    get_from_file(sudoku);

    


}

void get_from_file(int (&sudoku)[9][9])
{
    std::string c;
    std::ifstream sudoku_file("sudoku.txt");
    for (int j = 0; j < 9; j++)
    {
        for (int i = 0; i < 9;)
        {
            sudoku_file >> c;
            sudoku[j][i] = std::stoi(c);
            i++;

        }
    }
    sudoku_file.close();
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
            if (appeared[arrVal - 1] == arrVal && err[1].find(std::to_string(arrVal)) == std::string::npos)
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