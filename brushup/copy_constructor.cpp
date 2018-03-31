#include <iostream>
#include <string.h>
#include <stdlib.h>

class Foo
{
  private:
    char* str {};
    const char* t { "default constructor" };
  public:
  Foo(const char* str)
    : str(strdup(str)) {
    std::cout << "normal:" << __func__ << "\n";
    t = "normal";
  }

  Foo& operator = (const Foo& o) {
    auto pt = t;
    t = "operator =";
    std::cout << pt << "->" << t << ":" << __func__ << "\n";
    if (this->str)
        free(this->str);
    this->str = strdup(o.str);
    return *this;
  }

  Foo(const Foo& o) {
    std::cout << "copy:" << __func__ << "\n";
    this->str = strdup(o.str);
    t = "copy";
  }

#if 0
  Foo(Foo& o) {
    std::cout << "copy:" << __func__ << "\n";
    this->str = strdup(o.str);
    t = "copy";
  }
#endif

  ~Foo() {
    std::cout << t << ":" << __func__ << "\n";
    free(str);
  }

  Foo() = default;
};

int main() {
  const Foo a("hello");
  std::cout << "---before copy---\n";
  Foo b;
  std::cout << "---after copy---\n";
  std::cout << "---before assignment---\n";
  b = a;
  std::cout << "---after assignment---\n";
  return 0;
}
