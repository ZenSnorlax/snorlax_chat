#include <stdio.h>
#include <time.h>

int main() {
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);

  timeinfo = localtime(&rawtime);

  printf("Current year month day: %d-%d-%d\n", timeinfo->tm_year + 1900,
         timeinfo->tm_mon, timeinfo->tm_mday);

  printf("Current hour mintue second: %d:%d:%d\n", timeinfo->tm_hour,
         timeinfo->tm_min, timeinfo->tm_sec);
  char *wday[] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
  printf("%s\n", wday[timeinfo->tm_wday]);
  return 0;
}
