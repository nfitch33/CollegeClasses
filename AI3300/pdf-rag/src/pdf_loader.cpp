#include "pdf_loader.h"
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <iostream>
 
std::vector<std::string> load_pdf(const std::string& path) {
    std::vector<std::string> pages;
 
    poppler::document* doc = poppler::document::load_from_file(path);
 
    if (!doc) {
        std::cerr << "Failed to open PDF: " << path << "\n";
        return pages;
    }
 
    std::cout << "Loaded PDF with " << doc->pages() << " pages.\n";
 
    for (int i = 0; i < doc->pages(); i++) {
        poppler::page* page = doc->create_page(i);
 
        if (page) {
            // to_utf8() returns a poppler::byte_array (std::vector<char>)
            // so we construct a std::string from its data pointer and size
            poppler::byte_array bytes = page->text().to_utf8();
            std::string text(bytes.data(), bytes.size());
            pages.push_back(text);
            delete page;
        } else {
            pages.push_back("");
        }
    }
 
    delete doc;
    return pages;
}