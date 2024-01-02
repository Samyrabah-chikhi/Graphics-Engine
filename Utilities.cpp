#include "Utilities.h"


void generateSphereIndices(std::vector<int>* indices, std::vector<int>* lineIndices, int stackCount, int sectorCount) {

	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices->push_back(k1);
				indices->push_back(k2);
				indices->push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices->push_back(k1 + 1);
				indices->push_back(k2);
				indices->push_back(k2 + 1);
			}

			// store indices for lines
			// vertical lines for all stacks, k1 => k2
			if (lineIndices != NULL) {

				lineIndices->push_back(k1);
				lineIndices->push_back(k2);
				if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
				{
					lineIndices->push_back(k1);
					lineIndices->push_back(k1 + 1);
				}
			}
		}
	}

}

void generateSphereVertex(std::vector<float>* vertex, std::vector<float>* normals, std::vector<float>* textures, float radius, int stackCount, int sectorCount) {

	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord

	float sectorStep = 2 * M_PI / sectorCount;
	float stackStep = M_PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertex->push_back(x);
			vertex->push_back(y);
			vertex->push_back(z);

			// normalized vertex normal (nx, ny, nz)
			if (normals != NULL) {
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				normals->push_back(nx);
				normals->push_back(ny);
				normals->push_back(nz);
			}

			// vertex tex coord (s, t) range between [0, 1]
			if (textures != NULL) {
				s = (float)j / sectorCount;
				t = (float)i / stackCount;
				textures->push_back(s);
				textures->push_back(t);
			}
		}
	}
}
