#include <iostream>
#include <vector>


template<typename Iterator>
void recursiveInsertionSort(Iterator begin, Iterator end) {
    // Base case
    if (begin == end || ++begin == end) {
        return;
    }

    // Sort the first n-1 elements
    recursiveInsertionSort(begin, end--);

    // Insert the last element at its correct position in the sorted array
    Iterator last = end;
    --last;
    Iterator it = last;

    while (it != begin--) {
        if (*it < *last) {
            // Swap the elements
            typename Iterator::value_type temp = *it;
            *it = *last;
            *last = temp;
        }
        --it;
        --last;
    }
}

int main() {
    std::vector<int> arr;
    arr.push_back(8);
    arr.push_back(12);
    arr.push_back(7);
    arr.push_back(15);
    arr.push_back(11);
    arr.push_back(20);
    arr.push_back(6);
    arr.push_back(17);
    arr.push_back(5);
    arr.push_back(14);

    recursiveInsertionSort(arr.begin(), arr.end());

    std::cout << "Sorted array in descending order: ";
    for (std::vector<int>::iterator it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
