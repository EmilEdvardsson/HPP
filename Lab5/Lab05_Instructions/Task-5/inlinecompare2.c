#include <stdio.h>

int add(int a, int b) {
  return a + b;
}

int main() {
  int x = 10;
  int y = 20;
  int z;
  for (int i = 0; i < 1e8; i++){
  	z = add(x, y);
  }
  printf("%d\n", z);
  return 0;
}
