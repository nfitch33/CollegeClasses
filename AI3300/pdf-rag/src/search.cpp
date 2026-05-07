#include "search.h"
#include <sstream>
#include <algorithm>
#include <cctype>
 
// Convert a string to lowercase
static std::string to_lower(std::string s) {
    for (char& c : s) {
        c = std::tolower((unsigned char)c);
    }
    return s;
}
 
// Score how well chunk text matches the query.
// Both query and chunk text are lowercased before comparison.
static double score(const std::string& query, const std::string& chunk_text) {
    std::string lower_chunk = to_lower(chunk_text);
 
    std::istringstream stream(to_lower(query));
    std::string word;
 
    int match = 0;
    int total = 0;
 
    while (stream >> word) {
        total++;
        if (lower_chunk.find(word) != std::string::npos) {
            match++;
        }
    }
 
    return total == 0 ? 0.0 : (double)match / total;
}
 
std::vector<Chunk> search(const std::string& query,
                          const std::vector<Chunk>& chunks,
                          int top_k) {
 
    std::vector<std::pair<double, Chunk>> ranked;
 
    for (const auto& c : chunks) {
        ranked.push_back({score(query, c.text), c});
    }
 
    std::sort(ranked.begin(), ranked.end(),
              [](const auto& a, const auto& b) {
                  return a.first > b.first;
              });
 
    std::vector<Chunk> results;
 
    for (int i = 0; i < top_k && i < (int)ranked.size(); i++) {
        results.push_back(ranked[i].second);
    }
 
    return results;
}