
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <dos.h>
#include <time.h>


#define MAXSNAKESIZE 100
#define MAXFRAME_X 119
#define MAXFRAME_Y 29

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


    // allowing the player reappear on the screen e.g. 
    // the player goes to the top of the console, they will
    // at the bottom of the screen
    void moveUp() {
        y--;
        if (y < 0) {
            y = MAXFRAME_Y;
        }
    }
    void moveDown() {
        y++;
        if (y > MAXFRAME_Y) {
            y = 0;
        }
    }
    void moveRight() { 
        x++;
        if (x > MAXFRAME_X) {
            x = 0;
        }
    }
    void moveLeft() {
        x--;
        if (x < 0) {
            x = MAXFRAME_X;
        }
    }
    //Drawing the Snake 
    void Draw() {
        goToXY(x, y);
        cout << "O";
    }
    //Drawing the fruit 
    void fruitDraw() {
        goToXY(x, y);
        cout << "X";
    }
    void CopyPosition(Point * p) {
        p->x = x;
        p->y = y;
    }
};

//creating the Snake Class
class Snake {

private:
    Point* cell[MAXSNAKESIZE]; // Snake array 
    int size; //  size of the Snake
    char dir; // direction of the Snake
    Point fruit; // creating a fruit 
    int state; // Checking if the snakes alive using a boolean

    // creating start screen
    int startGame;

public:

    Snake() {
        size = 1; //starting size of the snake
        cell[0] = new Point(20, 20); //starting position of the Snake (20,20)
        for (int i = 1; i < MAXSNAKESIZE; i++) {
            cell[i] = NULL;
        }
        // setting position of fruit to random & within the window border
        fruit.setPoint(rand()%MAXFRAME_X, rand()%MAXFRAME_Y);
        
        // setting starting state of snake to *dead*
        state = 0;
        startGame = 0;
    }
    void addCell(int x, int y) {
        cell[size++] = new Point(x, y);
    }
    // setting the controls for the snake e.g. w = up 
    void turnUp() {
        if(dir != 's')
        dir = 'w'; //UP
    }
    void turnDown() {
        if(dir != 'w')
        dir = 's'; // DOWN
    }
    void turnLeft() {
        if (dir != 'd')
        dir = 'a'; //LEFT
    }
    void turnRight() {
        if(dir != 'a')
        dir = 'd'; //RIGHT
    }

    // creating the Welcome Screen  
    void welcomeScreen() {
        SetConsoleTextAttribute(console, 15); // setting the colour of the background 
        
        cout << R"( 
     Y											
   .-^-.										
  /     \      .- ~ ~ -.								
 ()     ()    /   _ _   `.                     _ _ _					
  \_   _/    /  /     \   \                . ~  _ _  ~ .				
    | |     /  /       \   \             .' .~       ~-. `.				
    | |    /  /         )   )           /  /             `.`.				
    \ \_ _/  /         /   /           /  /                `'				
     \_ _ _.'         /   /           (  (					
                     /   /             \  \						
                    /   /               \  \						
                   /   /                 )  )						
                  (   (                 /  /						
                   `.  `.             .'  /						
                    `.   ~ - - - - ~   .'						
                       ~ . _ _ _ _ . ~							
								                                
             Welcome to the Endless Snake Console Game!                     )";


    }
    //Creating the move function 
    void Move() {

        //creating the clear screen function 
        system("cls");

        if (state == 0) {
            if (startGame == 0) {
                welcomeScreen();
                cout << "\n \n Press any key to start";
                cout << "\n Press E to end the game";
                _getch();
                startGame = 1;
                state = 1;
            }

        }

        //making the snake body follow its head 
        for (int i = size - 1; i > 0; i--) {
            cell[i - 1]->CopyPosition(cell[i]);
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
            addCell(0, 0);
            fruit.setPoint(rand() % MAXFRAME_X, rand() % MAXFRAME_Y);
        }

        // drawing the Snake
        for (int i = 0; i < size; i++) {
            cell[i]->Draw();

            fruit.fruitDraw();

        }
      
    }
};

int main() {

    // random generator
    srand((unsigned)time(NULL));

    //Creating a new snake from the Snake class 
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