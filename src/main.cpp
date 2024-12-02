#include <iostream>
#include <iomanip>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <thread>

bool fileExists(const std::string& path);
void loadData(std::vector<long long>& dataset, std::ifstream& stream);
void selectionSort(std::vector<long long>& dataset);
bool verify(std::vector<long long>& dataset);

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
    }
}

bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);
}

void loadData(std::vector<long long>& dataset, std::ifstream& stream) {
    std::string line;
    int index = 0;
    while (std::getline(stream, line)) {
        dataset[index] = std::atoi(line.c_str());
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