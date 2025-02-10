/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/23/2025
 * CS302 Winter 2025
 * Program 2
 *
 ********************************************************************
 * core hierarchy implementation
 *********************************************************************
 */
#include "players.h"

/*
 **************************************************************************
 * Player implementation
 * data members are:
 *      int points
 *      char *name
 ***************************************************************************
 */

//default constructor
Player::Player() : name(nullptr), points(0) {}

//constructor, takes points as an arg as points will never be set by user input
Player::Player(int points) : points(points)
{
    using std::string, std::cout, std::endl;

    cout << "\nEnter the player name." << endl;
    string name_in{read_string()};
    while (name_in.length() > 7){
        cout << "\nSorry, but your player name must be 7 characters or less.\n"
             << "Enter a shorter name." << endl;
        name_in = read_string();
    }
    name = new char[name_in.length() + 1];
    strcpy(name, name_in.c_str());
}

//destructor
Player::~Player()
{
    if (name){
        delete [] name;
        name = nullptr;
    }
    points = 0;
}

//copy constructor
Player::Player(const Player &source) : name(nullptr), points(source.points)
{
    if (!source.name) return;
    name = new char[strlen(source.name) + 1];
    strcpy(name, source.name);
}

//getter bad! xD
std::string Player::get_name() const
{
    std::string player_name(name);
    return player_name;
}

//assign a player name and points
Player& Player::operator=(const Player &source)
{
    if (this == &source)
        return *this;
    if (name){
        delete [] name;
        name = nullptr;
    }
    if (source.name){
        name = new char[strlen(source.name) + 1];
        strcpy(name, source.name);
    }
    points = source.points;
    return *this;
}


//used by compare operators
bool compare(const int left, const int right)
{
    return (left > right);
}

//relational points
bool operator<(const Player &left, const Player &right)
{
    return compare(right.points, left.points);
}
bool operator<(const Player &left, const int right)
{
    return compare(right, left.points);
}
bool operator<(const int left, const Player &right)
{
    return compare(right.points, left);
}
bool operator<=(const Player &left, const Player &right)
{
    return (left.points == right.points || compare(right.points, left.points));
}
bool operator<=(const Player &left, const int right)
{
    return (left.points == right || compare(right, left.points));
}
bool operator<=(const int left, const Player &right)
{
    return (left == right.points || compare(right.points, left));
}
bool operator>(const Player &left, const Player &right)
{
    return compare(left.points, right.points);
}
bool operator>(const Player &left, const int right)
{
    return compare(left.points, right);
}
bool operator>(const int left, const Player &right)
{
    return compare(left, right.points);
}
bool operator>=(const Player &left, const Player &right)
{
    return (left.points == right.points || compare(left.points, right.points));
}
bool operator>=(const Player &left, const int right)
{
    return (left.points == right || compare(left.points, right));
}
bool operator>=(const int left, const Player &right)
{
    return (left == right.points || compare(left, right.points));
}
bool operator==(const Player &left, const int right)
{
    return (left.points == right);
}
bool operator==(const int left, const Player &right)
{
    return (left == right.points);
}
bool operator!=(const Player &left, const Player &right)
{
    return !(left.points == right.points);
}
bool operator!=(const Player &left, const int right)
{
    return !(left.points == right);
}
bool operator!=(const int left, const Player &right)
{
    return !(left == right.points);
}

//relational - names
bool operator==(const Player &left, const Player &right)
{
    if (!left.name && !right.name) return true;
    if (!left.name && right.name) return false;
    if (!right.name && left.name) return false;
    return !strcmp(left.name, right.name);
}
bool operator==(const std::string &left, const Player &right)
{
    if (!right.name && left != "") return false;
    if (!right.name && left == "") return true;
    if (right.name && left == "") return false;
    return !strcmp(left.c_str(), right.name);
}
bool operator==(const Player &left, const std::string &right)
{
    if (!left.name && right != "") return false;
    if (!left.name && right == "") return true;
    if (left.name && right == "") return false;
    return !strcmp(right.c_str(), left.name);
}

//arithmatic - alter points in base class
Player& Player::operator+=(const int points_in)
{
    points += points_in;
    return *this;
}

Player& Player::operator-=(const int points_in)
{
    points -= points_in;
    return *this;
}

Player operator+(const Player &left, const int right)
{
    Player temp(left);
    temp.points += right;
    return temp;

}
Player operator+(const int left, const Player &right)
{
    Player temp(right);
    temp.points += left;
    return temp;
}
Player operator+(const Player &left, const Player &right)
{
    Player temp(left);
    temp.points += right.points;
    return temp;
}

Player operator-(const Player &left, const int right)
{
    Player temp(left);
    temp.points -= right;
    return temp;
}
Player operator-(const int left, const Player &right)
{
    Player temp(right);
    temp.points = left;
    temp.points -= right.points;
    return temp;
}
Player operator-(const Player &left, const Player &right)
{
    Player temp(left);
    temp.points -= right.points;
    return temp;
}

//insertion
std::ostream& operator<<(std::ostream &out, const Player &object)
{
    using std::setw, std::left, std::right, std::flush, std::setfill;
    out << left << setw(9) << object.name << "(" << setw(2) << object.points << "pts)";
    return out;
}

//extraction
std::istream& operator>>(std::istream &in, Player &object)
{
    char temp[1000];
    in.get(temp, 1000, '\n');
    while (strlen(temp) > 9){
        in.ignore(100, '\n');
        std::cout << "\nSorry, but your player name must be 10 characters or less.\n"
             << "Enter a shorter name.\n>";
        in.get(temp, 1000, '\n');
    }
    in.ignore(100, '\n');
    if (object.name){
        delete [] object.name;
        object.name = nullptr;
    }
    object.name = new char[strlen(temp) + 1];
    strcpy(object.name, temp);
    return in;
}

//negation
bool Player::operator!()
{
    return name == nullptr;
}

//prefix
Player& Player::operator++()
{
    ++points;
    return *this;
}
Player& Player::operator--()
{
    --points;
    return *this;
}

//postfix
Player Player::operator++(int)
{
    Player temp(*this);
    ++points;
    return temp;
}
Player Player::operator--(int)
{
    Player temp(*this);
    --points;
    return temp;
}

//reads a string in and returns it
const std::string Player::read_string()
{
    using std::string, std::cout, std::endl, std::cin;
    string the_string;
    cout << "\033[38;5;35m" << ">>" << "\033[0m";;
    getline(cin, the_string);
    return the_string;
}

//reads an int in and return it
const int Player::read_int()
{
    using std::string, std::cout, std::endl, std::cin;
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

/*
 **************************************************************************
 * Easy implementation
 * data members are:
 *      char *motto
 ***************************************************************************
 */

//default constructor
Easy::Easy() : Player(), emoji(nullptr) {}

//constructor - builds an easy player w/ set number of points
Easy::Easy(const int points) : Player(points), emoji(nullptr) {}

//copy constructor
Easy::Easy(const Easy &source) : Player(source), emoji(nullptr)
{
    if (!source.emoji) return;
    emoji = new char[strlen(source.emoji) + 1];
    strcpy(emoji, source.emoji);
}

//assignemnt operator
Easy& Easy::operator=(const Easy &source)
{
    if (this == &source)
        return *this;

    Player::operator=(source);
    if (emoji){
        delete [] emoji;
        emoji = nullptr;
    }
    if (source.emoji){
        emoji = new char[strlen(source.emoji) + 1];
        strcpy(emoji, source.emoji);
    }
    return *this;
}

//destructor
Easy::~Easy()
{
    if (emoji){
        delete [] emoji;
        emoji = nullptr;
    }
}

bool Easy::operator()()
{
    using std::cout, std::setw, std::left, std::right, std::setfill, std::endl;
    cout << "\nChoose an emoji to represent how you feel about this game." << endl;
    cout << "\nYour choices are:\n"
         << "1. 🔥\n"
         << "2. 👍\n"
         << "3. 👀 \n"
         << "4. 💀\n"
         << "5. 👎" << endl;
    int choice{read_int()};
    while (choice < 1 || choice > 5){
        cout << "\nEnter a choice between 1 and 5" << endl;
        choice = read_int();
    }
    char selection[10];
    switch (choice){
        case 1:
            strcpy(selection, "🔥\0");
            break;
        case 2:
            strcpy(selection, "👍\0");
            break;
        case 3:
            strcpy(selection, "👀\0");
            break;
        case 4:
            strcpy(selection, "💀\0");
            break;
        case 5:
            strcpy(selection, "👎\0");
            break;
    }
    if (emoji)
        delete [] emoji;
    emoji = new char[strlen(selection) + 1];
    strcpy(emoji, selection);
    int correct{rand()%5};
    if (choice == correct){
        cout << "\nNice! Adding points to your score." << endl;
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream &out, const Easy &object)
{
    using std::left, std::setw;
    out << left << setw(7) << object.name << "(" << setw(2) << object.points << "pts)";
    if (object.emoji)
        out << object.emoji;
    return out;
}


//arithmatic - alter points in base class
Easy& Easy::operator+=(const int points_in)
{
    points += points_in;
    return *this;
}
Easy& Easy::operator-=(const int points_in)
{
    points -= points_in;
    return *this;
}
Easy operator+(const Easy &left, const int right)
{
    Easy temp(left);
    temp.points += right;
    return temp;
}
Easy operator+(const int left, const Easy &right)
{
    Easy temp(right);
    temp.points += left;
    return temp;
}
Easy operator+(const Easy &left, const Easy &right)
{
    Easy temp(left);
    temp.points += right.points;
    return temp;
}
Easy operator-(const Easy &left, const int right)
{
    Easy temp(left);
    temp.points -= right;
    return temp;
}
Easy operator-(const int left, const Easy &right)
{
    Easy temp(right);
    temp.points = left;
    temp.points -= right.points;
    return temp;
}
Easy operator-(const Easy &left, const Easy &right)
{
    Easy temp(left);
    temp.points -= right.points;
    return temp;
}


/*
 **************************************************************************
 * Medium implementation
 * data members are:
 *      char *motto
 ***************************************************************************
 */

//default constructor
Medium::Medium() : Player(), entries(0) {}

//constructor to set points
Medium::Medium(int points) : Player(points), entries(0) {}

bool Medium::operator()()
{
    bool correct{false};
    using std::cout, std::setw, std::left, std::right, std::setfill, std::endl, std::cin;
    cout << "\nGuess the number between 1 and 5 to gain points." << endl;
    int guess{read_int()};
    int answer{rand()%5};
    if (guess == answer){
        cout << "\nNice, you guessed correctly. Adding points to your score." << endl;
        correct = true;
    }
    char choice{};
    cout << "\nMake a journal entry?\n\033[38;5;35m>>\033[0;0m";
    cin >> choice;
    cin.ignore(100, '\n');
    if (toupper(choice) == 'Y'){
        cout << "\n\033[38;5;35m>>\033[0;0m";
        cin >> *this;
    }
    cout << "\n\nHere are all your journal entries from each turn of this game:" << endl;
    for (auto item : journal_entries)
        cout << item << endl;

    return correct;
}

//for reading into a journal entry
std::istream& operator>>(std::istream &in, Medium &object)
{
    using std::string, std::cin, std::to_string;
    string entry{to_string(object.entries + 1)};
    string text{};
    entry.append(". ");
    getline(in, text);
    entry.append(text);
    object.journal_entries.emplace_front(entry);
    ++object.entries;
    return in;
}

//arithmatic - alter points in base class
Medium& Medium::operator+=(const int points_in)
{
    points += points_in;
    return *this;
}
Medium& Medium::operator-=(const int points_in)
{
    points -= points_in;
    return *this;
}
Medium operator+(const Medium &left, const int right)
{
    Medium temp(left);
    temp.points += right;
    return temp;

}
Medium operator+(const int left, const Medium &right)
{
    Medium temp(right);
    temp.points += left;
    return temp;
}
Medium operator+(const Medium &left, const Medium &right)
{
    Medium temp(left);
    temp.points += right.points;
    return temp;
}
Medium operator-(const Medium &left, const int right)
{
    Medium temp(left);
    temp.points -= right;
    return temp;
}
Medium operator-(const int left, const Medium &right)
{
    Medium temp(right);
    temp.points = left;
    temp.points -= right.points;
    return temp;
}
Medium operator-(const Medium &left, const Medium &right)
{
    Medium temp(left);
    temp.points -= right.points;
    return temp;
}


/*
 **************************************************************************
 * Hard implementation
 * data members are:
 *      char *motto
 ***************************************************************************
 */
//default constructor
Hard::Hard() : Player(){}

//constructor to set points
Hard::Hard(int points) : Player(points), riddles_loaded(load_riddles()) {}

//fill map w/ riddles
int Hard::load_riddles()
{
    int item{};
    using std::string, std::ifstream;
    ifstream filein;
    filein.open("riddles.txt");
    if (!filein)
        throw FILE_ERROR::riddle_exception();
    filein.peek();
    if (filein.eof())
        throw FILE_ERROR::riddle_exception();
    while (!filein.eof()){
        string riddle{};
        string ans{};
        getline(filein, riddle, ',');
        getline(filein, ans, '\n');
        riddles[item] = riddle;
        answers[item] = ans;
        filein.peek();
        ++item;
    }
    return item;
}

bool Hard::operator()()
{
    using std::cout, std::setw, std::left, std::right, std::setfill, std::endl, std::string, std::transform, std::tolower;
    cout << "\nCorrectly answer a C++ questions to gain a significant point boost.\n"
         << "You can answer multiple questions as long as you keep getting them correct." << endl;
    int riddle_num = rand()%riddles_loaded;
    cout << "\nThe riddle is: \n" << riddles[riddle_num]
         << "\nEnter your answer (not case sensitive)." << endl;
    string player_answer{read_string()};
    string answer{answers[riddle_num]};
    transform(answer.begin(), answer.end(), answer.begin(),
        [](unsigned char c){return tolower(c);});
    transform(player_answer.begin(), player_answer.end(), player_answer.begin(),
        [](unsigned char c){return tolower(c);});
    if (answer == player_answer){
        cout << "\nNice work! Points added." << endl;
        return true;
    }
    cout << "\nSorry, but the correct answer was:\n" << "\033[38;5;95m" <<  answers[riddle_num] << "\033[0;0m" << endl;
    return false;
}

//arithmatic - alter points in base class
Hard& Hard::operator+=(const int points_in)
{
    points += points_in;
    return *this;
}
Hard& Hard::operator-=(const int points_in)
{
    points -= points_in;
    return *this;
}
Hard operator+(const Hard &left, const int right)
{
    Hard temp(left);
    temp.points += right;
    return temp;

}
Hard operator+(const int left, const Hard &right)
{
    Hard temp(right);
    temp.points += left;
    return temp;
}
Hard operator+(const Hard &left, const Hard &right)
{
    Hard temp(left);
    temp.points += right.points;
    return temp;
}
Hard operator-(const Hard &left, const int right)
{
    Hard temp(left);
    temp.points -= right;
    return temp;
}
Hard operator-(const int left, const Hard &right)
{
    Hard temp(right);
    temp.points = left;
    temp.points -= right.points;
    return temp;
}
Hard operator-(const Hard &left, const Hard &right)
{
    Hard temp(left);
    temp.points -= right.points;
    return temp;
}
