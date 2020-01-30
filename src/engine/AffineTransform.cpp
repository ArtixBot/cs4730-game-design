#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "AffineTransform.h"
#include <iostream>

/**
 * Affine Transforms
 * 
 * */	
AffineTransform::AffineTransform(){
	transform = identity();
}

AffineTransform::~AffineTransform(){
	cleanMatrix(transform);
}

void AffineTransform::cleanMatrix(double** m){
	for(int i=0; i<3; i++)
		delete m[i];
	delete m;
}

/* Returns the identity matrix as an array */ 
double** AffineTransform::identity(){
	double** id = new double*[3];
	for(int i=0; i<3; i++){
		id[i] = new double[3];
		for(int j=0; j<3; j++){
			if(i == j) id[i][j] = 1.0;
			else id[i][j] = 0.0;
		}
	}
	return id;
}

/* Takes a point in the local coordinate system and transforms it to global space given this AffineTransform */ 
SDL_Point AffineTransform::transformPoint(int x, int y){	
	SDL_Point global_point;
	int converted_to_global[3] = {0, 0, 1};
	int local_point[3] = {x, y, 1};
	for (int i = 0; i < 3; i++){
		int sum = 0;
		for (int j = 0; j < 3; j++){
			sum += transform[i][j] * local_point[j];
		}
		converted_to_global[i] = sum;
	}
	global_point.x = converted_to_global[0];
	global_point.y = converted_to_global[1];
	return global_point;
}

/* Add another transform to this one, is basically just matrix multiply */
void AffineTransform::concatenate(AffineTransform &at){
	double result[3][3] = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			for (int itr = 0; itr < 3; itr++){
				result[row][col] += transform[row][itr] * at.transform[itr][col];
			}
		}
	}

	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			transform[row][col] = result[row][col];
		}
	}
	return;
}

/* Move points in the x and y direction */
void AffineTransform::translate(int x, int y){
	AffineTransform at;
	at.transform[0][2] = x;
	at.transform[1][2] = y;
	concatenate(at);
}

/* rotate points by r radians */
void AffineTransform::rotate(double r){
	AffineTransform at;
	at.transform[0][0] = cos(r);
	at.transform[0][1] = -sin(r);
	at.transform[1][0] = sin(r);
	at.transform[1][1] = cos(r);
	concatenate(at);
}

/* scale in the x and y direction accordingly */
void AffineTransform::scale(double x, double y){
	AffineTransform at;
	at.transform[0][0] = x;
	at.transform[1][1] = y;
	concatenate(at);
}

double AffineTransform::getScaleX(){
	return transform[0][0];
}

double AffineTransform::getScaleY(){
	return transform[1][1];
}