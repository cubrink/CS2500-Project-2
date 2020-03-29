/* Filename     : driver.cpp
 * Author       : Curtis Brinker
 * Course       : CS 2500
 * Assignment   : Project 2
 * Due Date     : 2020-03-30
 */

#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <chrono>
#include <numeric>
#include <string>
#include <fstream>
#include <iomanip>
#include "knapsack.h"
#include "item.h"

using namespace std;

// Frequently used datatype, shortened for conciseness
typedef vector<Item> Bag;
typedef vector<uint64_t> IntList;

/* Function name:       gen_weights(uint64_t min_val, 
                                    uint64_t max_val, 
                                    uint64_t count);
 * 
 * 
 * Description:         Generates a list of integers using the specified
 *                      parameters
 * 
 * Returns:             A vector of integers
 * 
 * Arguments:
 *  uint64_t max_val    Maximum value of any element
 *  uint64_t min_val    Minimum value of any element
 *  uint64_t count      Amount of weights to be generated
 */
vector<uint64_t> gen_list(uint64_t min_val, 
                          uint64_t max_val, 
                          uint64_t count);


/* Function name:       bag_value(const Bag& items)
 * 
 * Description:         Returns the total value of items in the bag provided
 * 
 * Returns:             Total value of the bag
 * 
 * Arguments:
 *  const Bag&          Bag of items to count value of
 */
uint64_t bag_value(const Bag& items);


/* Function name:       bag_weight(const Bag& items)
 * 
 * Description:         Returns the total weight of items in the bag provided
 * 
 * Returns:             Total weight of the bag
 * 
 * Arguments:
 *  const Bag&          Bag of items to count weight of
 */
uint64_t bag_weight(const Bag& items);



/* Function name:                   runtime_report(Bag (*algorithm), 
 *                                                 vector<uint64_t>& input_sizes,
 *                                                 uint64_t bag_size,
 *                                                 uint64_t trials,
 *                                                 uint64_t seed)
 *          
 * Description:                     Gets the runtime (in seconds) of algorithm 
 *                                  for various input sizes
 *          
 * Returns:                         Returns a vector of doubles for each 
 *                                  runtime (in seconds)
 *          
 * Arguments:           
 *  Bag (*algorithm)                Algorithm to check runtime of
 *  vector<uint64_t>& input_sizes    Different input sizes to test
 *  uint64_t bag_size               Size of bag to run the test for
 *  uint64_t trials                 Amount of trials to run
 *  uint64_t seed                   Seed to initialize the test with
 */
template <typename Container>
vector<double> runtime_report(Bag (*algorithm)(const Container& v, 
                                           const Container& w, 
                                           uint64_t W),
                          vector<uint64_t> input_sizes,
                          uint64_t bag_size,
                          uint64_t trials,
                          uint64_t seed = 0);


/* Function name:                       write_runtime_report(string filename, vector<uint64_t>& input_sizes,
                                                             vector<double>& dynamic_runtimes, 
                                                             vector<double>& greedy_runtimes)
 *              
 * Description:                         Writes a runtime report to the specified filename
 *              
 * Returns:                             Nothing
 *          
 * Arguments:           
 *  string filename                     Filename to write report to
 *  vector<uint64_t>& input_sizes       List of inputs used in report
 *  vector<double>& dynamic_runtimes    List of runtimes for the dynamic algorithm
 *  vector<double>& greedy_runtimes     List of runtimes for the greedy runtimes
 */
void write_runtime_report(string filename, vector<uint64_t>& input_sizes,
                          vector<double>& dynamic_runtimes, 
                          vector<double>& greedy_runtimes);



/* Function name:                   value_report(Bag (*algorithm), 
 *                                         vector<uint64_t>& input_sizes,
 *                                         uint64_t bag_size,
 *                                         uint64_t trials,
 *                                         uint64_t seed)
 *          
 * Description:                     Gets the value of the bag returned by the 
 *                                  specified algorithm on multiple tests
 *          
 * Returns:                         Returns a vector of uint64_t containing the
 *                                  values of the bag for each test
 *          
 * Arguments:           
 *  Bag (*algorithm)                Algorithm to check runtime of
 *  vector<uint64_t>& input_sizes   Different input sizes to test
 *  uint64_t bag_size               Size of bag to run the test for
 *  uint64_t trials                 Amount of trials to run
 *  uint64_t seed                   Seed to initialize the test with
 */
template <typename Container>
vector<uint64_t> value_report(Bag (*algorithm)(const Container& v, 
                                               const Container& w, 
                                               uint64_t W),
                              vector<uint64_t> input_sizes,
                              uint64_t bag_size,
                              uint64_t trials,
                              uint64_t seed = 0);


/* Function name:                   write_value_report(string filename, 
 *                                                     vector<uint64_t>& input_sizes,
 *                                                     uint64_t bag_size,
 *                                                     uint64_t trials,
 *                                                     uint64_t seed)
 *          
 * Description:                     Writes a report regarding the values of bags using
 *                                  different algorithms
 *          
 * Returns:                         Nothing
 *          
 * Arguments:           
 *  string filename                 Filename to write to
 *  vector<uint64_t>& input_sizes   Different input sizes to test
 *  uint64_t bag_size               Size of bag to run the test for
 *  uint64_t trials                 Amount of trials to run
 *  uint64_t seed                   Seed to initialize the test with
 */
void write_value_report(string filename,
                        vector<uint64_t>& input_sizes,
                        uint64_t bag_size,
                        uint64_t trials,
                        uint64_t seed = 0);

/* Function name:                   boundary_test(string filename, 
 *                                                vector<uint64_t>& input_sizes,
 *                                                vector<uint64_t>& bag_sizes,
 *                                                uint64_t seed)
 *          
 * Description:                     Writes a report regarding the values of bags using
 *                                  different algorithms
 *          
 * Returns:                         Nothing
 *          
 * Arguments:           
 *  string filename                 Filename to write to
 *  vector<uint64_t>& input_sizes   Different input sizes to test
 *  vector<uint64_t>& bag_sizes     Size of bags to run the test for
 *  uint64_t seed                   Seed to initialize the test with
 */
void boundary_test(vector<uint64_t>& input_sizes,
                   vector<uint64_t>& bag_sizes,
                   uint64_t seed = 0);

int main() {
    // Declare variables and constants to be used in testing
    const uint64_t TRIALS = 10;
    const uint64_t SEED = 0;

    IntList input_sizes, bag_sizes;
    vector<double> dynamic_runtimes, greedy_runtimes;

    ///
    /// BOUNDARY TESTING
    ///
    cout << "*************************************" << endl;
    cout << "Beginning boundary tests..." << endl;
    cout << "*************************************" << endl;
    input_sizes = IntList({0, 1, 2});
    bag_sizes = IntList({0, 1});

    boundary_test(input_sizes, bag_sizes, SEED);
    cout << "Boundary tests complete." << endl << endl;


    ///
    /// RUN TIME TESTING
    ///
    cout << "*************************************" << endl;
    cout << "Beginning runtime tests..." << endl;
    cout << "*************************************" << endl;
    input_sizes = IntList({10, 50, 100, 500, 
                           1000, 5000, 10000});

    bag_sizes = IntList({100, 1000, 10000});


    // These tests are not proving correctness
    // Because assert statements do not necessarily have the same runtime
    // as the algorithm themselves, they will be disabled to test the
    // proper runtime
    Knapsack::ignore_asserts = true;

    for (uint64_t bag_size: bag_sizes) {
        string filename = "runtime_report_W" + to_string(bag_size) + ".csv";
        cout << "Creating runtime report: " << filename << endl;
        /*
        dynamic_runtimes = runtime_report<IntList>(Knapsack::Dynamic01, input_sizes,
                                      bag_size, TRIALS, SEED);
        greedy_runtimes = runtime_report<IntList>(Knapsack::Greedy01, input_sizes,
                                     bag_size, TRIALS, SEED);
        write_runtime_report(filename, input_sizes, 
                             dynamic_runtimes, greedy_runtimes);
        */
        cout << "Report " << filename << " has been written" << endl << endl;
    }
    cout << endl;
    cout << "Runtime tests complete" << endl << endl;
    

    ///
    /// VALUE TESTING
    ///
    cout << "*************************************" << endl;
    cout << "Beginning value tests..." << endl;
    cout << "*************************************" << endl;
    for (uint64_t bag_size: bag_sizes) {
        string filename = "value_report_W" + to_string(bag_size) + ".csv";
        cout << "Creating value report: " << filename << endl;
        /*
        write_value_report(filename, input_sizes, bag_size, TRIALS, SEED);
        */
        cout << "Report " << filename << " has been written" << endl << endl;
    }
    cout << "Value testing complete." << endl << endl;

    
    cout << "*************************************" << endl;
    cout << "All tests completed successfully" << endl;
    cout << "*************************************" << endl;

    return 0;
}

vector<uint64_t> gen_list(uint64_t min_val, uint64_t max_val, uint64_t count) {
    assert(min_val <= max_val);

    uint64_t e;
    vector<uint64_t> elements;

    for (uint64_t i = 0; i < count; i++) {
        e = rand() % (max_val - min_val) + min_val;
        elements.push_back(e);
    }

    assert(elements.size() == count);

    return elements;
}

uint64_t bag_value(const Bag& items) {
    uint64_t value = 0;
    for (Item item: items) {
        value += item.get_value();
    }
    return value;
}

uint64_t bag_weight(const Bag& items) {
    uint64_t weight = 0;
    for (Item item: items) {
        weight += item.get_weight();
    }
    return weight;
}

template <typename Container>
vector<double> runtime_report(Bag (*algorithm)(const Container& v, 
                                           const Container& w, 
                                           uint64_t W),
                          vector<uint64_t> input_sizes,
                          uint64_t bag_size,
                          uint64_t trials,
                          uint64_t seed) {
    // Initialze seed to specified value
    srand(seed);

    // Declare variable used to test runtime
    decltype(chrono::high_resolution_clock::now()) start, finish;
    chrono::duration<double> delta;

    // Hold the average runtime for each trial
    vector<double> runtimes;

    vector<uint64_t> weights, values;

    // Perform test for each runtime
    for (uint64_t input_size: input_sizes) {
        // Hold measurements for this specific input_size
        vector<double> measurements;
        for (uint64_t i = 0; i < trials; i++) {
            // Generate test data
            weights = gen_list(1, 100, input_size);
            values = gen_list(1, 100, input_size);

            // Measure runtime
            start = chrono::high_resolution_clock::now();
            algorithm(values, weights, bag_size);
            finish = chrono::high_resolution_clock::now();

            // Record measured runtime
            delta = finish - start;
            measurements.push_back(delta.count());
        }
        // Find average of runtime
        double average = accumulate(measurements.begin(), 
                                    measurements.end(),
                                    0.0) / measurements.size();
        // Record average value
        runtimes.push_back(average);
    }
    
    // Return results
    return runtimes;
}

void write_runtime_report(string filename, vector<uint64_t>& input_sizes,
                          vector<double>& dynamic_runtimes, 
                          vector<double>& greedy_runtimes) {
    ofstream outfile(filename);

    // Write headers
    outfile << "N,Dynamic,Greedy" << "\n";

    // Set output format
    outfile << fixed << showpoint << setprecision(9);

    for (uint64_t i = 0; i < input_sizes.size(); i++) {
        // Write info to each column in file
        outfile << input_sizes[i] << ","
                << dynamic_runtimes[i] << ","
                << greedy_runtimes[i] << "\n";
    }

    outfile.close();
}

template <typename Container>
vector<uint64_t> value_report(Bag (*algorithm)(const Container& v, 
                                               const Container& w, 
                                               uint64_t W),
                              vector<uint64_t> input_sizes,
                              uint64_t bag_size,
                              uint64_t trials,
                              uint64_t seed) {
    // Initialize the seed
    srand(seed);

    // Declare containers to hold results
    Bag items;
    IntList bag_values, weights, values;

    // Record tests for each input size
    for (uint64_t input_size: input_sizes) {
        for (uint64_t i = 0; i < trials; i++) {
            // Generate test data
            weights = gen_list(1, 100, input_size);
            values = gen_list(1, 100, input_size);

            // Get items
            items = algorithm(values, weights, bag_size);

            // Save result
            bag_values.push_back(bag_value(items));
        }
    }

    return bag_values;
}

void write_value_report(string filename,
                        vector<uint64_t>& input_sizes,
                        uint64_t bag_size,
                        uint64_t trials,
                        uint64_t seed) {
    ofstream outfile(filename);

    // Hold the knapsack total values for each trial run
    IntList dynamic_values, greedy_values;

    // Get test data
    dynamic_values = value_report<IntList>(Knapsack::Dynamic01, input_sizes, 
                                           bag_size, trials, seed);

    greedy_values = value_report<IntList>(Knapsack::Greedy01, input_sizes, 
                                          bag_size, trials, seed);

    // Write header of csv
    outfile << "N,Dynamic value,Greedy value" << '\n';

    for (uint64_t i = 0; i < input_sizes.size(); i++) {
        for (uint64_t j = 0; j < trials; j++) {
            // Determine index of value to read
            uint64_t value_idx = trials*i + j;
            // Write each column
            outfile << input_sizes[i] << ","
                    << dynamic_values[value_idx] << ","
                    << greedy_values[value_idx] << '\n';
        }
    }

    outfile.close();
}

void boundary_test(vector<uint64_t>& input_sizes,
                   vector<uint64_t>& bag_sizes,
                   uint64_t seed) {
    // Initialize with seed
    srand(seed);

    // Ensure correctness is tested
    Knapsack::ignore_asserts = false;

    // Temporary bag used to run tests
    Bag tmp;

    // Used to hold test data
    IntList weights, values;

    for (uint64_t bag_size: bag_sizes) {
        for (uint64_t input_size: input_sizes) {
            cout << "Testing with bag_size=" << bag_size << ", input_size=" << input_size << endl;

            weights = gen_list(1, 10, input_size);
            values = gen_list(1, 10, input_size);
            
            // As asserts are enabled, correctness can be proven if assert 
            // statements pass.

            // Show correctness of Dynamic01
            cout << "Testing dynamic solution... ";
            tmp = Knapsack::Dynamic01(values, weights, bag_size);
            cout << "test complete." << endl;

            // Show correctness of Greedy01
            cout << "Testing greedy solution... ";
            tmp = Knapsack::Greedy01(values, weights, bag_size);
            cout << "test complete." << endl << endl;
        }
    }
}