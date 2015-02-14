#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define gc getchar_unlocked
#define pc putchar_unlocked
int scan_d() {int ip=getchar_unlocked(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}
 
void print_d(int n) {if(n<0){n=-n;pc('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc ( output_buffer [ i ] ) ; } while ( ++i< 10 ) ; pc(' ');}

int main(int argc, char**argv) {
  const size_t t = scan_d();
  for(size_t i = 0; i < t; i++) {
    const size_t n = scan_d();
    size_t piles_map[(10 * 10 * 10 * 10 * 10)  + 1] = {0};
    size_t max_count = 0;
    for (size_t j = 0; j < n; j++) {
      size_t pile_count = scan_d();
      piles_map[pile_count]++;
      // printf("pile count %d, map %d\n", pile_count, piles_map[pile_count]);
      max_count = piles_map[pile_count] > max_count ? piles_map[pile_count] : max_count;
    }
    print_d( n - max_count);
  }
  return 0;
}
