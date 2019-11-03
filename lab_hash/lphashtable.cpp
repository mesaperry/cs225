/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"
#include <iostream>

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */
    elems++;
    if (shouldResize()) { resizeTable(); }

    unsigned i = hashes::hash(key, size);
    size_t inc = 0;
    while (should_probe[(i+inc)%size] == true) { inc++; }
    table[(i+inc)%size] = new std::pair<K, V>(key, value);
    should_probe[(i+inc)%size] = true;
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
    unsigned i = hashes::hash(key, size);
    size_t inc = 0;
    while (should_probe[(i+inc)%size] == true) {
        if (table[(i+inc)%size] != NULL) {
            if (table[(i+inc)%size]->first == key) {
                delete table[(i+inc)%size];
                table[(i+inc)%size] = NULL;
                elems--;
                return;
            }
        }
        inc++;
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{

    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    unsigned i = hashes::hash(key, size);
    size_t inc = 0;
    while (should_probe[(i+inc)%size] == true) {
        if (table[(i+inc)%size] != NULL) {
            if (table[(i+inc)%size]->first == key) {
                return (i+inc)%size;
            }
        }
        inc++;
    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    size_t new_size = findPrime(size*2);

    delete[] should_probe;
    should_probe = new bool[new_size];
    for (size_t i = 0; i < new_size; i++) {
        should_probe[i] = false;        
    }
    typename std::pair<K, V>** new_table = new std::pair<K, V>*[new_size];
    for (size_t i = 0; i < size; i++) {
        if (table[i] != NULL) {
            unsigned new_i = hashes::hash(table[i]->first, new_size);
            size_t inc = 0;
            while (should_probe[(new_i+inc)%new_size] == true) { inc++; }
            new_table[(new_i+inc)%new_size] = new std::pair<K, V>(table[i]->first, table[i]->second);
            should_probe[(new_i+inc)%new_size] = true;
        }
    }
    for (size_t i = 0; i < new_size; i++) {
        if (should_probe[i] == false) { new_table[i] = NULL; }
    }
    delete[] table;
    table = new_table;
    size = new_size;
}
