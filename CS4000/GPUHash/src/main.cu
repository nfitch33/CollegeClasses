#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "sha256.cuh"

struct Job {
    std::string salt;
    std::string target;
    std::string charset;
    int length;
};

std::vector<Job> load(const std::string &f) {
    std::ifstream in(f);
    std::vector<Job> j;
    Job x;

    while (in >> x.salt >> x.target >> x.charset >> x.length)
        j.push_back(x);

    return j;
}

void cpu_test(const Job &j) {
    char hash[65];
    sha256_hash_string(hash, j.salt.c_str());

    std::cout << "INPUT: " << j.salt << "\n";
    std::cout << "HASH : " << hash << "\n";
}

int main() {
    auto jobs = load("data/input.txt");

    for (auto &j : jobs)
        cpu_test(j);
}