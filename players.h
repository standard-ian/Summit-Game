/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/23/2025
 * CS302 Winter 2025
 * Program 2
 ********************************************************************
 *
 * generic programming and operator overloading with class templates
 *
 * building a game
 * supports 3 levels of player
 * doubly linked lists represent the game board
 * nodes = players
 * players navigate along the board, trying to reach the end with the most points
 * game mode sets difficulty (level 1-3) for all players
 *
 * basic requirements:
 *      3 classes to represent the 3 levels of player difficulty derived from a common base class
 *      i.e. novice - only travel forward
 *           intermediate - travel both directions
 *           advanced - additional obstacles
 *
 *      base class and one derived class must have dynamic memory (char*) and supporting copy constructor and assignent operator
 *      2 common (base class attributes i.e. name and age)
 *
 *      support a list of events using the STL:
 *           an event should also be its own class, should cause the player to do something like move backwards, start over, etc
 *           random number generation used to select a random event
 *
 * part 1 design:
 *      design core hierarchy specification with a UML diagram
 *      600 word specification (see .tex file in spec directory)
 *      600 word design guide (see .tex file in design directory)
 *      UML diagram
 *
 * part 2 core hierarchy:
 *      create 3 levels of player
 *      only one level (difficulty) on the "board" at a time
 *      must be similarities and differences
 *      common elements - like player name and points pushed up to base class
 *      any data within these classes should be contained in an STL container
 *
 * part 3 operator overloading:
 *      add opeators for the 3 levels of player
 *      class template for the data structure needs these to be independant of data type
 *      MUST HAVE: assignment (=)
 *                 relational and equality(>, <, <=, >=, ==, !=)
 *                 IO (<<, >>)
 *                 ONE binary arithmetic (- or + and the corresponding -=/+=).
 *                 ++/-- is optional but if implemented, must have prefix and postfix
 *
 * part 4 creating the application:
 *      Doubly linked list using class templates
 *      keep track of the game board for only 1 data type (player level) at a time
 *      create the DLL once and use templates to have 3 instantiations for each level of player
 *      repetetive methods must be implemented recursively
 *      for this progress submission, progress on the application and data structures should be evident
 *
 * completed program:
 *      playable by minimum 2 players
 *      align w/ spec and design
 *      single inheritance hierarchy
 *      operator overloading within core hierarchy
 *      exception handling - operators must use this for unexpected events, mostly within core hierarchy
 *      use of strings
 *      array, list, or forward list from stl
 *      NO USE OF VIRTUAL FUNCTIONS
 *
 * operator overloading considerations:
 *      1. what should be the residual value and what data type should this be
*           no void returns, throw exceptions for unexpected things, structs for exceptions
*       2. should residual value be a modifyable lvalue or rvalue?
*           lval return by reference, rval return by value
*       3. data types of the operands
*           never pass a class by value, pass by ref when possible
*           avoind passing pointers to operators
*       4. is the first operand always an object?
*           if so, member; if not, friend
*       5. Can the operator be used with constant operands?
*           if the first operand can be const and if it is a member function, it should be const function
*
* notes from lecture:
*       nodes could be an individual player spot
*       assignemnt is intentionally vauge
*
*/

/*
 ********************************************************************
 * core hierarchy interface
 *********************************************************************
 */

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <array>
#include <fstream>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <list>
#include <unistd.h>
#include <algorithm>
//#include <algorithm>
//#include <bits/stdc++.h>

//game exceptions
struct FILE_ERROR
{
        struct good_events_exception{
            std::string msg{"ERROR! Positive events could not be loaded."};
        };
        struct bad_events_exception{
            std::string msg{"ERROR! Negative events could not be loaded."};
        };
        struct riddle_exception{
            std::string msg{"ERROR! Riddles could not be loaded."};
        };
};

//base player declaration - must have dynamic memory
class Player
{

    public:
        Player();
        Player(const int points);
        ~Player();
        Player(const Player &source);

        std::string get_name() const;
        /*
         ***********************************************************
         * overloaded operators
         ***********************************************************
         */
        //assignemnt
        Player& operator=(const Player &source);

        //relational, points
        friend bool operator<(const Player &left, const Player &right);
        friend bool operator<(const Player &left, const int right);
        friend bool operator<(const int left, const Player &right);

        friend bool operator<=(const Player &left, const Player &right);
        friend bool operator<=(const Player &left, const int right);
        friend bool operator<=(const int left, const Player &right);

        friend bool operator>(const Player &left, const Player &right);
        friend bool operator>(const Player &left, const int right);
        friend bool operator>(const int left, const Player &right);

        friend bool operator>=(const Player &left, const Player &right);
        friend bool operator>=(const Player &left, const int right);
        friend bool operator>=(const int left, const Player &right);

        friend bool operator==(const Player &left, const int right);
        friend bool operator==(const int left, const Player &right);

        friend bool operator!=(const Player &left, const Player &right);
        friend bool operator!=(const Player &left, const int right);
        friend bool operator!=(const int left, const Player &right);

        //relational, names
        friend bool operator==(const Player &left, const Player &right);
        friend bool operator==(const std::string &left, const Player &right);
        friend bool operator==(const Player &left, const std::string &right);

        //compound arithmetic
        Player& operator+=(const int points);
        Player& operator-=(const int points);

        //binary arithmetic
        friend Player operator+(const Player &left, const int right);
        friend Player operator+(const int left, const Player &right);
        friend Player operator+(const Player &left, const Player &right);

        friend Player operator-(const Player &left, const int right);
        friend Player operator-(const int left, const Player &right);
        friend Player operator-(const Player &left, const Player &right);

        //IO
        friend std::ostream& operator<<(std::ostream &out, const Player &object);
        friend std::istream& operator>>(std::istream &in, Player &object);

        //negation
        bool operator!();

        //prefix
        Player& operator++();
        Player& operator--();

        //postfix
        Player operator++(int);
        Player operator--(int);

    protected:
        char *name;
        int points;

        friend bool compare(const int left, const int right);

        const std::string read_string();
        const int read_int();
};

//"easy" level player declaration - must have dynamic memory
class Easy : public Player
{
    public:
        Easy();
        Easy(const int points);
        Easy(const Easy &source);
        Easy& operator=(const Easy &source);
        ~Easy();

        //used to trigger unique player event in a universal way within the template
        bool operator()();

        friend std::ostream& operator<<(std::ostream &out, const Easy &object);

        //arithmatic - alter points (+/+=) only in base class
        Easy& operator+=(const int points);
        Easy& operator-=(const int points);

        friend Easy operator+(const Easy &left, const int right);
        friend Easy operator+(const int left, const Easy &right);
        friend Easy operator+(const Easy &left, const Easy &right);

        friend Easy operator-(const Easy &left, const int right);
        friend Easy operator-(const int left, const Easy &right);
        friend Easy operator-(const Easy &left, const Easy &right);

    private:
        char *emoji;
};

//"medium" level player declaration - no dynamic memory
class Medium : public Player
{
    public:
        Medium();
        Medium(const int points);

        bool operator()();

        friend std::istream& operator>>(std::istream &in, Medium &object);

        //arithmatic - alter points (+/+=) only in base class
        Medium& operator+=(const int points);
        Medium& operator-=(const int points);

        friend Medium operator+(const Medium &left, const int right);
        friend Medium operator+(const int left, const Medium &right);
        friend Medium operator+(const Medium &left, const Medium &right);

        friend Medium operator-(const Medium &left, const int right);
        friend Medium operator-(const int left, const Medium &right);
        friend Medium operator-(const Medium &left, const Medium &right);

    private:
        int entries;
        std::list<std::string> journal_entries;
};

//"hard" level player declaration - no dynamic memory
class Hard : public Player
{
    public:
        Hard();
        Hard(const int points);

        bool operator()();

        //arithmatic - alter points (+/+=) only in base class
        Hard& operator+=(const int points);
        Hard& operator-=(const int points);

        friend Hard operator+(const Hard &left, const int right);
        friend Hard operator+(const int left, const Hard &right);
        friend Hard operator+(const Hard &left, const Hard &right);

        friend Hard operator-(const Hard &left, const int right);
        friend Hard operator-(const int left, const Hard &right);
        friend Hard operator-(const Hard &left, const Hard &right);


        bool riddle();

    private:
        std::map<int, std::string> riddles;
        std::map<int, std::string> answers;
        int riddles_loaded;

        int load_riddles();
};

