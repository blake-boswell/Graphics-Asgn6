////----------------------------------------------
//// Purpose: Test Phong class
//// Author:  John Gauch
////----------------------------------------------
//
//#include "classes2.h"
//#include "phong2.h"
//
////----------------------------------------------
//int main()
//{
//	Phong shader;
//	string name;
//	while (cin >> name)
//	{
//		if (name == "Camera")
//		{
//			// Read and save camera information
//			Point3D pos;
//			cin >> pos.px >> pos.py >> pos.pz;
//			shader.SetCamera(pos);
//		}
//
//		else if (name == "Light")
//		{
//			// Read and save light information
//			ColorRGB color;
//			Vector3D dir;
//			cin >> color.R >> color.G >> color.B;
//			cin >> dir.vx >> dir.vy >> dir.vz;
//			shader.SetLight(color, dir);
//		}
//
//		else if (name == "Object")
//		{
//			// Read and save object information
//			ColorRGB color;
//			float ka, kd, ks, kp;
//			cin >> color.R >> color.G >> color.B;
//			cin >> ka >> kd >> ks >> kp;
//			shader.SetObject(color, ka, kd, ks, kp);
//		}
//
//		else if (name == "Point")
//		{
//			// Read and use point information
//			Point3D point;
//			Vector3D normal;
//			ColorRGB color;
//			cin >> point.px >> point.py >> point.pz;
//			cin >> normal.vx >> normal.vy >> normal.vz;
//			shader.GetShade(point, normal, color);
//			point.print();
//			cout << " ";
//			color.print();
//			cout << endl;
//		}
//
//		else
//		{
//			cout << "Ignoring '" << name << "' token\n";
//		}
//	}
//}