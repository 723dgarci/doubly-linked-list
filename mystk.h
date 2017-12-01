//
// Created by WorkD on 10/15/2017.
//

#ifndef ASSIGNMENT2_MYSTK_H
#define ASSIGNMENT2_MYSTK_H

#include "List.h"

using namespace cop4530;

template <typename T>
class mystk {
public:
    mystk(): L{}{}
    mystk(int num, const T& val){
        L = List<T>(num,val);
        size = num;
    }
    ~mystk (){
        std::cout<< "\nmystk distructor\n";
    }
    void push(const T & data){
        size++;
        L.push_back(data);
    }
    void pop(){
        size--;
        L.pop_back();
    }
    T& top(){*(--L.end());}
    const T& top() const {
        return *(--L.end());
    }

    int getsize() const { return size;}
private:
    List<T> L;
    int size;
};


#endif //ASSIGNMENT2_MYSTK_H
