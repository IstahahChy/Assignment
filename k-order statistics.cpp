#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 10000000 + 4321;

int main() {
  int n, k;
  long long A0, A1;
  cin >> n >> k >> A0 >> A1;

  vector<long long> A(n);
  A[0] = A0;
  A[1] = A1;

  for (int i = 2; i < n; ++i) {
    A[i] = (A[i - 1] * 123 + A[i - 2] * 45) % MOD;
  }

  nth_element(A.begin(), A.begin() + k - 1, A.end());
  cout << A[k - 1] << endl;

  return 0;
}
