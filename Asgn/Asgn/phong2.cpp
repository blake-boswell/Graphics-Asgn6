//----------------------------------------------
// Purpose: Phong class implementation
// Author:  John Gauch
//----------------------------------------------
#include "phong2.h"


const bool DEBUG = false;

//----------------------------------------------
Phong::Phong()
{
	CameraPos.set(0, 0, 0);
	LightColor.set(0, 0, 0);
	LightDir.set(0, 0, 0);
	ObjectColor.set(0, 0, 0);
	Ka = 0; Kd = 0; Ks = 0; Kp = 0;
}

//----------------------------------------------
Phong::~Phong()
{
}

//----------------------------------------------
void Phong::SetCamera(Point3D pos)
{
	CameraPos = pos;
	if (DEBUG) cout << CameraPos.print() << endl;
}

//----------------------------------------------
void Phong::SetLight(ColorRGB color, Vector3D dir)
{
	LightColor = color;
	if (DEBUG) cout << LightColor.print() << endl;
	LightDir = dir;
	LightDir.normalize();
	if (DEBUG) cout << LightDir.print() << endl;
}

//----------------------------------------------
void Phong::SetObject(ColorRGB color, float ka, float kd, float ks, float kp)
{
	ObjectColor = color;
	if (DEBUG) cout << ObjectColor.print() << endl;
	Ka = ka; Kd = kd; Ks = ks; Kp = kp;
}

//----------------------------------------------
void Phong::GetShade(Point3D point, Vector3D normal, ColorRGB & color)
{
	// Normalize surface normal
	normal.normalize();

	// Calculate ambient term
	ColorRGB ambient;
	ambient = LightColor;
	ambient.mult(ObjectColor);
	ambient.mult(Ka);
	if (DEBUG) cout << "ambient " << ambient.print() << endl;
	color = ambient;

	// Calculate NdotL value
	float NdotL = normal.dot(LightDir);
	if (DEBUG) cout << "NdotL " << NdotL << endl;
	if (NdotL > 0)
	{
		// Calculate diffuse term
		ColorRGB diffuse;
		diffuse = LightColor;
		diffuse.mult(ObjectColor);
		diffuse.mult(Kd * NdotL);
		if (DEBUG) cout << "diffuse " << diffuse.print() << endl;
		color.add(diffuse);

		// Calculate R vector
		Vector3D R = normal;
		R.mult(2 * NdotL);
		R.sub(LightDir);
		R.normalize();

		// Calculate V vector
		Vector3D V;
		float Vx = CameraPos.px - point.px;
		float Vy = CameraPos.py - point.py;
		float Vz = CameraPos.pz - point.pz;
		V.set(Vx, Vy, Vz);
		V.normalize();

		// Calculate RdotV value 
		float RdotV = R.dot(V);
		if (DEBUG) cout << "RdotV " << RdotV << endl;
		if (RdotV > 0)
		{
			// Calculate specular term
			RdotV = pow(RdotV, Kp);
			ColorRGB specular;
			specular = LightColor;
			specular.mult(Ks * RdotV);
			if (DEBUG) cout << "specular " << specular.print() << endl;
			color.add(specular);
		}
	}
}