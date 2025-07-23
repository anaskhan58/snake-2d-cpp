#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class SnakeGame {
private:
    bool gameOver;
    const int width = 20;
    const int height = 20;
    int x, y, fruitX, fruitY, score;
    vector<pair<int, int>> tail;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

public:
    SnakeGame() {
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
    }

    void Draw() {
        system("cls");
        
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";
                
                if (i == y && j == x)
                    cout << "O";
                else if (i == fruitY && j == fruitX)
                    cout << "F";
                else {
                    bool print = false;
                    for (int k = 0; k < tail.size(); k++) {
                        if (tail[k].first == j && tail[k].second == i) {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }

                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
        
        cout << "Score: " << score << endl;
        cout << "Use WASD to move, X to quit" << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    void Logic() {
        int prevX = x;
        int prevY = y;
        int prev2X, prev2Y;
        
        if (!tail.empty()) {
            prev2X = tail[0].first;
            prev2Y = tail[0].second;
            tail[0].first = prevX;
            tail[0].second = prevY;
            
            for (int i = 1; i < tail.size(); i++) {
                prevX = tail[i].first;
                prevY = tail[i].second;
                tail[i].first = prev2X;
                tail[i].second = prev2Y;
                prev2X = prevX;
                prev2Y = prevY;
            }
        }

        switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
        }

        if (x >= width) x = 0; else if (x < 0) x = width - 1;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;

        for (int i = 0; i < tail.size(); i++) {
            if (tail[i].first == x && tail[i].second == y)
                gameOver = true;
        }

        if (x == fruitX && y == fruitY) {
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
            tail.push_back(make_pair(0, 0));
        }
    }

    bool IsGameOver() {
        return gameOver;
    }

    int GetScore() {
        return score;
    }
};

int main() {
    srand(time(0));
    SnakeGame game;
    
    cout << "=== SNAKE GAME ===" << endl;
    cout << "Press any key to start..." << endl;
    _getch();

    while (!game.IsGameOver()) {
        game.Draw();
        game.Input();
        game.Logic();
        Sleep(100);
    }

    system("cls");
    cout << "=== GAME OVER ===" << endl;
    cout << "Final Score: " << game.GetScore() << endl;
    cout << "Thanks for playing!" << endl;
    cout << "Press any key to exit..." << endl;
    _getch();

    return 0;
}