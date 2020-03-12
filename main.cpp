#include <iostream>
#include <vector>

// This method returns all primes up to a given point (using sieve of Eratosthenes algorithm)
std::vector<uint32_t > sieveOfEratosthenes(uint32_t num)
{
    std::vector<uint32_t> result {1};

    for (int i=2; i<=num; i++) {
        bool prime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                prime = false;
                break;
            }
        }
        if (prime) result.push_back(i);

    }

    return result;
}

void recNumOfCombinationsToSum(std::vector<uint32_t> &nums, std::vector<uint32_t> &partial,
        const int32_t net_amount, uint32_t &net_combinations, int idx, const uint32_t &min_comb, const uint32_t &max_comb)
{


    // If the size of partial ( number of values in current combination ) exceeds max combination number, return
    // If the net_amount is negative the partial values do not sum
    if (net_amount < 0 || partial.size() > max_comb)
        return;

    // Partial values sum to net_amount
    if (net_amount == 0) {
        for (uint32_t num : partial)
            std::cout << num << " "; // TODO : only for debugging
        std::cout << std::endl;
        // If the size of partial (number of numbers that sum to net_amount) is not in the bounds do not count it
        net_combinations++;
        return;
    }


    // Recur for all remaining elements that have value less than sum (as we are backtracking)
    while (idx < nums.size() && net_amount - nums[idx] >= 0)
    {

        // Until every element in the array starting
        // from idx which can contribute to the sum
        partial.push_back(nums[idx]); // add them to list

        // recur for next numbers
        recNumOfCombinationsToSum(nums, partial, net_amount - nums[idx], net_combinations, idx, min_comb, max_comb);
        idx++;

//        if (partial.size() == min_comb)


    // remove number from list (backtracking)
    partial.pop_back();

    }

}

uint32_t sumCombinations(std::vector<uint32_t > &nums, const int32_t net_amount, const uint32_t &min_comb, const uint32_t &max_comb)
{


    uint32_t net_combinations = 0;
    std::vector<uint32_t> partial;

    recNumOfCombinationsToSum(nums, partial, net_amount, net_combinations, 0, min_comb, max_comb);

    return net_combinations;
}

uint32_t sumCombinations(std::vector<uint32_t > &nums, const int32_t net_amount)
{
    return sumCombinations(nums, net_amount, 0, net_amount);
}


int main() {

    uint32_t num = 20;
    uint32_t min_comb = 10; // minimum number of combinations
    uint32_t max_comb = 15; // maximum number of combinations

    clock_t start_t, end_t;
    double cpu_time_used;

    start_t = clock();

    std::vector<uint32_t> primes = sieveOfEratosthenes(num);

    std::cout << sumCombinations(primes, num, min_comb, max_comb) << std::endl;

    end_t = clock();
    cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

    std::cout << std::fixed << "\nI have slept for " << cpu_time_used << " seconds."  << std::endl;




    return 0;
}