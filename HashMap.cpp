#include "HashMap.h"

template<typename T, typename U>
HashMap<T, U>::HashMap(int capacity):m_capacity(capacity)
{
    m_hashMap.reserve(capacity);
}

template<typename T, typename U>
int HashMap<T, U>::hashFunction(const T& key)
{
    std::hash<T> hasher;

    size_t hashCode = hasher(key);

    return hashCode % m_capacity;
}

template<typename T, typename U>
std::pair<typename HashMap<T, U>::iterator, bool> HashMap<T, U>::insert(const T& key, const U& value)
{
    int index = hashFunction(key);
    for(iterator itr = m_hashMap[index].begin(); itr != m_hashMap[index].end(); itr++)
    {
        if((*itr)->m_key == key)
        {
            return {itr, false};
        }
    }
    m_hashMap[index].emplace_back(make_unique<Data>(key, value));

    return {(m_hashMap[index].end())--, true};
}

int main()
{
    HashMap<string, int> hashmap;

    auto ret = hashmap.insert("hello", 23);

    
    return 0;
}

