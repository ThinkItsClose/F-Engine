#include "Primitive.h"

// Define the vertices as arrays then convert them because the conversion is only done once and writing the vertices down in an array is alot easier
std::vector<Vertex> ArrayToVector(Vertex* arr, unsigned int size) {
	std::vector<Vertex> result;
	for (unsigned int index = 0; index < size / sizeof(Vertex); index++) {
		result.push_back(arr[index]);
	}
	return result;
}

std::vector<unsigned int> ArrayToVector(unsigned int* arr, unsigned int size) {
	std::vector<unsigned int> result;
	for (unsigned int index = 0; index < size / sizeof(unsigned int); index++) {
		result.push_back(arr[index]);
	}
	return result;
}

// Quad mesh definition
Mesh QuadPrimitive::GetMesh() {

	Vertex vertexArray[4 * sizeof(Vertex)] = {
		glm::vec3(-0.5, 0.5, 0.5),  glm::vec2(0, 1), glm::vec3(0, 0, 1), glm::vec3(),
		glm::vec3(0.5, 0.5, 0.5),   glm::vec2(1, 1), glm::vec3(0, 0, 1), glm::vec3(),
		glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0, 0), glm::vec3(0, 0, 1), glm::vec3(),
		glm::vec3(0.5, -0.5, 0.5),  glm::vec2(1, 0), glm::vec3(0, 0, 1), glm::vec3()
	};
	unsigned int indicesArray[2 * 3] = {
		0, 3, 1,
		0, 2, 3
	};

	// Calculate the tangents
	// Temporary placement for now

	int faces = 1;
	int vertiesPerFace = 4;
	int trianglesPerFace = 2;
	// Calculate the tangents
	for (int face = 0; face < faces; face++) {
		int index = face * vertiesPerFace;

		glm::vec3 pos1 = vertexArray[index + 0].position;
		glm::vec3 pos2 = vertexArray[index + 1].position;
		glm::vec3 pos3 = vertexArray[index + 2].position;

		glm::vec2 uv1 = vertexArray[index + 0].textureCoordinate;
		glm::vec2 uv2 = vertexArray[index + 1].textureCoordinate;
		glm::vec2 uv3 = vertexArray[index + 2].textureCoordinate;

		glm::vec3 edge1 = pos2 - pos1;
		glm::vec3 edge2 = pos3 - pos1;
		glm::vec2 deltaUV1 = uv2 - uv1;
		glm::vec2 deltaUV2 = uv3 - uv1;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		glm::vec3 tangent1;
		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent1 = glm::normalize(tangent1);

		for (int vertex = 0; vertex < vertiesPerFace; vertex++) {
			vertexArray[index + vertex].tangent = tangent1;
		}
	}

	std::vector<Vertex> vertices = ArrayToVector(vertexArray, sizeof(vertexArray));
	std::vector<unsigned int> indices = ArrayToVector(indicesArray, sizeof(indicesArray));
	return Mesh(vertices, indices);
}

// Cube mesh definition
Mesh CubePrimitive::GetMesh() {
	Vertex vertexArray[6 * 4 * sizeof(Vertex)] = {
		// Front face
		glm::vec3(-0.5, 0.5, 0.5),  glm::vec2(0, 1), glm::vec3(0, 0, 1),  glm::vec3(),
		glm::vec3(0.5, 0.5, 0.5),   glm::vec2(1, 1), glm::vec3(0, 0, 1),  glm::vec3(),
		glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0, 0), glm::vec3(0, 0, 1),  glm::vec3(),
		glm::vec3(0.5, -0.5, 0.5),  glm::vec2(1, 0), glm::vec3(0, 0, 1),  glm::vec3(),

		// Back face
		glm::vec3(-0.5, 0.5, -0.5), glm::vec2(1, 1), glm::vec3(0, 0, -1), glm::vec3(),
		glm::vec3(0.5, 0.5, -0.5),  glm::vec2(0, 1), glm::vec3(0, 0, -1), glm::vec3(),
		glm::vec3(-0.5, -0.5, -0.5),glm::vec2(1, 0), glm::vec3(0, 0, -1), glm::vec3(),
		glm::vec3(0.5, -0.5, -0.5), glm::vec2(0, 0), glm::vec3(0, 0, -1), glm::vec3(),

		// Top Face
		glm::vec3(-0.5, 0.5, 0.5),  glm::vec2(0, 1),  glm::vec3(0, 1, 0), glm::vec3(),
		glm::vec3(0.5, 0.5, 0.5),   glm::vec2(1, 1),  glm::vec3(0, 1, 0), glm::vec3(),
		glm::vec3(-0.5, 0.5, -0.5), glm::vec2(0, 0),  glm::vec3(0, 1, 0), glm::vec3(),
		glm::vec3(0.5, 0.5, -0.5),  glm::vec2(1, 0),  glm::vec3(0, 1, 0), glm::vec3(),

		// Bottom Face
		glm::vec3(-0.5, -0.5, 0.5),  glm::vec2(0, 1),  glm::vec3(0, -1, 0), glm::vec3(),
		glm::vec3(0.5, -0.5, 0.5),   glm::vec2(1, 1),  glm::vec3(0, -1, 0), glm::vec3(),
		glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0, 0),  glm::vec3(0, -1, 0), glm::vec3(),
		glm::vec3(0.5, -0.5, -0.5),  glm::vec2(1, 0),  glm::vec3(0, -1, 0), glm::vec3(),

		// Left Face
		glm::vec3(-0.5, -0.5, -0.5),  glm::vec2(0, 0),  glm::vec3(-1, 0, 0), glm::vec3(),
		glm::vec3(-0.5, 0.5, -0.5),   glm::vec2(0, 1),  glm::vec3(-1, 0, 0), glm::vec3(),
		glm::vec3(-0.5, -0.5, 0.5),   glm::vec2(1, 0),  glm::vec3(-1, 0, 0), glm::vec3(),
		glm::vec3(-0.5, 0.5, 0.5),    glm::vec2(1, 1),  glm::vec3(-1, 0, 0), glm::vec3(),

		// Right Face
		glm::vec3(0.5, -0.5, 0.5),   glm::vec2(0, 0),  glm::vec3(1, 0, 0), glm::vec3(),
		glm::vec3(0.5, 0.5, 0.5),    glm::vec2(0, 1),  glm::vec3(1, 0, 0), glm::vec3(),
		glm::vec3(0.5, -0.5, -0.5),  glm::vec2(1, 0),  glm::vec3(1, 0, 0), glm::vec3(),
		glm::vec3(0.5, 0.5, -0.5),   glm::vec2(1, 1),  glm::vec3(1, 0, 0), glm::vec3()
	};
	unsigned int indicesArray[6 * 2 * 3] = {
		// Front
		0, 3, 1,
		0, 2, 3,

		// Back
		4, 5, 7,
		4, 7, 6,

		// Top
		8, 9, 11,
		8, 11, 10,

		// Bottom
		12, 15, 13,
		12, 14, 15,

		// Left
		16, 19, 17,
		16, 18, 19,

		// Right
		20, 23, 21,
		20, 22, 23
	};

	std::vector<Vertex> vertices = ArrayToVector(vertexArray, sizeof(vertexArray));
	std::vector<unsigned int> indices = ArrayToVector(indicesArray, sizeof(indicesArray));
	return Mesh(vertices, indices);
}

// Sphere mesh definition
Mesh SpherePrimitive::GetMesh() {

	// Credit to http://www.songho.ca/opengl/gl_sphere.html
	// Might refactor into my own code eventually

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	float radius = 0.5;
	float sectorCount = 64;
	float stackCount = 64;
	float lengthInv = 1.0f / radius;
	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float x, y, z, xy, nx, ny, nz, s, t, sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i) {
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			glm::vec3 position = glm::vec3(x, z, y); // x, z, y because the sphere is calculated using the z axis as the y axis, might reformat to clear up later on

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			glm::vec2 textureCoordinate = glm::vec2(s, t);

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;

			glm::vec3 normal = glm::vec3(nx, nz, ny);
			Vertex vertex;
			vertex.position = position;
			vertex.textureCoordinate = textureCoordinate;
			vertex.normal = normal;
			vertex.tangent = glm::vec3(0, 0, 0);

			vertices.push_back(vertex);
		}
	}

	// generate CCW index list of sphere triangles
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
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	return Mesh(vertices, indices);
}