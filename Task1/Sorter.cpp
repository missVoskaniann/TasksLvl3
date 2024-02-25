#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

void insertionSort(std::vector<int>& arr) {
    int key, j;
    for (int i = 1; i < arr.size(); ++i) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(std::vector<int>& arr) {
    bool swapped;
    for (int i = 0; i < arr.size() - 1; ++i) {
        swapped = false;
        for (int j = 0; j < arr.size() - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) {
            break;
        }
    }
}

void selectionSort(std::vector<int>& arr) {
    int minPos;
    for (int i = 0; i < arr.size() - 1; ++i) {
        minPos = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minPos]) {
                minPos = j;
            }
        }
        if (minPos != i) {
            std::swap(arr[minPos], arr[i]);
        }
    }
}

enum SortingStrategy {
    INSERTION_SORT,
    BUBBLE_SORT,
    SELECTION_SORT,
};

struct SortingOption {
    SortingStrategy strategy;
    void (*fp)(std::vector<int>&);
};

std::vector<int> readFromFile(const std::string& filename) {
    std::vector<int> arr;
    std::ifstream file(filename);
    if (file.is_open()) {
        int num;
        while (file >> num) {
            arr.push_back(num);
        }
        file.close();
    } else {
        std::cerr << "Could not open the file" << std::endl;
    }
    return arr;
}

void saveToFile(const std::vector<int>& arr, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int num : arr) {
            file << num << " ";
        }
        file.close();
    } else {
        std::cerr << "Could not open the file" << std::endl;
    }
}

int main() {
    SortingOption sortingOpt[] = {
        {INSERTION_SORT, insertionSort},
        {BUBBLE_SORT, bubbleSort},
        {SELECTION_SORT, selectionSort}
    };
    std::string filename;
    std::cout << "Enter the name of the file: ";
    std::cin >> filename;
    
    std::vector<int> arr = readFromFile(filename);
    if (arr.empty()) {
        return 1;
    }
    int choice;
    std::cout << "Select algorithm to sort:" << std::endl;
    for (int i = 0; i < sizeof(sortingOpt) / sizeof(sortingOpt[0]); ++i) {
        std::cout << i + 1 << ". ";
        switch (sortingOpt[i].strategy) {
            case BUBBLE_SORT: 
                std::cout << "Bubble Sort" << std::endl;
                break;
            case INSERTION_SORT:
                std::cout << "Insertion Sort" << std::endl;
                break;
            case SELECTION_SORT:
                std::cout << "Selection Sort" << std::endl;
                break;
        }
    }
    std::cin >> choice;
    if (choice < 1 || choice > sizeof(sortingOpt) / sizeof(sortingOpt[0])) {
        std::cerr << "Invald input" << std::endl;
        return 1;
    }
    sortingOpt[choice - 1].fp(arr);
    saveToFile(arr, "sorted_" + filename);
    return 0;
}