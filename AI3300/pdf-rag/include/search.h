#pragma once
#include <vector>
#include <string>
#include "chunker.h"

std::vector<Chunk> search(const std::string& query,
                          const std::vector<Chunk>& chunks,
                          int top_k = 5);