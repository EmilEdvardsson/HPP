#include <stdio.h>
#include <stdlib.h>
//#include "graphics.h"
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

//const float circleRadius=0.0025, circleColor=0;
//const int windowWidth=800;
const double eps = 0.001;

/* Calculates and updates for new velocity and position of single star */
void update_stars(cbody_t *stars, const double G, const int N, const double dt){
        double *xp = stars->xp;
        double *yp = stars->yp;
        double *mass = stars->mass;
        double *xv = stars->xv;
        double *yv = stars->yv;
        const double Gdt = G*dt;

	/* Initialize loop vars here */
	double ix, iy, axi, ayi, jx, jy, mj, rx, ry, rsqrt, inv_r, inv_r_mj;
	int j, i;
	#pragma omp parallel for private(ix, iy, axi, ayi, j, jx, jy, mj, rx, ry, rsqrt, inv_r, inv_r_mj) schedule(static)
        for (i = 0; i < N; i++) {
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
	/* Wait for threads to finish calculate all forces before updating position */
	#pragma omp barrier
	/* Static scheduling for better data locality */
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < N; i++){
		xp[i] += xv[i]*dt;
		yp[i] += yv[i]*dt;
	}
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

	if (graphics == 1){
		//printf("Graphics on\n");
		/*
		float L=1, W=1;

		InitializeGraphics(argv[0],windowWidth,windowWidth);
		SetCAxes(0,1);

		while(count < nsteps) {
			update_stars(&stars, G, N, dt);
			ClearScreen();
			for (int k = 0; k < N; k++) {
				DrawCircle(stars.xp[k], stars.yp[k], L, W, circleRadius, circleColor);
			}
			Refresh();
			usleep(0);
			count++;
		}
		FlushDisplay();
		CloseDisplay();
		*/
	} else {
		while (count < nsteps){
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

