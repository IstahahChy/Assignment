#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int>& arr, int low, int high) {
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

      swap(arr[i], arr[j]);
    }

    quickSort(arr, low, j);
    quickSort(arr, j + 1, high);
  }
}

int main() {
  int N;
  cin >> N;
  vector<int> arr(N);
  for (int i = 0; i < N; ++i) {
    cin >> arr[i];
  }

  quickSort(arr, 0, N - 1);

  for (int i = 0; i < N; ++i) {
    cout << arr[i] << endl;
  }

  return 0;
}
