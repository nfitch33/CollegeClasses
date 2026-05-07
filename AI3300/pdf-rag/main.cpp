#include <iostream>
#include "pdf_loader.h"
#include "chunker.h"
#include "search.h"
#include "llm.h"
 
std::string build_prompt(const std::string& question,
                         const std::vector<Chunk>& context) {
 
    std::string prompt =
        "You are a helpful textbook assistant.\n"
        "Answer ONLY using the provided context below.\n"
        "Do not use any outside knowledge.\n"
        "Explain clearly and justify your answer with references to the context.\n"
        "If the context does not contain enough information to answer, say so.\n\n"
        "CONTEXT:\n";
 
    for (const auto& c : context) {
        prompt += "[Page " + std::to_string(c.page) + "]\n";
        prompt += c.text + "\n\n";
    }
 
    prompt += "QUESTION:\n" + question + "\n\n";
    prompt += "ANSWER:\n";
 
    return prompt;
}
 
int main() {
    std::string path = ".././textbook/ESL.pdf";
 
    std::cout << "Loading PDF: " << path << "\n";
    auto pages = load_pdf(path);
 
    if (pages.empty()) {
        std::cerr << "Failed to load PDF. Check the path and try again.\n";
        return 1;
    }
 
    std::cout << "Chunking text...\n";
    auto chunks = chunk_text(pages);
    std::cout << "Created " << chunks.size() << " chunks.\n\n";
 
    std::cout << "Ready! Type your question or 'exit' to quit.\n\n";
 
    while (true) {
        std::string q;
        std::cout << "Question: ";
        std::getline(std::cin, q);
 
        if (q == "exit") break;
        if (q.empty()) continue;
 
        auto retrieved = search(q, chunks);
 
        std::string prompt = build_prompt(q, retrieved);
 
        std::cout << "\n--- Answer ---\n\n";
 
        std::string response = ask_ollama(prompt);
 
        std::cout << response << "\n\n";
        std::cout << "--------------\n\n";
    }
 
    return 0;
}
 