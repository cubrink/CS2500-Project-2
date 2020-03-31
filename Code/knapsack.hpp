/* Filename     : knapsack.hpp
 * Author       : Curtis Brinker
 * Course       : CS 2500
 * Assignment   : Project 2
 * Due Date     : 2020-03-30
 */

#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <vector>
#include <algorithm>        // For std::reverse, std::is_sorted
#include <cassert>
#include "item.h"
#include "sorter.h"

using std::vector;

bool Knapsack::ignore_asserts = false;

template <typename Container>
vector<Item> Knapsack::Greedy01(const Container& v, const Container& w, uint64_t W) {
    // Preconditions:
    // v is a container of non-negative integer values
    for (auto element: v) { assert(ignore_asserts || element >= 0); }
    // w is a container of positive integer weights
    for (auto element: w) { assert(ignore_asserts || element > 0); }
    // v.size() == w.size()
    assert(ignore_asserts || v.size() == w.size());
    // W is a non-negative integer
    assert(ignore_asserts || W >= 0);


    vector<Item> bag;   // Bag that items will be put into

    // Combine weights and values into items
    vector<Item> items = Knapsack::combine(v, w);
    Sorter::ignore_asserts = true;              // See note in Sorter.h
    items = Sorter::HeapSort(items);            // Sort into ascending order

    // Invariant: items are sorted in ascending order before being reversed
    assert(ignore_asserts || std::is_sorted(items.begin(), items.end()));

    std::reverse(items.begin(), items.end());   // Reverse into descending order
    for (uint64_t item_idx = 0; item_idx < items.size() && W > 0; item_idx++) {
        // Invariant: W > 0
        assert(ignore_asserts || W > 0);
        Item item = items[item_idx];
        if (item.get_weight() <= W) {
            W -= item.get_weight();
            bag.push_back(item);
        }
        if (W == 0) {
            break;
        }
        // Invariant: W > 0
        assert(ignore_asserts || W > 0);
    }
    // Invariant: W >= 0
    assert(ignore_asserts || W >= 0);

    return bag;
}

template <typename Container>
vector<Item> Knapsack::Dynamic01(const Container& v, const Container& w, uint64_t W) {
    // Preconditions:
    // v is a container of non-negative integer values
    for (auto element: v) { assert(ignore_asserts || element >= 0); }
    // w is a container of positive integer weights
    for (auto element: w) { assert(ignore_asserts || element > 0); }
    // v.size() == w.size()
    assert(ignore_asserts || v.size() == w.size());
    // W is a non-negative integer
    assert(ignore_asserts || W >= 0);


    // Generate table and use it to find items to take
    Knapsack::table K = Knapsack::GenerateTable(v, w, W);
    vector<Item> bag = Knapsack::ReadTable(K, v, w, W);


    // Postcondition: An optimal solution to the 0/1 Knapsack
    //                problem is returned
    uint64_t max_value = 0;
    uint64_t bag_value = 0;
    for (auto& row: K) {
        max_value = std::max(max_value, *std::max_element(row.begin(), row.end()));
    }
    for (Item& item: bag) { bag_value += item.get_value(); }
    assert(ignore_asserts || bag_value == max_value);

    // Return bag of optimal items
    return bag;
}

template <typename Container>
vector<vector<uint64_t>> Knapsack::GenerateTable(const Container& v, 
                                                 const Container& w, 
                                                 const uint64_t W) {
    // Preconditions:
    // v is a container of non-negative integer values
    for (auto element: v) { assert(ignore_asserts || element >= 0); }
    // w is a container of positive integer weights
    for (auto element: w) { assert(ignore_asserts || element > 0); }
    // v.size() == w.size()
    assert(ignore_asserts || v.size() == w.size());
    // W is a non-negative integer
    assert(ignore_asserts || W >= 0);

    // Table to be filled
    Knapsack::table K;

    // Height and width of the table K
    const uint64_t height = w.size() + 1;
    const uint64_t width = W + 1;

    // Invariant: K.size() == 0
    assert(ignore_asserts || K.size() == 0);
    for (uint64_t i = 0; i < height; i++) {
        // Invariant: K.size() < height
        assert(ignore_asserts || K.size() < height);

        // Create vector of width (W+1) initialized with 0's
        vector<uint64_t> tmp(width, 0);
        K.push_back(tmp);

        // Invariant: K.size() <= height
        assert(ignore_asserts || K.size() <= height);
    }
    // Invariant: K.size() == height
    assert(ignore_asserts || K.size() == height);


    // Invariant: Upper edge of table is all 0's
    for (uint64_t elem: K.at(0)) { assert(ignore_asserts || elem == 0); }
    // Invariant: Left edge of table is all 0's
    for (auto& row: K) { assert(ignore_asserts || row.at(0) == 0); }
    for (uint64_t y = 1; y < height; y++) {
        // Invariant: K[y-1,0..W] are optimal values of sacks of sizes 0..W 
        // 			  for (y-1)-th row (from subset of first y-1 weights)
        for (uint64_t row_idx = 0; row_idx < y-1; row_idx++) {
            assert(ignore_asserts || K.at(y-1).at(W) >= *std::max_element(K.at(row_idx).begin(), 
                                                        K.at(row_idx).end()));
        }

        uint64_t wt = w.at(y-1);    // Weight of current item
        uint64_t vl = v.at(y-1);    // Value of current item

        for (uint64_t x = 1; x < width; x++) {
            // Invariant: K[y,x-1] is optimal value of sack of size x-1 in 
			//            the y-th row (from subset of first y weights)
            uint64_t current_value = K.at(y).at(x-1);
            uint64_t optimal_value = K.at(y-1).at(x-1);
            if ((x-1) >= wt) {
                optimal_value = std::max(optimal_value,
                                         vl + K.at(y-1).at(x-1-wt));
            }
            assert(ignore_asserts || current_value == optimal_value);
            


            if (wt > x) {
                // Item does not fit into bag
                K.at(y).at(x) = K.at(y-1).at(x);
            }
            else if (vl + K.at(y-1).at(x-wt) <= K.at(y-1).at(x)) {
                // Item fits but isn't worth taking
                K.at(y).at(x) = K.at(y-1).at(x);
            }
            else {
                // Item fits and is worth taking
                K.at(y).at(x) = vl + K.at(y-1).at(x-wt);
            }


            // Invariant: K[y,x] is optimal value of sack of size x in 
			//            the y-th row (from subset of first y weights)
            current_value = K.at(y).at(x);
            optimal_value = K.at(y-1).at(x);
            if (x >= wt) {
                optimal_value = std::max(optimal_value,
                                         vl + K.at(y-1).at(x-wt));
            }
            assert(ignore_asserts || current_value == optimal_value);
        }


		// Invariant: K[y,0..W] are optimal values of sacks of sizes 0..W 
		//		      for y-th row (from subset of first y weights)
        for (uint64_t row_idx = 0; row_idx < y-1; row_idx++) {
            assert(ignore_asserts || K.at(y).at(W) >= *std::max_element(K.at(row_idx).begin(), 
                                                      K.at(row_idx).end()));
        }
    }
    return K;
}


template <typename Container>
vector<Item> Knapsack::ReadTable(const Knapsack::table& K, const Container& v,
                              const Container& w, const uint64_t W) {
    // Preconditions:
    // K is a 2-d array of height w.size()+1, width W+1
    assert(ignore_asserts || K.size() == w.size()+1);
    assert(ignore_asserts || K.at(0).size() == W + 1);
    // v is a container of non-negative integer values
    for (auto element: v) { assert(ignore_asserts || element >= 0); }
    // w is a container of positive integer weights
    for (auto element: w) { assert(ignore_asserts || element > 0); }
    // v.size() == w.size()
    assert(ignore_asserts || v.size() == w.size());
    // W is a non-negative integer
    assert(ignore_asserts || W >= 0);
    

    // Bag of items put into the knapsack
    vector<Item> bag;

    uint64_t wt;   // Weight of current item
    uint64_t vl;   // Value of current item

    uint64_t y = w.size();
    uint64_t x = W;

    while (y > 0 && x > 0) {
        // Invariant: bag.size() <= w.size()
        assert(ignore_asserts || bag.size() <= w.size());

        while (y > 0 && K.at(y).at(x) == K.at(y-1).at(x)) {
            // Invariant: y > 0, x > 0
            assert(ignore_asserts || y > 0 && x > 0);
            
            // Skip items that were not used
            y -= 1;

            // Invariant: y >= 0, x > 0
            assert(ignore_asserts || y >= 0 && x > 0);
        }

        if (y > 0) {
            wt = w.at(y-1);   // Weight of current item
            vl = v.at(y-1);   // Value of current item

            // If there is an item, add it to the bag
            bag.push_back(Item(wt, vl));

            x -= wt;    // Account for weight of item
            y -= 1;     // Move to next item
        }

        // Invariant: bag.size() <= w.size()
        assert(ignore_asserts || bag.size() <= w.size());
    }
    

    // Postcondition: An optimal solution to the 0/1 Knapsack
    //                problem is returned
    uint64_t max_value = 0;
    uint64_t bag_value = 0;
    for (auto& row: K) {
        max_value = std::max(max_value, *std::max_element(row.begin(), row.end()));
    }
    for (Item& item: bag) { bag_value += item.get_value(); }
    assert(ignore_asserts || bag_value == max_value);
    
    
    // Optimal solution is returned
    return bag;
}

template <typename Container>
vector<Item> Knapsack::combine(const Container& v, const Container& w) {
    // Preconditions:
    // v is a container of non-negative integer values
    for (auto element: v) { assert(ignore_asserts || element >= 0); }
    // w is a container of positive integer weights
    for (auto element: w) { assert(ignore_asserts || element > 0); }
    // v.size() == w.size()
    assert(ignore_asserts || v.size() == w.size());


    vector<Item> items;

    for (uint64_t i = 0; i < w.size(); i++) {
        // Invariant: items.size() < w.size()
        assert(ignore_asserts || items.size() < w.size());

        Item item(w[i], v[i]);
        items.push_back(item);

        // Invariant: items.size() <= w.size()
        assert(ignore_asserts || items.size() <= w.size());
    }

    // Postcondition: items.size() == w.size()
    assert(ignore_asserts || items.size() == w.size());

    return items;
}


#endif
