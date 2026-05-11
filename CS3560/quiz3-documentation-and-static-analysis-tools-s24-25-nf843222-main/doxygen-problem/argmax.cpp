/**
 * @file
 * @brief Finds the index of the maximum element in a vector of floats.
 *
 * This function returns the index of the maximum value in the given vector.
 * If the vector is empty, it returns -1. If the vector has only one element,
 * it returns 0.
 *
 * @param values A constant reference to a std::vector<float> containing the input values.
 * @return long int The index of the maximum value in the vector.
 *         Returns -1 if the input vector is empty.
 */
#include "argmax.hpp"
#include <vector>

using namespace std;

long int argmax(const vector<float> &values) {
  if (values.size() == 0) {
    return -1;
  } else if (values.size() == 1) {
    return 0;
  }

  size_t max_index = 0;
  for (size_t idx = 1; idx < values.size(); idx++) {
    if (values[idx] > values[max_index]) {
      max_index = idx;
    }
  }

  return static_cast<long int>(max_index);
}