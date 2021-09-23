#include <iostream>
#include <list>
#include <olcPixelGameEngine.h>

class Game : public olc::PixelGameEngine
{
private:
    olc::vi2d pos;
    olc::vf2d direction;
    float speed;
    std::list<olc::vi2d> snake;
    olc::vi2d food;
    float time_passed;
    
    unsigned int score;  
    int drop_food;
    bool GameOver;
    bool MainMenu;

    const int GRID_WIDTH = 40, GRID_HEIGHT = 40;
    std::string scoreString = "Score :";
    const olc::vi2d pixels = {10, 10};

public:
    Game()
    {
        sAppName = "Snake";
        winTitle = sAppName;
    }


    
    void init()
    {
        snake.clear();
        pos = {int(GRID_WIDTH / 2), int(GRID_HEIGHT / 2)};
        snake.push_back(pos);
        GameOver = true;
        MainMenu = true;

        direction = {1.0f, 0.0f};
        food = {rand() % GRID_WIDTH, rand() % GRID_HEIGHT};
        time_passed = 0;
        score = 0;
        drop_food = 0;
    }

    bool OnUserCreate()
    {
        init();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime)
    {
        this->Clear(olc::BLACK);

        if (!GameOver)
        {
            time_passed += fElapsedTime;
            DrawString({10, 10}, scoreString + std::to_string(score), olc::WHITE);

            if (GetKey(olc::Key::W).bPressed || GetKey(olc::Key::UP).bPressed)
            {
                direction = {0.0f, -1.0f};
            }
            else if (GetKey(olc::Key::S).bPressed || GetKey(olc::Key::DOWN).bPressed)
            {
                direction = {0.0f, +1.0f};
            }
            else if (GetKey(olc::Key::D).bPressed || GetKey(olc::Key::RIGHT).bPressed)
            {
                direction = {1.0f, 0.0f};
            }
            else if (GetKey(olc::Key::A).bPressed || GetKey(olc::Key::LEFT).bPressed)
            {
                direction = {-1.0f, 0.0f};
            }

            if (snake.front().x < 0)
            {
                snake.front().x += GRID_WIDTH - 1;
            }
            else if (snake.front().x > GRID_WIDTH - 1)
            {
                snake.front().x -= GRID_WIDTH;
            }
            if (snake.front().y < 0)
            {
                snake.front().y += GRID_HEIGHT - 1;
            }
            else if (snake.front().y > GRID_HEIGHT - 1)
            {
                snake.front().y -= GRID_HEIGHT;
            }

            if (time_passed >= 1.f / 10)
            {
                snake.push_front(snake.front() + direction);
                if (food == olc::vi2d(snake.front()))
                {
                    score++;
                    food = {-1000, -1000};
                }
                else
                {
                    snake.pop_back();
                }
                for (auto x = ++(snake.begin()); x != snake.end(); ++x)
                {
                    if (*x == snake.front())
                    {
                        GameOver = true;
                    }
                }
                if (drop_food == 80)
                {
                    food = {rand() % GRID_WIDTH, rand() % GRID_HEIGHT};

                    drop_food = 0;
                }
                drop_food++;
                time_passed = 0;
            }
            DrawRect(food * pixels.x, pixels, olc::RED);

            for (auto &x : snake)
            {
                DrawRect(x * pixels.x, pixels, olc::GREEN);
            }
        }
        else if (MainMenu)
        {
            DrawString(ScreenWidth() / 2 - 44, ScreenHeight() / 2, "Play Game", olc::RED);
            DrawRect(ScreenWidth() / 2 - 52, ScreenHeight() / 2 - 5, 85, 20, olc::RED);
            olc::vi2d p = {ScreenWidth() / 2 - 120, 50};
            DrawString(p, "SNAKE", olc::GREEN, 6);
            if (this->GetMouse(olc::Mouse::LEFT).bPressed)
            {
                olc::vi2d p1 = {ScreenWidth() / 2 - 52, ScreenHeight() / 2 - 5};
                olc::vi2d p2 = {ScreenWidth() / 2 - 52 + 85, ScreenHeight() / 2 - 5 + 20};
                int mouseX = this->GetMouseX();
                int mouseY = this->GetMouseY();
                if ((p1.x <= mouseX && mouseX <= p2.x) && (p1.y <= mouseY && mouseY <= p2.y))
                {
                    MainMenu = false;
                    GameOver = false;
                }
            }
        }
        else
        {
            // Game Over
            DrawString(ScreenWidth() / 2 - 160, ScreenHeight() / 2, "Game Over", olc::WHITE, 4);
            DrawString(10, 10, "Score :" + std::to_string(score));
            if (this->GetMouse(olc::Mouse::LEFT).bPressed)
            {
                init();
            }
        }
        return true;
    }
};

int main(int argc, char **argv)
{
    Game game;
    if (game.Construct(400, 400, 1, 1, false, true))
    {
        game.Start();
    }
    return 0;
}