#pragma once
#include <vector>
#include <string>

struct Chunk {
    std::string text;
    int page;
};

std::vector<Chunk> chunk_text(const std::vector<std::string>& pages, int chunk_size = 800);