/* Filename     : item.h
 * Author       : Curtis Brinker
 * Course       : CS 2500
 * Assignment   : Project 2
 * Due Date     : 2020-03-30
 */
#ifndef ITEM_H
#define ITEM_H

#include <cstdint>          // For uint64_t

/* Class name:              Item
 * 
 * Description:             Provides comparison operations based on pairs
 *                          of weight and values
 */
class Item {
private:
    uint64_t weight;
    uint64_t value;
    double ratio;
public:
    /* Function name:       Item::Item(uint64_t weight, uint64_t value)
     * 
     * Description:         Creates a weight, value pair item
     * 
     * Arguments:
     *  uint64_t weight     weight of the item
     *  uint64_t value      value of the item
     */
    Item(uint64_t weight, uint64_t value);


    /* Function name:       Item::get_weight()
     * 
     * Description:         Inline getter function for the weight attribute
     * 
     * Returns:             this->weight
     */
    uint64_t get_weight() const {return this->weight;};


    /* Function name:       Item::get_value()
     * 
     * Description:         Inline getter function for the value attribute
     * 
     * Returns:             this->value
     */
    uint64_t get_value() const {return this->value;};


    /* Function name:       Item::get_ratio()
     * 
     * Description:         Inline getter function for the ratio attribute
     * 
     * Returns:             this->ratio
     */
    double get_ratio() const {return this->ratio;};


    /* Function name:       operator<(const Item& lhs, const Item& rhs)
     * 
     * Description:         Compares two items
     * 
     * Returns:             true if lhs.ratio < rhs.ratio
     *                      false otherwise
     * 
     * Arguments:
     *  const Item& lhs     Item on left hand side
     *  const Item& rhs     Item on right hand side
     */
    friend bool operator<(const Item& lhs, const Item& rhs);


    /* Function name:       operator=<(const Item& lhs, const Item& rhs)
     * 
     * Description:         Compares two items
     * 
     * Returns:             true if lhs.ratio <= rhs.ratio
     *                      false otherwise
     * 
     * Arguments:
     *  const Item& lhs     Item on left hand side
     *  const Item& rhs     Item on right hand side
     */
    friend bool operator<=(const Item& lhs, const Item& rhs);


    /* Function name:       operator>(const Item& lhs, const Item& rhs)
     * 
     * Description:         Compares two items
     * 
     * Returns:             true if lhs.ratio > rhs.ratio
     *                      false otherwise
     * 
     * Arguments:
     *  const Item& lhs     Item on left hand side
     *  const Item& rhs     Item on right hand side
     */
    friend bool operator>(const Item& lhs, const Item& rhs);


    /* Function name:       operator>=(const Item& lhs, const Item& rhs)
     * 
     * Description:         Compares two items
     * 
     * Returns:             true if lhs.ratio >= rhs.ratio
     *                      false otherwise
     * 
     * Arguments:
     *  const Item& lhs     Item on left hand side
     *  const Item& rhs     Item on right hand side
     */
    friend bool operator>=(const Item& lhs, const Item& rhs);


    /* Function name:       operator==(const Item& lhs, const Item& rhs)
     * 
     * Description:         Compares two items
     * 
     * Returns:             true if lhs.weight == rhs.weight
     *                          and lhs.value  == rhs.value
     *                      false otherwise
     * 
     * Arguments:
     *  const Item& lhs     Item on left hand side
     *  const Item& rhs     Item on right hand side
     */
    friend bool operator==(const Item& lhs, const Item& rhs);
};


#endif