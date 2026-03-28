#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <memory>

using namespace std;

template<typename T, typename U>
class HashMap
{
    typedef T key_type;
    typedef U value_type;

    struct Data
    {
        T key;
        U value;
    };

    int m_capacity;
    vector<list<unique_ptr<Data> >> m_hashMap;
public:
    HashMap(int capacity = 10);

};
