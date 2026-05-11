add_executable(tests test_evaluate.cpp test_othello_primary.cpp test_othello_aux.cpp test_utils.cpp)
target_link_libraries(tests PRIVATE othello game piece utils Catch2::Catch2WithMain)
