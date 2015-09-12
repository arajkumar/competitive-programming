#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <map>

int main(int argc, char **argv) {
  size_t t;
  scanf("%lu", &t);
  std::map<std::string, size_t> map;
  for (size_t i = 0; i < t; i++) {
    std::string name;
    std::cin >> name;
    map[name] ++;
  }
  for (const auto& name : map) {
    std::cout << name.first << " " << name.second << "\n";
  }
  return 0;
}
