/**
 * Hashtable.cpp
 *
 *      Implementation of Hashtable, using chaining.
 *      Interface mostly follows std::unordered_map
 *
 * Alan Weide and Meghana Chamarty
 * CPSC 223
 * Spring 2023
 *
 */
#include "Hashtable.h"
#include <iostream>
#include <vector>
#include <functional>

template <class Value>
Hashtable<Value>::Hashtable() : Hashtable(initial_capacity) {}

template <class Value>
Hashtable<Value>::Hashtable(size_t tablesize)
{
    hashtable.resize(tablesize);
}

template <class Value>
Value *Hashtable<Value>::insert(const Key &key, const Value &to_insert)
{
    size_t bucket_index = index_of(key); 
    
      if (load_factor() > max_load_factor) {
        expand();
    }

    Value* index_var = find(key); 

    if (index_var != nullptr){
        *index_var = to_insert;
        return index_var; 
    }
    hashtable[bucket_index].emplace_back(key, to_insert);
    num_elements++;
    return &(hashtable[bucket_index].back().val);
}

template <class Value>
void Hashtable<Value>::expand()
{
    size_t new_capacity = size() * 2;
    Hashtable<Value> temp_table = Hashtable(new_capacity);

    for (auto& bucket : hashtable) {
        for (auto& kv : bucket) {
            temp_table.insert(kv.key, kv.val);
        }
    }
    std::swap(*this, temp_table);
}

template <class Value>
Value &Hashtable<Value>::at(const Key &key)
{
    Value *to_return = find(key);
    if (to_return == nullptr) {
        throw std::runtime_error(" ");
    }
    return *to_return;
}

template <class Value>
const Value &Hashtable<Value>::at(const Key &key) const
{
    const Value *to_return = find(key);
    if (to_return == nullptr) {
        throw std::runtime_error(" ");
    }
    return *to_return;
}

template <class Value>
Value *Hashtable<Value>::find(const Key &key)
{   
    size_t bucket_index = index_of(key);
    for (auto& kv : hashtable[bucket_index]) {
        if (kv.key == key) {
            return &kv.val;
        }
    }
    return nullptr;
}

template <class Value>
const Value *Hashtable<Value>::find(const Key &key) const
{
    size_t bucket_index = index_of(key);
    for (const auto& kv : hashtable[bucket_index]) {
        if (kv.key == key) {
            return &kv.val;
        }
    }
    return nullptr;
}

template <class Value>
Value &Hashtable<Value>::operator[](const Key &key)
{
    Value* val = find(key);
    if (val == nullptr) {
        return *insert(key, Value());
    }
    return *val;
}

template <class Value>
size_t Hashtable<Value>::index_of(const Key &key) const
{
    size_t index = hash(key);
    if (index){
        return index;
    }
    return 0; 
}

template <class Value>
size_t Hashtable<Value>::size() const
{
    return num_elements; 
}

template <class Value>
double Hashtable<Value>::load_factor() const
{
    return (num_elements) / hashtable.size();  
}

template <class Value>
size_t Hashtable<Value>::hash(const Key &key) const
{
    std::hash<Key> key_hash;
    return key_hash(key) % hashtable.size(); 
}

// Explicit template specialization for "string"s
template class Hashtable<std::string>;

// Explicit template specialization for "Entry"s
#include "Entry.h"
template class Hashtable<std::vector<Entry>>;
