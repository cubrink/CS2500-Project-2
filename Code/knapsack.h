/* Filename     : knapsack.h
 * Author       : Curtis Brinker
 * Course       : CS 2500
 * Assignment   : Project 2
 * Due Date     : 2020-03-30
 */

#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "item.h"

#include <vector>
#include <cstdint>
#include <cassert>

using std::vector;

/* Class name:              Knapsack
 * 
 * Description:             Provides different methods of solving the 
 *                          0/1 Knapsack problem
 */
class Knapsack {
public:
    // Frequently used datatype
    typedef vector<vector<uint64_t>> table;

    static bool ignore_asserts;

    /* Function name:       Knapsack::Greedy01(const Container& v, const Container& w, uint64_t W)
     * 
     * Description:         Attempts to find a solution to the 0/1 Knapsack
     *                      problem using a greedy algorithm
     * 
     * Returns:             Returns a vector of items that were placed
     *                      into the knapsack
     * 
     * Arguments:
     *  const Container& v  Container of values
     *  const Container& w  Container of weights
     *  uint64_t W          Size of the knapsack
     * 
     * Pre-conditions:      v is a container of non-negative integer values
     *                      w is a container of positive integer weights
     *                      v.size() == w.size()
     *                      W is a non-negative integer
     * 
     * Post-conditions:     A possible optimal solution to the 0/1 Knapsack
     *                      problem is returned
     */
    template <typename Container>
    static vector<Item> Greedy01(const Container& v, const Container& w, uint64_t W);


    /* Function name:       Knapsack::Dynamic(const Container& v, const Container& w, uint64_t W)
     * 
     * Description:         Finds the optimal solution to the 0/1 Knapsack
     *                      problem using a dynamic algorithm
     * 
     * Returns:             Returns a vector of items that were placed
     *                      into the knapsack
     * 
     * Arguments:
     *  const Container& v  Container of values
     *  const Container& w  Container of weights
     *  uint64_t W          Size of the knapsack
     * 
     * Pre-conditions:      v is a container of non-negative integer values
     *                      w is a container of positive integer weights
     *                      v.size() == w.size()
     *                      W is a non-negative integer
     * 
     * Post-conditions:     An optimal solution to the 0/1 Knapsack
     *                      problem is returned
     */
    template <typename Container>
    static vector<Item> Dynamic01(const Container& v, const Container& w, uint64_t W);

public:
    /* Function name:       Knapsack::GenerateTable(const Container& v, const Container& w, const uint64_t W)
     * 
     * Description:         Returns a 2-D table of optimal values for
     *                      sub problems of the 0/1 Knapsack problem
     * 
     * Returns:             Returns a 2-D table of optimal values for
     *                      sub problems of the 0/1 Knapsack problem
     * 
     * Arguments:
     *  const Container& v  Container of values
     *  const Container& w  Container of weights
     *  const uint64_t W    Size of the knapsack
     * 
     * Pre-conditions:      v is a container of non-negative integer values
     *                      w is a container of positive integer weights
     *                      v.size() == w.size()
     *                      W is a non-negative integer
     * 
     * Post-conditions:     K[0..n][0..W], are optimal values
     */
    template <typename Container>
    static table GenerateTable(const Container& v, const Container& w, const uint64_t W);


    /* Function name:       Knapsack::ReadTable(const table& K, const Container& v,
     *                                          const Container& w, const uint64_t W)
     * 
     * Description:         Finds the items used in the optimal solution
     *                      to the 0/1 Knapsack problem
     * 
     * Returns:             Returns the items used in the optimal solution
     *                      to the 0/1 Knapsack problem
     * 
     * Arguments:
     *  const table& K      2-D table of optimal values
     *  const Container& v  Container of values
     *  const Container& w  Container of weights
     *  const uint64_t W    Size of the knapsack
     * 
     * Pre-conditions:      K is a 2-d array of height w.size()+1, width W+1
     *                      v is a container of non-negative integer values
     *                      w is a container of positive integer weights
     *                      v.size() == w.size()
     *                      W is a non-negative integer
     * 
     * Post-conditions:     An optimal list of items for the 0/1 Knapsack
     *                      problem is found
     */
    template <typename Container>
    static vector<Item> ReadTable(const table& K, const Container& v,
                                  const Container& w, const uint64_t W);

    /* Function name:       Knapsack::combine(const Container& v, const Container& w)
     * 
     * Description:         Returns a vector of items to use in the
     *                      knapsack problem
     * 
     * Returns:             Returns a vector of items to use in the 
     *                      knapsack problem
     * 
     * Arguments:
     *  const Container& v  Container of values
     *  const Container& w  Container of weights
     * 
     * Pre-conditions:      v is a container of non-negative integer values
     *                      w is a container of positive integer weights
     *                      v.size() == w.size()
     * 
     * Post-conditions:     A vector of items to use in the knapsack problem
     *                      is created which has length == w.size()
     */
    template <typename Container>
    static vector<Item> combine(const Container& v, const Container& w);
};

#include "knapsack.hpp"
#endif