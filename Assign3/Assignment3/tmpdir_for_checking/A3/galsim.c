#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
//int check_counter = 0;

/* Calculates and updates for new velocity and position of single star */
void update_stars(cbody_t *stars, const double G, const int N, const double dt){
	double *xp = stars->xp;
	double *yp = stars->yp;
	double *mass = stars->mass;
	double *xv = stars->xv;
	double *yv = stars->yv;
	const double Gdt = G*dt;
	for (int i = 0; i < N; i++) {
		double im = mass[i];
		double ix = xp[i];
		double iy = yp[i];
		double axi = 0;
		double ayi = 0;
		for (int j = i+1;j < N; j++) {
			double mj = mass[j];
			double rx = ix - xp[j];
			double ry = iy - yp[j];
			double rsqrt = sqrt(rx*rx + ry*ry) + eps;
			double inv_r = 1.0/(rsqrt*rsqrt*rsqrt);
			double inv_r_mj = inv_r*mj;
			axi += rx*inv_r_mj;
			ayi += ry*inv_r_mj;
			xv[j] += Gdt*im*inv_r*rx;
			yv[j] += Gdt*im*inv_r*ry;
		}
		xv[i] += -Gdt*axi;
		yv[i] += -Gdt*ayi;
		xp[i] += xv[i]*dt;
		yp[i] += yv[i]*dt;
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

	while (count < nsteps) {
		update_stars(&stars, G, N, dt);
		count++;
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

