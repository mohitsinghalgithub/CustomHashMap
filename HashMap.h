#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <memory>

using namespace std;

template<typename T, typename U>
class HashMap
{
    using Data = std::pair<T, U>;
    using key_type = T;
    using value_type = U;

    int m_capacity;
    vector<list<Data>> m_bucket;
    int num_element;
    double max_load_factor;
public:
    using iterator = typename list<Data>::iterator;
    HashMap(int capacity = 1);
    std::pair<iterator, bool> insert(const T& key, const U& value);
    template<typename ... Args>
    std::pair<iterator, bool> try_emplace(Args &&... args);
    template<typename ... Args>
    std::pair<iterator, bool> emplace(Args &&... args);
    void erase(const T & key);
    int hashFunction(const key_type & key);
    U & operator[](const T & key);
    template<typename TupleKey, typename TupleValue>
    T extract_key(std::piecewise_construct_t,
                        TupleKey&& key_tuple,
                        TupleValue&&);
    const T& extract_key(const T & key, const U& value);
    const T& extract_key(const std::pair<T, U>& pair);
    void rehashBucket();
};
