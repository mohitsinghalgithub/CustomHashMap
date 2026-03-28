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
    return {nullptr, true};
}

int main()
{
    return 0;
}

