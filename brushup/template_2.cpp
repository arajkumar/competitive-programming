// factorial

template<int n> struct factorial;

template<> struct factorial<0> { static const auto value = 1; };
template<int n> struct factorial { static const auto value = n * factorial<n-1>::value; };

static_assert(factorial<0>::value == 1, " 0! == 1");
static_assert(factorial<1000000000>::value == 1, " 0! == 1");
