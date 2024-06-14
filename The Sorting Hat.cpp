#include <iostream>
#include <limits>
#include <string>

template <typename T>
struct Pair {
  T val;
  T min;
};

template <typename T>
struct IsLess {
  bool operator()(const T& l, const T& r) const { return l <= r; }
};

template <typename T, class TLess = IsLess<T>>
class Stack {
 private:
  Pair<T>* out_stack_;
  std::size_t size_;
  std::size_t capacity_;

  void Resize(std::size_t new_capacity) {
    Pair<T>* new_array = new Pair<T>[new_capacity];
    for (std::size_t i = 0; i < size_; i++) {
      new_array[i] = out_stack_[i];
    }
    delete[] out_stack_;
    out_stack_ = new_array;
    capacity_ = new_capacity;
  }

 public:
  Stack() : size_(0), capacity_(1) { out_stack_ = new Pair<T>[capacity_]; }

  ~Stack() { delete[] out_stack_; }

  void Enqueue(T val) {
    if (size_ == capacity_) {
      Resize(capacity_ * 2);
    }
    if (size_ == 0) {
      out_stack_[0].val = val;
      out_stack_[0].min = val;
    } else {
      out_stack_[size_].val = val;
      out_stack_[size_].min =
          (out_stack_[size_ - 1].min < val) ? out_stack_[size_ - 1].min : val;
    }
    size_++;
  }

  T PopBack() {
    if (size_ == 0) {
      throw "error";
    }
    return out_stack_[--size_].val;
  }

  T GetMin() const {
    if (size_ == 0) {
      throw "error";
    }
    return out_stack_[size_ - 1].min;
  }

  T Front(bool fromStart) const {
    if (size_ == 0) {
      throw "error";
    }
    return fromStart ? out_stack_[0].val : out_stack_[size_ - 1].val;
  }

  std::size_t Size() const { return size_; }

  void Clear() {
    delete[] out_stack_;
    size_ = 0;
    capacity_ = 1;
    out_stack_ = new Pair<T>[capacity_];
  }

  void CopyStack(Stack<T>& stack1) {
    while (stack1.Size() > 0) {
      Enqueue(stack1.PopBack());
    }
  }
};

template <typename T, class TLess = IsLess<T>>
class MinQueue {
 private:
  Stack<T> in_stack_;
  Stack<T> out_stack_;

 public:
  MinQueue() = default;

  void Enqueue(T val) { in_stack_.Enqueue(val); }

  T Dequeue() {
    if (out_stack_.Size() == 0) {
      if (in_stack_.Size() == 0) {
        throw "error";
      }
      out_stack_.CopyStack(in_stack_);
    }
    return out_stack_.PopBack();
  }

  T Front() const {
    if (out_stack_.Size() == 0) {
      if (in_stack_.Size() == 0) {
        throw "error";
      }
      return in_stack_.Front(true);
    }
    return out_stack_.Front(false);
  }

  T GetMin() const {
    if (out_stack_.Size() == 0 && in_stack_.Size() == 0) {
      throw "error";
    } else if (out_stack_.Size() == 0) {
      return in_stack_.GetMin();
    } else if (in_stack_.Size() == 0) {
      return out_stack_.GetMin();
    }
    return (in_stack_.GetMin() < out_stack_.GetMin()) ? in_stack_.GetMin()
                                                      : out_stack_.GetMin();
  }

  std::size_t Size() const { return in_stack_.Size() + out_stack_.Size(); }

  void Clear() {
    in_stack_.Clear();
    out_stack_.Clear();
  }
};

int main() {
  using std::cin;
  using std::cout;
  using std::string;

  std::size_t n;
  cin >> n;
  MinQueue<long long> Queue;

  string command;
  for (std::size_t i = 0; i < n; i++) {
    cin >> command;
    if (command == "enqueue") {
      long long val;
      cin >> val;
      Queue.Enqueue(val);
      cout << "ok\n";
    } else if (command == "dequeue") {
      try {
        cout << Queue.Dequeue() << '\n';
      } catch (const char* msg) {
        cout << msg << '\n';
      }
    } else if (command == "front") {
      try {
        cout << Queue.Front() << '\n';
      } catch (const char* msg) {
        cout << msg << '\n';
      }
    } else if (command == "size") {
      cout << Queue.Size() << '\n';
    } else if (command == "clear") {
      Queue.Clear();
      cout << "ok\n";
    } else if (command == "min") {
      try {
        cout << Queue.GetMin() << '\n';
      } catch (const char* msg) {
        cout << msg << '\n';
      }
    }
  }

  return 0;
}
