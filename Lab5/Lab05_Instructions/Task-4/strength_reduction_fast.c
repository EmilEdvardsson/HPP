#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   int i;
   unsigned int a = 1, b = 2, c = 3, d = 1;
   float x = 0.1, y = 0.5, z = 0.33;
   printf("%d %d %d %d, %f %f %f\n", a, b, c, d, x, y, z);

   float fraction = 1/1.33;

   for (i=0; i<50000000; i++)
   {
      c = d << 1;
      b = c*15;
      a = b >> 4;
      d = b/a;

      z = 0.33;
      y = 2*z;
      x = y * fraction;
      z = x * fraction;
   }
   printf("%d %d %d %d, %f %f %f\n", a, b, c, d, x, y, z);
   return 0;
}
