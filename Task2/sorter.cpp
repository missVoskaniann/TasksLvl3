#include "sorter.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void BubbleSort::sort(std::vector<int>& arr) {
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

void InsertionSort::sort(std::vector<int>& arr) {
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

void SelectionSort::sort(std::vector<int>& arr) {
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

std::vector<int> FileHandler::readFromFile(const std::string& filename) {
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

void FileHandler::saveToFile(const std::vector<int>& arr, const std::string& filename) {
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

SortingApplication::SortingApplication() : strategy{nullptr} {}

SortingApplication::~SortingApplication() {
    delete strategy;
}

void SortingApplication::runSortingProcess() {      
        std::string inputFileName;
        std::cout << "Enter the input file name: ";
        std::cin >> inputFileName;

        std::vector<int> arr = fileHandler.readFromFile(inputFileName);

        if (arr.empty()) {
            std::cerr << "Input array is empty or file could not be read." << std::endl;
            return;
        }
        int choice;
        std::cout << "Select a sorting algorithm:" << std::endl;
        std::cout << "1. Bubble Sort" << std::endl;
        std::cout << "2. Selection Sort" << std::endl;
        std::cout << "3. Insertion Sort" << std::endl;
        std::cin >> choice;
 
        switch (choice) {
            case 1:
                strategy = new BubbleSort();
                break;
            case 2:
                strategy = new SelectionSort();
                break;
            case 3:
                strategy = new InsertionSort();
                break;
            default:
                std::cerr << "Invalid choice!" << std::endl;
                return;                
        }

        strategy->sort(arr);

        std::string outputFileName;
        std::cout << "Enter the output file name: ";
        std::cin >> outputFileName;

        fileHandler.saveToFile(arr, outputFileName);
    }