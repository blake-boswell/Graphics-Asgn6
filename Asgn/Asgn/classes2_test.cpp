////----------------------------------------------
//// Purpose: Definition and implementation of the
////    Point3D, Vector3D, Ray3D and Sphere3D classes.
////
////    These classes have no private variables and
////    they have "inline" method implementations
////    so they should be used with care (since there
////    is no data hiding provided).
////    
//// Author:  John Gauch
////----------------------------------------------
//#include <iostream>
//#include <cmath>
//using namespace std;
//
//#include "classes2.h"
//
//int main()
//{
//	cout << "\nTest point class\n";
//	Point3D p1;
//	p1.set(1, 2, 3);
//	cout << "p1 = ";
//	p1.print();
//	cout << endl;
//
//	Point3D p2;
//	p2.set(3, 4, 5);
//	cout << "p2 = ";
//	p2.print();
//	cout << endl;
//
//	float dist12 = p1.distance(p2);
//	float dist21 = p2.distance(p1);
//	cout << "dist12 = " << dist12 << endl;
//	cout << "dist21 = " << dist21 << endl;
//
//	cout << "\nTest vector class\n";
//	Vector3D v1;
//	v1.set(2, 1, 0);
//	cout << "v1 = ";
//	v1.print();
//	cout << endl;
//
//	Vector3D v2;
//	v2.set(-1, 1, 0);
//	cout << "v2 = ";
//	v2.print();
//	cout << endl;
//
//	v2.normalize();
//	cout << "v2 = ";
//	v2.print();
//	cout << endl;
//
//	float v1dotv1 = v1.dot(v1);
//	float v1dotv2 = v1.dot(v2);
//	float v2dotv2 = v2.dot(v2);
//	cout << "v1dotv1 = " << v1dotv1 << endl;
//	cout << "v1dotv2 = " << v1dotv2 << endl;
//	cout << "v2dotv2 = " << v2dotv2 << endl;
//
//	cout << "\nTest ray class\n";
//	Ray3D r1;
//	r1.set(p1, v1);
//	cout << "r1(p1,v1) = ";
//	r1.print();
//	cout << endl;
//
//	Ray3D r2;
//	r2.set(p2, p1);
//	cout << "r2(p2,p1) = ";
//	r2.print();
//	cout << endl;
//
//	for (int i = 0; i <= 10; i++)
//	{
//		cout << "r1(" << i / 10.0 << ") = ";
//		r1.get_sample(i / 10.0).print();
//		cout << endl;
//	}
//
//	cout << "\nTest sphere class\n";
//	Sphere3D sphere;
//	Point3D center;
//	center.set(0, 0, 0);
//	sphere.set(center, 2);
//	cout << "sphere = ";
//	sphere.print();
//	cout << endl;
//
//	for (int px = -3; px <= 3; px++)
//	{
//		Point3D point;
//		point.set(px, 0, 0);
//		Vector3D dir;
//		dir.set(1, 0, 0);
//		Ray3D ray;
//		ray.set(point, dir);
//		cout << "ray = ";
//		ray.print();
//		cout << endl;
//
//		Point3D p;
//		Vector3D n;
//		if (!sphere.get_intersection(ray, p, n))
//			cout << "no intersection\n";
//		else
//		{
//			cout << "point = ";
//			p.print();
//			cout << endl;
//			cout << "normal = ";
//			n.print();
//			cout << endl;
//		}
//	}
//	return 0;
//}