#ifndef RADIXSORTNAMESPACE_H
#define RADIXSORTNAMESPACE_H

#include <vector>

namespace RadixSortNamespace {
void radixSort(std::vector<int> &numbers);
std::vector<double> benchmark(std::vector<int> &numbers, int numberOfRuns);
}; // namespace RadixSortNamespace

#endif // RADIXSORTNAMESPACE_H
