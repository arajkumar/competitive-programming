#include <stdio.h>

#define gc getchar_unlocked
#define pc putchar_unlocked
int scan_d() {int ip=getchar_unlocked(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}
 
void print_d(int n) {if(n<0){n=-n;pc('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc ( output_buffer [ i ] ) ; } while ( ++i< 10 ) ; pc(' ');}

int main(int argc, char**argv) {
  size_t t, i;
  t = scan_d();
  for (i = 0; i < t; i++) {
    char a = '+', b = '-';
    size_t plus_count = 0, minus_count = 0;
#if 0
    char str[10 * 10 * 10 * 10 * 10];
    char* strp = str;
    scanf("%s",strp);
#endif
    while(1) {
#if 0
      char ch = *strp;
      strp++;
#else
      char ch = gc();
#endif
      if (ch != '+' && ch != '-')
        break;
      if (a != ch)
        plus_count++;
      if (b != ch)
        minus_count++;
      // swap
      char t = a; a = b; b = t;
    }
    print_d(plus_count < minus_count?plus_count:minus_count);
  }
  return 0;
}
