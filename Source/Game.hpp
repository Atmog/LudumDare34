#ifndef GAME_HPP
#define GAME_HPP

#include <string>

class Game
{
    public:
        static Game& instance();

        static std::string getTitle();

    private:
        Game();
        ~Game();

        static Game mInstance;
};

#endif // GAME_HPP
