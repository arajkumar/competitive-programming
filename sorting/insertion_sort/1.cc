#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

namespace {
template <class T>
void insertion_sort(std::vector<T>& input) {
  for(size_t i = 1; i < input.size(); i++) {
    auto key = input[i];
    int p = i - 1;
    while(p >= 0 && key < input[p]) {
      input[p + 1] = input[p];
      p--;
    }
    input[p + 1] = key;
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
}

int main(int argc, char** argv) {
  std::srand(std::time(0));
  const int l = 100000;

  std::vector<int> int_ip1;
  for (int i = 0; i < l; i++) {
    int_ip1.push_back(std::rand() * 1000 + 1);
  }

  // prepare expected
  auto int_expected1 = int_ip1;
  std::sort(int_expected1.begin(), int_expected1.end());
  insertion_sort(int_ip1);
  // std::cout << int_ip1 << "!=" << int_expected1 <<"\n";
  std::cout << (int_ip1  == int_expected1) << std::endl;
  return 0;
}
