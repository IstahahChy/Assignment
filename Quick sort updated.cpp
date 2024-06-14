#include <iostream>

class Vector {
 public:
  Vector() : size_(0), capacity_(1), data_(new int[capacity_]) {}

  ~Vector() { delete[] data_; }

  void push_back(int value) {
    if (size_ == capacity_) {
      resize();
    }
    data_[size_++] = value;
  }

  int& operator[](int index) {
    if (index < 0 || index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }

  int size() const { return size_; }

 private:
  void resize() {
    capacity_ *= 2;
    int* newData = new int[capacity_];
    for (int i = 0; i < size_; ++i) {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
  }

  int size_;
  int capacity_;
  int* data_;
};

void quickSort(Vector& arr, int low, int high) {
  if (low < high) {
    int pivot = arr[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;

    while (true) {
      do {
        i++;
      } while (arr[i] < pivot);

      do {
        j--;
      } while (arr[j] > pivot);

      if (i >= j) {
        break;
      }

      std::swap(arr[i], arr[j]);
    }

    quickSort(arr, low, j);
    quickSort(arr, j + 1, high);
  }
}

int main() {
  int N;
  std::cin >> N;
  Vector arr;
  for (int i = 0; i < N; ++i) {
    int value;
    std::cin >> value;
    arr.push_back(value);
  }

  if (N > 0) {
    quickSort(arr, 0, N - 1);
  }

  for (int i = 0; i < N; ++i) {
    std::cout << arr[i] << std::endl;
  }

  return 0;
}
