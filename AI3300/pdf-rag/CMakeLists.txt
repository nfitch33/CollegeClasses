cmake_minimum_required(VERSION 3.10)
project(pdf_rag)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(pdf_rag
    main.cpp
    src/pdf_loader.cpp
    src/chunker.cpp
    src/search.cpp
    src/llm.cpp
)

target_link_libraries(pdf_rag poppler-cpp)