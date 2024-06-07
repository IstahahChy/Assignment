#include <cstdint>
#include <iostream>
#include <vector>

// Function to perform counting sort based on a specific byte position
void countingSort(std::vector<uint64_t>& arr, int bytePos) {
  const int radix = 256;  // 8 bits, as we're sorting bytes
  std::vector<uint64_t> output(arr.size());
  std::vector<int> count(radix, 0);

  // Count occurrences of each byte value
  for (uint64_t num : arr) {
    int byte = (num >> (bytePos * 8)) & 0xFF;
    count[byte]++;
  }

  // Adjust count to represent the position of each byte value in the output
  // array
  for (int i = 1; i < radix; i++) {
    count[i] += count[i - 1];
  }

  // Build the output array
  for (int i = arr.size() - 1; i >= 0; i--) {
    int byte = (arr[i] >> (bytePos * 8)) & 0xFF;
    output[count[byte] - 1] = arr[i];
    count[byte]--;
  }

  // Copy the sorted elements back to the original array
  for (size_t i = 0; i < arr.size(); i++) {
    arr[i] = output[i];
  }
}

// LSD Radix Sort
void lsdRadixSort(std::vector<uint64_t>& arr) {
  const int numBytes = sizeof(uint64_t);
  for (int bytePos = 0; bytePos < numBytes; bytePos++) {
    countingSort(arr, bytePos);
  }
}

int main() {
  int N;
  std::cin >> N;

  std::vector<uint64_t> arr(N);
  for (int i = 0; i < N; i++) {
    std::cin >> arr[i];
  }

  // Sort the array using LSD Radix Sort
  lsdRadixSort(arr);

  // Output the sorted array
  for (uint64_t num : arr) {
    std::cout << num << std::endl;
  }

  return 0;
}
