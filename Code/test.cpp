#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include "item.h"
#include "sorter.h"
#include "knapsack.h"

using namespace std;

void comparison_test();
void combine_and_sort_test();
void greedy_test(uint64_t W = 50);
void table_test();
void dynamic_test();

template<typename T>
void print_vector(const T& v);

void print_2d_vector(const vector<vector<uint64_t>>& v);

int main() {
    table_test();
    dynamic_test();
    greedy_test();
    return 0;
}

void dynamic_test() {
    cout << "Dynamic test" << endl;

    vector<uint64_t> v = {5,7,8,9};
    vector<uint64_t> w = {1,2,4,3};
    uint64_t W = 4;

    vector<Item> bag = Knapsack::Dynamic01(v, w, W);
    for (Item item: bag) {
        cout << "(" << item.get_weight() << "," << item.get_value() << "), ";
    }
    cout << endl;
}

void table_test() {
    cout << "Table test" << endl;
    vector<uint64_t> v = {5,7,8,9};
    vector<uint64_t> w = {1,2,4,3};
    uint64_t W = 4;

    vector<vector<uint64_t>> K = Knapsack::GenerateTable(v, w, W);

    print_2d_vector(K);
}

void greedy_test(uint64_t W) {
    cout << "greedy test" << endl;
    vector<uint64_t> v, w;

    for (uint64_t i = 0; i < 10; i++) {
        w.push_back(2*i + 5);
        v.push_back(i*(i+1) + 1);
    }

    vector<Item> bag = Knapsack::Greedy01(v, w, W);

    for (uint64_t i = 0; i < bag.size(); i++) {
        cout << i << ": " << bag[i].get_value() 
             << "/" << bag[i].get_weight() 
             << "\t" << bag[i].get_ratio() << endl;    }

}

void combine_and_sort_test() {
    cout << "combine and sort test" << endl;
    vector<uint64_t> v, w;

    for (uint64_t i = 0; i < 10; i++) {
        w.push_back(i + 1);
        v.push_back(25 - 2*i);
    }

    vector<Item> items = Knapsack::combine(v, w);

    cout << "Combined: " << endl;
    for (uint64_t i = 0; i < items.size(); i++) {
        cout << i << ": " << items[i].get_value() 
             << "/" << items[i].get_weight() 
             << "\t" << items[i].get_ratio() << endl;
    }

    vector<Item> sorted_items = Sorter::HeapSort(items);
    reverse(sorted_items.begin(), sorted_items.end());

    cout << "Combined and sorted: " << endl;
    for (uint64_t i = 0; i < sorted_items.size(); i++) {
        cout << i << ": " << sorted_items[i].get_value() << "/" 
             << sorted_items[i].get_weight()
             << "\t" << sorted_items[i].get_ratio() << endl;

    }



}

void comparison_test() {
    cout << "comparison test" << endl;

    Item i(112943, 13532423235234234);
    Item j(112943, 13532423235234234);
    // Item j(112943, 23251341523423452);
    // cout << i.weight << " " << i.value << " " << i.ratio << endl;
    // cout << j.weight << " " << j.value << " " << j.ratio << endl;

    cout << boolalpha << "i < j: " << (i < j) << endl;
    cout << boolalpha << "i <= j: " << (i <= j) << endl;
    cout << boolalpha << "i > j: " << (i > j) << endl;
    cout << boolalpha << "i >= j: " << (i >= j) << endl;
    cout << boolalpha << "i == j: " << (i == j) << endl;
}


template<typename T>
void print_vector(const T& v) {
    cout << "<";
    for (auto item: v) {
        cout << item << ", ";
    }
    cout << ">";
}


void print_2d_vector(const vector<vector<uint64_t>>& v) {
    for (vector<uint64_t> vec: v) {
        print_vector(vec);
        cout << '\n';
    }
}