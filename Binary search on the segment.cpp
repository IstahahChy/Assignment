#include <iostream>
#include <vector>

bool BinarySearch(const int* begin, const int* end, int target) {
  while (begin < end) {
    const int* mid = begin + (end - begin) / 2;
    if (*mid == target) {
      return true;
    } else if (*mid < target) {
      begin = mid + 1;
    } else {
      end = mid;
    }
  }
  return false;
}

int main() {
  int N;
  std::cin >> N;
  std::vector<int> array(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> array[i];
  }

  int Q;
  std::cin >> Q;
  for (int q = 0; q < Q; ++q) {
    int i, j, t;
    std::cin >> i >> j >> t;
    if (BinarySearch(&array[i], &array[j], t)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }

  return 0;
}
