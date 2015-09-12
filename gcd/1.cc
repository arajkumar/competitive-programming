#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <set>

namespace {
std::set<uint32_t> find_factors(uint64_t num) {
  std::set<uint32_t> factors;
  size_t i = 1;
  bool do_job = true;
  do {
    if (num % i == 0) {
      factors.insert(i);
      factors.insert(num / i);
    }
    // use sqrt ?
    if ((num / i) - i <= 1)
      do_job = false;
    i++;
  } while(do_job);
  // std::cout << "insert point:" << i << " num:" << std::sqrt(num) << "\n";
  // std::sort(factors.begin(), factors.end());
  return factors;
}

// overload << for vector
std::ostream& operator << (std::ostream& out, std::set<uint32_t>& v) {
  out << "std::vector[";
  for(const auto& i : v)
    out << i << ",";
  out << "], length:" << v.size();
  return out;
}
}  // namespace

int main(int argc, char** argv) {
  auto factors = find_factors(1111171);
  std::cout << factors << "\n";
  return 0;
}
