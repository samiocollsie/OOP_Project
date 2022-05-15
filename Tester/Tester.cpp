/*
// Tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <string>

//creating a function 

//Function overloading, can use the same name for a function 
// but if depending on the requirements, it will run one over the
// other e.g. if it requires an argument it will run the second,
// if no argument, then the first one

// this example uses the idea of already knowing the int inputted
// for an int you put %d
// for a float %g 

//void print() {
//
//    printf("func1\n");
//}
//Int 
//void print(int x) {
//    printf("func1 with an argument %d\n", x);
//
//}
// float 
//void print(float f) {
//    printf("log: %f\n", f);
//}
//  string 
//void print(const char* str) {
//    printf("log: %s\n", str);
//}



// Class Vertex 
class Vertex {
    float x, y, z;
};

// a struct is a way to group low level data types & create more complex
// concepts. Can be used as shapes, plus OOP.  
struct VertexStruct {
    float x, y, z;
    void setToZero() {
        x = 0;
        y = 0;
        z = 0;
    }
};

// MAIN CODE 
int main()
{
    //Overloading functions 
    //print();
    //print(0.5f);
    //print("hi");

    VertexStruct v, v2; 
    v.x = 0;
    v.y = 1;
    v.z = 2;

    v2.x = 0;

    v.setToZero();

    printf("%g\n", v.y);

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
*/

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <dos.h>

#define MAXSNAKESIZE 100

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void goToXY(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}


class Point {
private:
    int x;
    int y;
public:
    Point() {
        x = y = 10;
    }
    Point(int x, int y) {
        this-> x = y;
        this-> y = y;
    }
    int GetX() {
        return x;
    }
    int GetY() {
        return y;
    }
    void moveUp() {
        y--;
    }
    void moveDown() {
        y++;
    }
    void moveRight() {
        x++;
    }
    void moveLeft() {
        x--;
    }
    void Draw() {
        goToXY(x, y);
        cout << "*";
    }
    void Delete() {
        goToXY(x, y);
        cout << " ";
    }
    void CopyPosition(Point * p) {
        p->x = x;
        p->y = y;
    }
    void Debug() {
        cout << "(" << x << "," << y << ")";
    }
};

class Snake {
private:
    Point* cell[MAXSNAKESIZE]; // Snake array 
    int size; // current size of the Snake
    char dir; // the current direction of the Snake
    Point fruit;
public:
    Snake() {
        size = 1; //starting size of the snake
        cell[0] = new Point(20, 20); //starting position of the Snake (20,20)
        for (int i = 1; i < MAXSNAKESIZE; i++) {
            cell[i] = NULL;

        }
    }
    void addCell(int x, int y) {
        cell[size++] = new Point(x, y);
    }
    // setting the controls for the snake e.g. w = up 
    void turnUp() {
        dir = 'w'; //UP
    }
    void turnDown() {
        dir = 's'; // DOWN
    }
    void turnLeft() {
        dir = 'a'; //LEFT
    }
    void turnRight() {
        dir = 'd'; //RIGHT
    }
    void Move() {
        //making the snake body follow its head 
        for (int i = size - 1; i > 0; i--) {
            cell[i]->CopyPosition(cell[i - 1]);
        }
        //turning of snake head
        switch (dir) {
        case 'w':
            cell[0]->moveUp();
            break;
        case 's':
            cell[0]->moveDown();
            break;
        case 'a':
            cell[0]->moveLeft();
            break;
        case 'd':
            cell[0]->moveRight();
            break;
        }

        // drawing the Snake
        for (int i = 0; i < size; i++) {
            cell[i]->Draw();

            Sleep(100);
        }
    }
};

int main() {
    
    //Testing Snake
    Snake snake;

    char op = '1';
    do {
        if (_kbhit()) {
            op = _getch();
        }
        switch (op) {
        // calling the movement functions 
        case 'w':
        case 'W':
            snake.turnUp();
            break;

        case 's':
        case 'S':
            snake.turnDown();
            break;

        case 'a':
        case 'A':
            snake.turnLeft();
            break;

        case 'd':
        case 'D':
            snake.turnRight();
            break;

        }
        snake.Move();

    } while (op != 'e');


        return 0;
}