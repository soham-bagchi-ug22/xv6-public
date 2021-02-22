
#include "types.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[])
{
  struct rtcdate r;

  if (date(&r)) {
    printf(2, "date failed\n");
    exit();
  }

  // your code to print the time in any format you like...

  printf(1, "%d:", r.hour);
  printf(1, "%d:", r.minute);
  printf(1, "%d; ", r.second);
  printf(1, "%d/", r.day);
  printf(1, "%d/", r.month);
  printf(1, "%d\n", r.year);
  exit(); 
}
