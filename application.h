/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/23/2025
 * CS302 Winter 2025
 * Program 2
 *
 ********************************************************************
 * application definition
 *********************************************************************
 */

#include "templates.h"


enum class Difficulty{easy, medium, hard};

//event
//manages random number generation, file io,
//indvidual event characteristics
class Event
{
    public:
        Event();
        bool build_good(std::ifstream &filein, const Difficulty &difficulty);
        bool build_bad(std::ifstream &filein, const Difficulty &difficulty);
        int trigger_event(int &moves);
        void display();
        int gen_random(int range);

    private:
        std::string description;
        int moves;
        int points;
};

//"game" definition
//manages players, io, game boards, event list
class Game
{
    public:
        Game();
        ~Game();
        void prompt();
        int build_events();
        bool set_players();
        bool build_boards();
        bool a_turn();
        void display_board();

    protected:
        Difficulty difficulty;
        std::string *player;
        int player_count;

        DLL<Easy, 10> easy_board;
        DLL<Medium, 20> medium_board;
        DLL<Hard, 40> hard_board;

        std::array<Event, 50> good_events;
        std::array<Event, 50> bad_events;

        std::ifstream filein;

        const std::string read_string();
        const int read_int();
        bool again();

};

