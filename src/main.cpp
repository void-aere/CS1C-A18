#include <iostream>
#include <iomanip>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <thread>
#include "helpers.hpp"

void printMenu(long long target, int sequentialComparisons, int binaryComparisons);

bool fileExists(const std::string& path);
void loadData(std::vector<long long>& dataset, std::ifstream& stream);
void selectionSort(std::vector<long long>& dataset);
bool verify(std::vector<long long>& dataset);
int sequentialSearch(std::vector<long long> dataset, long long query);
int binarySearch(std::vector<long long> dataset, long long query, int low, int high);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No data file provided." << std::endl;
        return 1;
    }

    std::string path = argv[1];
    if (!fileExists(path)) {
        std::cout << path << ": file does not exist." << std::endl;
        return 2;
    }

    std::string line;
    std::ifstream file(path);
    std::getline(file, line);
    const int length = std::atoi(line.c_str());

    std::vector<long long> dataset(length);

    // std::thread loader(loadData, dataset, file)
    // loader.join();
    std::cout << "loading... " << std::flush;
    loadData(dataset, file);
    std::cout << "done." << std::endl;

    std::cout << "verifying... " << std::flush;
    bool sorted = verify(dataset);
    std::cout << std::boolalpha << "done. " << (sorted ? "(sorted)" : "(unsorted)") << std::endl;

    if (!sorted) {
        std::cout << "sorting... " << std::flush;
        selectionSort(dataset);
        std::cout << "done." << std::endl;

        std::cout << "verifying... " << std::flush;
        sorted = verify(dataset);
        std::cout << std::boolalpha << "done. " << (sorted ? "(sorted)" : "(unsorted)") << std::endl;
        if (!sorted) {
            std::cout << "sorting failed. terminating." << std::endl;
            return 3;
        }

        // std::cout << "saving... " << std::flush;
        // std::ofstream outfile(path + ".sorted");
        // outfile << length << std::endl;
        // for (auto i : dataset) outfile << i << std::endl;
        // std::cout << "done." << std::endl;
    }

    int option, sComps, bComps;
    long long target;
    option = sComps = bComps = target = 0;
    do {
        clearScreen();
        printMenu(target, sComps, bComps);
        option = getMenuOptionAuto(4);

        switch (option) {
            case 1:
                target = inputLL("Enter a new target: ");
                break;
            case 2:
                sComps = sequentialSearch(dataset, target);
                break;
            case 3:
                bComps = binarySearch(dataset, target, 0, dataset.size());
                break;
            case 4:
                return 0;
        }
    } while (option != 4);
}

void printMenu(long long target, int sequentialComparisons, int binaryComparisons) {
    std::string sString = sequentialComparisons != 0 ? std::to_string(sequentialComparisons) + " comparisons" : "unknown";
    std::string bString = binaryComparisons != 0 ? std::to_string(binaryComparisons) + " comparisons" : "unknown";
    const int width = 80;
    std::cout << center("Search Algorithm Comparison", width) << std::endl;;
    std::cout << "\tCURRENT TARGET: " << (target != 0 ? std::to_string(target) : "none") << std::endl;
    std::cout << std::endl;
    std::cout << center("Search Metrics", width) << std::endl;
    std::cout << "\tSequential Sort:\t\t\t\t" << sString << std::endl;
    std::cout << "\tBinary Sort:\t\t\t\t\t" << bString << std::endl;
    std::cout << std::endl;
    std::cout << center("Menu", width) << std::endl;
    std::cout << "\t[1] Enter long long integer to search\n"
              << "\t[2] Perform sequential (linear) search\n"
              << "\t[3] Perform binary search\n"
              << "\t[4] Quit\n\n" << std::flush;
}

bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);
}

void loadData(std::vector<long long>& dataset, std::ifstream& stream) {
    std::string line;
    int index = 0;
    while (std::getline(stream, line)) {
        dataset[index] = std::stoll(line.c_str());
        ++index;
    }
}

void selectionSort(std::vector<long long>& dataset) {
    int length = static_cast<int>(dataset.size());
    int mindex;
    long long temp;
    for (int i = 0; i < length - 1; ++i) {
        if (i % 100 == 0) std::cout << 100.00*i/length << "%" << std::endl;
        mindex = i;
        for (int j = i; j < length; ++j) {
            if (dataset[j] < dataset[mindex]) mindex = j;
        }
        if (mindex != i) {
            temp = dataset[i];
            dataset[i] = dataset[mindex];
            dataset[mindex] = temp;
        }
    }
}

bool verify(std::vector<long long>& dataset) {
    for (size_t i = 1; i < dataset.size(); ++i) {
        if (dataset[i - 1] > dataset[i]) return false;
    }
    return true;
}

int sequentialSearch(std::vector<long long> dataset, long long query) {
    int comparisons = 0;
    for (long long i : dataset) {
        ++comparisons;
        if (i == query) {
            return comparisons;
        }
    }
    return comparisons;
}

int binarySearch(std::vector<long long> dataset, long long query, int low, int high) {
    if (high - low < 2) {
        // is the last value the target?
        return 1; // one comparison
    }

    int mid = (high + low) / 2;
    if (dataset[mid] == query) {
        return 2;
    } else if (dataset[mid] > query) {
        return 3 + binarySearch(dataset, query, low, mid);
    } else {
        return 3 + binarySearch(dataset, query, mid, high);
    }
}