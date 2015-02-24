#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <algorithm>
#include <cmath>
#define gc getchar_unlocked
#define pc putchar_unlocked
/*int scan_d() {int ip=getchar_unlocked(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}
 
void print_d(int n) {if(n<0){n=-n;pc('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc ( output_buffer [ i ] ) ; } while ( ++i< 10 ) ; pc(' ');}
*/

int main(int argc, char**argv) {
  long long t;
  scanf("%llu",&t);
  const long long max = (4*10*10*10*10*10) + 1;
  for (long long i = 0; i < t; i++) {
    long long n;
    scanf("%llu",&n);
    long long A[max], B[max];
    for(long long j = 0; j < n; j++)
      scanf("%llu", &A[j]);
    for(long long j = 0; j < n; j++) 
      scanf("%llu",&B[j]);
    long long d;
    scanf("%llu",&d);
    long long min_steps =  std::numeric_limits<long long>::max(), number = 0;
    for(long long j = 0; j < n; j++) {
      const long long net_steps = A[j] - B[j];
      const long long first_try = d - A[j];
      if (first_try <= 0) {
        number = j +1;
        break;
      }
      long long iterations = std::ceil((d  - A[j])/ (1.0 * net_steps));
      long long still_needed = d - (iterations * net_steps);
      long long steps_i = iterations * (A[j] + B[j]) + still_needed; 
      // printf("A=%lld b=%lld steps_i=%lld, j=%lld\n",A[j], B[j], steps_i, j+1);
      if (steps_i < min_steps) {
        number = j + 1; min_steps = steps_i;
      }
    }
    printf("%llu\n",number);
  }
  return 0;
}
