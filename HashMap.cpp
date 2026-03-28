#include "HashMap.h"

template<typename T, typename U>
HashMap<T, U>::HashMap(int capacity):m_capacity(capacity)
{
    m_hashMap.reserve(capacity);
}

int main()
{
    return 0;
}

