/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/25/2025
 * CS302 Winter 2025
 * Program 2
 *
 ********************************************************************
 * data structures template definition
 * * This template is a DLL of vectors that outputs a "game board" containing the arguments data types.
 * use it as such: DLL<data type, length>
 *
 * The following considerations are mandatory to ensure correct functionality
 *
 * This template will rely on having the following operators overloaded in the instatiating object:
 *  1. == for comparison of the underlying data's "key" or name.
 *  2. () to trigger a unique action upon use of the add function, must return a boolean value for success/faliure at the action
 *  3. += and other composite operators for modifying a "point" value
 *  4. << (insertion) for displaying the name and points
 *  5. = if the instantiating object uses dynamic memory
 *
 * Other considerations:
 *  for proper formatting, whatever is sent to the output buffer by << in your object type should at most 15 characters +/-2
 *  this template creates list of numbered spaces based on the length given in the argument list <data type, length>
 *
 *********************************************************************
 */


#include "players.h"

//bad template use exceptions
struct DLL_ERROR{
    std::string bad_name = "That key is already taken.";
    std::string full_vec = "To many items in a node.";
    std::string lost_key = "item key was lost on placement.";
};

//Node template
template <typename TYPE>
class Node
{
    public:
        Node();

        Node<TYPE>*& get_next();
        Node<TYPE>*& get_prev();
        bool has_next();
        bool has_prev();
        void set_next(Node<TYPE> *new_next);
        void set_prev(Node<TYPE> *new_next);
        void copy(const Node<TYPE> &source);

        void size_vector(const int players, const int length);
        void set_space_num(const int num);

        void display_vector();
        bool place_item(const TYPE &object);
        TYPE move(const std::string &key);
        TYPE& retrieve(const std::string &key);
        bool find(const std::string &key);

    protected:
        Node<TYPE> *next;
        Node<TYPE> *prev;
        std::vector<TYPE> objects;

        int objects_here;
        int num_objects;
        int list_length;
        int space_num;

};

//DLL template
template <typename TYPE, const int LENGTH>
class DLL
{
    public:
        DLL();
        ~DLL();
        DLL(const DLL &source);
        DLL& operator=(const DLL &source);

        //retrieve an item reference associated with a given key
        //this gets THE item in the list for modification, not a copy
        TYPE& operator[](std::string &key);

        //move an item to the left or right, removes the item from its original position
        //WARNING ! these are ugly and stupid and imlemented purely for fun
        //the move object function is superior
        bool operator<<(TYPE& contained);
        bool operator>>(TYPE& contained);

        bool build(const int items_at_vec);
        bool display();
        int remove_all();
        std::string start(const TYPE &object);
        bool move(const std::string &key, int moves);
        int deep_copy(const DLL<TYPE, LENGTH> &source);

    private:
        Node<TYPE> *head;
        Node<TYPE> *tail;
        int length;

        TYPE& find_sub(const std::string &key, Node<TYPE> *&);
        bool build(const int items_at_vec, Node<TYPE> *&head, int &to_build);
        bool display(Node<TYPE> *head);
        int remove_all(Node<TYPE> *&head);
        bool find_to_move(const std::string &key, int moves, Node<TYPE> *&head);
        bool move_fwd(const TYPE &object, Node<TYPE> *&head, int &moves);
        bool move_bck(const TYPE &object, Node<TYPE> *&head, int &moves);
        int deep_copy(Node<TYPE> *source, Node<TYPE> *&dest);
};

#include "templates.tpp"

