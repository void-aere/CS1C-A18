#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <thread>

bool fileExists(const std::string& path);
void loadData(std::vector<long long>& dataset, std::ifstream& stream);
void selectionSort(std::vector<long long>& dataset);

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
    std::cout << "loading... " << std::endl;
    loadData(dataset, file);
    std::cout << "done.\nsorting... " << std::endl;;
    selectionSort(dataset);
    std::cout << "done.\nsaving..." << std::endl;
    std::ofstream outfile(path + ".sorted");
    for (long long i : dataset) outfile << i << std::endl;
    std::cout << "done." << std::endl;
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