#include <iostream>
#include <vector>
#include <algorithm>

namespace {
template <class T> 
void swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
void insertion_sort(std::vector<T>& input) {
  for(int key = 1; key < input.size(); key++) {
    for(int p = 0; p <= key; p++) {
      if (input[key] < input[p])
        swap(input[key], input[p]);
    }
  }
}
}

// overload << for vector
template<class T>
std::ostream& operator << (std::ostream& out, std::vector<T>& v) {
  out << "std::vector[";
  for(int i=0; i < v.size(); i++)
    out << v[i] << (i + 1 == v.size() ? "":",");
  out << "], length:" << v.size();
  return out;
}

int main(int argc, char** argv) {
  const int l = 10000;

  std::vector<int> int_ip1;
  for (int i = 0; i < l; i++) {
    int_ip1.push_back(rand() * 1000 + 1);
  }
  int_ip1.push_back(10);
  int_ip1.push_back(1);
  int_ip1.push_back(100);
  int_ip1.push_back(3);
  // prepare expected
  auto int_expected1 = int_ip1;
  std::sort(int_ip1.begin(), int_ip1.end());
  insertion_sort(int_expected1);
  std::cout << (int_ip1  == int_expected1) << std::endl;
  return 0;
}
