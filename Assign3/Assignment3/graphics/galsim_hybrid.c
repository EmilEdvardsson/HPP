#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include <math.h>

/* Define struct for a celestial body */
typedef struct {
	double posX; //X Position
	double posY; //Y Position
	double mass;
	double velX; //X Velocity
	double velY; //Y Velocity
	double brightness; //Keep, but not used in this simulation
} CBody;

const float circleRadius=0.0025, circleColor=0;
const int windowWidth=800;
const double epsilon = 0.001;

/* Calculates and updates for new velocity and position of single star */

void move(CBody *stars, int N, double deltaT, double gravConst)
{
    double massesDivRCU, posXi, posXj, posYi, posYj, massi, massj, distX, distY, rEpsilon;
    double massesDivRCUSumX = 0, massesDivRCUSumY = 0;
    CBody *starPoint1 = stars;
    CBody *starPoint2 = stars;
    starPoint2++;    
    const double dTG = deltaT * gravConst;

    for (int i = 0; i < N; i++)
    {
        posXi = (starPoint1)->posX;
        posYi = (starPoint1)->posY;
        massi = (starPoint1)->mass;
        
        for (int j = i + 1; j < N; j++)
        {
            posXj = (starPoint2)->posX;
            posYj = (starPoint2)->posY;
            massj = (starPoint2)->mass;
            distX = posXi-posXj;
            distY = posYi-posYj;
            rEpsilon = sqrt(distX*distX + distY*distY) + epsilon;
            massesDivRCU = massj * massi / (rEpsilon*rEpsilon*rEpsilon);
            massesDivRCUSumX += massesDivRCU * distX;
            massesDivRCUSumY += massesDivRCU * distY;
            massesDivRCU = massesDivRCU * dTG / massj;
            (starPoint2)->velX += distX * massesDivRCU;
            (starPoint2)->velY += distY * massesDivRCU;  
            starPoint2++;  
        }
        (starPoint1)->velX += -(dTG * massesDivRCUSumX) / massi;
        (starPoint1)->velY += -(dTG * massesDivRCUSumY) / massi;
        (starPoint1)->posX += ((starPoint1)->velX) * deltaT;
        (starPoint1)->posY += ((starPoint1)->velY) * deltaT;
        
        massesDivRCUSumX = 0;
        massesDivRCUSumY = 0;

        starPoint1++;
        starPoint2 = starPoint1;
        starPoint2++;  
    }
}
int main(int argc, char const *argv[]) {
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
	int count = 0;
	double G = 100/(double)N;

	//double G = 1.0;
	printf("N = %d, filename = %s, nsteps = %d, delta_t = %lf, graphics = %d\n", N, filename, nsteps, delta_t, graphics);
	//CBody stars[N];
	CBody *stars = (CBody *)malloc(N*sizeof(CBody));

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
		CBody *new_star = &stars[i];
		fread(new_star, sizeof(CBody), 1, file);
		/*fread(&(stars[i]->xp), sizeof(double),1,file);
		fread(&(stars[i]->yp), sizeof(double),1,file);
		fread(&(stars[i]->mass), sizeof(double),1,file);
		fread(&(stars[i]->xv), sizeof(double),1,file);
		fread(&(stars[i]->yv), sizeof(double),1,file);
		fread(&(stars[i]->brightness), sizeof(double),1,file);*/
	}

	fclose(file); //Don't need file anymore

	/* print values to check its working */
	CBody *star_ptr = stars;
	for (int i = 0; i < N; i++) {
		printf("Star #%d\n", i+1);
		printf("xp = %.15lf\n", (star_ptr->posX));
		printf("yp = %.15lf\n", (star_ptr->posY));
		printf("xv = %.15lf\n", (star_ptr->velX));
		printf("yv = %.15lf\n", (star_ptr->velY));
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
			//update_stars(stars, G, N, delta_t);
			move(stars, N, delta_t, G);
			/* Call graphics routines. */
			ClearScreen();
			for (int k = 0; k < N; k++) {
				DrawCircle(stars[k].posX, stars[k].posY, L, W, circleRadius, circleColor);
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
			//update_stars(stars, G, N, delta_t);
			count++;
			move(stars, N, delta_t, G);
		}/*
		for (i = 0; i < N; i++) {
			stars[i].xp += delta_t*stars[i].xv;
			stars[i].yp += delta_t*stars[i].yv;
		}*/
	}
	printf("HERE COMES COUNT");
	printf("Count = %d\n", count);
	/* Write result to new file */
	FILE *new_file = fopen("output.gal", "wb");
	CBody *starPointer = stars;
	for (int i = 0; i < N; i++){
		//int arr[] = {1, 2, 3, 4, 5};
		printf("Writing to file...");
    		//fwrite(&stars[i], sizeof(CBody), 1, new_file);

        	fwrite(&(starPointer->posX),sizeof(double),1,new_file);
        	fwrite(&(starPointer->posY),sizeof(double),1,new_file);
        	fwrite(&(starPointer->mass),sizeof(double),1,new_file);
        	fwrite(&(starPointer->velX),sizeof(double),1,new_file);
        	fwrite(&(starPointer->velY),sizeof(double),1,new_file);
        	fwrite(&(starPointer->brightness),sizeof(double),1,new_file);
        	starPointer++;
	}
    	fclose(new_file);
	free(stars);
    	return 0;
}

