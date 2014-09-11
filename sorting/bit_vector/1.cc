#include <iostream>
#include <string.h>
#include <assert.h>

namespace {
template<typename T, size_t size>
class BitVector {
 private:
  const static size_t bit_width = sizeof(T);
  T array_[size / bit_width + 1];

 public:
  BitVector() {
    memset(array_, sizeof(array_), 0x00);
  }

  bool operator[](size_t pos) const {
    return get_bit(pos);
  }

  bool get_bit(size_t pos) const {
    assert(pos < size);
    return array_[pos / bit_width] & (1 << (pos % bit_width));
  }

  void set_bit(size_t pos) {
    assert(pos < size);
    T& val = array_[pos / bit_width];
    val = val | (1 << (pos % bit_width));
  }
};
}

int main(int argc, char** argv) {
  BitVector<size_t, 100> b;
  assert(!b[0]);
  b.set_bit(10);
  assert(b[10]);
  return 0;
}
