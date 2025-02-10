/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/23/2025
 * CS302 Winter 2025
 * Program 2
 *
 ********************************************************************
 * application implementation
 *********************************************************************
 */
#include "application.h"
using namespace std;


/*
 ***************************************************************************
 * Event class implementation
 * data members are:
 *      string description
 *      int moves
 *      int points
 ***************************************************************************
 */

//constructor
Event::Event() : moves(0), points(0) {}

//builds good events
bool Event::build_good(ifstream &filein, const Difficulty &difficulty)
{
    /*
    if (!read_string_from_file(filein, description, '\n'))
        return false;
        */
    getline(filein, description);
    switch (difficulty){
        //harder difficulties get less moves forward and less points added
        case Difficulty::easy:
            {
            moves = gen_random(4) + 1;
            points = gen_random(4) + 1;
            }
            break;
        case Difficulty::medium:
            {
            moves = gen_random(3) + 1;
            points = gen_random(3) + 1;
            }
            break;
        case Difficulty::hard:
            {
            moves = gen_random(2) + 1;
            points = gen_random(2) + 1;
            }
            break;
    }
    return true;
}

bool Event::build_bad(ifstream &filein, const Difficulty &difficulty)
{
    /*
    if (!read_string_from_file(filein, description, '\n'))
        return false;
        */
    getline(filein, description);
    switch (difficulty){
        case Difficulty::easy:
            {
            //can generate negative points, but player only moves forward. only a little less that a "good" event
            moves = gen_random(2) + 1;
            points = gen_random(3) * -1;
            }
            break;
        case Difficulty::medium:
            {
            //can generate backwards moves and negative points
            moves = (gen_random(3) + 1) * -1;
            points = gen_random(5) * -1;
            }
            break;
        case Difficulty::hard:
            {
            //can generate backwards moves and negative points
            moves = (gen_random(4) + 1) * -1;
            points = gen_random(8) * -1;
            }
            break;
    }
    return true;
}

//causes an event to share it's contents for use by the DLL (gameboard)
int Event::trigger_event(int &moves_out)
{
    display();
    moves_out = moves;
    return points;
}

//displays a single event
void Event::display()
{
    int display_moves{moves};
    int display_points{points};
    cout << left << setw(150) << description << "\nMove " << abs(display_moves);
    if (display_moves > 0)
        cout << " move(s) forward and ";
    else
        cout << " move(s) backward and ";
    if (display_points > 0)
        cout << "gain ";
    else
        cout << "lose ";
    cout << abs(display_points) << " points." << endl;
}

//genereates and returns a random number
int Event::gen_random(int max)
{
    return rand()%max;
}


/*
 **************************************************************************
 * Game class implementation
 * data members are:
 ***************************************************************************
 */

//constructor
Game::Game()
    : difficulty(Difficulty::easy), player(nullptr) , player_count(0) {}

//destructor clears player keys
Game::~Game()
{
    delete [] player;
}

//prompt players and welcome them to the game
void Game::prompt()
{
    //push up to top of term window and print welcome
    cout << "\033[2J\033[1;1H" << endl
        << R"(

                          _
                         /#\
                        /###\     /\
                       /  ###\   /##\  /\
                      /      #\ /####\/##\)" << "\033[38;5;39m" << R"(
                     /  /      /   # /  ##\)"
                      << "\033[0;0m" << R"(             _       /\)" << "\033[38;5;39m" << R"(
                   // //  /\  /    _/  /  #\ _)"
                         << "\033[0;0m" << R"(         /#\    _/##\    /\)" << "\033[38;5;39m" << R"(
                  // /   /  \     /   /    #\ \      _/###\_ /   ##\__/ _\ )" << "\033[38;5;39m" << R"(
                 /  \   / .. \   / /   _   { \ \   _/       / //    /    \\
         /\     /    /\  ...  \_/   / / \   } \ | /  /\  \ /  _    /  /    \ /\
      _ /  \  /// / .\  ..%:.  /... /\ . \ {:  \\   /. \     / \  /   ___   /  \
     /.\ .\.\// \/... \.::::..... _/..\ ..\:|:. .  / .. \\  /.. \    /...\ /  \ \
    /...\.../..:.\. ..:::::::..:..... . ...\{:... / %... \\/..%. \  /./:..\__   \
     .:..\:..:::....:::;)" << "\033[38;5;35m"
                  << R"(;;;;)" << "\033[38;5;39m"
                      << R"(;::::::::.:::::.\}.....::%.:. \ .:::. \/.%:::.:..\
    ::::...:::;;:::)" << "\033[38;5;35m"
             << R"(::;;;;;;;;;;;;;;:)" << "\033[38;5;39m"
                            << R"(::::;;::{:::::::;;;:..  .:;:... ::;;::::.. )" << "\033[38;5;35m" << R"(
    ;;;;:::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;];;;;;;;;;;::::::;;;;:.::;;;;;;;;:..
    ;;;;;;;;;;;;;;ii;;;;;;;;;;;;;;;;;;;;;;;;[;;;;;;;;;;;;;;;;;;;;;;:;;;;;;;;;;;;;
         )" << "\033[0;0m" << R"(
           ______     __  __     __    __     __    __     __     ______
          /\  ___\   /\ \/\ \   /\ "-./  \   /\ "-./  \   /\ \   /\__  _\
          \ \___  \  \ \ \_\ \  \ \ \-./\ \  \ \ \-./\ \  \ \ \  \/_/\ \/
           \/\_____\  \ \_____\  \ \_\ \ \_\  \ \_\ \ \_\  \ \_\    \ \_\
            \/_____/   \/_____/   \/_/  \/_/   \/_/  \/_/   \/_/     \/_/
         )" << "\033[0;0m" << endl;

    cout << "\t\t     Welcome to Summit - The Mountain Climbing Game. \n" << "\033[38;5;39m"
         << "\033[3m"
         << "\t For the best experience, please set your terminal window to fullscreen now."
         << "\033[00;0m" << endl;
    bool choice{};

    //int player_count{};
    do{
        choice = set_players();
        //call set_players to set the player type ("players" data member) in the Game class
        //reserve space in the event stl
        if (choice){
            try{
                cout << build_events() << " events were loaded in from files";
            }
            catch (const FILE_ERROR::good_events_exception &error){
                cout << "\n" << error.msg << endl;
            }
            catch (const FILE_ERROR::bad_events_exception &error){
                cout << "\n" << error.msg << endl;
            }
            cout << "\033[2J\033[1;1H" << endl;
            display_board();
            bool play{true};
            while (play){
                play = a_turn();
                if (play){
                    cout << "\033[2J\033[1;1H" << endl;
                    display_board();
                }
            }
        }
    }while (choice);
}

//build the events lists in the game
int Game::build_events()
{
    filein.open("good_events.txt");
    if (!filein || filein.eof())
        throw FILE_ERROR::good_events_exception();
    int built{};
    while (!filein.eof()){
        if (!good_events[built].build_good(filein, difficulty))
            throw FILE_ERROR::good_events_exception();
        ++built;
        filein.peek();
    }
    filein.close();
    int pos{};
    filein.open("bad_events.txt");
    if (!filein || filein.eof())
        throw FILE_ERROR::bad_events_exception();
    while (!filein.eof()){
        if (!bad_events[pos].build_bad(filein, difficulty))
            throw FILE_ERROR::bad_events_exception();
        ++pos;
        filein.peek();
    }
    filein.close();
    return pos + built - 2;
}

//builds preliminary details needed for a game
bool Game::set_players()
{
    // prompt for player count
    cout << "\nPlease enter the number of players (2-4)." << endl;
    player_count = read_int();
    while (player_count > 4 || player_count < 2){
        cout << "\nEnter between 2 and 4 players!" << endl;
        player_count = read_int();
    }

    //allocate memory for array of player keys
    player = new string[player_count];

    // prompt for player type selection,
    int choice{};
    cout << "\nPlease choose a player level."
         << "\n\t0. Quit\n\n\t1. Easy\n\t2. Medium\n\t3. Hard" << endl;
    choice = read_int();
    while (choice > 3 || choice < 0){
        cout << "\nEnter a difficulty level 1-3, or 0 to quit" << endl;
        choice = read_int();
    }
        /*
         * sets "difficulty" in Game
         * builds the requisite board
         * reads player and places on the board at first space
         * returning key (name) as a string
         */
        switch (choice){
            case 0:
                    return false;
            case 1: {
                        difficulty = Difficulty::easy;
                        easy_board.build(player_count);
                        // places players on boards
                        // stores their names as keys in the game class "players" member
                        for (int item = 0; item < player_count; ++ item){
                            cout << "\nPlayer " << item + 1 << ':' << endl;
                            player[item] = easy_board.start(Easy(30));
                        }
                    }
                    break;

            case 2: {
                        difficulty = Difficulty::medium;
                        medium_board.build(player_count);
                        for (int item = 0; item < player_count; ++ item){
                            cout << "\nPlayer " << item + 1 << ':' << endl;
                            player[item] = medium_board.start(Medium(20));
                        }
                    }
                    break;

            case 3: {
                        difficulty = Difficulty::hard;
                        hard_board.build(player_count);
                        for (int item = 0; item < player_count; ++ item){
                            cout << "\nPlayer " << item + 1 << ':' << endl;
                            player[item] = hard_board.start(Hard(15));
                        }
                    }
                    break;

            default:
                    break;
        }
    return true;
}

/*
 * routine for a turn (each player rolls and is moved on the board)
 * switch case based on game difficulty
 * try using a player in the player[] to perform their turn actions
 * catch an exception if the player is not valid
 */
bool Game::a_turn()
{
    bool another{true};
    for (int current_player{0}; current_player < player_count; ++ current_player){
        //meaningless, but lets players take their individual turns
        cout << "\n\n" << player[current_player] << ", enter any number to roll for an event." << endl;
        int prompt{read_int()};
        if (prompt){
            //not ideal (use of getters) - transfers info to from an event to the gameboard
            int moves{};
            int point_change{};

            //probability adjustments for good/bad events
            int good_bad{good_events[0].gen_random(10)};
            if (good_bad > 2)
                point_change = good_events[good_events[0].gen_random(50)].trigger_event(moves);
            else
                point_change = bad_events[good_events[0].gen_random(50)].trigger_event(moves);

            //moves appropriate difficulty players on the boards for the current game
            //move player will return false if the given move results in a player reaching the summit
            switch (difficulty){
                case Difficulty::easy:
                    {
                        try{
                            easy_board[player[current_player]] += point_change;
                            //loop while moves and move the player appropriately
                            while (moves != 0){
                                //positive/
                                if (moves > 0){
                                    another = easy_board >> easy_board[player[current_player]];
                                    --moves;
                                }
                                else{
                                    another = easy_board << easy_board[player[current_player]];
                                    ++moves;
                                }
                            }
                            if (easy_board[player[current_player]]())
                                easy_board[player[current_player]] += 5;
                            sleep(2);
                        }

                        //player name moved out of range
                        catch (std::out_of_range &error){
                            cout << "\nERROR! Invalid player name." << endl;
                        }
                        //the "move operator" overloaded <</>>  will return false
                        //if the player is being moved greater than the length of the board (i.e. they've won)
                        if (!another){
                            cout << "\033[2J\033[1;1H" << endl;
                            display_board();
                            cout << "\033[38;5;39m" << "\n\nThe first player to the summit is " << player[current_player] << "!" << "\033[0;0m" << endl;
                            sleep(3);
                            cout << "\033[2J\033[1;1H" << endl;
                            return another;
                        }
                    }
                    break;

                case Difficulty::medium:
                    {
                        try{
                            medium_board[player[current_player]] += point_change;
                            while (moves != 0){
                                if (moves > 0){
                                    another = medium_board >> medium_board[player[current_player]];
                                    --moves;
                                }
                                else{
                                    another = medium_board << medium_board[player[current_player]];
                                    ++moves;
                                }
                            }
                            if (medium_board[player[current_player]]())
                                medium_board[player[current_player]] += 3;
                            sleep(2);
                        }

                        catch (std::out_of_range &error){
                            cout << "\nERROR! Invalid player name." << endl;
                        }

                        if (!another){
                            cout << "\033[2J\033[1;1H" << endl;
                            display_board();
                            cout << "\033[38;5;39m" << "\n\nThe fist player to the summit is " << player[current_player] << "!" << "\033[0;0m" << endl;
                            sleep(3);
                            cout << "\033[2J\033[1;1H" << endl;
                            return another;
                        }
                    }
                    break;

                case Difficulty::hard:
                    {
                        try{
                            hard_board[player[current_player]] += point_change;
                            while (moves != 0){
                                if (moves > 0){
                                    another = hard_board >> hard_board[player[current_player]];
                                    --moves;
                                }

                                else{
                                    another = hard_board << hard_board[player[current_player]];
                                    ++moves;
                                }
                            }
                            int item{1};
                            cout << "\n" << item++ << "." << endl;

                            while (hard_board[player[current_player]]()){
                                cout << "\n" << item++ << "." << endl;
                                hard_board[player[current_player]] += 7;
                                cout << hard_board[player[current_player]] << endl;
                            }
                            sleep(2);
                        }

                        catch (std::out_of_range &error){
                            cout << "\nERROR! Invalid player name." << endl;
                        }

                        if (!another){
                            cout << "\033[2J\033[1;1H" << endl;
                            display_board();
                            cout << "\033[38;5;39m" << "\n\nThe fist player to the summit is " << player[current_player] << "!" << "\033[0;0m" << endl;
                            sleep(3);
                            cout << "\033[2J\033[1;1H" << endl;
                            return another;
                        }
                    }
                    break;
            }
        }
    }
    return another;
}


//display the correct board for the selected difficulty
void Game::display_board(){
    switch (difficulty){
        //harder difficulties get less moves forward and less points added
        case Difficulty::easy:
            {
                easy_board.display();
            }
            break;
        case Difficulty::medium:
            {
                medium_board.display();
            }
            break;
        case Difficulty::hard:
            {
                hard_board.display();
            }
            break;
    }
}

//reads a string in and returns it
const string Game::read_string()
{
    string the_string;
    cout << "\033[38;5;35m" << ">>" << "\033[0m";;
    getline(cin, the_string);
    return the_string;
}

//reads an int in and return it
const int Game::read_int()
{
    int the_int{};
    cout << "\033[38;5;35m" << ">>" << "\033[0m";;
    cin >> the_int;
    while (cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "\nYou must enter a number." << endl;
        cout << "\033[38;5;35m" << ">>" << "\033[0m";;
        cin >> the_int;
    }
    cin.ignore(100, '\n');
    return the_int;
}

//utility function to prompt repeat
bool Game::again()
{
    char again{};
    cout << "\nAgain? (y/n)" << endl;
    cout << "\033[38;5;35m" << ">>" << "\033[0m";;
    cin >> again;
    cin.ignore(100, '\n');
    if (toupper(again) == 'Y')
        return true;
    return false;
}

