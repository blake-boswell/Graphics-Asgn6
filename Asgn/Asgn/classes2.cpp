//----------------------------------------------
// Purpose: Definition and implementation of ColorRGB, 
//          Point3D, Vector3D, Ray3D and Sphere3D classes.
//
//    These classes have no private variables so
//    they should be used with care (since there
//    is no data hiding provided).
//    
// Author:  John Gauch
//----------------------------------------------
#include "classes2.h"

void ColorRGB::set(float r, float g, float b)
{
	R = r;
	G = g;
	B = b;
	clamp();
}

//----------------------------------------------
string ColorRGB::print()
{
	cout << "(" << int(R) << "," << int(G) << "," << int(B) << ")";
	return "";
}

//----------------------------------------------
void ColorRGB::mult(float c)
{
	R *= c;
	G *= c;
	B *= c;
	clamp();
}

//----------------------------------------------
void ColorRGB::mult(ColorRGB c)
{
	R *= c.R / 255;
	G *= c.G / 255;
	B *= c.B / 255;
	clamp();
}

//----------------------------------------------
void ColorRGB::add(ColorRGB c)
{
	R += c.R;
	G += c.G;
	B += c.B;
	clamp();
}

//----------------------------------------------
void ColorRGB::sub(ColorRGB c)
{
	R -= c.R;
	G -= c.G;
	B -= c.B;
	clamp();
}

//----------------------------------------------
void ColorRGB::clamp()
{
	if (R < 0) R = 0;
	if (G < 0) G = 0;
	if (B < 0) B = 0;
	if (R > 255) R = 255;
	if (G > 255) G = 255;
	if (B > 255) B = 255;
}

//----------------------------------------------
void Point3D::set(float x, float y, float z)
{
	px = x;
	py = y;
	pz = z;
}

//----------------------------------------------
string Point3D::print()
{
	cout << "(" << px << "," << py << "," << pz << ")";
	return "";
}

//----------------------------------------------
float Point3D::distance(Point3D p)
{
	float dx = px - p.px;
	float dy = py - p.py;
	float dz = pz - p.pz;
	return sqrt(dx*dx + dy * dy + dz * dz);
}

//----------------------------------------------
void Vector3D::set(float x, float y, float z)
{
	vx = x;
	vy = y;
	vz = z;
}

//----------------------------------------------
string Vector3D::print()
{
	cout << "(" << vx << "," << vy << "," << vz << ")";
	return "";
}

//----------------------------------------------
void Vector3D::normalize()
{
	float length = sqrt(vx*vx + vy * vy + vz * vz);
	vx /= length;
	vy /= length;
	vz /= length;
}

//----------------------------------------------
float Vector3D::dot(Vector3D v)
{
	return vx * v.vx + vy * v.vy + vz * v.vz;
}

//----------------------------------------------
void Vector3D::mult(float c)
{
	vx *= c;
	vy *= c;
	vz *= c;
}

//----------------------------------------------
void Vector3D::add(Vector3D v)
{
	vx += v.vx;
	vy += v.vy;
	vz += v.vz;
}

//----------------------------------------------
void Vector3D::sub(Vector3D v)
{
	vx -= v.vx;
	vy -= v.vy;
	vz -= v.vz;
}

//----------------------------------------------
void Ray3D::set(Point3D p, Vector3D d)
{
	point = p;
	dir = d;
	dir.normalize();
}

//----------------------------------------------
void Ray3D::set(Point3D p1, Point3D p2)
{
	point = p1;
	dir.set(p2.px - p1.px, p2.py - p1.py, p2.pz - p1.pz);
	dir.normalize();
}

//----------------------------------------------
string Ray3D::print()
{
	point.print(); cout << " "; dir.print();
	return "";
}

//----------------------------------------------
Point3D Ray3D::get_sample(float t)
{
	Point3D result;
	result.set(point.px + t * dir.vx, point.py + t * dir.vy, point.pz + t * dir.vz);
	return result;
}

//----------------------------------------------
void Sphere3D::set(Point3D p, float r)
{
	center = p;
	radius = r;
}

//----------------------------------------------
string Sphere3D::print()
{
	center.print();
	cout << " " << radius;
	return "";
}

//----------------------------------------------
bool Sphere3D::get_intersection(Ray3D ray, Point3D &point, Vector3D &normal)
{
	// Define oc vector
	Point3D p1 = center;
	Point3D p2 = ray.point;
	Vector3D oc;
	oc.set(p2.px - p1.px, p2.py - p1.py, p2.pz - p1.pz);

	// Calculate quadratic equation 
	float A = ray.dir.dot(ray.dir);
	float B = 2 * oc.dot(ray.dir);
	float C = oc.dot(oc) - radius * radius;
	// cout << "A = " << A << endl;
	// cout << "B = " << B << endl;
	// cout << "C = " << C << endl;

	// Solve quadratic equation for intersection points
	float discriminant = B * B - 4 * A*C;
	// cout << "discriminant = " << discriminant << endl;
	if (discriminant >= 0)
	{
		// Calculate two roots
		float root1 = (-B - sqrt(discriminant)) / 2 * A;
		float root2 = (-B + sqrt(discriminant)) / 2 * A;
		// cout << "root1 = " << root1 << endl;
		// cout << "root2 = " << root2 << endl;
		float solution = 0;

		// No positive roots found
		if ((root1 < 0) && (root2 < 0))
			return false;

		// One positive root
		else if ((root1 < 0) && (root2 >= 0))
			solution = root2;

		// One positive root
		else if ((root2 < 0) && (root1 >= 0))
			solution = root1;

		// Two positive roots
		else if (root1 <= root2)
			solution = root1;

		// Two positive roots
		else if (root2 <= root1)
			solution = root2;

		// Get intersection point
		point = ray.get_sample(solution);

		// Get surface normal
		normal.set(point.px - center.px, point.py - center.py, point.pz - center.pz);
		normal.normalize();
		return true;
	}
	return false;
}

void ObjectProperties::set(ColorRGB color, float Ka, float Kd, float Ks, float Kp) {
	this->color.set(color.R, color.G, color.B);
	this->Ka = Ka;
	this->Kd = Kd;
	this->Ks = Ks;
	this->Kp = Kp;
}
