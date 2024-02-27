#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateSquare1(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 1), color),
		VertexFormat(corner + glm::vec3(length, length, 1), color),
		VertexFormat(corner + glm::vec3(0, length, 1), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// Draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* object2D::CreateRhombus(
	const std::string &name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(length / 2, 0, 1), color),
        VertexFormat(corner + glm::vec3(0, length / 2, 1), color),
        VertexFormat(corner + glm::vec3(-length / 2, 0, 1), color),
        VertexFormat(corner + glm::vec3(0, -length / 2, 1), color)
    };

	Mesh* rhombus = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rhombus->SetDrawMode(GL_LINE_LOOP);
	} else {
		// Draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rhombus->InitFromData(vertices, indices);
	return rhombus;
}

// Raza = (pe OX) (scale_star = 1.5) * 20 = 30
Mesh* object2D::CreateStar(
	const std::string &name,
	glm::vec3 color,
	glm::vec3 color1,
	bool fill)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-2, 4, 2), color),
		VertexFormat(glm::vec3(0, 10, 2), color1),
		VertexFormat(glm::vec3(2, 4, 2), color),
		VertexFormat(glm::vec3(10, 2, 2), color1),
		VertexFormat(glm::vec3(4, -2, 2), color),
		VertexFormat(glm::vec3(6, -8, 2), color1),
		VertexFormat(glm::vec3(0, -4, 2), color),
		VertexFormat(glm::vec3(-6, -8, 2), color1),
		VertexFormat(glm::vec3(-4, -2, 2), color),
		VertexFormat(glm::vec3(-10, 2, 2), color1)
	};

	Mesh* star = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7 };

	if (!fill) {
		star->SetDrawMode(GL_LINE_LOOP);
	} else {
		indices = {
			0, 1, 2,
			2, 3, 4,
			4, 5, 6,
			6, 7, 8,
			8, 9, 0,
			0, 2, 8,
			2, 4, 8,
			4, 6, 8
		};
	}

	star->InitFromData(vertices, indices);
	return star;
}
// create hexagon mesh
// Raza = (pe OX) 90
Mesh* object2D::CreateHexagon(
	const std::string &name,
	glm::vec3 color,
	bool fill)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-22.5f, -39, 1), color),
		VertexFormat(glm::vec3(22.5f, -39, 1), color),
		VertexFormat(glm::vec3(45, 0, 1), color),
		VertexFormat(glm::vec3(22.5f, 39, 1), color),
		VertexFormat(glm::vec3(-22.5f, 39, 1), color),
		VertexFormat(glm::vec3(-45, 0, 1), color)
	};

	Mesh* hexagon = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5 };

	if (!fill) {
		hexagon->SetDrawMode(GL_LINE_LOOP);
	} else {
		indices = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5
		};
	}

	hexagon->InitFromData(vertices, indices);
	return hexagon;
}


// Raza = (pe OX) 72
Mesh* object2D::CreateHexagon1(
	const std::string& name,
	glm::vec3 color,
	bool fill)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-22, -31.2f, 1), color),
		VertexFormat(glm::vec3(22, -31.2f, 1), color),
		VertexFormat(glm::vec3(36, 0, 1), color),
		VertexFormat(glm::vec3(22, 31.2f, 1), color),
		VertexFormat(glm::vec3(-22, 31.2f, 1), color),
		VertexFormat(glm::vec3(-36, 0, 1), color)
	};

	Mesh* hexagon = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5 };

	if (!fill) {
		hexagon->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5
		};
	}

	hexagon->InitFromData(vertices, indices);
	return hexagon;
}

// Raza = (pe OX) 10
Mesh* object2D::CreateHeart(
	const std::string& name,
	glm::vec3 color,
	bool fill)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 3), color),
		VertexFormat(glm::vec3(0, 3, 3), color),
		VertexFormat(glm::vec3(2.5f, 5, 3), color),
		VertexFormat(glm::vec3(5, 3, 3), color),
		VertexFormat(glm::vec3(5, 0, 3), color),
		VertexFormat(glm::vec3(2.5f, -3, 3), color),
		VertexFormat(glm::vec3(0, -5, 3), color),
		VertexFormat(glm::vec3(-2.5f, -3, 3), color),
		VertexFormat(glm::vec3(-5, 0, 3), color),
		VertexFormat(glm::vec3(-5, 3, 3), color),
		VertexFormat(glm::vec3(-2.5f, 5, 3), color),

		VertexFormat(glm::vec3(-2.5f, 3, 3), color),
		VertexFormat(glm::vec3(0, -3, 3), color),
		VertexFormat(glm::vec3(0, -3, 3), color),
		VertexFormat(glm::vec3(0, 3, 3), color),
		VertexFormat(glm::vec3(2.5f, 3, 3), color)
	};

	Mesh* hexagon = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
											10, 11, 12, 13, 14, 15};

	if (!fill) {
		hexagon->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices = {
			1, 2, 15,
			2, 15, 3,
			3, 15, 14,
			3, 4, 14,
			1, 15, 14,
			1, 0, 14,
			4, 14, 5,
			0, 14, 13,
			14, 5, 13,
			5, 6, 13,

			7, 13, 6,
			12, 13, 7,
			12, 0, 13,
			1, 0, 12,
			8, 12, 7,
			9, 12, 8,
			11, 1, 12,
			9, 11, 12,
			10, 11, 9,
			10, 1, 11
		};
	}

	hexagon->InitFromData(vertices, indices);
	return hexagon;
}