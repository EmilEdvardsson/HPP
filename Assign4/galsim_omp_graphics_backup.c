#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <math.h>
#include <omp.h>

/* Define struct for a celestial body */
typedef struct {
	double* xp; //X Position
	double* yp; //Y Position
	double* mass;
	double* xv; //X Velocity
	double* yv; //Y Velocity
	double* brightness; //Keep, but not used in this simulation
} cbody_t;

const float circleRadius=0.0025, circleColor=0;
const int windowWidth=800;
const double eps = 0.001;

/* Calculates and updates for new velocity and position of single star */
void update_stars(cbody_t *stars, const double G, const int N, const double dt){
        double *xp = stars->xp;
        double *yp = stars->yp;
        double *mass = stars->mass;
        double *xv = stars->xv;
        double *yv = stars->yv;
        const double Gdt = G*dt;

	/* Try initialize loop vars here */
	double im, ix, iy, axi, ayi, jx, jy, mj, rx, ry, rsqrt, inv_r, inv_r_mj;
	int j, i;
	for (int b = 0; b < 1; b++)
	//#pragma omp parallel num_threads(n_threads)
	//#pragma omp single
	{
		//int tid = omp_get_thread_num();
		//int i_start = tid * chunk_size;
		//int i_end = (tid == n_threads - 1) ? N : (tid + 1) * chunk_size;
		//#pragma omp parallel for default(none) shared(N, mass, xp, yp, xv, yv, Gdt, eps, dt) private(i,j,im,ix,iy,axi,ayi,mj,rx,ry,rsqrt,inv_r,inv_r_mj) reduction(+:xv*, yv*, xp*, yp*)
		//#pragma omp parallel for default(none) shared(im, ix, iy, N, mj, rx, ry, rsqrt, inv_r, inv_r_mj, xp, yp, xv, yv, mass, eps, Gdt, dt) private(j, axi, ayi) schedule(dynamic)
		//omp_set_num_threads(n_threads);
		#pragma omp parallel for private(im, ix, iy, axi, ayi, j, jx, jy, mj, rx, ry, rsqrt, inv_r, inv_r_mj) schedule(dynamic)
        	for (i = 0; i < N; i++) {
                	im = mass[i];
                	ix = xp[i];
                	iy = yp[i];
                	axi = 0;
                	ayi = 0;
			//printf("i = %d", i);
			//printf("Starting thread\n");
			//#pragma omp parallel for firstprivate(im, ix, iy) reduction(+:axi) reduction(+:ayi) reduction(+:xv[j]) reduction(+:yv[j])
			//#pragma omp parallel for reduction(+:axi) reduction(+:ayi)
			//#pragma omp parallel for shared(i, xp, yp, mass, xv, yv, Gdt, N) reduction(+:axi) reduction(+:ayi)
			//printf("Starting parallel region\n");
			//#pragma omp parallel for default(none) shared(N, xp, yp, mass, xv, yv, Gdt, eps, i, ix, iy, im) reduction(+:axi) reduction(+:ayi)
			//#pragma omp parallel for private(j, mj, rx, ry, rsqrt, inv_r, inv_r_mj, axi, ayi) reduction(+:xv[:N]) reduction(+:yv[:N])
			//#pragma omp parallel for reduction(+:axi, ayi) schedule(static)
			//#pragma omp parallel for schedule(static)
                	for (j = 0;j < N; j++) {
				//printf("j = %d\n", j);
				//printf("%d\n", j);
				jx = xp[j];
				jy = yp[j];
                        	mj = mass[j];
                        	rx = ix - jx;
				//rx = xp[i] - xp[j];
                        	ry = iy - jy;
				//ry = yp[i] - yp[j];
                        	rsqrt = sqrt(rx*rx + ry*ry) + eps;
                        	inv_r = 1.0/(rsqrt*rsqrt*rsqrt);
                        	inv_r_mj = inv_r*mj;
                        	axi += rx*inv_r_mj;
                        	ayi += ry*inv_r_mj;
				//#pragma omp critical
                        	//xv[j] += Gdt*im*inv_r*rx;
				//xv[j] += Gdt*mass[i]*inv_r*rx;
				//#pragma omp critical
                        	//yv[j] += Gdt*mj*inv_r*ry;
				//yv[j] += Gdt*mass[j]*inv_r*ry;
                	}
			//#pragma omp barrier
			//#pragma omp barrier
			//printf("Ending parallel region\n");
			//printf("Ending thread\n");
			//#pragma omp critical
                	xv[i] += -Gdt*axi;
			//#pragma omp critical
                	yv[i] += -Gdt*ayi;
			//#pragma omp critical
                	//xp[i] += xv[i]*dt;
			//#pragma omp critical
                	//yp[i] += yv[i]*dt;
        	}

		#pragma omp barrier
		#pragma omp parallel for schedule(static)
		for (int i = 0; i < N; i++){
			xp[i] += xv[i]*dt;
			yp[i] += yv[i]*dt;
		}

	}
	//#pragma omp taskwait
}

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
	const int n_threads = atoi(argv[6]);
	int count = 0;
	const double G = 100/(double)N;

	omp_set_num_threads(n_threads);

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

	/* print values to check its working */
	/* for (int i = 0; i < N; i++) {
		printf("Star #%d\n", i+1);
		printf("xp = %.15lf\n", stars.xp[i]);
		printf("yp = %.15lf\n", stars.yp[i]);
		printf("xv = %.15lf\n", stars.xv[i]);
		printf("yv = %.15lf\n", stars.yv[i]);
		printf("brightness = %.15lf\n", stars.brightness[i]);
		printf("mass = %.15lf\n", stars.mass[i]);
	}*/

	if (graphics == 1){
		//printf("Graphics on\n");
		float L=1, W=1;

		InitializeGraphics(argv[0],windowWidth,windowWidth);
		SetCAxes(0,1);

		while(count < nsteps) {
			/* Update star position and velocity */
			update_stars(&stars, G, N, dt);
			/* Call graphics routines. */
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
		//printf("Graphics turned off\n");
		while (count < nsteps){
			//printf("Count: %d\n",count);
			update_stars(&stars, G, N, dt);
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

