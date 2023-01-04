#include <iostream>
#include <conio.h>
#ifdef __WIN32
#define WINDOWS_SYSTEM true
#include <windows.h>
#define timer Sleep
#else
#define WINDOWS_SISTEM false
#include <unistd.h>
#define  timer usleep
#endif
#include <experimental/random>


enum class Direction{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};


void time()
{
    timer(100);
}


class SnakeGame{
public:
    bool gameover {true};

    // constructor
    SnakeGame() = default;

    // public methods
    void setup(){
        _setup();
    }

    void draw_map(){
        _draw_map();
    }

    void input(){
        _input();
    }

    void logic(){
        _logic();
    }


    void start(){
        draw_map();
        input();
        logic();
    }

private:
    Direction dir;
    const int width {50}; // 50 x 10
    const int height {10};
    int position_x, position_y, fruit_x, fruit_y, score;

    void _setup()
    {
        // restart settings
        gameover = false;
        dir = Direction::STOP;
        position_x = width / 2;
        position_y = height / 2;
        fruit_x = std::experimental::randint(1, 19);
        fruit_y = std::experimental::randint(1, 19);
        score = 0;
    }

    void _draw_map() const
    {
        // refresh window
        if(WINDOWS_SYSTEM){
            system("CLS");
        }else{
            system("clear");
        }

        // top
        for(size_t i = 0; i < width; i++){
            std::cout << "#" << std::flush;
        }
        std::cout << '\n' << std::flush;

        // middle
        for(size_t line = 1; line < height; line++){
            for(size_t column = 0; column < width; column++){
                if(column == 0 or column == (width - 1))
                    std::cout << "#" << std::flush;
                else
                    std::cout << ' ' << std::flush;

                // snake
                if(column == position_x  and line == position_y ){
                    std::cout << "O" ;
                }
                // fruit
                if(column == position_y and line == position_x / 5 ){
                    std::cout << "F";
                }

                }
            std::cout << '\n' << std::flush;
        }

        // bottom
        for(size_t i = 0; i < width; i++){
            std::cout << "#" << std::flush;
        }
        std::cout << '\n' << std::flush;

        time(); // 10ms to refresh
    }

    void _input()
    {
        // capture the keyboard entries
        if(_kbhit())
        {
            switch (_getch()) {
                case 'a':
                    dir = Direction::LEFT;
                    break;
                case 'w':
                    dir = Direction::UP;
                    break;
                case 's':
                    dir = Direction::DOWN;
                    break;
                case 'd':
                    dir = Direction::RIGHT;
                    break;
                case 'x':
                    gameover = false;
                    break;
            }
        }
    }

    void _logic()
    {
        switch (dir) {
            case Direction::UP:
                position_y--;
                break;
            case Direction::DOWN:
                position_y++;
                break;
            case Direction::LEFT:
                position_x--;
                break;
            case Direction::RIGHT:
                position_x++;
                break;
            default:
                break;
        }
    }


};


int main(){
    std::ios::ios_base::sync_with_stdio(false);

    SnakeGame snake = SnakeGame();
    while(snake.gameover){
        snake.start();
    }
    return EXIT_SUCCESS;
}