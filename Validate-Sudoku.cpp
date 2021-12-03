// Validate-Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hoang Nguyen - Cmpsc 122
// check if sudoku puzzle is valid

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

std::string validateRowsCols(std::vector<int>&);
void get_from_file(std::vector<std::vector<int>>&);
void get_sectors(std::vector<std::vector<int>>&, std::vector<std::vector<int>>&);

int main()
{
    //int sudoku[9][9];
    std::vector<std::vector<int>> sudoku;
    std::vector<std::vector<int>> sectors_vec;
    get_from_file(sudoku);
    for (int col = 0; col < 9; col++)
    {
        printf("[ ");
        for (int row = 0; row < 9; row++)
        {
            printf(" %d, ", sudoku[col][row]);
        }
        printf(" ]\n");
    }
    get_sectors(sudoku, sectors_vec);
    

    printf("----------------------------------------\n");

    for (int col = 0; col < 9; col++)
    {
        printf("[ ");
        for (int row = 0; row < 9; row++)
        {
            printf(" %d, ", sectors_vec[col][row]);
        }
        printf(" ]\n");
    }
}

void get_from_file(std::vector<std::vector<int>>& sudoku)
{
    std::string c;
    std::ifstream sudoku_file("sudoku.txt");
    for (int col = 0; col < 9; col++)
    {
        sudoku.push_back(std::vector<int>());
        for (int row = 0; row < 9; row++)
        {
            sudoku_file >> c;
            sudoku[col].push_back(std::stoi(c));
        }
    }
    sudoku_file.close();
}

// TODO: FIX LOGIC ERROR
void get_sectors(std::vector<std::vector<int>>& vec_to_get_sector, std::vector<std::vector<int>>& out)
{
    for (int sec_col = 1; sec_col <= 7; sec_col += 3)
    {
        for (int sec_row = 1; sec_row <= 7; sec_row += 3)
        {
            out.push_back(std::vector<int>());
            for (int col = sec_row - 1; col <= sec_row + 1; col++)
            {
                for (int row = sec_row - 1; row <= sec_row + 1; row++)
                {
                    out.back().push_back(vec_to_get_sector[col][row]);
                }
            }
        }
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