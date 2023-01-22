/*squares.c
table over squares of numbers.
*/

#include <stdio.h>

int main() {
	int i = 1;
	while (i <= 10) {
		printf("%d \t %d \t %d \n", i, i*i, 2*i);
		i++;
	}
	return 0;
}
