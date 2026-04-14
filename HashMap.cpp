#include "HashMap.h"
#include <unordered_map>

template<typename T, typename U>
HashMap<T, U>::HashMap(int capacity):m_capacity(capacity), m_hashMap(capacity)
{
    
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
        if(itr->first == key)
        {
            return {itr, false};
        }
    }
    m_hashMap[index].emplace_back(key, value);

    return {(m_hashMap[index].end())--, true};
}

template<typename T, typename U>
void HashMap<T, U>::erase(const T & key)
{
    const auto index = hashFunction(key);

    if(m_hashMap[index].empty())
        return;
    for(iterator itr = m_hashMap[index].begin(); itr != m_hashMap[index].end(); itr++)
    {
        if(itr->first == key)
        {
            m_hashMap[index].erase(itr);
            break;
        }
    }
}

//pair with lvalue or rValue
template<typename T, typename U>
const T& HashMap<T, U>::extract_key(const std::pair<T, U>& pair)
{
    return pair.first;
}

//key + value
template<typename T, typename U>
const T& HashMap<T, U>::extract_key(const T & key, const U& value)
{
    return key;
}

//piecewise_construct
template<typename T, typename U>
template<typename TupleKey, typename TupleValue>
T HashMap<T, U>::extract_key(std::piecewise_construct_t,
                     TupleKey&& key_tuple,
                     TupleValue&&)
{
    return std::apply(
        [](auto&&... args) {
            return T(std::forward<decltype(args)>(args)...);
        },
        std::forward<TupleKey>(key_tuple)
    );
}

template<typename T, typename U>
template<typename... Args>
pair<typename HashMap<T, U>::iterator, bool> HashMap<T, U>::emplace(Args&&... args)
{
    T key = extract_key(std::forward<Args>(args)...);

    const int index = hashFunction(key);

    if(!m_hashMap[index].empty())
    {
        for(iterator itr = m_hashMap[index].begin(); itr != m_hashMap[index].end(); itr++)
        {
            if(itr->first == key)
            {
                return {itr, false};
            }
        }
    }
    m_hashMap[index].emplace_back(std::forward<Args>(args)...);
    auto it = m_hashMap[index].end();
    return {--it, true};
}

template<typename T, typename U>
U & HashMap<T, U>::operator [](const T & key)
{
    const auto index = hashFunction(key);

    if(!m_hashMap[index].empty())
    {
        for(iterator itr = m_hashMap[index].begin(); itr != m_hashMap[index].end(); itr++)
        {
            if(itr->first == key)
            {
                return itr->second;
            }
        }
    }
    m_hashMap[index].emplace_back(key, U());
    return (m_hashMap[index].begin())->second;
}

int main()
{
    unordered_map<int, int> map;

    //std::cout<<map["hello"] << endl;
    map.try_emplace(1, 2);
    
    HashMap<string, int> hashmap;

    std::cout<<hashmap["hello"] << endl;
    auto ret = hashmap.insert("hello", 23);
    hashmap["hello"] = 11;
    std::cout<<hashmap["hello"] << endl;

    hashmap.erase("hello");
    std::cout<<hashmap["hello"] << endl;
    hashmap.erase("hello");
    hashmap["hello"] = 10;
    std::cout<<hashmap["hello"] << endl;

    auto ret1 = hashmap.emplace("hello9", 30);
    std::cout<<ret1.first->second;

    std::unordered_map<std::string, std::pair<int, int>  > hashmap3;


    hashmap3.emplace(std::piecewise_construct, std::forward_as_tuple("hello"), std::forward_as_tuple( 3, 4));
    return 0;
}
