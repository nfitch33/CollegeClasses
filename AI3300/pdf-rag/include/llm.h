#pragma once
#include <string>

// Sends prompt to local Ollama and returns response text
std::string ask_ollama(const std::string& prompt);