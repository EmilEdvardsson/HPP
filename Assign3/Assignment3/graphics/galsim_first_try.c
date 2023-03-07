#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <math.h>

/* Define struct for a celestial body */
typedef struct {
	double xp; //X Position
	double yp; //Y Position
	double mass;
	double xv; //X Velocity
	double yv; //Y Velocity
	double brightness; //Keep, but not used in this simulation
} CBody;

const float circleRadius=0.0025, circleColor=0;
const int windowWidth=800;
const double eps = 1e-3;

void keep_within_box(double* x, double* y){
	printf("x = %lf, y = %lf\n", *x, *y);

	if(*x > 1 || *x < 0)
		*x = 0.5;
	if(*y > 1 || *y < 0)
		*y = 0.5;
}

/* Calculates and updates for new velocity and position of single star */
void update_stars(CBody stars[], double G, int N, double delta_t){
	/* initialize force in x and y direction */
	for (int i = 0; i < N; i++) {
		double ix = stars[i].xp;
		double iy = stars[i].yp;
		double sum_xv = 0;
		double sum_yv = 0;
		double gm = -G*stars[i].mass;

		for (int j = 0;j < N; j++) {
			if (j == i){
				 continue;
			}
			double f = 0;
			double rix = ix - stars[j].xp;
			double riy = iy - stars[j].yp;
			double risq = sqrt(rix*rix + riy*riy);
			/* Calculate f without unit vectors */
			f += gm*stars[j].mass/((risq + eps)*(risq + eps)*(risq + eps));

			/* Multiply with respective unit vector to get force in x and y direction */
			double fx = f*rix;
			double fy = f*riy;

			/* Acceleration contribution to star i from star j */
			double ax = fx/stars[i].mass;
			double ay = fy/stars[i].mass;

			/* Speed contribution to star i from star j*/
			sum_xv += delta_t*ax;
			sum_yv += delta_t*ay;
		}
		/* New speed of star i*/
		stars[i].xv += sum_xv;
		stars[i].yv += sum_yv;

		/* New position of star i */
		stars[i].xp += delta_t*stars[i].xv;
		stars[i].yp += delta_t*stars[i].yv;
	}
}

int main(int argc, char *argv[]) {
	/* Make sure input arguments are correct */
	if (argc != 6) {
		printf("Error: Correct inputs: ./galsim N filename nsteps delta_t graphics, only got %d arguments.\n", argc-1);
        	return 1;
    	}

	/* Save initial arguments and create the stars objects */
	int N = atoi(argv[1]);
	char *filename = argv[2];
	int nsteps = atoi(argv[3]);
	double delta_t = atof(argv[4]);
	int graphics = atoi(argv[5]);
	int i;
	int count = 0;
	double G = (double)100/N;
	printf("N = %d, filename = %s, nsteps = %d, delta_t = %lf, graphics = %d\n", N, filename, nsteps, delta_t, graphics);
	CBody stars[N];

	/* Read the file */
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Error: failed to open the file %s\n", filename);
		return 1;
	}

	/* Input initial conditions into stars */
	for (i = 0; i < N; i++) {
		fread(&stars[i].xp, sizeof(CBody), 1, file);
	}

	fclose(file); //Don't need file anymore

	/* print values to check its working */
	for (i = 0; i < N; i++) {
		printf("Star #%d\n", i+1);
		printf("xp = %.15lf\n", stars[i].xp);
		printf("yp = %.15lf\n", stars[i].yp);
		printf("xv = %.15lf\n", stars[i].xv);
		printf("yv = %.15lf\n", stars[i].yv);
		printf("brightness = %.15lf\n", stars[i].brightness);
		printf("mass = %.15lf\n", stars[i].mass);
		printf("G = %.15fl\n", G);
	}

	if (graphics == 1){
		printf("Graphics on\n");
		float L=1, W=1;

		InitializeGraphics(argv[0],windowWidth,windowWidth);
		SetCAxes(0,1);

		printf("Hit q to quit.\n");
		while(count < nsteps) {
			/* Update star position and velocity */
			update_stars(stars, G, N, delta_t);
			/* Call graphics routines. */
			ClearScreen();
			for (int k = 0; k < N; k++) {
				DrawCircle(stars[k].xp, stars[k].yp, L, W, circleRadius, circleColor);
			}
			Refresh();
			/* Sleep a short while to avoid screen flickering. */
			usleep(3000);
			count++;
		}
		FlushDisplay();
		CloseDisplay();
	} else {
		printf("Graphics turned off\n");
		while (count < nsteps-1) {
			update_stars(stars, G, N, delta_t);
			count++;
		}
	}

	/* Write result to new file */
	FILE *new_file = fopen("output.gal", "wb");
	for (i = 0; i < N; i++){
		//int arr[] = {1, 2, 3, 4, 5};
		//printf("Writing to file...");
    		fwrite(&stars[i], sizeof(CBody), 1, new_file);
	}
    	fclose(new_file);
    	return 0;
}

