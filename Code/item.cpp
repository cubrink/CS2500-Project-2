/* Filename     : item.cpp
 * Author       : Curtis Brinker
 * Course       : CS 2500
 * Assignment   : Project 2
 * Due Date     : 2020-03-30
 */

#ifndef ITEM_CPP
#define ITEM_CPP

#include "item.h"

Item::Item(uint64_t weight, uint64_t value) {
    this->weight = weight;
    this->value = value;
    this->ratio = this->value / static_cast<double>(this->weight);
}


bool operator<(const Item& first, const Item& second) {
    return (first.ratio < second.ratio);
}


bool operator<=(const Item& first, const Item& second) {
    return (first.ratio <= second.ratio);
}


bool operator>(const Item& first, const Item& second) {
    return (first.ratio > second.ratio);
}


bool operator>=(const Item& first, const Item& second) {
    return (first.ratio >= second.ratio);
}

bool operator==(const Item& first, const Item& second) {
    return (first.weight == second.weight) 
           && (first.value == second.value);
}


#endif