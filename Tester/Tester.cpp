
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

// setting timer variable
int count = 0;

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
    void Delete() {
        goToXY(x, y);
        cout << " ";
    }
    void CopyPosition(Point * p) {
        p->x = x;
        p->y = y;
    }
    // Trying to figure out how to sort collision out between the players head and its body 
    int IsEqual(Point* p) {
        if (p->x == x && p->y == y) {
            return 1;
        }
        return 0;
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

    // creating the move function 
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
								                                
                Welcome to the Snake Console Game!                     )";


    }
    void Move() {

        //creating the clear screen function 
        system("cls");

        if (state == 0) {
            if (startGame == 0) {
                welcomeScreen();
                cout << "\n \n Press any key to start";
                _getch();
                startGame = 1;
                state = 1;
            }
            //else{
            //    cout << "\n Game Over";
            //    cout << "\n Press any key to start";
            //    _getch(); // pauses the output console until an input it entered 
            //    state = 0;
            //    size = 1;
            //    startGame = 0;
            //    SetConsoleTextAttribute(console, 15);
            //}
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

    //random generator
    //setcursor(0, 0);
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