#include "llm.h"
#include <string>
#include <cstdio>
#include <iostream>
 
// Escape a string to be safely embedded in a JSON value
static std::string json_escape(const std::string& s) {
    std::string out;
 
    for (unsigned char c : s) {
        switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            default:
                // Strip control characters
                if (c >= 32) out += c;
        }
    }
 
    return out;
}
 
// Parse the "response" field out of Ollama's JSON reply.
// Ollama returns: {"model":"...","response":"...","done":true,...}
// We extract just the value of "response".
static std::string parse_response(const std::string& json) {
    const std::string key = "\"response\":\"";
    size_t start = json.find(key);
 
    if (start == std::string::npos) {
        std::cerr << "ERROR: could not find 'response' field in:\n" << json << "\n";
        return "ERROR: unexpected response from Ollama.";
    }
 
    start += key.size();
    std::string out;
 
    for (size_t i = start; i < json.size(); i++) {
        if (json[i] == '\\' && i + 1 < json.size()) {
            // Handle JSON escape sequences
            char next = json[i + 1];
            if      (next == 'n')  { out += '\n'; i++; }
            else if (next == 't')  { out += '\t'; i++; }
            else if (next == '"')  { out += '"';  i++; }
            else if (next == '\\') { out += '\\'; i++; }
            else if (next == 'r')  { out += '\r'; i++; }
            else                   { out += next; i++; }
        } else if (json[i] == '"') {
            // Closing quote of the response string
            break;
        } else {
            out += json[i];
        }
    }
 
    return out;
}
 
std::string ask_ollama(const std::string& prompt) {
    std::string safe = json_escape(prompt);
 
    std::string cmd =
        "curl -s http://localhost:11434/api/generate "
        "-d \"{"
        "\\\"model\\\": \\\"llama3.1\\\","
        "\\\"prompt\\\": \\\"" + safe + "\\\","
        "\\\"stream\\\": false"
        "}\"";
 
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "ERROR: failed to run curl\n";
        return "ERROR: could not connect to Ollama.";
    }
 
    std::string raw;
    char buffer[256];
 
    while (fgets(buffer, sizeof(buffer), pipe)) {
        raw += buffer;
    }
 
    pclose(pipe);
 
    return parse_response(raw);
}