#include "radixsortnamespace.h"
#include <QElapsedTimer>

namespace RadixSortNamespace {
namespace {
int getMax(std::vector<int> &numbers) {
  int max = numbers[0];
  for (std::size_t i = 1; i < numbers.size(); i++) {
    if (numbers[i] > max) {
      max = numbers[i];
    }
  }
  return max;
}

void countingSort(std::vector<int> &numbers, int exp) {
  int size = numbers.size();
  std::vector<int> output(size);

  int i;
  int count[10] = {0};

  // Store count of occurrences in count array
  for (i = 0; i < size; i++) {
    count[(numbers[i] / exp) % 10]++;
  }

  // Change count[i] so that count[i] now contains actual position of this digit
  // in output array
  for (i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  // Build the output array
  for (i = size - 1; i >= 0; i--) {
    output[count[(numbers[i] / exp) % 10] - 1] = numbers[i];
    count[(numbers[i] / exp) % 10]--;
  }

  // Copy the output array to the numbers vector
  for (i = 0; i < size; i++) {
    numbers[i] = output[i];
  }
}
} // namespace

void radixSort(std::vector<int> &numbers) {
  // Get the maximum value in the vector
  int max = getMax(numbers);

  // Do counting sort for every digit
  for (int exp = 1; max / exp > 0; exp *= 10) {
    countingSort(numbers, exp);
  }
}

std::vector<double> benchmark(std::vector<int> &numbers, int numberOfRuns) {
  // Create copy of numbers
  std::vector<int> copy = numbers;

  // Sort the numbers using radix sort and measure the time it takes for
  // numberOfRuns times
  std::vector<double> times;
  QElapsedTimer timer;
  for (int i = 0; i < numberOfRuns; i++) {
    // Measure sorting time
    timer.start();
    radixSort(numbers);
    double elapsedTime = timer.nsecsElapsed() / 1000000.0;

    // Add time to vector
    times.push_back(elapsedTime);

    // Reset numbers
    numbers = copy;
  }

  return times;
}
} // namespace RadixSortNamespace
