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
} cbody_t;

const float circleRadius=0.0025, circleColor=0;
const int windowWidth=800;
const double eps = 0.15;
//int check_counter = 0;

/* Calculates and updates for new velocity and position of single star */
void update_stars(cbody_t *stars, double G, int N, double dt){
	 /* initialize force in x and y direction */
	//double ix, iy, im, jx, jy, jm, rix, riy, risq, f, vj, fx_sum = 0, fy_sum = 0;
	const double Gdt = G*dt;
	//int check_counter = 0;
	cbody_t *star_ptr_i = stars;
	cbody_t *star_ptr_j = stars + 1;
	/*Loop unrolling */
	//cbody_t *star_ptr_i2 = stars + 1;
	//cbody_t *star_ptr_j2 = stars + 2;
	for (int i = 0; i < N; i++) {
		//const double Gdt = G*dt;
		//double ix, iy, im,
		double fx_sum = 0, fy_sum = 0;
		double ix = (star_ptr_i)->xp;
		double iy = (star_ptr_i)->yp;
		double im = (star_ptr_i)->mass;

		/* Add contribution from i to all j as well as all j to i */
		for (int j = i+1;j < N; j++) {
			//double jx, jy, jm, rix, riy, risq, f, vj;
			/*Calculate distance */
			double jx = (star_ptr_j)->xp;
			double jy = (star_ptr_j)->yp;
			double rix = ix - jx;
			double riy = iy - jy;
			double risq = sqrt(rix*rix + riy*riy) + eps;

			/* Calculate force without unit vectors */
			double jm = (star_ptr_j)->mass;
			double f = jm*im/(risq*risq*risq);
			fx_sum += f*rix;
			fy_sum += f*riy;

			/* get acceleration of j as consequence of i */
			double vj = Gdt*f/jm;

			/*add this contribution to j */
			(star_ptr_j)->xv += vj*rix;
			(star_ptr_j)->yv += vj*riy;
			star_ptr_j++;
			//if (vj*rix < 1e-7 && vj*rix > -1e-7){
			//	printf("vj*rix = %lf\n", vj*rix);
			//}
		}
		/* New speed of star i as consequence of all other stars*/
		(star_ptr_i)->xv += -Gdt*fx_sum/im;
		(star_ptr_i)->yv += -Gdt*fy_sum/im;
		(star_ptr_i)->xp += ((star_ptr_i)->xv)*dt;
		(star_ptr_i)->yp += ((star_ptr_i)->yv)*dt;
		star_ptr_i++;
		star_ptr_j = star_ptr_i + 1;
		//fx_sum = 0;
		//fy_sum = 0;
		//printf("Counter: %d\n", check_counter);
		//check_counter = 0;
	}
}

int main(int argc, char const *argv[]) {
	/* Make sure input arguments are correct */
	if (argc != 6) {
		printf("Error: Correct inputs: ./galsim N filename nsteps delta_t graphics, only got %d arguments.\n", argc-1);
        	return 1;
    	}

	/* Save initial arguments and create the stars objects */
	const int N = atoi(argv[1]);
	const char *filename = argv[2];
	const int nsteps = atoi(argv[3]);
	const double dt = atof(argv[4]);
	const int graphics = atoi(argv[5]);
	int count = 0;
	const double G = 100/(double)N;

	//double G = 1.0;
	printf("N = %d, filename = %s, nsteps = %d, delta_t = %lf, graphics = %d\n", N, filename, nsteps, dt, graphics);
	//CBody stars[N];
	cbody_t *stars = (cbody_t *)malloc(N*sizeof(cbody_t));

	/* Read the file */
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error: failed to open the file %s\n", filename);
		return 1;
	}

	/* Input initial conditions into stars */
	/*for (i = 0; i < N; i++) {
		fread(&stars[i], sizeof(CBody), 1, file);
	}*/

	for (int i = 0; i < N; i++) {
		cbody_t *new_star = &stars[i];
		fread(new_star, sizeof(cbody_t), 1, file);
		/*fread(&(stars[i]->xp), sizeof(double),1,file);
		fread(&(stars[i]->yp), sizeof(double),1,file);
		fread(&(stars[i]->mass), sizeof(double),1,file);
		fread(&(stars[i]->xv), sizeof(double),1,file);
		fread(&(stars[i]->yv), sizeof(double),1,file);
		fread(&(stars[i]->brightness), sizeof(double),1,file);*/
	}

	fclose(file); //Don't need file anymore

	/* print values to check its working */
	cbody_t *star_ptr = stars;
	for (int i = 0; i < N; i++) {
		printf("Star #%d\n", i+1);
		printf("xp = %.15lf\n", (star_ptr->xp));
		printf("yp = %.15lf\n", (star_ptr->yp));
		printf("xv = %.15lf\n", (star_ptr->xv));
		printf("yv = %.15lf\n", (star_ptr->yv));
		printf("brightness = %.15lf\n", (star_ptr->brightness));
		printf("mass = %.15lf\n", (star_ptr->mass));
		star_ptr++;
	}

	if (graphics == 1){
		printf("Graphics on\n");
		float L=1, W=1;

		InitializeGraphics(argv[0],windowWidth,windowWidth);
		SetCAxes(0,1);

		printf("Hit q to quit.\n");
		while(count < nsteps) {
			/* Update star position and velocity */
			update_stars(stars, G, N, dt);
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
		/*for (i = 0; i < N; i++) {
			stars[i].xp += delta_t*stars[i].xv;
			stars[i].yp += delta_t*stars[i].yv;
		}*/
		while (count < nsteps) {
			update_stars(stars, G, N, dt);
			count++;
		}/*
		for (i = 0; i < N; i++) {
			stars[i].xp += delta_t*stars[i].xv;
			stars[i].yp += delta_t*stars[i].yv;
		}*/
	}
	//printf("HERE COMES COUNT");
	//printf("Count = %d\n", count);
	/* Write result to new file */
	FILE *new_file = fopen("output.gal", "wb");
	cbody_t *starPointer = stars;
	for (int i = 0; i < N; i++){
		//int arr[] = {1, 2, 3, 4, 5};
		//printf("Writing to file...");
    		//fwrite(&stars[i], sizeof(CBody), 1, new_file);

        	fwrite(&(starPointer->xp),sizeof(double),1,new_file);
        	fwrite(&(starPointer->yp),sizeof(double),1,new_file);
        	fwrite(&(starPointer->mass),sizeof(double),1,new_file);
        	fwrite(&(starPointer->xv),sizeof(double),1,new_file);
        	fwrite(&(starPointer->yv),sizeof(double),1,new_file);
        	fwrite(&(starPointer->brightness),sizeof(double),1,new_file);
        	starPointer++;
	}
    	fclose(new_file);
	free(stars);
    	return 0;
}

