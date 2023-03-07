#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	omp_set_nested(1);
	if (omp_get_nested()){
		printf("Nested turned ON\n");
	} else {
		printf("Nested turned OFF\n");
	}
#pragma omp parallel num_threads(2)
	{
		printf("Thread %d creating new thread\n", omp_get_thread_num());
		#pragma omp parallel num_threads(2)
		{
			printf("This is the created thread with id %d\n", omp_get_thread_num());
		}
	}
	return 0;
}
