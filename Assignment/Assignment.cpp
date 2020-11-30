#include <math.h>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <GL/GLU.h>
#include <string>

using namespace std;

#define PI			3.1415926
#define	COLORNUM		14
#define DEG2RAD	(PI / 180.0)


float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };


/// <summary>
/// Class
/// </summary>

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	string printPoint3()
	{
		string res = to_string(x) + " ; " + to_string(y) + " ; " + to_string(z);
		return res;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}
	void set(Color3& c)
	{
		r = c.r; g = c.g; b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw() {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float 	x, y;
};
class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw() {
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth() { return (r - l); }
	int  getHeight() { return (t - b); }
private:
	int	l, r, b, t;
};


class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float  getWidth() { return (r - l); }
	float  getHeight() { return (t - b); }
	void draw() {
		glRectf(l, b, r, t);
		glFlush();
	};// draw this rectangle using OpenGL
private:
	float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	void flip()
	{
		x = -x; y = -y; z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x * x + y * y + z * z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}

class VertexID
{
public:
	int		vertIndex; //index of this vertex in the vertex list
	int		normIndex; // index of this vertex's normal
	int		colorIndex; // index of this vertex's color
};

class Face
{
public:
	int	nVerts;
	VertexID* vert;
	// danh sách các đỉnh + vector pháp tuyến của đỉnh
	Vector3 vtNewell;
	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};


class Mesh
{
public:
	int	numVerts; // chiều dài
	Point3* pt; // danh sách các đỉnh

	int	numFaces; // chiều dài 
	Face* face; // danh sách các mặt

public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void Draw(int chooseColor);
	void DrawColor();
	void SetColor(int colorIdx);
	void addMaterial(float ambient[], float diffuse[], float specular[], float shiness);

	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateRectangular(float fLength, float fWidth, float fHeight);
	void CreateShape1(float fLength, float fWidth, float fHeight, float fRadius);
	void CreateShape2(float fLength1, float fRadius1, float fLength2, float fRadius2, float fHeight);
	void CreateShape3(float fLength1, float fLength2, float fWidth, float fHeight, float fRadius);
	void CreateShape4(float fLength, float fWidth, float fHeight, float fRadius);
	void CreateShape5(float fLength, float fWidth, float fHeight);

	void vectorNewell();
};

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2; // đỉnh ở phía trên + dưới (bao gồm cả tâm)
	//cout << numVerts << endl;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * i);
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateRectangular(float fLength, float fWidth, float fHeight)
{
	numVerts = 8;
	numFaces = 6;
	pt = new Point3[numVerts];
	face = new Face[numFaces];
	int idx = 0;
	int indexColor = 1;
	{
		pt[0].set(0, 0, 0); //A
		pt[1].set(0, 0, fLength); //B
		pt[2].set(fWidth, 0, fLength); //C
		pt[3].set(fWidth, 0, 0); //D
		pt[4].set(0, fHeight, 0); //A'
		pt[5].set(0, fHeight, fLength); //B
		pt[6].set(fWidth, fHeight, fLength); //C
		pt[7].set(fWidth, fHeight, 0); //D

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 2;
		face[idx].vert[3].vertIndex = 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 4;
		face[idx].vert[1].vertIndex = 5;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 7;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 1;
		face[idx].vert[1].vertIndex = 2;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 5;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 2;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 6;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 5;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = indexColor;
		idx++;
	}
}

void Mesh::CreateShape1(float fLength, float fWidth, float fHeight, float fRadius)
{
	int i;
	int nSegment = 16;
	float fOx = fWidth;
	float fOy = fHeight;
	float fOz = fLength;
	int	idx = 0, idp = 0;
	float fAngle = (PI / 2) / nSegment;
	float x, y, z;
	int iStart = 8;


	numVerts = nSegment * 4 + 8; 
	numFaces = nSegment * 4 + 8;
	face = new Face[numFaces];
	pt = new Point3[numVerts];
	// Ve khoi hinh thang vuong
	// Ve cube 1
	{
		pt[idp].set(0, 0, 0); //A
		pt[++idp].set(fOx, 0, 0); //B
		pt[++idp].set(fRadius, 0, fOz); //C
		pt[++idp].set(0, 0, fOz); //D
		pt[++idp].set(0, fOy, 0); //A'
		pt[++idp].set(fOx, fOy, 0); //B'
		pt[++idp].set(fRadius, fOy, fOz); //C'
		pt[++idp].set(0, fOy, fOz); //D'
		idp++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 2;
		face[idx].vert[3].vertIndex = 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 4;
		face[idx].vert[1].vertIndex = 5;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 7;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 2;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 3;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 1;
		face[idx].vert[1].vertIndex = 2;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 5;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 4;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 5;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 6;
		idx++;
	}
	// 1/4 hinh tru
	{
		iStart = idp;
		float iStop;
		float iCount = 0;
		pt[iStart].set(0, 0, fOz);
		idp++;
		for (int i = 0; i < nSegment; i++)
		{
			//cout << sin(fAngle * i) << ";" << cos(fAngle * i) << " -- " << fAngle * i << ">" << beta << endl;
			x = fRadius * sin(fAngle * i);
			z = fRadius * cos(fAngle * i) + fOz;
			y = 0;
			pt[idp].set(x, y, z); // 17
			idp++;
			//cout << i + iStart + 1 << endl;
			//cout << i + idp << endl;
		}
		pt[idp].set(fRadius, 0, fOz);
		idp++;
		int iStart2 = idp;
		pt[iStart2].set(0, fHeight, fOz);
		idp++;
		for (int i = 0; i < nSegment; i++)
		{
			x = fRadius * sin(fAngle * i);
			z = fRadius * cos(fAngle * i) + fOz;
			y = fHeight;
			pt[idp].set(x, y, z); 
			idp++;
		}
		pt[idp].set(fRadius, fHeight, fOz);
		idp++;
		for (int i = 1; i <= nSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart;
			face[idx].vert[1].vertIndex = iStart + i;
			face[idx].vert[2].vertIndex = iStart + i + 1;
			cout << pt[iStart + i].printPoint3() << endl;
			idx++;
		}
		for (int i = 1; i <= nSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart2;
			face[idx].vert[1].vertIndex = iStart2 + i;
			face[idx].vert[2].vertIndex = iStart2 + i + 1;
			idx++;
		}
		for (int i = 1; i <= nSegment; i++)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + i;
			face[idx].vert[1].vertIndex = iStart2 + i;
			face[idx].vert[2].vertIndex = iStart2 + i + 1;
			face[idx].vert[3].vertIndex = iStart + i + 1;
			idx++;
		}
	}
}

void Mesh::CreateShape2(float fLength1, float fRadius1, float fLength2, float fRadius2, float fHeight)
{
	//int i;
	/*
		fLength1 / 4
		1 phần bên trái + 3 phần bên phải
		x1 = 0
		x2 = fLength1
		z1 = fRadius1
		z2 = -fRadius1

		A					    B
		  ******************* E   F
		  *					* ****
		  *					* ****
		  ******************* H   G
		D					    C

		A(x1,z1)
		B(x2,z1)
		C(x2,z2)
		D(x1,z2)

		E (x_C, fRadius2)
		F (x_C + fLength2, fRadius2)
		G (x_C + fLength2, -fRadius2)
		H (x_C, -fRadius2)

	*/
	int nSegment = 16;
	int		idx = 0, idp = 0;
	float	fAngle = PI / nSegment;
	float	x, y, z;
	int iStart = 0, iCount = 0;


	numVerts = nSegment * 6 + 8 * 2;
	numFaces = 6 * 2 + nSegment * 8 + 4;
	face = new Face[numFaces];
	pt = new Point3[numVerts];
	// Ve cube 1
	{
		float Oxz_x1 = 0;
		float Oxz_x2 = fLength1;
		float Oxz_z1 = fRadius1;
		float Oxz_z2 = -fRadius1;
		float Oxz_y = fHeight;
		pt[0].set(Oxz_x1, 0, Oxz_z1); //A
		pt[1].set(Oxz_x2, 0, Oxz_z1 + 0.1); //B
		pt[2].set(Oxz_x2, 0, Oxz_z2 - 0.1); //C
		pt[3].set(Oxz_x1, 0, Oxz_z2); //D
		pt[4].set(Oxz_x1, Oxz_y, Oxz_z1); //A'
		pt[5].set(Oxz_x2, Oxz_y, Oxz_z1 + 0.1); //B'
		pt[6].set(Oxz_x2, Oxz_y, Oxz_z2 - 0.1); //C'
		pt[7].set(Oxz_x1, Oxz_y, Oxz_z2);// D'

		//Left face
		face[0].nVerts = 4;
		face[0].vert = new VertexID[face[0].nVerts];
		face[0].vert[0].vertIndex = 1;
		face[0].vert[1].vertIndex = 5;
		face[0].vert[2].vertIndex = 6;
		face[0].vert[3].vertIndex = 2;
		for (int i = 0; i < face[0].nVerts; i++)
			face[0].vert[i].colorIndex = 0;

		//Right face
		face[1].nVerts = 4;
		face[1].vert = new VertexID[face[1].nVerts];
		face[1].vert[0].vertIndex = 0;
		face[1].vert[1].vertIndex = 3;
		face[1].vert[2].vertIndex = 7;
		face[1].vert[3].vertIndex = 4;
		for (int i = 0; i < face[1].nVerts; i++)
			face[1].vert[i].colorIndex = 1;

		//top face
		face[2].nVerts = 4;
		face[2].vert = new VertexID[face[2].nVerts];
		face[2].vert[0].vertIndex = 0;
		face[2].vert[1].vertIndex = 1;
		face[2].vert[2].vertIndex = 2;
		face[2].vert[3].vertIndex = 3;
		for (int i = 0; i < face[2].nVerts; i++)
			face[2].vert[i].colorIndex = 2;

		//bottom face
		face[3].nVerts = 4;
		face[3].vert = new VertexID[face[3].nVerts];
		face[3].vert[0].vertIndex = 7;
		face[3].vert[1].vertIndex = 6;
		face[3].vert[2].vertIndex = 5;
		face[3].vert[3].vertIndex = 4;
		for (int i = 0; i < face[3].nVerts; i++)
			face[3].vert[i].colorIndex = 3;

		//near face
		face[4].nVerts = 4;
		face[4].vert = new VertexID[face[4].nVerts];
		face[4].vert[0].vertIndex = 4;
		face[4].vert[1].vertIndex = 5;
		face[4].vert[2].vertIndex = 1;
		face[4].vert[3].vertIndex = 0;
		for (int i = 0; i < face[4].nVerts; i++)
			face[4].vert[i].colorIndex = 4;

		//Far face
		face[5].nVerts = 4;
		face[5].vert = new VertexID[face[5].nVerts];
		face[5].vert[0].vertIndex = 3;
		face[5].vert[1].vertIndex = 2;
		face[5].vert[2].vertIndex = 6;
		face[5].vert[3].vertIndex = 7;
		for (int i = 0; i < face[5].nVerts; i++)
			face[5].vert[i].colorIndex = 5;
	}
	// Ve cube 2
	{
		float Oxz_x1 = fLength1;
		float Oxz_x2 = fLength1 + fLength2;
		float Oxz_z1 = fRadius2;
		float Oxz_z2 = -fRadius2;
		float Oxz_y = fHeight;
		pt[8].set(Oxz_x1, 0, Oxz_z1); //A					0
		pt[9].set(Oxz_x2, 0, Oxz_z1); //B				1
		pt[10].set(Oxz_x2, 0, Oxz_z2); //C			2
		pt[11].set(Oxz_x1, 0, Oxz_z2); //D					3
		pt[12].set(Oxz_x1, Oxz_y, Oxz_z1); //A'				4
		pt[13].set(Oxz_x2, Oxz_y, Oxz_z1); //B'		5
		pt[14].set(Oxz_x2, Oxz_y, Oxz_z2); //C'		6
		pt[15].set(Oxz_x1, Oxz_y, Oxz_z2);// D'				7

		//Left face
		face[6].nVerts = 4;
		face[6].vert = new VertexID[face[6].nVerts];
		face[6].vert[0].vertIndex = 1 + 8;
		face[6].vert[1].vertIndex = 5 + 8;
		face[6].vert[2].vertIndex = 6 + 8;
		face[6].vert[3].vertIndex = 2 + 8;
		for (int i = 0; i < face[6].nVerts; i++)
			face[6].vert[i].colorIndex = 0;

		//Right face
		face[7].nVerts = 4;
		face[7].vert = new VertexID[face[7].nVerts];
		face[7].vert[0].vertIndex = 0 + 8;
		face[7].vert[1].vertIndex = 3 + 8;
		face[7].vert[2].vertIndex = 7 + 8;
		face[7].vert[3].vertIndex = 4 + 8;
		for (int i = 0; i < face[7].nVerts; i++)
			face[7].vert[i].colorIndex = 1;

		//top face ========> chinh sua cho nay
		face[8].nVerts = 4;
		face[8].vert = new VertexID[face[8].nVerts];
		face[8].vert[0].vertIndex = 0 + 8;
		face[8].vert[1].vertIndex = 1 + 8;
		face[8].vert[2].vertIndex = 2 + 8;
		face[8].vert[3].vertIndex = 3 + 8;
		for (int i = 0; i < face[8].nVerts; i++)
			face[8].vert[i].colorIndex = 2;

		//bottom face
		face[9].nVerts = 4;
		face[9].vert = new VertexID[face[9].nVerts];
		face[9].vert[0].vertIndex = 7 + 8;
		face[9].vert[1].vertIndex = 6 + 8;
		face[9].vert[2].vertIndex = 5 + 8;
		face[9].vert[3].vertIndex = 4 + 8;
		for (int i = 0; i < face[9].nVerts; i++)
			face[9].vert[i].colorIndex = 3;

		//near face
		face[10].nVerts = 4;
		face[10].vert = new VertexID[face[10].nVerts];
		face[10].vert[0].vertIndex = 4 + 8;
		face[10].vert[1].vertIndex = 5 + 8;
		face[10].vert[2].vertIndex = 1 + 8;
		face[10].vert[3].vertIndex = 0 + 8;
		for (int i = 0; i < face[10].nVerts; i++)
			face[10].vert[i].colorIndex = 4;

		//Far face
		face[11].nVerts = 4;
		face[11].vert = new VertexID[face[11].nVerts];
		face[11].vert[0].vertIndex = 3 + 8;
		face[11].vert[1].vertIndex = 2 + 8;
		face[11].vert[2].vertIndex = 6 + 8;
		face[11].vert[3].vertIndex = 7 + 8;
		for (int i = 0; i < face[11].nVerts; i++)
			face[11].vert[i].colorIndex = 5;

	}
	// ve hinh tron 1
	{
		idp = 16;
		idx = 12;
		iStart = idp;
		iCount = 0;
		pt[iStart].set(0, 0, 0);
		//cout << "===" << iStart << endl;
		idp++;
		for (int i = 0; i <= nSegment; i++)
		{
			//cout << sin(fAngle * i) << ";" << cos(fAngle * i) << " -- " << fAngle * i << ">" << beta << endl;
			x = fRadius1 * cos(fAngle * i + 90 * DEG2RAD);
			z = fRadius1 * sin(fAngle * i + 90 * DEG2RAD);
			y = 0;
			pt[i + iStart + 1].set(x, y, z); // 17
			//cout << pt[i + iStart + 1].printPoint3() << endl;
			idp++;
			//cout << i + iStart + 1 << endl;
			//cout << i + idp << endl;
		}
		int iStart2 = idp;
		//cout << "===" << iStart2 << endl;
		pt[iStart2].set(0, fHeight, 0);
		idp++;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius1 * cos(fAngle * i + 90 * DEG2RAD);
			z = fRadius1 * sin(fAngle * i + 90 * DEG2RAD);
			y = fHeight;
			//cout << x << ";" << z << endl;
			pt[i + iStart2 + 1].set(x, y, z); // 17
			//cout << i + iStart2 + 1 << endl;
			idp++;
			//cout << i + idp << endl;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart;
			face[idx].vert[1].vertIndex = iStart + i + 1;
			face[idx].vert[2].vertIndex = iStart + i + 2;
			if (i == nSegment)
			{
				//cout << pt[iStart + i + 1].y << endl;
				face[idx].vert[2].vertIndex = iStart;
			}
			idx++;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart2;
			face[idx].vert[1].vertIndex = iStart2 + i + 1;
			face[idx].vert[2].vertIndex = iStart2 + i + 2;
			if (i == nSegment)
			{
				face[idx].vert[2].vertIndex = iStart2;
			}
			idx++;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + i + 1;
			face[idx].vert[1].vertIndex = iStart2 + i + 1;
			face[idx].vert[2].vertIndex = iStart2 + i + 2;
			face[idx].vert[3].vertIndex = iStart + i + 2;
			if (i == nSegment)
			{
				face[idx].vert[2].vertIndex = iStart2;
				face[idx].vert[3].vertIndex = iStart;
			}
			idx++;
		}
	}
	// ve hinh tron 2
	{
		iStart = idp;
		iCount = 0;
		pt[iStart].set(fLength1 + fLength2, 0, 0);
		//cout << "===" << iStart << endl;
		idp++;
		for (int i = 0; i <= nSegment; i++)
		{
			//cout << sin(fAngle * i) << ";" << cos(fAngle * i) << " -- " << fAngle * i << ">" << beta << endl;
			x = fRadius2 * cos(fAngle * i - 90 * DEG2RAD) + fLength1 + fLength2;
			z = fRadius2 * sin(fAngle * i - 90 * DEG2RAD);
			y = 0;
			pt[i + iStart + 1].set(x, y, z); // 17
			//cout << pt[i + iStart + 1].printPoint3() << endl;
			idp++;
			//cout << i + iStart + 1 << endl;
			//cout << i + idp << endl;
		}
		int iStart2 = idp;
		//cout << "===" << iStart2 << endl;
		pt[iStart2].set(fLength1 + fLength2, fHeight, 0);
		idp++;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius2 * cos(fAngle * i - 90 * DEG2RAD) + fLength1 + fLength2;
			z = fRadius2 * sin(fAngle * i - 90 * DEG2RAD);
			y = fHeight;
			//cout << x << ";" << z << endl;
			pt[i + iStart2 + 1].set(x, y, z); // 17
			//cout << i + iStart2 + 1 << endl;
			idp++;
			//cout << i + idp << endl;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart;
			face[idx].vert[1].vertIndex = iStart + i + 1;
			face[idx].vert[2].vertIndex = iStart + i + 2;
			if (i == nSegment)
			{
				//cout << pt[iStart + i + 1].y << endl;
				face[idx].vert[2].vertIndex = iStart;
			}
			idx++;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart2;
			face[idx].vert[1].vertIndex = iStart2 + i + 1;
			face[idx].vert[2].vertIndex = iStart2 + i + 2;
			if (i == nSegment)
			{
				face[idx].vert[2].vertIndex = iStart2;
			}
			idx++;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + i + 1;
			face[idx].vert[1].vertIndex = iStart2 + i + 1;
			face[idx].vert[2].vertIndex = iStart2 + i + 2;
			face[idx].vert[3].vertIndex = iStart + i + 2;
			if (i == nSegment)
			{
				face[idx].vert[2].vertIndex = iStart2;
				face[idx].vert[3].vertIndex = iStart;
			}
			idx++;
		}
	}
}

void Mesh::CreateShape3(float fLength1, float fLength2, float fWidth, float fHeight, float fRadius)
{
	/*
		A(0,0)
		B(0,fLength1)
		C(fWidth, fLength1)
		D(fWidth, fLength1 - fLength2)
	*/
	int nSegment = 24;
	int	idx = 0, idp = 0;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;

	numVerts = 26 + nSegment * 4;
	numFaces = 6 + 5 * 3 + nSegment * 4;
	face = new Face[numFaces];
	pt = new Point3[numVerts];
	// Ve cube 1
	{
		pt[idp].set(0, 0, 0); //A
		pt[++idp].set(0, 0, fLength1); //B
		pt[++idp].set(fWidth, 0, fLength1); //C
		pt[++idp].set(fWidth, 0, fLength1 - fLength2); //D
		pt[++idp].set(0, fHeight, 0); //A'
		pt[++idp].set(0, fHeight, fLength1); //B'
		pt[++idp].set(fWidth, fHeight, fLength1); //C'
		pt[++idp].set(fWidth, fHeight, fLength1 - fLength2); //D'

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 2;
		face[idx].vert[3].vertIndex = 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 4;
		face[idx].vert[1].vertIndex = 5;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 7;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 2;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 3;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 1;
		face[idx].vert[1].vertIndex = 2;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 5;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 4;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 2;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 6;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 5;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 5;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 6;
		idx++;
	}
	// Ve khoi 
	{
		/*
		A(0,0)
		D(fWidth, fLength1 - fLength2)
		M(x,y)

		MA = (x,y)
		MD = (x - fWidth, y - fLength1 + fLength2)
		x(x-fWidth) + y(y - fLength1 + fLength2) = 0
		MD = d^2 = (x-fWidth)^2 + (y - fLength1 + fLength2)^2
		x = sqrt(d^2 - (y - fLength1 + fLength2)^2) + fWidth

		AD = sqrt(fWitdth^2 + (fLength1 - fLength2)^2)
		MD = fWidth
		MA = sqrt(AD^2 - MD^2)

		*/
		float MA = fLength1 - fLength2;
		float MD = fWidth;
		float AD = sqrt(MA * MA + MD * MD);
		float alpha = asinf(MD / AD) * 2.0;
		float x_circle = sin(alpha) * MA;
		float z_circle = cos(alpha) * MA;
		float x_n = x_circle;
		float z_n = z_circle - fRadius;
		float beta = PI - (asinf(x_circle / MA) + acosf(fRadius / MD));
		float x_e = cos(beta) * fRadius + x_circle;
		float z_e = sin(beta) * fRadius + z_circle;
		int iStart = idp + 1;

		// Tam giac 1
		{
			pt[++idp].set(0, 0, 0); //A
			pt[++idp].set(MD, 0, MA); //D
			pt[++idp].set(x_circle, 0, z_circle); //M
			pt[++idp].set(0, fHeight, 0); //A'
			pt[++idp].set(MD, fHeight, MA); //D'
			pt[++idp].set(x_circle, fHeight, z_circle); //M'

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 2;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 3;
			face[idx].vert[1].vertIndex = iStart + 4;
			face[idx].vert[2].vertIndex = iStart + 5;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 4;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 1;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 4;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;
		}
		// Tam giac 2
		{
			iStart = idp + 1;
			pt[++idp].set(0, 0, 0); //A
			pt[++idp].set(x_circle, 0, z_circle); //M
			pt[++idp].set(x_n, 0, z_n); //N
			pt[++idp].set(0, fHeight, 0); //A'
			pt[++idp].set(x_circle, fHeight, z_circle); //M'
			pt[++idp].set(x_n, fHeight, z_n); //N'

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 2;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 3;
			face[idx].vert[1].vertIndex = iStart + 4;
			face[idx].vert[2].vertIndex = iStart + 5;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 4;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 1;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 4;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;
		}
		// Tam giac 3
		{
			iStart = idp + 1;
			pt[++idp].set(x_circle, 0, z_circle); //M
			pt[++idp].set(MD, 0, MA); //D
			pt[++idp].set(x_e, 0, z_e); //E
			pt[++idp].set(x_circle, fHeight, z_circle); //M'
			pt[++idp].set(MD, fHeight, MA); //D'
			pt[++idp].set(x_e, fHeight, z_e); //E'

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 2;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 3;
			face[idx].vert[1].vertIndex = iStart + 4;
			face[idx].vert[2].vertIndex = iStart + 5;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 1;
			face[idx].vert[2].vertIndex = iStart + 4;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 0;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 3;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;

			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + 1;
			face[idx].vert[1].vertIndex = iStart + 2;
			face[idx].vert[2].vertIndex = iStart + 5;
			face[idx].vert[3].vertIndex = iStart + 4;
			for (int i = 0; i < face[idx].nVerts; i++)
				face[idx].vert[i].colorIndex = 0;
			idx++;
		}
		// hinh tron
		{
			fAngle = (beta + PI / 2.0) / nSegment;
			iStart = idp + 1;
			float iStop;
			float iCount = 0;
			pt[iStart].set(x_circle, 0, z_circle);
			//cout << "===" << iStart << endl;
			idp++;
			for (int i = 0; i <= nSegment; i++)
			{
				//cout << sin(fAngle * i) << ";" << cos(fAngle * i) << " -- " << fAngle * i << ">" << beta << endl;
				x = fRadius * sin(fAngle * i) + x_circle;
				z = fRadius * -cos(fAngle * i) + z_circle;
				y = 0;
				pt[i + iStart + 1].set(x, y, z); // 17
				idp++;
				//cout << i + iStart + 1 << endl;
				//cout << i + idp << endl;
			}
			int iStart2 = idp + 1;
			//cout << "===" << iStart2 << endl;
			pt[iStart2].set(x_circle, fHeight, z_circle);
			idp++;
			for (int i = 0; i <= nSegment; i++)
			{
				x = fRadius * sin(fAngle * i) + x_circle;
				z = fRadius * -cos(fAngle * i) + z_circle;
				y = fHeight;
				//cout << x << ";" << z << endl;
				pt[i + iStart2 + 1].set(x, y, z); // 17
				//cout << i + iStart2 + 1 << endl;
				idp++;
				//cout << i + idp << endl;
			}
			for (int i = 0; i <= nSegment; i++)
			{
				face[idx].nVerts = 3;
				face[idx].vert = new VertexID[face[idx].nVerts];
				face[idx].vert[0].vertIndex = iStart;
				face[idx].vert[1].vertIndex = iStart + i + 1;
				face[idx].vert[2].vertIndex = iStart + i + 2;
				if (i == nSegment)
				{
					//cout << pt[iStart + i + 1].y << endl;
					face[idx].vert[2].vertIndex = iStart;
				}
				idx++;
			}
			for (int i = 0; i <= nSegment; i++)
			{
				face[idx].nVerts = 3;
				face[idx].vert = new VertexID[face[idx].nVerts];
				face[idx].vert[0].vertIndex = iStart2;
				face[idx].vert[1].vertIndex = iStart2 + i + 1;
				face[idx].vert[2].vertIndex = iStart2 + i + 2;
				if (i == nSegment)
				{
					face[idx].vert[2].vertIndex = iStart2;
				}
				idx++;
			}
			for (int i = 0; i <= nSegment; i++)
			{
				face[idx].nVerts = 4;
				face[idx].vert = new VertexID[face[idx].nVerts];
				face[idx].vert[0].vertIndex = iStart + i + 1;
				face[idx].vert[1].vertIndex = iStart2 + i + 1;
				face[idx].vert[2].vertIndex = iStart2 + i + 2;
				face[idx].vert[3].vertIndex = iStart + i + 2;
				if (i == nSegment)
				{
					face[idx].vert[2].vertIndex = iStart2;
					face[idx].vert[3].vertIndex = iStart;
				}
				idx++;
			}
		}
	}
}

void Mesh::CreateShape4(float fLength, float fWidth, float fHeight, float fRadius)
{
	int nSegment = 10;
	int	idx = 0, idp = 0;
	float fAngle = PI / nSegment;
	float x, y, z;
	int iStart, iCount;
	numVerts = 8 + 6 + 6 + nSegment * 4;
	numFaces = 8 + 6 + 6 + 3 * nSegment;// 6 + nSegment * 4;
	face = new Face[numFaces];
	pt = new Point3[numVerts];

	float x_d = fWidth / tan(62 * DEG2RAD);
	float z_d = fWidth;
	float CD = sqrt(pow(fLength - x_d, 2) + pow(fLength - z_d, 2));
	float CE = sqrt(CD * CD - pow(2 * fRadius, 2));
	float CN = CE * cos(70 * DEG2RAD);
	float EN = CE * sin(70 * DEG2RAD);
	float x_e = fLength + CN;
	float z_e = fLength + EN;
	float x_m = (x_e + x_d) / 2.0;
	float z_m = (z_e + z_d) / 2.0;
	iStart = 0; iCount = 0, idx = 0;
	// Ve hinh 8 dinh
	{
		pt[idp].set(0, 0, 0); //A
		pt[++idp].set(fLength, 0, 0); //B
		pt[++idp].set(fLength, 0, fLength); //C
		pt[++idp].set(x_d, 0, z_d); //D
		pt[++idp].set(0, fHeight, 0); //A'
		pt[++idp].set(fLength, fHeight, 0); //B'
		pt[++idp].set(fLength, fHeight, fLength); //C'
		pt[++idp].set(x_d, fHeight, z_d); //D'
		idp++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 2;
		face[idx].vert[3].vertIndex = 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 4;
		face[idx].vert[1].vertIndex = 5;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 7;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 2;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 3;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 1;
		face[idx].vert[1].vertIndex = 2;
		face[idx].vert[2].vertIndex = 6;
		face[idx].vert[3].vertIndex = 5;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 4;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 2;
		face[idx].vert[1].vertIndex = 3;
		face[idx].vert[2].vertIndex = 7;
		face[idx].vert[3].vertIndex = 6;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 5;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = 5;
		face[idx].vert[3].vertIndex = 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 6;
		idx++;
	}
	// ve hinh 6 dinh
	// Tam giac 1
	{
		iStart = idp;
		pt[idp].set(fLength, 0, fLength); //C
		pt[++idp].set(x_d, 0, z_d); //D
		pt[++idp].set(x_m, 0, z_m); //M
		pt[++idp].set(fLength, fHeight, fLength); //C'
		pt[++idp].set(x_d, fHeight, z_d); //D'
		pt[++idp].set(x_m, fHeight, z_m); //M'
		idp++;

		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 0;
		face[idx].vert[1].vertIndex = iStart + 1;
		face[idx].vert[2].vertIndex = iStart + 2;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 3;
		face[idx].vert[1].vertIndex = iStart + 4;
		face[idx].vert[2].vertIndex = iStart + 5;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 0;
		face[idx].vert[1].vertIndex = iStart + 1;
		face[idx].vert[2].vertIndex = iStart + 4;
		face[idx].vert[3].vertIndex = iStart + 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 0;
		face[idx].vert[1].vertIndex = iStart + 2;
		face[idx].vert[2].vertIndex = iStart + 5;
		face[idx].vert[3].vertIndex = iStart + 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 1;
		face[idx].vert[1].vertIndex = iStart + 2;
		face[idx].vert[2].vertIndex = iStart + 5;
		face[idx].vert[3].vertIndex = iStart + 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;
	}
	// Tam giac 2
	{
		iStart = idp;
		pt[idp].set(fLength, 0, fLength); //C
		pt[++idp].set(x_e, 0, z_e); //E
		pt[++idp].set(x_m, 0, z_m); //M
		pt[++idp].set(fLength, fHeight, fLength); //C'
		pt[++idp].set(x_e, fHeight, z_e); //E'
		pt[++idp].set(x_m, fHeight, z_m); //M'
		idp++;

		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 0;
		face[idx].vert[1].vertIndex = iStart + 1;
		face[idx].vert[2].vertIndex = iStart + 2;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 3;
		face[idx].vert[1].vertIndex = iStart + 4;
		face[idx].vert[2].vertIndex = iStart + 5;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 0;
		face[idx].vert[1].vertIndex = iStart + 1;
		face[idx].vert[2].vertIndex = iStart + 4;
		face[idx].vert[3].vertIndex = iStart + 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 0;
		face[idx].vert[1].vertIndex = iStart + 2;
		face[idx].vert[2].vertIndex = iStart + 5;
		face[idx].vert[3].vertIndex = iStart + 3;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;

		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = iStart + 1;
		face[idx].vert[1].vertIndex = iStart + 2;
		face[idx].vert[2].vertIndex = iStart + 5;
		face[idx].vert[3].vertIndex = iStart + 4;
		for (int i = 0; i < face[idx].nVerts; i++)
			face[idx].vert[i].colorIndex = 0;
		idx++;
	}
	// hinh tron
	{
		iStart = idp;
		iCount = 0;
		pt[iStart].set(x_m, 0, z_m);
		//cout << "===" << iStart << endl;
		idp++;
		for (int i = 0; i <= nSegment; i++)
		{
			//cout << sin(fAngle * i) << ";" << cos(fAngle * i) << " -- " << fAngle * i << ">" << beta << endl;
			x = fRadius * cos(fAngle * i - 25 * DEG2RAD) + x_m;
			z = fRadius * sin(fAngle * i - 25 * DEG2RAD) + z_m;
			y = 0;
			if (i == 0)
			{
				x = x_e;
				z = z_e;
			}
			else if (i == nSegment)
			{
				x = x_d;
				z = z_d;
			}
			pt[i + iStart + 1].set(x, y, z); // 17
			//cout << pt[i + iStart + 1].printPoint3() << endl;
			idp++;
			//cout << i + iStart + 1 << endl;
			//cout << i + idp << endl;
		}
		int iStart2 = idp;
		//cout << "===" << iStart2 << endl;
		pt[iStart2].set(x_m, fHeight, z_m);
		idp++;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * cos(fAngle * i - 25 * DEG2RAD) + x_m;
			z = fRadius * sin(fAngle * i - 25 * DEG2RAD) + z_m;
			y = fHeight;
			if (i == 0)
			{
				x = x_e;
				z = z_e;
			}
			else if (i == nSegment)
			{
				x = x_d;
				z = z_d;
			}
			//cout << x << ";" << z << endl;
			pt[i + iStart2 + 1].set(x, y, z); // 17
			//cout << i + iStart2 + 1 << endl;
			idp++;
			//cout << i + idp << endl;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart;
			face[idx].vert[1].vertIndex = iStart + i + 1;
			face[idx].vert[2].vertIndex = iStart + i + 2;
			if (i == nSegment)
			{
				//cout << pt[iStart + i + 1].y << endl;
				face[idx].vert[2].vertIndex = iStart;
			}
			idx++;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 3;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart2;
			face[idx].vert[1].vertIndex = iStart2 + i + 1;
			face[idx].vert[2].vertIndex = iStart2 + i + 2;
			if (i == nSegment)
			{
				face[idx].vert[2].vertIndex = iStart2;
			}
			idx++;
		}
		for (int i = 0; i <= nSegment; i++)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + i + 1;
			face[idx].vert[1].vertIndex = iStart2 + i + 1;
			face[idx].vert[2].vertIndex = iStart2 + i + 2;
			face[idx].vert[3].vertIndex = iStart + i + 2;
			if (i == nSegment)
			{
				face[idx].vert[2].vertIndex = iStart2;
				face[idx].vert[3].vertIndex = iStart;
			}
			idx++;
		}
	}

}

void Mesh::CreateShape5(float fLength, float fWidth, float fHeight)
{
	int nSegment = 36;
	int	idx = 0, idp = 0;
	float fAngle = PI / nSegment;
	float x, y, z;
	float fRadius = fWidth / 2.0;
	int iStart, iCount;
	numVerts = 8 + nSegment * 4;
	numFaces = 4 + 2 * nSegment;// 6 + nSegment * 4;
	face = new Face[numFaces];
	pt = new Point3[numVerts];
	//mat duoi
	{
		iStart = idp;
		float iStop;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * -sin(fAngle * i);
			z = fRadius * -cos(fAngle * i);
			y = 0;
			//cout << x << ";" << y << ";" << z << endl;
			pt[iStart + i].set(x, y, z); // 17
			idp++;
		}
		iStart = idp;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * sin(fAngle * i) + fLength;
			z = fRadius * cos(fAngle * i);
			y = 0;
			//cout << x << ";" << y << ";" << z << endl;
			pt[iStart + i].set(x, y, z); // 17
			idp++;
		}
		pt[idp].set(pt[0].x, pt[0].y, pt[0].z);
		idp++;
		//cout << "=================" << endl;
		iCount = idp;
		iStart = 0;
		face[idx].nVerts = iCount;
		face[idx].vert = new VertexID[face[idx].nVerts];
		for (int i = 0; i < iCount; i++)
		{
			face[idx].vert[i].vertIndex = iStart + i;
			//cout << pt[iStart+i].printPoint3() << endl;
		}
		//cout << "======= END ======" << endl;
		idx++;
	}
	//mat tren
	{
		iStart = idp;
		iCount = 0;
		float iStop;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * -sin(fAngle * i);
			z = fRadius * -cos(fAngle * i);
			y = fHeight;
			//cout << x << ";" << y << ";" << z << endl;
			pt[iStart + i].set(x, y, z); // 17
			idp++;
			iCount++;
		}
		int iStart2 = idp;
		for (int i = 0; i <= nSegment; i++)
		{
			x = fRadius * sin(fAngle * i) + fLength;
			z = fRadius * cos(fAngle * i);
			y = fHeight;
			//cout << x << ";" << y << ";" << z << endl;
			pt[iStart2 + i].set(x, y, z); // 17
			idp++;
			iCount++;
		}
		pt[idp].set(pt[iStart].x, pt[iStart].y, pt[iStart].z);
		idp++;
		//cout << "=================" << endl;
		iCount++;
		//cout << "Count: " << iCount << endl;
		face[idx].nVerts = iCount;
		face[idx].vert = new VertexID[face[idx].nVerts];
		for (int i = 0; i < iCount; i++)
		{
			face[idx].vert[i].vertIndex = iStart + i;
			//cout << pt[iStart+i].printPoint3() << endl;
		}
		//cout << "======= END ======" << endl;
		idx++;
	}
	//xung quang
	{
		iStart = 0;
		int iStart2 = 2 * nSegment + 3;
		iCount = 2 * nSegment + 2;
		for (int i = 0; i < iCount; i++)
		{
			face[idx].nVerts = 4;
			face[idx].vert = new VertexID[face[idx].nVerts];
			face[idx].vert[0].vertIndex = iStart + i;
			face[idx].vert[1].vertIndex = iStart2 + i;
			face[idx].vert[2].vertIndex = iStart2 + i + 1;
			face[idx].vert[3].vertIndex = iStart + i + 1;
			idx++;
		}
	}
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int ic = face[f].vert[v].colorIndex;
			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
			glNormal3f(face[f].vtNewell.x, face[f].vtNewell.y, face[f].vtNewell.z);
		}
		glEnd();
	}
}


void Mesh::Draw(int chooseColor)
{
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
			glNormal3f(face[f].vtNewell.x, face[f].vtNewell.y, face[f].vtNewell.z);
		}
		glEnd();
	}
}

void Mesh::addMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void Mesh::SetColor(int colorIdx)
{
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::vectorNewell()
{
	for (int f = 0; f < numFaces; f++)
	{
		//float mx = 0, my = 0, mz = 0;
		float vectorN[] = { 0,0,0 };
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			vectorN[0] += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			vectorN[1] += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			vectorN[2] += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].vtNewell.set(vectorN[0], vectorN[1], vectorN[2]);
		face[f].vtNewell.normalize();
	}
}

/// <summary>
/// Main Program
/// </summary>

/// <summary>
/// ================================================================================
/// </summary>

/// <summary>
/// ================================================================================
/// </summary>

/// <summary>
/// ================================================================================
/// </summary>

int		screenWidth = 1200;
int		screenHeight = 600;

Mesh rectangular;
Mesh shape1;
Mesh shape2;
Mesh shape3;
Mesh shape4;
Mesh shape5;
Mesh cylinder;

int		nChoice = 1;

float camera_dis = 4.5;
float camera_height = 2;
float camera[3];
float cameraState[7];
bool lightState = true;
GLfloat camera_angle = 30.0;

GLfloat	fHalfSize = 8;
GLfloat fConstFS = fHalfSize;

void OnKeyboard(unsigned char key, int x, int y);
void OnKeySpecial(int key, int x, int y);
void updatePosCamera();

float* vectorNewell(float iVector[10][3], int n)
{
	float vectorResult[] = { 0,0,0 };
	for (int i = 0; i < n; i++)
	{
		vectorResult[0] += (iVector[i][1] - iVector[(i + 1) % n][1]) * (iVector[i][2] + iVector[(i + 1) % n][2]);
		vectorResult[1] += (iVector[i][2] - iVector[(i + 1) % n][2]) * (iVector[i][0] + iVector[(i + 1) % n][0]);
		vectorResult[2] += (iVector[i][0] - iVector[(i + 1) % n][0]) * (iVector[i][1] + iVector[(i + 1) % n][1]);
	}
	return vectorResult;
}

void rotateCamera(int value)
{
	camera_angle += (GLfloat)value;
	if (camera_angle > 360) camera_angle = camera_angle - 360.0f;
	camera[0] = camera_dis * cos(DEG2RAD * camera_angle);
	camera[2] = camera_dis * sin(DEG2RAD * camera_angle);
	glutTimerFunc(10, rotateCamera, 1);
	glutPostRedisplay();
}

void drawAxis()
{
	float lengthAxis = 20;
	// Truc toa do Oxyz
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1); //Ox, blue
	glVertex3f(0, 0, 0);
	glVertex3f(lengthAxis, 0, 0);

	glColor3f(0, 1, 0); //Oy, green 
	glVertex3f(0, 0, 0);
	glVertex3f(0, lengthAxis, 0);

	glColor3f(1, 0, 0); //Oz, red
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, lengthAxis);
	glEnd();
}
void drawLucGiac(float x, float y, float z, float R, float alpha)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(-60 * PI / 180), y, z + R * sin(-60 * PI / 180));
	glVertex3f(x + R * cos(0), y, z + R * sin(0));
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(77.0 / 255.0, 166.0 / 255.0, 210.0 / 255.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x + R * cos(120 * PI / 180), y, z + R * sin(120 * PI / 180));
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x + R * cos(240 * PI / 180), y, z + R * sin(240 * PI / 180));
	glVertex3f(x + R * cos(300 * PI / 180), y, z + R * sin(300 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
}

void drawNen(float alpha)
{
	float y = 0;
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	float d = 0.7, R = d / cos(PI / 6);
	int i = 0;
	for (float x = -30; x < 30; x += R + R * cos(PI / 3))
	{
		float z = (i % 2 == 0) ? -20 : (-20 - d);
		for (; z < 20; z += 2 * d)
			drawLucGiac(x, y, z, R, alpha);
		i++;
	}
	glEnable(GL_LIGHTING);
}
void DrawDe()
{
	glPushMatrix();

	glTranslatef(-3, 0, -7.5); // di chuyen goc toa do
	if (nChoice == 0)
	{
		rectangular.DrawWireframe();
	}
	else
	{
		rectangular.DrawColor();
		//rectangular.Draw(0);
	}
	glTranslatef(3, 0, 7.5); // tra lai goc toa do ban dau

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	rectangular.addMaterial(ambient, diffuse, specular, shininess);
	glPopMatrix();
}
void DrawGiaDo1()
{
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glTranslatef(1, -1, 1);
	

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape3.addMaterial(ambient, diffuse, specular, shininess);

	if (nChoice == 0)
	{
		shape3.DrawWireframe();
	}
	else
	{
		shape3.DrawColor();
		//shape3.Draw(9);
	}
	glTranslatef(-1, 1, -1);
	glRotatef(-90, 0, 0, 1);

	glPopMatrix();
}
void DrawGiaDo2()
{
	glPushMatrix();
	
	glRotatef(-90, 1, 0, 0);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-6.25, 0, 1);
	if (nChoice == 0)
	{
		shape4.DrawWireframe();
	}
	else
	{
		shape4.DrawColor();
		//shape4.Draw(9);
	}
	glTranslatef(6.25, 0, -1);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape4.addMaterial(ambient, diffuse, specular, shininess);
	glPopMatrix();
}
void DrawLuoiDao()
{
	glPushMatrix();

	glRotatef(90, 0, 0, 1);
	glRotatef(5, 0, 1, 0);
	glTranslatef(1.8, 0, -1.7);
	if (nChoice == 0)
	{
		shape1.DrawWireframe();
	}
	else
	{
		shape1.DrawColor();
		//shape1.Draw(2);
	}
	glTranslatef(-1.8, 0, 1.7);
	glRotatef(-5, 0, 1, 0);
	glRotatef(-90, 0, 0, 1);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape1.addMaterial(ambient, diffuse, specular, shininess);
	glPopMatrix();
}
void DrawCanDao()
{
	glPushMatrix();

	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(1.3, -1, -4.2);
	glRotatef(30, 0, 1, 0);
	if (nChoice == 0)
	{
		shape2.DrawWireframe();
	}
	else
	{
		shape2.DrawColor();
		//shape2.Draw(1);
	}
	glRotatef(-30, 0, 1, 0);
	glTranslatef(-1.3, 1, 4.2);
	glRotatef(-90, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape2.addMaterial(ambient, diffuse, specular, shininess);
	glPopMatrix();
}
void DrawTayNoi()
{
	glPushMatrix();

	glRotatef(90, 0, 0, 1);
	glRotatef(5, 0, 1, 0);
	glTranslatef(2.5, -1, -0.9);
	if (nChoice == 0)
	{
		shape5.DrawWireframe();
	}
	else
	{
		shape5.DrawColor();
		//shape5.Draw(4);
	}
	glTranslatef(-2.5, 1, 0.9);
	glRotatef(-5, 0, 1, 0);
	glRotatef(-90, 0, 0, 1);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	shape5.addMaterial(ambient, diffuse, specular, shininess);
	glPopMatrix();
}
void DrawChot1()
{
	glPushMatrix();

	glRotatef(90, 0, 0, 1);
	glTranslatef(2.55, 0, 1.87);
	if (nChoice == 0)
	{
		cylinder.DrawWireframe();
	}
	else
	{
		cylinder.DrawColor();
		//cylinder.Draw(6);
	}
	glTranslatef(-2.55, 0, -1.87);
	glRotatef(-90, 0, 0, 1);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cylinder.addMaterial(ambient, diffuse, specular, shininess);
	glPopMatrix();
}
void DrawChot2()
{
	glPushMatrix();

	glRotatef(90, 0, 0, 1);
	glTranslatef(5.15, 0, -3.4);
	if (nChoice == 0)
	{
		cylinder.DrawWireframe();
	}
	else
	{
		cylinder.DrawColor();
		//cylinder.Draw(6);
	}
	glTranslatef(-5.15, 0, 3.4);
	glRotatef(-90, 0, 0, 1);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cylinder.addMaterial(ambient, diffuse, specular, shininess);
	glPopMatrix();
}

void DrawObject()
{
	drawAxis();
	glColor3f(0, 0, 0);
	DrawDe();
	DrawGiaDo1();
	DrawGiaDo2();
	DrawCanDao();
	DrawLuoiDao();
	DrawTayNoi();
	DrawChot1();
	DrawChot2();

	/*
	if (nChoice == 0)
	{
		glTranslatef(-3, 0, -7.5); // di chuyen goc toa do
		rectangular.DrawWireframe();
		//rectangular.DrawColor();
		glTranslatef(3, 0, 7.5); // tra lai goc toa do ban dau

		glRotatef(90, 0, 0, 1);
		glRotatef(5, 0, 1, 0);
		glTranslatef(1.8, 0, -1.7);
		shape1.DrawWireframe();
		//shape1.DrawColor();
		glTranslatef(-1.8, 0, 1.7);
		glRotatef(-5, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);

		glRotatef(90, 0, 0, 1);
		glTranslatef(1, -1, 1);
		shape3.DrawWireframe();
		//shape3.DrawColor();
		glTranslatef(-1, 1, -1);
		glRotatef(-90, 0, 0, 1);

		glRotatef(90, 0, 0, 1);
		glRotatef(5, 0, 1, 0);
		glTranslatef(2.5, -1, -0.9);
		shape5.DrawWireframe();
		//shape5.DrawColor();
		glTranslatef(-2.5, 1, 0.9);
		glRotatef(-5, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);

		glRotatef(-90, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		glTranslatef(-6.25, 0, 1);
		shape4.DrawWireframe();
		//shape4.DrawColor();
		glTranslatef(6.25, 0, -1);
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 1, 0, 0);

		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glTranslatef(1.3, -1, -4.2);
		glRotatef(30, 0, 1, 0);
		shape2.DrawWireframe();
		//shape2.DrawColor();
		glRotatef(-30, 0, 1, 0);
		glTranslatef(-1.3, 1, 4.2);
		glRotatef(-90, 1, 0, 0);
		glRotatef(-90, 0, 1, 0);

		glRotatef(90, 0, 0, 1);
		glTranslatef(2.55, 0, 1.87);
		cylinder.DrawWireframe(); //chot 1
		glTranslatef(-2.55, 0, -1.87);
		glRotatef(-90, 0, 0, 1);

		glRotatef(90, 0, 0, 1);
		glTranslatef(5.15, 0, -3.4);
		cylinder.DrawWireframe(); //chot 2
		glTranslatef(-5.15, 0, 3.4);
		glRotatef(-90, 0, 0, 1);

		glRotatef(90, 0, 0, 1);
		glTranslatef(2, 0, -1.5);
		cylinder.DrawWireframe(); //chot 3
		glTranslatef(-5.15, 0, 3.4);
		glRotatef(-90, 0, 0, 1);
	}
	else if (nChoice == 1)
	{
		glTranslatef(-3, 0, -7.5); // di chuyen goc toa do
		//rectangular.DrawWireframe();
		rectangular.DrawColor(0);
		glTranslatef(3, 0, 7.5); // tra lai goc toa do ban dau

		glRotatef(90, 0, 0, 1);
		glRotatef(5, 0, 1, 0);
		glTranslatef(1.8, 0, -1.7);
		//shape1.DrawWireframe();
		shape1.DrawColor(2);
		glTranslatef(-1.8, 0, 1.7);
		glRotatef(-5, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);

		glRotatef(90, 0, 0, 1);
		glTranslatef(1, -1, 1);
		//shape3.DrawWireframe();
		shape3.DrawColor(9);
		glTranslatef(-1, 1, -1);
		glRotatef(-90, 0, 0, 1);

		glRotatef(90, 0, 0, 1);
		glRotatef(5, 0, 1, 0);
		glTranslatef(2.5, -1, -0.9);
		//shape5.DrawWireframe();
		shape5.DrawColor(4);
		glTranslatef(-2.5, 1, 0.9);
		glRotatef(-5, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);

		glRotatef(-90, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		glTranslatef(-6.25, 0, 1);
		//shape4.DrawWireframe();
		shape4.DrawColor(9);
		glTranslatef(6.25, 0, -1);
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 1, 0, 0);

		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glTranslatef(1.3, -1, -4.2);
		glRotatef(30, 0, 1, 0);
		//shape2.DrawWireframe();
		shape2.DrawColor(1);
		glRotatef(-30, 0, 1, 0);
		glTranslatef(-1.3, 1, 4.2);
		glRotatef(-90, 1, 0, 0);
		glRotatef(-90, 0, 1, 0);

		glRotatef(90, 0, 0, 1);
		glTranslatef(2.55, 0, 1.87);
		cylinder.DrawColor(6);
		glTranslatef(-2.55, 0, -1.87);
		glRotatef(-90, 0, 0, 1);

		glRotatef(90, 0, 0, 1);
		glTranslatef(5.15, 0, -3.4);
		cylinder.DrawColor(6);
		glTranslatef(-5.15, 0, 3.4);
		glRotatef(-90, 0, 0, 1);

	}
	*/
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	if (lightState == true)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera[0], camera[1], camera[2], 0, 0, 0, 0, 1, 0);
	glViewport(0, 0, screenWidth, screenHeight);

	glClearStencil(0);
	glClearDepth(1.0f);

	DrawObject();

	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	drawNen(1);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
	glScalef(1, -1, 1);
	DrawObject();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawNen(0.7f);
	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);

	glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);

}
void CreateObject()
{
	rectangular.CreateRectangular(15, 6, 1);
	rectangular.SetColor(0);
	rectangular.vectorNewell();

	shape1.CreateShape1(7, 1.25, 1, 1);
	shape1.SetColor(2);
	shape1.vectorNewell();

	shape2.CreateShape2(8, 0.75, 2, 0.5, 1);
	shape2.SetColor(1);
	shape2.vectorNewell();

	shape3.CreateShape3(5.25, 3.5, 1, 1, 0.5);
	shape3.SetColor(9);
	shape3.vectorNewell();

	shape4.CreateShape4(3, 4.3, 1, 0.53);
	shape4.SetColor(9);
	shape4.vectorNewell();

	shape5.CreateShape5(1.75, 1.5, 1);
	shape5.SetColor(4);
	shape5.vectorNewell();

	cylinder.CreateCylinder(36, 2.2, 0.25);
	cylinder.SetColor(6);
	cylinder.vectorNewell();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Huynh Pham Phuoc Linh - MSSV: 1710165"); // open the screen window
	
	cout << "1, 2: Xoay can dao" << endl;
	cout << "W, w: Chuyen doi qua lai giua che do khung day va to mau" << endl;
	cout << "V, v: Chuyen doi qua lai giua hai che do nhin khac nhau" << endl;
	cout << "+   : Tang khoang cach camera" << endl;
	cout << "-   : Giam khoang cach camera" << endl;
	cout << "up arrow  : Tang chieu cao camera" << endl;
	cout << "down arrow: Giam chieu cao camera" << endl;
	cout << "<-        : Quay camera theo chieu kim dong ho" << endl;
	cout << "->        : Quay camera nguoc chieu kim dong ho" << endl;
	
	camera[0] = camera_dis * cos(DEG2RAD * camera_angle);
	camera[1] = camera_height;
	camera[2] = camera_dis * sin(DEG2RAD * camera_angle);
	cameraState[6] = 0;
	lightState = true;

	CreateObject();

	glutKeyboardFunc(OnKeyboard);
	glutSpecialFunc(OnKeySpecial);

	myInit();

	glutDisplayFunc(myDisplay);
	//glutTimerFunc(100, rotateCamera, 10);
	glutMainLoop();
	return 0;
}
void updatePosCamera()
{
	camera[0] = camera_dis * cos(DEG2RAD * camera_angle);
	camera[1] = camera[1];
	camera[2] = camera_dis * sin(DEG2RAD * camera_angle);
}
void OnKeySpecial(int key, int x, int y)
{
	//cout << key << endl;
	if (cameraState[6] == 1)
	{
		return;
	}
	switch (key)
	{
	case GLUT_KEY_LEFT:
	{
		camera_angle++;
		if (camera_angle > 360) camera_angle = camera_angle - 360.0f;
		updatePosCamera();
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		camera_angle--;
		if (camera_angle < 0) camera_angle = 360.0f;
		updatePosCamera();
		break;
	}
	case GLUT_KEY_UP:
	{
		if (fHalfSize >= fConstFS / 2 && camera[1] < 0)
		{
			fHalfSize -= 0.1;
			camera[1] += 0.1;
		}
		else
		{
			fHalfSize += 0.1;
			camera[1] += 0.1;
		}
		//glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);
		myInit();
		break;
	}
	case GLUT_KEY_DOWN:
	{
		if (fHalfSize >= fConstFS / 2 && camera[1] >= 0)
		{
			fHalfSize -= 0.1;
			camera[1] -= 0.1;
		}
		else
		{
			fHalfSize += 0.1;
			camera[1] -= 0.1;
		}
		//glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);
		myInit();
		break;
	}
	default:
		break;
	}
	glutPostRedisplay();
}
void OnKeyboard(unsigned char key, int x, int y)
{
	//cout << key << endl;
	if (key == 'w' || key == 'W')
	{
		nChoice = (nChoice + 1) % 2;
	}
	else if (key == 'v' || key == 'V')
	{
		cameraState[6] = ((int)cameraState[6] + 1) % 2;
		if (cameraState[6] == 0)
		{
			camera[0] = cameraState[0];
			camera[1] = cameraState[1];
			camera[2] = cameraState[2];
			lightState = true;
		}
		else
		{
			cameraState[0] = camera[0];
			cameraState[1] = camera[1];
			cameraState[2] = camera[2];
			cameraState[3] = 2;
			cameraState[4] = 0;
			cameraState[5] = 0;

			camera[0] = cameraState[3];
			camera[1] = cameraState[4];
			camera[2] = cameraState[5];

			fHalfSize = 7;
			lightState = false;
			//glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);
			myInit();
		}
	}
	else if (key == 'd' || key == 'D')
	{
		lightState = !lightState;
	}
	else if (key == '-' && cameraState[6] != 1)
	{
		if (camera_dis >= 0)
		{
			camera_dis += 0.1;
			fHalfSize += 0.1;
		}
		else
		{
			camera_dis += 0.1;
			fHalfSize -= 0.1;
		}
		updatePosCamera();
		//glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);
		myInit();
	}
	else if (key == '+' && cameraState[6] != 1)
	{
		if (camera_dis < 0)
		{
			camera_dis -= 0.1;
			fHalfSize += 0.1;
		}
		else
		{
			camera_dis -= 0.1;
			fHalfSize -= 0.1;
		}
		updatePosCamera();
		//glOrtho(-fHalfSize * 2, fHalfSize * 2, -fHalfSize / 2, fHalfSize + fHalfSize / 2, -1000, 1000);
		myInit();
	}
	glutPostRedisplay();
}
