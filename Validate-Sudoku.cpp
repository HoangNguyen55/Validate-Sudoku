// Validate-Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hoang Nguyen - Cmpsc 122
// check if sudoku puzzle is valid

// include headers
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <chrono>
#include <thread>

// function prototypes
std::string validateRowsCols(std::vector<int>&);
void get_from_file(std::vector<std::vector<int>>&);
void get_sectors(std::vector<std::vector<int>>&, std::vector<std::vector<int>>&);
void get_cols_vec(std::vector<std::vector<int>>&, std::vector<std::vector<int>>&);

int main()
{
    // sleep variable for the sleep function
    // put to false to not sleep for faster program testing
    bool sleep = true;

    // declaring 2d vector variables
    std::vector<std::vector<int>> sudoku;
    std::vector<std::vector<int>> sectors_vec;
    std::vector<std::vector<int>> cols_vec;
    
    // process the text and populate the vectors
    // see function definition for more explaination
    get_from_file(sudoku);
    get_cols_vec(sudoku, cols_vec);
    get_sectors(sudoku, sectors_vec);

    // printing out the input sudoku puzzle
    for (int col = 0; col < 9; col++)
    {
        // print a line every 3 iterations for a more readable output
        if (col % 3 == 0) printf(" -----------------------------\n");

        for (int row = 0; row < 9; row++)
        {
            if (row % 3 == 0) printf("|");

            printf(" %d ", sudoku[col][row]);
        }
        printf("|\n");
    }
    printf("------------------------------\n");
    
    // print out the result of validation
    printf("\nValidating the sudoku puzzle:\n\n");
    for (int i = 0; i < 9; i++)
    {
        // validating rows, added a sleep function to make the validation feel slow
        // therefore adding a dramatic effect.
        if (sleep) std::this_thread::sleep_for(std::chrono::milliseconds(300));
        printf("Row %d: %s\n", i+1, validateRowsCols(sudoku[i]).c_str());
    }
    printf("------------------------------\n");
    for (int i = 0; i < 9; i++)
    {
        // validating column
        if (sleep) std::this_thread::sleep_for(std::chrono::milliseconds(300));
        printf("Column %d: %s\n", i+1, validateRowsCols(cols_vec[i]).c_str());
    }
    printf("------------------------------\n");
    for (int i = 0; i < 9; i++)
    {
        // validating Sectors
        if (sleep) std::this_thread::sleep_for(std::chrono::milliseconds(300));
        printf("Sector %d: %s\n", i+1, validateRowsCols(sectors_vec[i]).c_str());
    }

}

// read from a file
// using passing by reference to omit 
// creating a new vector variable and then returning it
void get_from_file(std::vector<std::vector<int>>& sudoku)
{
    std::string c;
    std::ifstream sudoku_file("sudoku.txt");
    
    for (int col = 0; col < 9; col++)
    {
        // add in an empty array into the 2d array
        sudoku.push_back(std::vector<int>());
        for (int row = 0; row < 9; row++)
        {
            // read a character
            sudoku_file >> c;
            // add it to the vector
            sudoku[col].push_back(std::stoi(c));
        }
    }
    sudoku_file.close();
}


// basically take the original sudoku puzzle and then put the columns as rows
// and rows as columns
// passing by reference for the same reason as above
void get_cols_vec(std::vector<std::vector<int>>& vec_to_get_cols, std::vector<std::vector<int>>& out)
{
    for (int row = 0; row < 9; row++)
    {
        out.push_back(std::vector<int>());
        for (int col = 0; col < 9; col++)
        {
            out[row].push_back(vec_to_get_cols[col][row]);
        }
    }
}

void get_sectors(std::vector<std::vector<int>>& vec_to_get_sector, std::vector<std::vector<int>>& out)
{
    // make a middle point every 3 cols of the original sudoku
    for (int sec_col = 1; sec_col <= 7; sec_col += 3)
    {
        // make a middle point every 3 rows of the original sudoku
        for (int sec_row = 1; sec_row <= 7; sec_row += 3)
        {
            // push a newly created vector into the 2d vector
            out.push_back(std::vector<int>());
            // start at the lower limit of the section (current middle point minus 1)
            // and keep iterating until the upper limit (current middle point plus 1)
            for (int col = sec_col - 1; col <= sec_col + 1; col++)
            {
                for (int row = sec_row - 1; row <= sec_row + 1; row++)
                {
                    // push the values into the most recently created vector
                    out.back().push_back(vec_to_get_sector[col][row]);
                }
            }
        }
    }
}

// clean up version of the sudoku validation from previous lab
// added the repeated number input the output
std::string validateRowsCols(std::vector<int>& arr)
{
    std::string err[2] = { "", "" };
    std::vector<int> appeared = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (const int& arrVal : arr)
    {
        if ((arrVal < 1 || arrVal > 9) )
        {
            err[0] += std::to_string(arrVal) + ", ";
        }
        else
        {
            if (appeared[arrVal - 1] == arrVal && err[1].find(std::to_string(arrVal)) == std::string::npos)
            {
                err[1] += std::to_string(arrVal) + ", ";
            }
            else
            {
                appeared[arrVal - 1] = arrVal;
            }
        }
    }


    if (err[0].length())
    {
        // 2 popback to remove the last two character ",[space]"
        err[0].pop_back();
        err[0].pop_back();
        err[0] += " is out of range from 1 to 9.\n";
    } 
    if (err[1].length())
    {
        err[1].pop_back();
        err[1].pop_back();
        err[1] += " is repeated.\n";
    }
    else if (!err[0].length())
    {
        err[0] += "Is valid\n";
    }

    return err[0] + err[1];
}