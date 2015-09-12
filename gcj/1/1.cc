#include <stdio.h>
#include<stdint.h>
#include <inttypes.h>

int main(int argc, char** argv) {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    int s_max;
    int aud_count = 0;
    int level_aud_count = 0;
    scanf("%d", &s_max);
    char level_map[s_max + 10];
    scanf("%s", level_map);
    //printf("ip %s\n", level_map);
    for (int j = 0; j <= s_max; j++) {
      level_aud_count += level_map[j] - '0';
      //printf("lc %d, j %d\n", level_aud_count, j);
      if (level_aud_count < j + 1) {
        aud_count++;
        level_aud_count++;
      }
    }
    //printf("\n");
    printf("Case #%d: %d\n", i,  aud_count);
  }
  return 0;
}
