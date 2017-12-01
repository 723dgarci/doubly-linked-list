/* Programmer: Daniel Garcia
 * Date: 10/12/17
 * Program: This is a implementation of a doubly linked list with iterators
 * This file is the definitions of the functions given to define.
 * */
#include "List.h"

using namespace cop4530;

    ///constructors & destructor
    //initialize to an empty list
    template<typename T>
    void List<T>::init() {
        theSize =0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

    // create empty linked list
    template<typename T>
    List<T>::List (){ init(); }

    template <typename T>
    List<T>::~List () {
        clear();                            //deletes all elements
        delete head;                        //delete terminal nodes and set to null
        delete tail;
        head = tail = nullptr;
    }

    // create list with num copies of val
    template<typename T>
    List<T>::List( int num, const T& val) {
        init();                                         //start off as empty
        for (int i = 0; i < num; i++) {
            push_front(val);
        }
    }

    template <typename T>
    List<T>::List (List<T> && rhs)
            : theSize{rhs.theSize} , head{rhs.head}, tail{rhs.tail}
    {
        rhs.theSize =0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    //copy constructor
    template<typename T>
    List<T>::List(const List &rhs): theSize(rhs.theSize){
        init();                                                 //start off empty
        auto s = --begin();                                     //make starting point
        for(auto i = rhs.begin(); i != rhs.end(); i++)          //go through rhs and insert the values into this list
            s = insert(s,*i);
    }

    //move assignment operator
    template<typename T>
    const List<T>& List<T>::operator= (const List<T> &rhs) {        // move assignment operator
        if(this != &rhs) {                                          // skip if self assignment
            auto copy = rhs;                                        //used copy constructor
            std::swap(*this, copy);                                 //swap dummy
        }
        return *this;
    }

    template<typename T>
    List<T>& List <T> ::operator= (List &&rhs) {        // move assignment operator
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        return *this;
    }

    //constructor consist of range given in iterators
    template<typename T>
    List<T>::List(const_iterator start, const_iterator end){
        init();
        auto n = --begin();
        while(start != end) {
            n = insert(n, *start);
            start++;
        }
    }

    //constructor made of std::initializer_list<T>
    template<typename T>
    List<T>::List (std::initializer_list<T> iList){
        init();                                         //make empty list
        for(auto &x: iList) {                            //push back each element brought in
            push_back(x);
        }
    }

    //assignment operator made of std::initializer_list<T>
    template<typename T>
    List<T>& List<T>::operator= (std::initializer_list<T> iList){
        clear();                                        //delete previous elements
        for(auto &x: iList)                            //push back each element brought in
            push_back(x);

        return *this;
    }

    ///Basic accessors
    //chks if empty
    template<class T>
    bool List<T>::empty () const { return theSize == 0; }

    //gets size
    template<class T>
    int List<T>::size () const { return theSize; }

    /// element accessors
    //return first modifiable element style
    template<class T>
   T& List<T>::front () { return *begin(); }                // return head element of list

    //return first const element style
    template<class T>
    const T& List<T>::front () const { return *begin(); }       //automatic type conversion

    //return the modifiable last element
    template<class T>
    T& List<T>::back () { return *end(); }                    // return tail element of list

    //return the const last element
    template<class T>
    const T& List<T>::back () const { return *end(); }                    // return tail element of list

    ///iterator accessors
    //return iterator to the first element (modifiable)
    template <typename T>
    typename List<T>::iterator List<T>::begin(){
        return head->next;
    }

    //return iterator to the first element (const)
    template <typename T>
    typename List<T>::const_iterator List<T>::begin() const{
        return head->next;
    }

    //return iterator to the last element (modifiable)
    template <typename T>
    typename List<T>::iterator List<T>::end(){
        return tail;
    }

    //return iterator to the last element (const)
    template <typename T>
    typename List<T>::const_iterator List<T>::end() const{
        return tail;
    }

    ///Insert and pushes
    //Insert val ahead of iter as an element
    template<typename T>
    typename List<T>::iterator List<T>::insert(iterator itr, const T &val) {
        Node * nn = new Node(val, itr.current ,itr.current->next);              //create a new node
        Node * p = itr.current->next;
        theSize++;
        p->prev =itr.current->next = nn;;
        return nn;
    }

    template <typename T>
    typename List<T>::iterator List<T>::insert(iterator itr, T &&val) {
        Node * nn = new Node(std::move(val), itr.current ,itr.current->next);              //create a new node
        Node * p = itr.current->next;
        theSize++;
        p->prev =itr.current->next = nn;;
        return nn;
    }
    //insert at the front of list
    template<typename T>
    void List<T>::push_front(const T &val) {
        insert(--begin(), val);
    }
    //insert at the front of list
    template<typename T>
    void List<T>::push_front( T &&val) {
        insert(--begin(), val);
    }
    //insert at the back of list
    template<typename T>
    void List<T>::push_back(const T &val){
        insert((--end()),val);
    }
    //insert at the back of list
    template <typename T>
    void List<T>::push_back(T &&val){
        insert((--end()),val);
    }

    ///Erase and pops
    //Erase one element from list
    //delete element at itr
    template<typename T>
    typename List<T>::iterator List<T>::erase(List<T>::iterator itr){
        theSize--;
        Node * rm = itr.current;
        auto  n = (++itr);
        rm->prev->next= rm->next;
        rm->next->prev= rm->prev;
        delete rm;
        return n;
    }

    //delete first element in the list
    template<typename T>
    void List<T>::pop_front () {
        erase(begin());
    }

    //delete last element in list
    template<typename T>
    void List<T>::pop_back () {
        erase(--end());
    }

    //delete all ellements in the list
    template<typename T>
    void List<T>::clear () {
        while(!empty())
            pop_back();
    }

    //will delete a range {[start, end)} from calling object
    template<typename T>
    typename List<T>::iterator List<T>::erase(List<T>::iterator start, List<T>::iterator end){
        auto n = std::move(start);                     //make next iterator set to the start
        for(;n != end;)                                 //go though list until end and delete elements
            n = erase(n);
        return n;                                       //return end
    }

    //delete all nodes that have val
    template<typename T>
    void List<T>::remove (const T &val) {
        auto n = std::move(begin());                    //make next iterator start at the begining
        for(;n != end();) {                      //deletes each element
            if (*n == val)
                n = erase(n);
            else
                n++;
        }
    }

    ///print, remove_if, and reverse
    // print list contents in order, separated by given delimiter
    template<class T>
    void List<T>::print (std::ostream &os, char delim) const {
        if (empty())
            os << "Empty\n";
        else {
            auto itr = begin();
            for (int i = 0; i < theSize; i++) {
                os << *itr;
                itr++;
                if (i < theSize - 1)
                    os << delim;
            }
        }
        //std::cout <<"print list end\n";
    }

    //recursive counting (acting like there is not theSize data element)
    template<typename T>
    int List<T>::count (int s , iterator i) {
        if(s == 0)                      //first time around need to initialize i
            i = begin();
        if(i == end())
            return 0;

        else if(++i == end()){          //incremet to next element and chk if it is end
            s++;                        //count last element(prevous node)
            return s;
        }
        else
            count(++s, i);              //count this element and go on to next

    }

    // print list contents in order (the intuitive way)
    template<typename T>
    std::ostream & operator<<(std::ostream &os, const List<T> &l){
        if (l.empty())
            os << "Empty\n";
        else {
            auto itr = l.begin();
            for (int i = 0; i < l.size(); i++) {
                os << *itr;
                itr++;
                if (i < l.size() - 1)
                    os << ' ';
            }
        }
        return os;
    }
    //returns true if 2 lists are equal to one another
    template <typename T>
    bool operator==(const List<T> & lhs, const List<T> &rhs){
        if (lhs.size() == rhs.size()) {                 //if they dont even have the same size return false at the bottom
            auto lb = lhs.begin(), rb = rhs.begin();    //used to iterate through lists
            while (lb != lhs.end()) {                   //goes through each element if they do not match return false
                if (*lb != *rb) {
                    return false;
                }
                else {                                  //increment
                    lb++;
                    rb++;
                }
            }
            return true;                                //it is equal
        }

        return false;
    }

    template <typename T>
    bool operator!=(const List<T> & lhs, const List<T> &rhs){
        return !(lhs == rhs);
    }

    template <typename T>
    void List<T>::reverse() {       // reverse the order of the elements
        auto i = begin();           //start iterator at beginning
        while( i != end()) {        //while the end is not reached..
            push_front(*i);         //add the first element to the front of the list
            i = erase(i);           //remove the element at current position, and return the next element
        }
    }
    template <typename T>
    template <typename PREDICATE>
    void List<T>::remove_if(PREDICATE pred) {    // remove all elements for which Predicate pred
        auto i = begin();
        while(i != end()){                      //walk through
            if(pred(*i))                        //if meets predicate delete element, else to to next element
                i = erase(i);
            else
                i++;
        }
    }


/*********************************************************/
//iterators                                              //
//-does not do bonds checking                            //
/*********************************************************/
template<typename T>
List<T>::const_iterator::const_iterator(): current(nullptr){}            // default zero parameter constructor
///accessors
// operator*() to return element
template<typename T>
const T & List<T>::const_iterator::operator*() const{
    return retrieve();
}

//returns current's data
template<typename T>
T & List<T>::const_iterator::retrieve () const { return current->data;}

/// increment/decrement operators
template<typename T>
 typename List<T>::const_iterator & List<T>::const_iterator::operator++(){
    current = current->next;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator:: operator++(int){
    auto temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--(){
    current = current->prev;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int){
    auto temp = *this;
    --(*this);
    return temp;
}
template<typename T>
List<T>::const_iterator::const_iterator(Node *p): current(p){}

/// comparison operators
template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{ return current == rhs.current;}

template<typename T>
bool List<T>::const_iterator:: operator!=(const const_iterator &rhs) const
{ return !(*this == rhs);}

/////normal iterator's constructors
template<typename T>
List<T>::iterator::iterator () {}

template<typename T>
List<T>::iterator::iterator (Node *p):const_iterator{p} {}

///accessors
template<typename T>
const T& List<T>::iterator::operator* () const {
    return const_iterator::retrieve();
}

template<typename T>
 T& List<T>::iterator::operator* ()  {
    return const_iterator::retrieve();
}

///(in/de)crement oprators
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++(){
    this->current = this->current->next;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator:: operator++(int){
    auto temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--(){
    this->current = this->current->prev;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int){
    auto temp = *this;
    --(*this);
    return temp;
}


