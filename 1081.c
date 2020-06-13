#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Populates the array on the first start of the program by the user
void populateArray(int rows, int columns, int board[rows][columns]);
//Every evolution is a tick in lifeforms live.
void nextTick(int rows, int columns, int board[rows][columns], int nextBoard[rows][columns], int steps);
//Counts the neighbours for the specific cell (x,y)
int countNeighbours(int rows, int columns, int x, int y, int board[rows][columns]);
/*
...X..
..X.X.
..X.X.
...X..
......
......
*/
//Prints the matrix in this format ("X" is Alive, "." is a dead cell)
void printMatrix(int rows, int columns, int board[rows][columns]);

int main() {
  //int rows=6,columns = 6, steps = 20;
  int rows, columns, steps = 0;
  scanf("%d %d %d", & rows, & columns, & steps);
  int board[rows][columns];
  populateArray(rows, columns, board);
  int step = 0; //set to 0
  //for all steps given by user i.e 20 steps = 20 loops
  while (steps > step) {
    step += 1;
    int nextBoard[rows][columns];
    nextTick(rows, columns, board, nextBoard, steps);
  }
  printMatrix(rows, columns, board);
  return 0;
}
//Prints the matrix in this format ("X" is Alive, "." is a dead cell)
void printMatrix(int rows, int columns, int board[rows][columns]) {
  bool removeEnter = false;
  for (int row = 0; row < rows; row++) {
    //removes unnecessary enter at the start of the input
    if (removeEnter == false) {
      removeEnter = true;
    } else if (removeEnter == true) {
      printf("\n");
    }
    for (int column = 0; column < columns; column++) {
      //if cell alive
      if (board[row][column] == 1) {
        printf("X");
      } //if cell dead
      else if (board[row][column] == 0) {
        printf(".");
      } //otherwise print the problem with the cell in int format
      //debuging feature
      else {
        printf("%d ", board[row][column]);
      }
    }

  }
}
//Counts the neighbours for the specific cell (x,y)
int countNeighbours(int rows, int columns, int x, int y, int board[rows][columns]) {
  int count = 0;
  //do a search of all 9 inputs 
  for (int a = -1; a < 2; a++) {
    for (int b = -1; b < 2; b++) {
      //make sure that the check is within the boundries of the array
      if ((((x + a) >= 0) && ((a + x) < rows)) && (((y + b) >= 0) && ((b + y) < columns))) {
        count += board[x + a][y + b];
      }
    }
  }
  count = count - board[x][y];
  return count;
}
//Every evolution is a tick in lifeforms live.
void nextTick(int rows, int columns, int board[rows][columns], int nextBoard[rows][columns], int steps) {
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      //n = neighbours
      int n = countNeighbours(rows, columns, row, column, board);
      // <2 n = die
      if (board[row][column] == 1 && n < 2) {
        nextBoard[row][column] = 0;

      } //live on if n==2 || n==3 and alive
      else if ((n == 2 || n == 3) && board[row][column] == 1) {
        nextBoard[row][column] = 1;

      } //if b==1 && n >3 die
      else if (board[row][column] == 1 && n > 3) {
        nextBoard[row][column] = 0;
      } //if cell is dead && neighbours is 3
      else if (board[row][column] == 0 && n == 3) {
        nextBoard[row][column] = 1;
      } //otherwise set the board to the older model
      else {
        nextBoard[row][column] = board[row][column];
      }

      //RULES
      // cell < 2 = die
      // 1 && 2 || 3 = live
      // cell > 3  = die
      // if 0 && n == 3 = live
      //spawn if 3 neighbours and is dead
    }
  }
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      board[row][column] = nextBoard[row][column];
    }
  }
}
//Populates the array on the first start of the program by the user
void populateArray(int rows, int columns, int board[rows][columns]) {
  //printf("%d %d %d\n", rows,columns);
  char c;
  if ((rows > 0) && (columns > 0)) {
    for (int row = 0; row < rows; row++) {
      for (int column = 0; column < columns; column++) {
        //change into 0's and 1's
        //. == 0 == dead
        //X == 1 == alive
        scanf(" %c", & c);
        if (c == 'X') {
          board[row][column] = 1;
        } else if (c == '.') {
          board[row][column] = 0;
        }
      }
    }
  } else {
    printf("args: <columns> <rows> <gameboard>");
  }
}
