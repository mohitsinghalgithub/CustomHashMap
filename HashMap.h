#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <memory>

using namespace std;

template<typename T, typename U>
class HashMap
{
    struct Data
    {
        T key;
        U value;
    };
    using key_type = T;
    using value_type = U;

    int m_capacity;
    vector<list<unique_ptr<Data>>> m_hashMap;
public:
    using iterator = typename list<std::unique_ptr<Data>>::iterator;
    HashMap(int capacity = 10);
    std::pair<iterator, bool> insert(const T& key, const U& value);

    int hashFunction(const key_type & key);

};
