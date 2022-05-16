
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <dos.h>
#include <time.h>

#define MAXSNAKESIZE 100

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


// testing position of mouse at start 
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
    void setPoint(int x, int y) {
        this->x = x;
        this->y = y;

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
    //Drawing the Snake 
    void Draw() {
        goToXY(x, y);
        cout << "*";
    }
    //Drawing the fruit 
    void fruitDraw() {
        goToXY(x, y);
        cout << "o";
    }
    void Delete() {
        goToXY(x, y);
        cout << " ";
    }
    void CopyPosition(Point * p) {
        p->x = x;
        p->y = y;
    }
    // testing it displayed (at the start of project) 
    void Debug() {
        cout << "(" << x << "," << y << ")";
    }
};

//creating the Snake Class
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
        // setting position of snake to random 
        fruit.setPoint(rand()%50, rand()%25);
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

    // creating the move function 
    void Move() {

        //creating the clear screen function 
        system("cls");

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

        // detection of the fruit 
        if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()) {
            addCell(0,0);
            fruit.setPoint(rand() % 50, rand() % 25);
        }

        // drawing the Snake
        for (int i = 0; i < size; i++) {
            cell[i]->Draw();
            
            fruit.fruitDraw();
            
            Sleep(100);
        }
    }
};

int main() {

    //random generator
    srand((unsigned)time(NULL));
    
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