#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <random>

#include "lab_m1/Tema1/object2D.h"
#include "Colors.h"
#include "lab_m1/Tema1/transform2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = 0;           // logic x
	logicSpace.y = 0;           // logic y
	logicSpace.width = 1280;    // logic width
	logicSpace.height = 720;    // logic height

	// initialize the hexagons
	for (int i = 0; i < 4; i++) {
		hexagons[i].HexaMatrix = visMatrix * transform2D::Translate(1380, 0) * transform2D::Scale(0, 0);
		hexagons[i].lane = rand() % 3;
		hexagons[i].translateX = 0;
		hexagons[i].colour = i;
		hexagons[i].alive = -1;
	}
	stars = std::vector <struct star>(45);
	for (int l = 0; l < 45; l++) {
		stars[l].translateX = 0;
		stars[l].rotate = 0;
		stars[l].starMatrix = visMatrix;
	}

	shooters_matrix = std::vector <std::vector <struct Shooter>>(3, std::vector <struct Shooter>(3));

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			int rowx = first_rowx + i * dist_between;
			int rowy = first_rowy + j * dist_between;
			shooters_matrix[i][j].initX = rowx + 125 / 2;
			shooters_matrix[i][j].initY = rowy + 125 / 2;

			shooters_matrix[i][j].placed = -2;
			shooters_matrix[i][j].Matrix1 = visMatrix;
			shooters_matrix[i][j].Matrix2 = visMatrix;
			shooters_matrix[i][j].Matrix1 *= transform2D::Scale(0, 0);
			shooters_matrix[i][j].Matrix1 *= transform2D::Scale(0, 0);
		}

	glm::vec3 corner = glm::vec3(0, 0, 0);

	// square used for the cells - shade 1
	Mesh* square1 = object2D::CreateSquare("square1", corner, length, Cell_Color1, 1);
	AddMeshToList(square1);

	// square used for the cells - shade 2
	Mesh* square12 = object2D::CreateSquare("square12", corner, length, Cell_Color2, 1);
	AddMeshToList(square12);

	// square used for the cells - shade 3
	Mesh* square13 = object2D::CreateSquare("square13", corner, length, Cell_Color3, 1);
	AddMeshToList(square13);

	// square used for the rectangle behind the cells
	Mesh* square2 = object2D::CreateSquare("square2", corner, length, Plant, 1);
	AddMeshToList(square2);

	// square used for the cell for the rhombus
	Mesh* square3 = object2D::CreateSquare("square3", corner, length_S, Plant_Cell, 1);
	AddMeshToList(square3);

	// square used for the top of the screen
	Mesh* square4 = object2D::CreateSquare("square4", corner, length, Top, 1);
	AddMeshToList(square4);


	// create rhombus
	Mesh* rhombus = object2D::CreateRhombus("rhombus", corner, length / 2, Plant, 1);
	AddMeshToList(rhombus);

	// square used to be added under the rhombus to complete the 1st shooter
	Mesh* Shooter1 = object2D::CreateSquare1("Shooter1", corner, length, DarkRed, 1);
	AddMeshToList(Shooter1);

	// square used to be added under the rhombus to complete the 2nd shooter
	Mesh* Shooter2 = object2D::CreateSquare1("Shooter2", corner, length, DarkGreen, 1);
	AddMeshToList(Shooter2);

	// square used to be added under the rhombus to complete the 3rd shooter
	Mesh* Shooter3 = object2D::CreateSquare1("Shooter3", corner, length, DarkOrange, 1);
	AddMeshToList(Shooter3);

	// square used to be added under the rhombus to complete the 4th shooter
	Mesh* Shooter4 = object2D::CreateSquare1("Shooter4", corner, length, DarkBlue, 1);
	AddMeshToList(Shooter4);


	// create stars 
	Mesh* star = object2D::CreateStar("star", LightYellow, DarkYellow, 1);
	AddMeshToList(star);

	Mesh* starR = object2D::CreateStar("starR", Red, DarkRed, 1);
	AddMeshToList(starR);

	Mesh* starP = object2D::CreateStar("starP", Green, DarkGreen, 1);
	AddMeshToList(starP);

	Mesh* starO = object2D::CreateStar("starO", Orange, DarkOrange, 1);
	AddMeshToList(starO);

	Mesh* starB = object2D::CreateStar("starB", Blue, DarkBlue, 1);
	AddMeshToList(starB);

	Mesh* starG = object2D::CreateStar("starG", LightPink, Pink, 1);
	AddMeshToList(starG);

	Mesh* hexa1 = object2D::CreateHexagon("hexa1", DarkRed, 1);
	AddMeshToList(hexa1);

	Mesh* hexa1_s = object2D::CreateHexagon1("hexa1_s", Red, 1);
	AddMeshToList(hexa1_s);

	Mesh* hexa2 = object2D::CreateHexagon("hexa2", DarkGreen, 1);
	AddMeshToList(hexa2);

	Mesh* hexa2_s = object2D::CreateHexagon1("hexa2_s", Green, 1);
	AddMeshToList(hexa2_s);

	Mesh* hexa3 = object2D::CreateHexagon("hexa3", DarkOrange, 1);
	AddMeshToList(hexa3);

	Mesh* hexa3_s = object2D::CreateHexagon1("hexa3_s", Orange, 1);
	AddMeshToList(hexa3_s);

	Mesh* hexa4 = object2D::CreateHexagon("hexa4", DarkBlue, 1);
	AddMeshToList(hexa4);

	Mesh* hexa4_s = object2D::CreateHexagon1("hexa4_s", Blue, 1);
	AddMeshToList(hexa4_s);

	Mesh* heart = object2D::CreateHeart("heart", Red, 1);
	AddMeshToList(heart);
}


// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width),
		(float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw - the 1280 x 720 window
	viewSpace = ViewportSpace(0, 0, 1280, 720);
	SetViewportArea(viewSpace, glm::vec3(0), true);

	// Compute the 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

	DrawScene(visMatrix);

	// The viewport is now the right resolution so that the cursor can be rightfully detected
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0.5f), true);

	// Compute uniform 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
	DrawScene(visMatrix);

	current_time = glfwGetTime();

	if (lives) {
		// Render the rectangle behind the cells, which needs to be protected
		// by the enemies :(, using the original square mesh
		modelMatrix = visMatrix * transform2D::Translate(rect_x, rect_y);
		modelMatrix *= transform2D::Scale(0.5f, 3.8f);
		RenderMesh2D(meshes["square13"], shaders["VertexColor"], modelMatrix);

		if (current_time - last_time > attack_time && nr_hexa < 4) {
			for (int i = 0; i < 4; i++) {
				if (hexagons[i].alive == -1) {
					index = i;
					break;
				}
			}
			last_time = current_time;
			hexagons[index].alive = 3;
			hexagons[index].HexaMatrix = visMatrix * transform2D::Translate(1380, first_rowy +
				dist_between * hexagons[index].lane + 62.5);
			hexagons[index].translateX = 0;
			nr_hexa++;
		}

		for (int i = 0; i < 4; i++) {
			RenderMesh2D(meshes["hexa" + std::to_string(i + 1) + "_s"], shaders["VertexColor"], hexagons[i].HexaMatrix);
			RenderMesh2D(meshes["hexa" + std::to_string(i + 1)], shaders["VertexColor"], hexagons[i].HexaMatrix);
			// if the hexagon is still on the screen, translate it
			if (hexagons[i].alive > 0) {
				hexagons[i].translateX += deltaTimeSeconds * 1 / 32;
				if ((hexagons[i].HexaMatrix[2][0] - 31.25) >= 0) {
					hexagons[i].HexaMatrix *= transform2D::Translate(-hexagons[i].translateX, 0);
				}
				else {
					hexagons[i].alive = 0;
					lives--;
				}
			}
			else if (hexagons[i].alive == 0) {
				// slowly shrink the hexagon
				if (hexagons[i].HexaMatrix[0][0] > 0.5f) {
					hexagons[i].HexaMatrix *= transform2D::Scale(1 - deltaTimeSeconds, 1 - deltaTimeSeconds);
					hexagons[i].lane = rand() % 3;
					hexagons[i].translateX = 0;
				}
				else {
					hexagons[i].HexaMatrix = visMatrix * transform2D::Scale(0, 0);
					nr_hexa--;
					hexagons[i].alive = -1;
				}
			}
		}
		// picking up rhombus
		for (int i = 0; i < 4; i++) {
			if (shooters[i].pressed) {
				modelMatrix = visMatrix * transform2D::Translate(shooters[i].initX, shooters[i].initY);
				modelMatrix *= transform2D::Translate(shooters[i].moveX, shooters[i].moveY);
				RenderMesh2D(meshes["rhombus"], shaders["VertexColor"], modelMatrix);

				modelMatrix = visMatrix * transform2D::Translate(shooters[i].initX, shooters[i].initY - length_S * 0.1f);
				modelMatrix *= transform2D::Translate(shooters[i].moveX, shooters[i].moveY);
				modelMatrix *= transform2D::Scale(0.4f, 0.2f);

				switch (shooters[i].color) {
				case 0:
					RenderMesh2D(meshes["Shooter1"], shaders["VertexColor"], modelMatrix);
					break;
				case 1:
					RenderMesh2D(meshes["Shooter2"], shaders["VertexColor"], modelMatrix);
					break;
				case 2:
					RenderMesh2D(meshes["Shooter3"], shaders["VertexColor"], modelMatrix);
					break;
				case 3:
					RenderMesh2D(meshes["Shooter4"], shaders["VertexColor"], modelMatrix);
					break;
				}
			}
		}
		// filling the 3 x 3 cells
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (shooters_matrix[i][j].placed == 1) {
					RenderMesh2D(meshes["rhombus"], shaders["VertexColor"], shooters_matrix[i][j].Matrix1);
					switch (shooters_matrix[i][j].color) {
					case 0:
						RenderMesh2D(meshes["Shooter1"], shaders["VertexColor"], shooters_matrix[i][j].Matrix2);
						break;
					case 1:
						RenderMesh2D(meshes["Shooter2"], shaders["VertexColor"], shooters_matrix[i][j].Matrix2);
						break;
					case 2:
						RenderMesh2D(meshes["Shooter3"], shaders["VertexColor"], shooters_matrix[i][j].Matrix2);
						break;
					case 3:
						RenderMesh2D(meshes["Shooter4"], shaders["VertexColor"], shooters_matrix[i][j].Matrix2);
						break;
					}

					// if a hexagon is in the same lane as the shooter, shoot it
					for (int k = 0; k < 4; k++) {
						if (hexagons[k].alive > 0) {
							int x = hexagons[k].HexaMatrix[2][0];
							int y = hexagons[k].HexaMatrix[2][1];

							int y1 = shooters_matrix[i][j].initY;
							int y2 = shooters_matrix[i][j].initY + 100;
							if (x > shooters_matrix[i][j].initX && x <= 1280 && y >= y1 && y <= y2) {
								if (shooters_matrix[i][j].color == k && shooters_matrix[i][j].t_star < 5) {
									// shoot a star every 2 seconds
									if (current_time - shooters_matrix[i][j].t_star_last >= 2) {
										shooters_matrix[i][j].t_star_last = current_time;
										shooters_matrix[i][j].t_star++;
									}
								}
							}
							else if (x <= shooters_matrix[i][j].initX && y >= y1 && y <= y2) {
								shooters_matrix[i][j].placed = -1;
								// the shooter was hit by a hexagon, so it will be removed
							}
						}
					}

				}
				else if (shooters_matrix[i][j].placed == -1) {
					// slowly shrink the rhombus and the square under it
					shooters_matrix[i][j].Matrix1 *= transform2D::Scale(1 - deltaTimeSeconds, 1 - deltaTimeSeconds);
					shooters_matrix[i][j].Matrix2 *= transform2D::Scale(1 - deltaTimeSeconds, 1 - deltaTimeSeconds);
					RenderMesh2D(meshes["rhombus"], shaders["VertexColor"], shooters_matrix[i][j].Matrix1);
					switch (shooters_matrix[i][j].color) {
					case 0:
						RenderMesh2D(meshes["Shooter1"], shaders["VertexColor"], shooters_matrix[i][j].Matrix2);
						break;
					case 1:
						RenderMesh2D(meshes["Shooter2"], shaders["VertexColor"], shooters_matrix[i][j].Matrix2);
						break;
					case 2:
						RenderMesh2D(meshes["Shooter3"], shaders["VertexColor"], shooters_matrix[i][j].Matrix2);
						break;
					case 3:
						RenderMesh2D(meshes["Shooter4"], shaders["VertexColor"], shooters_matrix[i][j].Matrix2);
						break;
					}

					// if the rhombus is too small, remove it
					if (shooters_matrix[i][j].Matrix1[0][0] < 0.5f) {
						shooters_matrix[i][j].placed = -2;
					}
				}
				int nr_stars = shooters_matrix[i][j].t_star;
				int first = 5 * (i * 3 + j);

				for (int k = first; k < first + nr_stars; k++) {
					stars[k].translateX += deltaTimeSeconds * 100;
					stars[k].rotate += deltaTimeSeconds * 10;
					for (int l = 0; l < 5; l++) {
						// check if the star and hexagon collided
						if (hexagons[l].alive > 0) {
							int x = hexagons[l].HexaMatrix[2][0];
							int y = hexagons[l].HexaMatrix[2][1];

							int x1 = stars[k].starMatrix[2][0];
							int y1 = stars[k].starMatrix[2][1];

							if (x1 >= x - 31.25 && x1 <= x + 31.25 && y1 >= y - 31.25 && y1 <= y + 31.25) {
								if (l == shooters_matrix[i][j].color) {
									hexagons[l].alive--;
									// move this star to the back of the vector

									for (int m = first; m < first + nr_stars - 1; m++) {
										stars[m].translateX = stars[m + 1].translateX;
									}

									shooters_matrix[i][j].t_star--;
								}
							}
						}
					}

					if (stars[k].starMatrix[2][0] > 1380) {
						for (int m = first; m < first + nr_stars - 1; m++) {
							stars[m].translateX = stars[m + 1].translateX;
						}
						shooters_matrix[i][j].t_star--;
					}
					
					stars[k].starMatrix = visMatrix * transform2D::Translate(shooters_matrix[i][j].initX,
						shooters_matrix[i][j].initY);
					stars[k].starMatrix *= transform2D::Translate(stars[k].translateX, 0);
					stars[k].starMatrix *= transform2D::Rotate(stars[k].rotate);

					switch (shooters_matrix[i][j].color) {
					case 0:
						RenderMesh2D(meshes["starR"], shaders["VertexColor"], stars[k].starMatrix);
						break;
					case 1:
						RenderMesh2D(meshes["starP"], shaders["VertexColor"], stars[k].starMatrix);
						break;
					case 2:
						RenderMesh2D(meshes["starO"], shaders["VertexColor"], stars[k].starMatrix);
						break;
					case 3:
						RenderMesh2D(meshes["starB"], shaders["VertexColor"], stars[k].starMatrix);
						break;
					}
				 }
			}
		}
		// Render the collectables (stars)
		dropC = rand() % 500;
		if (current_time - last_timeC > dropC && change == true) {
			last_timeC = current_time;
			for (int i = 0; i < 3; i++) {
				int index_x = 800 + rand() % 400;
				int index_y = 200 + rand() % 200;
				collect_stars[i].x = index_x;
				collect_stars[i].y = index_y;
				collect_stars[i].collected = 0;
			}
		}
		change = true;

		for (int i = 0; i < 3; i++) {
			if (collect_stars[i].collected == 0 && collect_stars[i].x) {
				modelMatrix = visMatrix * transform2D::Translate(collect_stars[i].x, collect_stars[i].y);
				modelMatrix *= transform2D::Scale(4, 4);
				RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
				change = false;
			}
		}

		if (change == true)
			last_timeC = current_time;

		for (int i = 0; i < resources; i++) {
			modelMatrix = visMatrix * transform2D::Translate(900 + 60 * i, 600);
			modelMatrix *= transform2D::Scale(2, 2);
			RenderMesh2D(meshes["starG"], shaders["VertexColor"], modelMatrix);
		}

	}

	for (int i = 0; i < lives; i++) {
		modelMatrix = visMatrix * transform2D::Translate(950 + 100 * i, 650) * transform2D::Scale(6, 6);
		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
	}
}


void Tema1::FrameEnd()
{
}


void Tema1::DrawScene(glm::mat3 visMatrix)
{
	// Render the rhombuses: 125 x 125 rhombuses, with a distance of 50 between them
	for (int i = 0; i < 4; i++) {
		shooters[i].initX = first_rowx_S + length_S / 2 - 12.5f + dist_between_S * i;
		shooters[i].initY = 720 - length_S / 2 - 12.5f;
		modelMatrix = visMatrix * transform2D::Translate(shooters[i].initX, shooters[i].initY);
		RenderMesh2D(meshes["rhombus"], shaders["VertexColor"], modelMatrix);
	}

	// Render the scaled squares in order to complete the shooters
	for (int i = 0; i < 4; i++) {
		shooters[i].initX = first_rowx_S + length_S / 2 - 12.5f + dist_between_S * i;
		shooters[i].initY = 720 - length_S / 2 - 12.5f;

		modelMatrix = visMatrix * transform2D::Translate(shooters[i].initX, shooters[i].initY - length_S * 0.1f);
		modelMatrix *= transform2D::Scale(0.4f, 0.2f);
		switch (i) {
		case 0:
			RenderMesh2D(meshes["Shooter1"], shaders["VertexColor"], modelMatrix);
			shooters[i].color = 0;
			break;
		case 1:
			RenderMesh2D(meshes["Shooter2"], shaders["VertexColor"], modelMatrix);
			shooters[i].color = 1;
			break;
		case 2:
			RenderMesh2D(meshes["Shooter3"], shaders["VertexColor"], modelMatrix);
			shooters[i].color = 2;
			break;
		case 3:
			RenderMesh2D(meshes["Shooter4"], shaders["VertexColor"], modelMatrix);
			shooters[i].color = 3;
			break;
		}
	}

	// Render the cells for the rhombus: 4 cells
	// 720 is the height of the window, the cells must be placed lower
	// considering their lenght and the distance between them (which is 12.5)
	modelMatrix = visMatrix * transform2D::Translate(first_rowx_S, 720 - length_S - 12.5f);
	for (int i = 0; i < 4; i++) {
		RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(dist_between_S, 0);

		// render the cost of each shooter (rhombus)
		int first_star;
		if (i == 0) {
			first_star = first_rowx_S + (length_S - 30) / 2 + 15;
			starMatrix = visMatrix * transform2D::Translate(first_star, 720 - length_S - 12.5f * 3);
			starMatrix *= transform2D::Scale(1.5f, 1.5f);
			RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
		}
		else if (i == 1 || i == 2) {
			first_star = first_rowx_S + i * dist_between_S + (length_S - 30 * 2 + 10) / 2 + 15 / 2;
			for (int j = 0; j < 2; j++) {
				starMatrix = visMatrix * transform2D::Translate(first_star + 40 * j,
					720 - length_S - 12.5f * 3);
				starMatrix *= transform2D::Scale(1.5f, 1.5f);
				RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
			}
		}
		else {
			first_star = first_rowx_S + i * dist_between_S - (4 * 30 + 3 * 10 - length_S) / 2 + 15;
			for (int j = 0; j <= i; j++) {
				starMatrix = visMatrix * transform2D::Translate(first_star + 40 * j,
					720 - length_S - 12.5f * 3);
				starMatrix *= transform2D::Scale(1.5f, 1.5f);
				RenderMesh2D(meshes["star"], shaders["VertexColor"], starMatrix);
			}
		}
	}

	// Render a small "background" area for the top of the screen, where the
	// diamonds (rhombus) and the resources (stars) are displayed
	// The area will be 1280 x 156.25
	modelMatrix = visMatrix * transform2D::Translate(0, 563.75f);
	modelMatrix *= transform2D::Scale(10.24f, 1.25f);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

	// Render the cells: 125 x 125 squares, with a distance of 50 between them
	for (int j = 0; j < 3; j++) {
		modelMatrix = visMatrix * transform2D::Translate(first_rowx, first_rowy + j * dist_between);
		// Render the row j
		for (int i = 0; i < 3; i++) {
			if (j % 2 == 0) {
				if (i % 2 == 0) {
					RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
					modelMatrix *= transform2D::Translate(dist_between, 0);
				}
				else {
					RenderMesh2D(meshes["square12"], shaders["VertexColor"], modelMatrix);
					modelMatrix *= transform2D::Translate(dist_between, 0);
				}
			}
			else {
				if (i % 2 == 0) {
					RenderMesh2D(meshes["square12"], shaders["VertexColor"], modelMatrix);
					modelMatrix *= transform2D::Translate(dist_between, 0);
				}
				else {
					RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
					modelMatrix *= transform2D::Translate(dist_between, 0);
				}
			}
			
		}
	}
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{

}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event

	int real_mouseY = 720 - mouseY;
	for (int i = 0; i < 4; i++) {
		if (shooters[i].pressed) {
			shooters[i].moveX = mouseX - first_rowx_S - i * dist_between_S - length_S / 2;
			shooters[i].moveY = real_mouseY - 720 + length_S / 2 + 12.5f;
		}
	}
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event

	// if the left mouse button is pressed, check if the mouse is over a shooter
	// if it is, then the shooter will be selected

	int real_mouseY = 720 - mouseY;

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		for (int i = 0; i < 4; i++) {
			int rowx = first_rowx_S + i * dist_between_S;
			int rowy = 720 - length_S - 12.5f;
			if (mouseX >= rowx && mouseX <= rowx + length_S) {
				if (real_mouseY >= rowy && real_mouseY <= rowy + length_S) {
					shooters[i].moveX = mouseX - first_rowx_S - i * dist_between_S - length_S / 2;
					shooters[i].moveY = real_mouseY - 720 + length_S / 2 + 12.5f;
					shooters[i].pressed = 1;
					break;
				}
			}
		}

		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				int rowx = first_rowx + i * dist_between;
				int rowy = first_rowy + j * dist_between;
				if (mouseX >= rowx && mouseX <= rowx + length_S) {
					if (real_mouseY >= rowy && real_mouseY <= rowy + length_S) {
						if (shooters_matrix[i][j].placed == 1) {
							shooters_matrix[i][j].t_star = 0;
							shooters_matrix[i][j].t_star_last = 0;
							shooters_matrix[i][j].moveX = 0;
							shooters_matrix[i][j].moveY = 0;
							shooters_matrix[i][j].pressed = 0;
							shooters_matrix[i][j].placed = -1;
						}
					}
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (collect_stars[i].collected == 0) {
				if (mouseX >= collect_stars[i].x - 30 && mouseX <= collect_stars[i].x + 30) {
					if (real_mouseY >= collect_stars[i].y - 30 && real_mouseY <= collect_stars[i].y + 30) {
						collect_stars[i].collected = 1;
						resources++;
						break;
					}
				}
			}
		}
	}
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
	for (int i = 0; i < 4; i++) {
		if (shooters[i].pressed) {
			shooters[i].pressed = 0;
			shooters[i].moveX = 0;
			shooters[i].moveY = 0;

			// check if the mouse was over a cell designated for the rhombus
			// if it was, then the rhombus will be placed there

			int real_mouseY = 720 - mouseY;
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					int rowx = first_rowx + j * dist_between;
					int rowy = first_rowy + k * dist_between;
					if (mouseX > rowx && mouseX < rowx + 125 && real_mouseY > rowy && real_mouseY < rowy + 125
														&& shooters_matrix[j][k].placed == -2) {
						int final = resources;

						if (shooters[i].color == 0)
							final -= 1;
						else if (shooters[i].color == 1)
							final -= 2;
						else if (shooters[i].color == 2)
							final -= 2;
						else
							final -= 4;
						
						if (final >= 0) {
							shooters_matrix[j][k].moveX = 0;
							shooters_matrix[j][k].moveY = 0;
							shooters_matrix[j][k].color = shooters[i].color;
							shooters_matrix[j][k].pressed = 0;
							shooters_matrix[j][k].placed = 1;
							shooters_matrix[j][k].Matrix1 = visMatrix * transform2D::Translate(shooters_matrix[j][k].initX,
								shooters_matrix[j][k].initY);
							shooters_matrix[j][k].Matrix2 = visMatrix * transform2D::Translate(shooters_matrix[j][k].initX,
								shooters_matrix[j][k].initY - length_S * 0.1f);
							shooters_matrix[j][k].Matrix2 *= transform2D::Scale(0.4f, 0.2f);

							resources = final;

							int first = (j * 3) + k;
							for (int l = 5 * first; l < 5 * (first + 1); l++) {
								stars[l].starMatrix = visMatrix * transform2D::Translate(shooters_matrix[j][k].initX,
									shooters_matrix[j][k].initY);
							}
						}
					}
				}
			}
		}
	}
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
