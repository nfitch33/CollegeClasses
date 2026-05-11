/**
 * @file
 * @author Krerkkiat Chusap
 * @brief Utility functions
*/
#pragma once
#include <string>
#include <vector>

/**
 * @brief Split the source by delim
 * 
 * @param source The text to be splitted.
 * @param delim The delimiter to split the text with.
*/
std::vector<std::string> split_by(const std::string &source, const std::string &delim);

/**
 * Concat all lines into one multi-line string.
 * 
 * Same concept as Haskell's unlines.
*/
std::string unlines(const std::vector<std::string> &lines);
