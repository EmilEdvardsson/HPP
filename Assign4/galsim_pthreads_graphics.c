#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <math.h>
#include <pthread.h>

/* Define struct for a celestial body */
typedef struct {
	double* xp; //X Position
	double* yp; //Y Position
	double* mass;
	double* xv; //X Velocity
	double* yv; //Y Velocity
	double* brightness; //Keep, but not used in this simulation
} cbody_t;

typedef struct {
	cbody_t *stars; // Pointer to celestial body
	int start; // Index where thread starts
	int end; // Index where thread ends
	double t_G; // Graviational constant
	double t_dt; //Time step
	int t_N; //N stars
} thread_info_t;

const float circleRadius=0.0025, circleColor=0;
const int windowWidth=800;
const double eps = 0.001;
pthread_barrier_t barrier;

/* Calculates and updates for new velocity and position of single star */
void* update_stars(void *arg){
	thread_info_t *tinfo = (thread_info_t *)arg;
	cbody_t *stars = tinfo->stars;
	const int start = tinfo->start;
	const int end = tinfo->end;
	const double t_G = tinfo->t_G;
	const double t_dt = tinfo->t_dt;
        const double Gdt = t_G*t_dt;
	const int N = tinfo->t_N;

        double *xp = stars->xp;
        double *yp = stars->yp;
        double *mass = stars->mass;
        double *xv = stars->xv;
        double *yv = stars->yv;


	/* Initialize loop vars here */
	double ix, iy, axi, ayi, jx, jy, mj, rx, ry, rsqrt, inv_r, inv_r_mj;
	int j, i;
        for (i = start; i < end; i++) {
               	ix = xp[i];
               	iy = yp[i];
               	axi = 0;
               	ayi = 0;
               	for (j = 0;j < N; j++) {
			jx = xp[j];
			jy = yp[j];
                       	mj = mass[j];
                       	rx = ix - jx;
                       	ry = iy - jy;
                       	rsqrt = sqrt(rx*rx + ry*ry) + eps;
                       	inv_r = 1.0/(rsqrt*rsqrt*rsqrt);
                       	inv_r_mj = inv_r*mj;
                       	axi += rx*inv_r_mj;
                       	ayi += ry*inv_r_mj;
               	}
               	xv[i] += -Gdt*axi;
               	yv[i] += -Gdt*ayi;
       	}
	pthread_barrier_wait(&barrier);
	for (int i = start; i < end; i++){
		xp[i] += xv[i]*t_dt;
		yp[i] += yv[i]*t_dt;
	}
	return NULL;
}

//#define NUM_THREADS 6

int main(int argc, char const *argv[]) {
	/* Make sure input arguments are correct */
	if (argc != 7) {
		printf("Error: Correct inputs: ./galsim N filename nsteps delta_t graphics n_threads, only got %d arguments.\n", argc-1);
        	return 1;
    	}

	/* Save initial arguments and create the stars objects */
	const int N = atoi(argv[1]);
	const char *filename = argv[2];
	const int nsteps = atoi(argv[3]);
	const double dt = atof(argv[4]);
	const int graphics = atoi(argv[5]);
	const int NUM_THREADS = atoi(argv[6]);
	int count = 0;
	const double G = 100/(double)N;

	//omp_set_num_threads(n_threads);

	pthread_t threads[NUM_THREADS];
	thread_info_t thread_info[NUM_THREADS];
	pthread_barrier_init(&barrier, NULL, NUM_THREADS);

	cbody_t stars;
	stars.xp = malloc(N * sizeof(double));
	stars.yp = malloc(N * sizeof(double));
	stars.mass = malloc(N * sizeof(double));
	stars.xv = malloc(N * sizeof(double));
	stars.yv = malloc(N * sizeof(double));
	stars.brightness = malloc(N * sizeof(double));

	/* Read the file */
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error: failed to open the file %s\n", filename);
		return 1;
	}

	for (int i = 0; i < N; i++) {
		fread(&stars.xp[i], sizeof(double),1,file);
		fread(&stars.yp[i], sizeof(double),1,file);
		fread(&stars.mass[i], sizeof(double),1,file);
		fread(&stars.xv[i], sizeof(double),1,file);
		fread(&stars.yv[i], sizeof(double),1,file);
		fread(&stars.brightness[i], sizeof(double),1,file);
	}

	fclose(file); //Don't need file anymore


	if (graphics == 1){
		//printf("Graphics on\n");
		float L=1, W=1;

		InitializeGraphics(argv[0],windowWidth,windowWidth);
		SetCAxes(0,1);

		while(count < nsteps) {
			/* Update star position and velocity */
			//update_stars(&stars, G, N, dt);
			/* Call graphics routines. */
			//update_stars(&stars, G, N, dt);
			for (int i = 0; i < NUM_THREADS; i++){
				thread_info[i].stars = &stars;
				thread_info[i].start = i*N/NUM_THREADS;
				thread_info[i].end = (i == NUM_THREADS-1) ? N : (i+1)*N/NUM_THREADS;
				//thread_info[i].G = G;
				//thread_info[i].dt = dt;

				pthread_create(&threads[i], NULL, update_stars, &thread_info[i]);
			}
			for (int i = 0; i < NUM_THREADS; i++){
				pthread_join(threads[i], NULL);
			}
			ClearScreen();
			for (int k = 0; k < N; k++) {
				DrawCircle(stars.xp[k], stars.yp[k], L, W, circleRadius, circleColor);
			}
			Refresh();
			/* Sleep a short while to avoid screen flickering. */
			usleep(0);
			count++;
		}
		FlushDisplay();
		CloseDisplay();
	} else {
		while (count < nsteps){
			//update_stars(&stars, G, N, dt);
			for (int i = 0; i < NUM_THREADS; i++){
				thread_info[i].stars = &stars;
				thread_info[i].start = i*N/NUM_THREADS;
				thread_info[i].end = (i == NUM_THREADS-1) ? N : (i+1)*N/NUM_THREADS;
				thread_info[i].t_G = G;
				thread_info[i].t_dt = dt;
				thread_info[i].t_N = N;

				pthread_create(&threads[i], NULL, update_stars, &thread_info[i]);
			}
			for (int i = 0; i < NUM_THREADS; i++){
				pthread_join(threads[i], NULL);
			}
			count++;
		}
	}
	/* Write result to new file */
	FILE *new_file = fopen("result.gal", "wb");
	for (int i = 0; i < N; i++){
        	fwrite(&stars.xp[i],sizeof(double),1,new_file);
        	fwrite(&stars.yp[i],sizeof(double),1,new_file);
        	fwrite(&stars.mass[i],sizeof(double),1,new_file);
        	fwrite(&stars.xv[i],sizeof(double),1,new_file);
        	fwrite(&stars.yv[i],sizeof(double),1,new_file);
        	fwrite(&stars.brightness[i],sizeof(double),1,new_file);
	}
    	fclose(new_file);
	free(stars.xp);
	free(stars.yp);
	free(stars.mass);
	free(stars.xv);
	free(stars.yv);
	free(stars.brightness);
    	return 0;
}

