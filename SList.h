/**
 * Author: Kimmo Heikkinen
 * File: SList.h
 * Description:
 * A header file for an implementation of singly linked list of
 * string values.
 */

#ifndef SLIST_H
#define SLIST_H
#include <string>
#include <iostream>

/*
 * Declaration of the class SListNode, used as a node for the linked list.
 * Copy constructor, assignment constructor and destructor are not declared,
 * because default ones are used.
 */
class SListNode{
    public:
        SListNode(std::string text):value(text), next(0){}
        std::string Getvalue() const { return value; }
        SListNode* Getnext() const { return next; }
        void Setnext(SListNode* val) { next = val; }
    protected:
    private:
        std::string value;
        SListNode* next;
};
/*
 * Declaration of the class SList which implements the functionality of the list.
 */
class SList{
    public:
        class iterator;
        class const_iterator;
        struct empty_list{};
        struct bad_iterator{};
        struct bad_alloc{};
        SList();
        ~SList();
        SList(const SList& other);
        SList& operator=(const SList& other);

        std::string front () const;
        void push_front(std::string value);
        std::string pop_front();
        void insert_after(std::string value, iterator position);
        void delete_after(iterator position);
        void reverse();
        void swap(SList& other);

        iterator begin ();
        iterator end ();
        const_iterator begin() const;
        const_iterator end() const;

        bool check();


    private:

        SListNode* first;
        SListNode* last;
        void deleteNodes();
};

/*
 * Declarations for the iterators. Notable part is the SList* -type variable
 * origin, which is used for sanity checks when manipulating lists trough
 * the use of iterators. Checking origin prevents using an iterator for a different
 * instance of SList to manipulate another.
 */

class SList::iterator{
    SList* origin;
    friend class SList;
    public:
        SListNode* curr;
        iterator(SListNode* p): curr(p), origin(0){}
        iterator& operator++(){curr = curr->Getnext(); return *this;}
        std::string operator*(){return curr->Getvalue();}
        bool operator==(const SList::iterator& b) const {return curr == b.curr;}
        bool operator!=(const SList::iterator& b) const {return curr != b.curr;}

};
class SList::const_iterator{
    const SList* origin;
    friend class SList;
    public:
        const SListNode* curr;
        const_iterator(SListNode* p): curr(p), origin(0){}
        const_iterator& operator++(){curr = curr->Getnext(); return *this;}
        std::string operator*() {return curr->Getvalue();}
        bool operator==(const SList::const_iterator& b) const {return curr == b.curr;}
        bool operator!=(const SList::const_iterator& b) const {return curr != b.curr;}

};

std::ostream& operator<<(std::ostream&, SList&);
std::istream& operator>>(std::istream&, SList&);
#endif // SLIST_H
