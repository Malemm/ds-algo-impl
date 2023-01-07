/*
Sudoku solver with recursive backtracking algorithm.
As taught in https://www.youtube.com/watch?v=G_UYXzGuqvM

Give input in the following format.
9 whitespace separated values form each row.
Fill '0' to represent blank cell.
Example:

5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9

*/

#include <iostream>

using namespace std;

void solveSudoku();
bool isNumPosAllowed(int x, int y, int v);
void printBoard();

static int board[9][9] = {0};
static int solutionCount = 0;

int main()
{
    cout << "~ Sudoku Solver ~" << endl;

    cout << "Enter sudoku: " << endl;

    for (int i = 0; i < 9; i++)
    {
        scanf("%d%d%d%d%d%d%d%d%d", &board[i][0], &board[i][1], &board[i][2], &board[i][3], &board[i][4], &board[i][5], &board[i][6], &board[i][7], &board[i][8]);
    }

    cout << endl
         << "Input:" << endl;

    printBoard();

    solveSudoku();

    if (solutionCount == 0)
    {
        cout << endl
             << "No solution found! Please check the input." << endl;
    }

    return 0;
}

void solveSudoku()
{
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (board[x][y] == 0)
            {
                for (int i = 1; i <= 9; i++)
                {
                    if (isNumPosAllowed(x, y, i))
                    {
                        board[x][y] = i;
                        solveSudoku();
                        board[x][y] = 0;
                    }
                }
                return; // backtrack; no number can be filled in this spot
            }
        }
    }

    // it would never reach here when no solution is found
    // the 'return' statement would hit all the way down the stack when no element can be found to complete the board
    solutionCount++;
    cout << endl
         << "Solution " << solutionCount << endl;
    printBoard();
    cout << endl;
}

bool isNumPosAllowed(int x, int y, int v)
{
    // check row
    for (int j = 0; j < 9; j++)
    {
        if (board[x][j] == v)
        {
            return false;
        }
    }

    // check column
    for (int i = 0; i < 9; i++)
    {
        if (board[i][y] == v)
        {
            return false;
        }
    }

    // check local sub-square
    int x_local = (x / 3) * 3;
    int y_local = (y / 3) * 3;

    for (int i = x_local; i < x_local + 3; i++)
    {
        for (int j = y_local; j < y_local + 3; j++)
        {
            if (board[i][j] == v)
            {
                return false;
            }
        }
    }

    return true;
}

void printBoard()
{
    cout << endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j == 3 || j == 6)
            {
                cout << " |";
            }

            cout << " " << board[i][j];

            // // print opening bracket "["
            // if (i == 0 && j == 0)
            // {
            //     cout << "[ ";
            // }
            // else if (j == 0)
            // {
            //     cout << "  ";
            // }

            // // print comma separated value
            // if (j == 8)
            // {
            //     cout << board[i][j];
            // }
            // else
            // {
            //     cout << board[i][j] << ", ";
            // }

            // // print closing bracket "]"
            // if (i == 8 && j == 8)
            // {
            //     cout << " ]";
            // }
        }
        cout << endl;
        if (i == 2 || i == 5)
        {
            cout << " ---------------------" << endl;
        }
    }
}

// bool validateSolution()
// {
//     // check rows and columns: the sum of elements in each row and column should be 45
//     for (int x = 0; x < 9; x++)
//     {
//         int row_sum = 0, col_sum = 0;
//         for (int y = 0; y < 9; y++)
//         {
//             row_sum += board[x][y];
//         }
//         for (int y = 0; y < 9; y++)
//         {
//             col_sum += board[y][x];
//         }
//         if (row_sum != 45 || col_sum != 45)
//         {
//             return false;
//         }
//     }

//     // check sub-squares: the sum of elements in each sub-square should be 45
//     for (int i = 0; i < 3; i++)
//     {
//         for (int j = 0; j < 3; j++)
//         {
//             int x_start = i * 3;
//             int y_start = j * 3;
//             int sum = 0;
//             for (int x = x_start; x < x_start + 3; x++)
//             {
//                 for (int y = y_start; y < y_start + 3; y++)
//                 {
//                     sum += board[x][y];
//                 }
//             }
//             if (sum != 45)
//             {
//                 return false;
//             }
//         }
//     }

//     return true;
// }