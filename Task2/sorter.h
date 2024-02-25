#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <string>

class SortingStrategy {
public:
    virtual void sort(std::vector<int>& arr) = 0;
    virtual ~SortingStrategy() {}
};

class BubbleSort : public SortingStrategy {
public:
    void sort(std::vector<int>& arr) override;
};

class InsertionSort : public SortingStrategy {
public:
    void sort(std::vector<int>& arr) override;
};

class SelectionSort : public SortingStrategy {
public:
    void sort(std::vector<int>& arr) override;
};

class FileHandler {
public:
    std::vector<int> readFromFile(const std::string& filename);
    void saveToFile(const std::vector<int>& arr, const std::string& filename);
};

class SortingApplication {
public:
    SortingApplication();
    ~SortingApplication();
    void runSortingProcess();
private:
    SortingStrategy* strategy;
    FileHandler fileHandler;
};
#endif // SORTER_H