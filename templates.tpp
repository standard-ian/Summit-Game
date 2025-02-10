/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/23/2025
 * CS302 Winter 2025
 * Program 2
 *
 ********************************************************************
 * data structures templates implementation
 *********************************************************************
 */

/*
 **************************************************************************
 * Node template implementation
 * data members are:
 *      vector<TYPE> objects
 *      Node<TYPE> *next
 *      Node<TYPE> *prev
 ***************************************************************************
 */

//Node constructor
template <typename TYPE>
Node<TYPE>::Node() : next(nullptr), prev(nullptr), objects_here(0), num_objects(0), list_length(0), space_num(0) {}

//get next
template <typename TYPE>
Node<TYPE>*& Node<TYPE>::get_next()
{
    return next;
}

//get prev
template <typename TYPE>
Node<TYPE>*& Node<TYPE>::get_prev() {
    return prev;
}

//has next
template <typename TYPE>
bool Node<TYPE>::has_next()
{
    if (next)
        return true;
    return false;
}

//has prev
template <typename TYPE>
bool Node<TYPE>::has_prev()
{
    if (prev) return true;
    return false;
}

//set next pointer
template <typename TYPE>
void Node<TYPE>::set_next(Node<TYPE> *new_next)
{
    next = new_next;
}

//set previous pointer
template <typename TYPE>
void Node<TYPE>::set_prev(Node<TYPE> *new_prev)
{
    prev = new_prev;
}

//return a node's vector
template <typename TYPE>
void Node<TYPE>::copy(const Node<TYPE> &source)
{
    objects_here = source.objects_here;
    num_objects = source.num_objects;
    list_length = source.list_length;
    space_num = source.space_num;
    objects = source.objects;
}

//set the vector at a node up for the correct number of objects
template <typename TYPE>
void Node<TYPE>::size_vector(const int num, const int length)
{
    objects.resize(num);
    num_objects = num;
    list_length = length;
}

//establish a space number at each node
template <typename TYPE>
void Node<TYPE>::set_space_num(const int num)
{
    space_num = num;
}

//display a single space and if appropriate, connections to the next line
template <typename TYPE>
void Node<TYPE>::display_vector()
{
    using std::cout, std::endl, std::setw, std::left, std::right, std::setfill, std::flush;

    cout << "\033[38;5;35m" << '[';
    cout << "\033[38;5;39m" << setw(2) << right <<  space_num << "\033[38;5;35m" << "│" << "\033[0;00m";

    for(auto item = objects.begin(); item != objects.end(); ++item){
        if (!(*item))
            cout << "                ";
        else
            cout << setw(17) << *item << flush;
        if (item != objects.end() -1)
            cout << "\033[38;5;35m" << "│" << "\033[0;0m";
    }
    cout << "\033[38;5;35m" << "]";
        switch (num_objects){
            case 2: {
                if ((list_length - space_num + 1) % 4 == 0)
                cout << "\033[38;5;35m" << "─┐\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t       │"
                     << "\n┌──────────────────────────────────────────────────────────────────────────"
                     << "────────────────────────────────────────────────────────────────────────────────────┘\n│\n└─" << "\033[0;00m";
                    }
                break;
            case 3: {
                if ((list_length - space_num + 1) % 2 == 0)
                cout << "\033[38;5;35m" << "─┐\n\t\t\t\t\t\t\t\t\t\t\t\t\t           │"
                     << "\n┌───────────────────────────────────────────────────────────────────"
                     << "───────────────────────────────────────────────┘\n│\n└─" << "\033[0;00m";
                    }
                break;
            case 4: {
                if ((list_length - space_num + 1) % 2 == 0)
                cout << "\033[38;5;35m" << "─┐\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t             │"
                     << "\n┌───────────────────────────────────────────────────────────────────"
                     << "─────────────────────────────────────────────────────────────────────────────────┘\n│\n└─" << "\033[0;00m";
                    }
                break;
        }
}

//place an object in the vector at a node
template <typename TYPE>
bool Node<TYPE>::place_item(const TYPE &object)
{
    DLL_ERROR ERROR;
    if (objects_here > 4)
        throw ERROR.full_vec;
    if (space_num == list_length){
        objects[objects_here] = object;
        ++objects_here;
        return false;
    }

    for (auto item : objects){
        if (object == item)
            throw ERROR.bad_name;
    }
    objects[objects_here] = object;
    ++objects_here;
    return true;
}

//makes a copy of the item matching the key, removes it, then returns the copy
template <typename TYPE>
TYPE Node<TYPE>::move(const std::string &key)
{
    TYPE temp;
    for (auto item = objects.begin(); item != objects.end();){
        if (key == *item){
            temp = *item;
            item = objects.erase(item);
            objects.resize(num_objects);
            --objects_here;
            break;
        }
        else
            ++item;
    }
    return temp;
}

//find an object in a nodes vector and returns a reference to it
//throws an error if the item is not found because we can't return anything
template <typename TYPE>
TYPE& Node<TYPE>::retrieve(const std::string &key)
{
    for (int item = 0; item < objects_here; ++item){
        if (objects[item] == key){
            return objects[item];
        }
    }
    throw std::out_of_range("Key not found in list.");
}

//find an in a nodes vector and returns true if it's there
template <typename TYPE>
bool Node<TYPE>::find(const std::string &key)
{
    bool found{false};
    for (auto item : objects)
        if (item == key){
            found = true;
        }
    return found;
}

/*
 **************************************************************************
 * DLL template implementation
 * data members are:
 *      int length *
 *      Node<TYPE> *head
 *      Node<TYPE> *tail
 ***************************************************************************
 */

//default constructor
template <typename TYPE, const int LENGTH>
DLL<TYPE, LENGTH>::DLL() : head(nullptr), tail(nullptr), length(LENGTH){}

//destructor
template <typename TYPE, const int LENGTH>
DLL<TYPE, LENGTH>::~DLL()
{
    remove_all();
    length = 0;
    head = nullptr;
    tail = nullptr;
}

//copy constructor
template <typename TYPE, const int LENGTH>
DLL<TYPE, LENGTH>::DLL(const DLL<TYPE, LENGTH> &source) : head(nullptr), tail(nullptr), length(source.length)
{
    deep_copy(source);
}

//assignemnt operator
template <typename TYPE, const int LENGTH>
DLL<TYPE, LENGTH>& DLL<TYPE, LENGTH>::operator=(const DLL<TYPE, LENGTH> &source)
{
    if (this == &source)
        return *this;
    deep_copy(source);
    return *this;
}

//find an item in the list based on the string key
template <typename TYPE, const int LENGTH>
TYPE& DLL<TYPE, LENGTH>::operator[](std::string &key)
{
    return find_sub(key, head);
}

//searches for the correct node containing the key
template <typename TYPE, const int LENGTH>
TYPE& DLL<TYPE, LENGTH>::find_sub(const std::string &key, Node<TYPE> *&current)
{
    if (!current)
        throw std::out_of_range("Key not found in list.");
    if (current -> find(key))
        return current -> retrieve(key);
    return find_sub(key, current -> get_next());
}

//wrapper for the find to move function, shifts an item 1 node to the right
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::operator>>(TYPE& contained)
{
    int moves{1};
    if (find_to_move(contained.get_name(), moves, head))
        return true;
    return false;
}

//wrapper for the find to move function, shifts an item 1 node to the left
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::operator<<(TYPE& contained)
{
    int moves{-1};
    if (find_to_move(contained.get_name(), moves, head))
        return true;
    return false;
}

//build wrapper
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::build(const int items_at_vec)
{
    int to_build = length;
    return build(items_at_vec, head, to_build);
}

//build recursive
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::build(const int items_at_vec, Node<TYPE> *&head, int &to_build)
{
    if (to_build == 0){
        head = nullptr;
        return true;
    }
    head = new Node<TYPE>;
    head -> set_next(nullptr);
    head -> size_vector(items_at_vec, length);
    head -> set_space_num(length - to_build + 1);
    tail = head;
    --to_build;
    bool success{build(items_at_vec, head -> get_next(), to_build)};
    if (head -> get_next())
        head -> get_next() -> set_prev(head);
    return success;
}

//display wrapper
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::display()
{
    std::cout << std::endl;
    std::cout << "\033[38;5;35m" << "┌───────────────[" << "\033[38;5;39m" << "END"
              << "\033[38;5;35m" << "]\n│\n└──" << "\033[0;00m";
    return display(tail);
}


//display recursive
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::display(Node<TYPE> *tail)
{
    using std::cout, std::endl, std::setw, std::left, std::right;
    if (!tail){
        cout << "\033[38;5;35m" << "─────────────[" << "\033[38;5;39m" << "START"
             << "\033[38;5;35m" << "]" << "\033[0;00m";
        return 0;
    }
    tail -> display_vector();
    if (tail -> has_prev())
        cout << "\033[38;5;35m" << "─" << "\033[0;00m";
    return display(tail -> get_prev());
}

//remove_all wrapper
template <typename TYPE, const int LENGTH>
int DLL<TYPE, LENGTH>::remove_all()
{
    if (!head) return 0;
    return remove_all(head);
}

//remove_all recursive
template <typename TYPE, const int LENGTH>
int DLL<TYPE, LENGTH>::remove_all(Node<TYPE> *&head)
{
    if (!head) return 0;
    Node<TYPE> *hold = head -> get_next();
    delete head;
    head = nullptr;
    return remove_all(hold) + 1;
}

//place object at first position
template <typename TYPE, const int LENGTH>
std::string DLL<TYPE, LENGTH>::start(const TYPE &object)
{
    DLL_ERROR ERROR;
    if (!head -> place_item(object))
        throw ERROR.lost_key;
    return object.get_name();
}

//move item wrapper
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::move(const std::string &key, int moves)
{
    return find_to_move(key, moves, head);
}

//find item by key to move
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::find_to_move(const std::string &key, int moves, Node<TYPE> *&head)
{
    //traversed w/o finding the object anywhere
    if (!head){
        throw std::out_of_range("Key not found in list.");
    }

    //the object is in the list at current node, but there's nowherer to move. They've won.
    if (head -> find(key) && !head -> has_next())
        return false;

    //if the object is nor at head, keep looking
    if (!head -> find(key))
        return find_to_move(key, moves, head -> get_next());

    //move object in the correct direction
    if (moves < 0){
        moves *= -1;
        //use the move function to remove the object from the node and return a copy
        //put this copy right back into the list <moves> number of moves fwd or bck
        return move_bck(head -> move(key), head, moves);
    }
    return move_fwd(head -> move(key), head, moves);
}

//move object recursive forward
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::move_fwd(const TYPE &object, Node<TYPE> *&current, int &moves)
{
    if (!(current -> has_next()) || moves == 0)
        return current -> place_item(object);
    --moves;
    return move_fwd(object, current -> get_next(), moves);
}

//move object recursive backward
template <typename TYPE, const int LENGTH>
bool DLL<TYPE, LENGTH>::move_bck(const TYPE &object, Node<TYPE> *&current, int &moves)
{
    if (!(current -> has_prev()) || moves == 0)
        return current -> place_item(object);
    --moves;
    return move_bck(object, current -> get_prev(), moves);
}

//deep copy wrapper
template <typename TYPE, const int LENGTH>
int DLL<TYPE, LENGTH>::deep_copy(const DLL<TYPE, LENGTH> &source)
{
    remove_all();
    length = source.length;

    return deep_copy(source.head, head);
}

//deep copy wrapper
template <typename TYPE, const int LENGTH>
int DLL<TYPE, LENGTH>::deep_copy(Node<TYPE> *source, Node<TYPE> *&dest)
{
    if (!source){
        dest = nullptr;
        return 0;
    }
    int copied;
    dest = new Node<TYPE>;
    dest -> copy(*source);
    dest -> set_next(nullptr);
    copied = deep_copy(source -> get_next(), dest -> get_next());
    if (dest -> has_next())
        dest -> get_next() -> set_prev(dest);
    else
        tail = dest;
    return copied;
}
