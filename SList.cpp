#include "SList.h"

/*The constructor*/
SList::SList():first(0), last(0){
}

/*Destructor*/
SList::~SList(){
    deleteNodes();
}

/*Copy constructor*/
SList::SList(const SList& other):first(0), last(0){
    SListNode* current = other.first;
    while(current != 0){
        SListNode* newNode = new SListNode(current->Getvalue());
        if(!newNode)
            throw bad_alloc();
        if(first == 0){
            first = newNode;
            last = newNode;
        }
        else{
            last->Setnext(newNode);
            last = newNode;
        }
        current = current->Getnext();
    }
}

/*Assignment operator overloading*/
SList& SList::operator=(const SList& rhs){
    if (this == &rhs) return *this; // handle self assignment


    deleteNodes();
    SListNode* current = rhs.first;
    while(current != 0){
        SListNode* newNode = new SListNode(current->Getvalue());
        if (!newNode)
            throw bad_alloc();
        if(first == 0){
            first = newNode;
            last = newNode;
        }
        else{
            last->Setnext(newNode);
            last = newNode;
        }
        current = current->Getnext();
    }
    return *this;
}

std::string SList::front() const{
    if(!first){
        throw empty_list();
    }
    return first->Getvalue();
}

/*Function for deleting the dynamically assigned memory of the list*/

void SList::deleteNodes(){
    if(first != 0){
        SListNode* current = first;
        SListNode* next = first->Getnext();
        while(next != 0){
            delete current;
            current = next;
            next = current->Getnext();
        }
        delete current;
    }
    first = 0;
    last = 0;
}

void SList::push_front(std::string value){
    SListNode* newNode = new SListNode(value);
    if(!newNode)
        throw bad_alloc();
    newNode->Setnext(first);
    first = newNode;
    if(last == 0)
        last = newNode;
}
std::string SList::pop_front(){
    if(!first)
        throw empty_list();
    SListNode* oldFirst = first;
    std::string value = oldFirst->Getvalue();
    first = oldFirst->Getnext();
    if(last == oldFirst)
        last = 0;
    delete oldFirst;
    return value;
}

/*Note the origin check. See SList.h for more information about iterator
 * sanity checks.
 */
void SList::insert_after(std::string value, iterator position){
    if(position.origin != this)
        throw bad_iterator();
    SListNode* newNode = new SListNode(value);
    if(!newNode)
        throw bad_alloc();
    SListNode* node = position.curr;
    newNode->Setnext(node->Getnext());
    node->Setnext(newNode);
    if(node == last)
        last = newNode;
}
void SList::delete_after(iterator position){
    if(position.origin != this)
        throw bad_iterator();

    SListNode* node = position.curr;

    if(node->Getnext() == 0){
        return;
    }
    SListNode* toBeDeleted = node->Getnext();
    node->Setnext(toBeDeleted->Getnext());
    if(toBeDeleted == last)
        last = node;
    delete toBeDeleted;
}

/* The swap function simply switches the pointers around between two lists.*/
void SList::swap(SList& other){
    SListNode* temp = first;
    first = other.first;
    other.first = temp;
    temp = last;
    last = other.last;
    other.last = temp;
}

void SList::reverse(){
    if(first == last)
        return;

    SListNode* current = first;
    SListNode* prev = 0;
    SListNode* next = 0;
    while(current != 0){
        next = current->Getnext();
        current->Setnext(prev);
        prev = current;
        current = next;
    }
    SListNode* temp = first;
    first = last;
    last = temp;

}

/* The check function confirms that the class invariant is in place. The invariant
 * is in place if and only if:
 * 1. If and only if the first pointer is null, then the last pointer is aswell
 * 2. Last pointer points to the very last node of the list
 * 3. If the first pointer is not null, then when traversing the list forward,
 * the node pointed by the last pointer will appear before the end of the list.
 *
 * If these claims are untrue, then the class invariant is false.
 */
bool SList::check(){
    if(first == 0 && last != 0)
        return false;
    if(first != 0 && last == 0)
        return false;
    if(last != 0 && last->Getnext() != 0)
        return false;
    if(first != 0){
        SListNode* curr = first;
        while(curr != last && curr != 0){
            curr = curr->Getnext();
        }
        if (curr != last)
            return false;
    }
    return true;
}

SList::iterator SList::begin(){
    iterator i = iterator(first);
    i.origin = this;
    return i;
}
SList::iterator SList::end(){
    iterator i = iterator(0);
    i.origin = this;
    return i;
}
SList::const_iterator SList::end() const{
    const_iterator i = const_iterator(0);
    i.origin = this;
    return i;
}
SList::const_iterator SList::begin() const{
    const_iterator i = const_iterator(first);
    i.origin = this;
    return i;
}


std::ostream& operator <<(std::ostream& out, SList& list){
    for(SList::iterator i = list.begin(); i != list.end(); ++i){
        out << *i <<"\n";
    }
    return out;
}


/* The input operator overloading only accepts a certain format of input.
 * If the format is not correct, the function returns and sets the failbit
 * on the input stream. The input is read safely, which means, that in case
 * of a failure, no input will be saved.
 */
std::istream& operator >>(std::istream& in, SList& list){
    SList tempList = list;
    char ch = ' ';
    in >> ch;
    if(ch != '{'){
        in.unget();
        in.clear(std::ios_base::failbit);
        return in;
    }
    std::string temp = "";

    while(1){
        if(in.eof()){
            in.clear(std::ios_base::failbit);
            return in;
        }
        in >> temp;
        if(in.fail()){
            return in;
        }
        if(temp == "}")
            break;
        if(temp.at(temp.length()-1) == '}'){
            tempList.push_front(temp.substr(0, temp.length()-1));
            break;
        }
        tempList.push_front(temp);
    }
    list.swap(tempList);
    return in;
}