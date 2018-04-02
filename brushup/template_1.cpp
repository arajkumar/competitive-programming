template<typename T, typename U = int> struct TypeCheck {
  static const bool is_void { false };
  static const bool is_boolean { false };
  static const bool is_int { false };
};

template<> struct TypeCheck<int> {
  static const bool is_void { false };
  static const bool is_boolean { false };
  static const bool is_int { true };
};

template<> struct TypeCheck<bool> {
  static const bool is_void { false };
  static const bool is_boolean { true };
  static const bool is_int { false };
};

template<> struct TypeCheck<void> {
  static const bool is_void { true };
  static const bool is_boolean { false };
  static const bool is_int { false };
};

#include <iostream>
#include <stdio.h>
int main() {
  std::cout << TypeCheck<double>::is_int << "\n";
  return 0;
}
