// Exercise 9. STL algorithms with lambdas.
// A lambda is just a function without a name, written where it is used. [] is
// the capture list, so what the lambda gets to see from around it.

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

ostream &operator<<(ostream &out, const vector<int> &table) {
  for (auto &e : table)
    out << e << " ";
  return out;
}

int main() {
  vector<int> v1 = {3, 3, 12, 14, 17, 25, 30};
  vector<int> v2 = {2, 3, 12, 14, 24};

  cout << "v1: " << v1 << endl;
  cout << "v2: " << v2 << endl
       << endl;

  // a) find_if takes a predicate and returns end() when nothing matches.
  auto pos = find_if(v1.begin(), v1.end(), [](int value) { return value > 15; });
  if (pos != v1.end())
    cout << "a) first element above 15: " << *pos
         << " at index " << (pos - v1.begin()) << endl;
  else
    cout << "a) no element above 15" << endl;

  // b) equal walks the first range and compares element by element against
  // the second. The predicate gets one element from each.
  const int tolerance = 2;
  auto about_equal = [tolerance](int a, int b) { return abs(a - b) <= tolerance; };

  // {3, 3, 12, 14, 17} against {2, 3, 12, 14, 24}. Last pair differs by 7.
  const bool equal5 = equal(v1.begin(), v1.begin() + 5, v2.begin(), about_equal);
  cout << "b) [begin, begin+5) about equal to v2: " << (equal5 ? "yes" : "no") << endl;

  // {3, 3, 12, 14} against {2, 3, 12, 14}. Largest difference is 1.
  const bool equal4 = equal(v1.begin(), v1.begin() + 4, v2.begin(), about_equal);
  cout << "b) [begin, begin+4) about equal to v2: " << (equal4 ? "yes" : "no") << endl;

  // c) replace_copy_if writes to a new range instead of changing the old one,
  // so the target needs room up front.
  vector<int> v3(v1.size());
  replace_copy_if(v1.begin(), v1.end(), v3.begin(),
                  [](int value) { return value % 2 != 0; }, 100);

  cout << endl;
  cout << "c) v1 unchanged: " << v1 << endl;
  cout << "c) v3 copy:      " << v3 << endl;
}
