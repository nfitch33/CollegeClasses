#include "chunker.h"
#include <cctype>
 
static std::string clean_text(const std::string& s) {
    std::string out;
 
    for (char c : s) {
        // keep printable chars, newlines, and tabs
        if (c >= 32 || c == '\n' || c == '\t') {
            out += c;
        }
    }
 
    return out;
}
 
std::vector<Chunk> chunk_text(const std::vector<std::string>& pages, int chunk_size) {
    std::vector<Chunk> chunks;
 
    for (int i = 0; i < (int)pages.size(); i++) {
        std::string text = clean_text(pages[i]);
 
        int j = 0;
        while (j < (int)text.size()) {
            int end = std::min(j + chunk_size, (int)text.size());
 
            // Walk back to the nearest word boundary (space or newline)
            if (end < (int)text.size()) {
                int boundary = end;
                while (boundary > j && text[boundary] != ' ' && text[boundary] != '\n') {
                    boundary--;
                }
                // Only use boundary if we actually found one
                if (boundary > j) {
                    end = boundary;
                }
            }
 
            Chunk c;
            c.text = text.substr(j, end - j);
            c.page = i + 1;
            chunks.push_back(c);
 
            // Skip past the whitespace character we broke on
            j = end + 1;
        }
    }
 
    return chunks;
}