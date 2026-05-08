#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

int k = 4;
int w = 5;

/* simple hash */
int hash_kmer(const string &kmer)
{
    int h = 0;
    for (char c : kmer)
        h = h * 31 + (c - '0');
    return abs(h);
}

vector<int> get_hashes(const string &s)
{
    vector<int> hashes;

    for (int i = 0; i <= (int)s.length() - k; i++)
    {
        string kmer = s.substr(i, k);
        hashes.push_back(hash_kmer(kmer));
    }

    return hashes;
}

vector<int> winnow(const vector<int> &hashes)
{
    vector<int> fingerprints;

    for (int i = 0; i <= (int)hashes.size() - w; i++)
    {
        int minVal = hashes[i];
        for (int j = 1; j < w; j++)
            minVal = min(minVal, hashes[i + j]);

        fingerprints.push_back(minVal);
    }

    return fingerprints;
}

double similarity(const vector<int> &a, const vector<int> &b)
{
    unordered_set<int> A(a.begin(), a.end());
    unordered_set<int> B(b.begin(), b.end());

    int shared = 0;
    for (auto &x : A)
        if (B.count(x)) shared++;

    int total = A.size() + B.size() - shared;

    return (double)shared / total;
}

int main()
{
    ifstream file("tokens.txt");

    vector<string> names;
    vector<string> programs;

    string name, tokens;

    while (file >> name >> tokens)
    {
        names.push_back(name);
        programs.push_back(tokens);
    }

    vector<vector<int>> fingerprints;

    for (auto &p : programs)
    {
        auto hashes = get_hashes(p);
        fingerprints.push_back(winnow(hashes));
    }

    struct Result {
        int i, j;
        double sim;
    };

    vector<Result> results;

    for (int i = 0; i < fingerprints.size(); i++)
    {
        for (int j = i + 1; j < fingerprints.size(); j++)
        {
            double sim = similarity(fingerprints[i], fingerprints[j]);
            results.push_back({i, j, sim});
        }
    }

    sort(results.begin(), results.end(), [](auto &a, auto &b) {
        return a.sim > b.sim;
    });

    for (auto &r : results)
    {
        cout << names[r.i] << " vs " << names[r.j]
             << " similarity: " << r.sim << endl;
    }
}