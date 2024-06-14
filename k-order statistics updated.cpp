#include <algorithm>
#include <iostream>

// Custom vector implementation
template <typename T>
class MyVector {
 public:
  MyVector(size_t initial_capacity = 2)
      : size_(0), capacity_(initial_capacity) {
    data_ = new T[capacity_];
  }

  ~MyVector() { delete[] data_; }

  void push_back(const T& value) {
    if (size_ == capacity_) {
      resize();
    }
    data_[size_++] = value;
  }

  T& operator[](size_t index) { return data_[index]; }

  const T& operator[](size_t index) const { return data_[index]; }

  size_t size() const { return size_; }

  T* begin() { return data_; }

  T* end() { return data_ + size_; }

 private:
  void resize() {
    capacity_ *= 2;
    T* new_data = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
  }

  T* data_;
  size_t size_;
  size_t capacity_;
};

int main() {
  int32_t n, k;
  int64_t A0, A1;
  std::cin >> n >> k >> A0 >> A1;

  const int32_t MOD = 10000000 + 4321;

  MyVector<int64_t> A;
  A.push_back(A0);
  A.push_back(A1);

  for (int32_t i = 2; i < n; ++i) {
    int64_t value = (A[i - 1] * 123 + A[i - 2] * 45) % MOD;
    A.push_back(value);
  }

  std::nth_element(A.begin(), A.begin() + k - 1, A.end());
  std::cout << A[k - 1] << std::endl;

  return 0;
}
