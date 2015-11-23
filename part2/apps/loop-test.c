/*
 * loop-test.c
 *
 *  Created on: Oct 31, 2015
 *      Author: jbb
 */

#include "mipslib.h"
int A[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

int main()
{
  int i;
  int sum = 0;
  for (i = 0;  i < 8;  i++) {
    sum = sum + A[i];
  }
  printf("sum = %d\n", sum);
}


