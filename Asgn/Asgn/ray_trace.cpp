//---------------------------------------
// Program: ray_trace.cpp
// Purpose: Demonstrate ray tracing.
// Author:  John Gauch
// Date:    Spring 2018
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Include ray tracing and phong shading code
#include "phong2.h"

// Global variables
#define XDIM 800
#define YDIM 800
const int DISTANCE = 300;
unsigned char image[YDIM][XDIM][3];

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
	// Initialize OpenGL
	glClearColor(0.0, 0.0, 0.0, 1.0);


	// Print command menu
	cout << "Program commands:\n"
		<< "   'q' - quit program\n";

}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
	// TO BE ADDED
	// initialize Phong scene from input file
	CONST int NUMSPHERES = 1;
	Sphere3D* spheres = new Sphere3D[NUMSPHERES];
	Point3D sphereOrigin;
	sphereOrigin.set(0, 0, 0);
	float sphereRadius = 100;
	spheres[0].set(sphereOrigin, sphereRadius);
	ColorRGB sphereColor;
	sphereColor.set(255, 0, 0);

	spheres[0].properties.set(sphereColor, .25, .707, .25, 5);

	// Phong scene;
	Point3D cameraPosition;
	Vector3D lightDirection;
	ColorRGB lightColor;
	cameraPosition.set(0, 0, -DISTANCE);
	// scene.SetCamera(cameraPosition);
	lightDirection.set(1, -1, 0);
	lightColor.set(255, 255, 255);
	// scene.SetLight(lightColor, lightDirection);

	float xOffset = XDIM / 2;
	float yOffset = YDIM / 2;

	for (int i = 0; i < YDIM; i++) {
		for (int j = 0; j < XDIM; j++) {
			// Calculate pixel location in world and image coords
			// World top left: -XDIM/2, -YDIM/2
			// Image top left: 0,0,0
			image[i][j][0] = image[i][j][1] = image[i][j][2] = 0;
			Point3D imagePixel;
			imagePixel.set(i, j, 0);
			Point3D worldPixel;
			worldPixel.set(i - xOffset, j - yOffset, 0);

			// Make ray from camera to image pixel
			Point3D rayOrigin;
			Vector3D rayDirection;
			rayOrigin = cameraPosition;
			rayDirection.vx = worldPixel.px - rayOrigin.px;
			rayDirection.vy = worldPixel.py - rayOrigin.py;
			rayDirection.vz = worldPixel.pz - rayOrigin.pz;
			rayDirection.normalize();
			Ray3D ray;
			ray.set(rayOrigin, rayDirection);

			// Intersect ray with objects in the world
			Point3D hitPoint;
			Vector3D hitNormal;
			for (int k = 0; k < NUMSPHERES; k++) {
				if (spheres[k].get_intersection(ray, hitPoint, hitNormal)) {
					// cout << "[HIT]\t\t" << hitPoint.px << "\t\t" << hitPoint.py << "\t\t" << hitPoint.pz << endl;
					// Intial pixel colors for the object used in Phong shading
					Phong pixel;
					pixel.SetCamera(cameraPosition);
					pixel.SetLight(lightColor, lightDirection);
					ColorRGB sphereColor = spheres[k].properties.color;
					float sphereKa = spheres[k].properties.Ka;
					float sphereKd = spheres[k].properties.Kd;
					float sphereKs = spheres[k].properties.Ks;
					float sphereKp = spheres[k].properties.Kp;
					pixel.SetObject(sphereColor, sphereKa, sphereKd, sphereKs, sphereKp);
					// Perform phong shading for the pixel
					ColorRGB pixelShade;
					pixel.GetShade(hitPoint, hitNormal, pixelShade);
					// save the pixel color to the image
					pixelShade.clamp();
					image[i][j][0] = pixelShade.R;
					image[i][j][1] = pixelShade.G;
					image[i][j][2] = pixelShade.B;

				}
			}
		}
	}



	// Display colorful square
	for (int y = 100; y<700; y++)
		for (int x = 100; x<700; x++)
		{
			image[y][x][0] = x * 255 / XDIM;
			image[y][x][1] = y * 255 / YDIM;
			image[y][x][2] = 0;
		}

	// Display image
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(XDIM, YDIM, GL_RGB, GL_UNSIGNED_BYTE, image);
	glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
	// End program
	if (key == 'q')
		exit(0);

	// TO BE ADDED

	// Display image
	glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
	// Create OpenGL window
	glutInit(&argc, argv);
	glutInitWindowSize(XDIM, YDIM);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Ray Trace");
	init();

	// Specify callback function
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}