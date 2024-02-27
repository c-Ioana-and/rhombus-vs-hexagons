#include "Tema1.h"
#include "transform2D.h"

#include <vector>

namespace Render {

	glm::mat3 modelMatrix;
	// function that renders the cells in a row, given the distance between them,
	// the height of the row and the visualization matrix
	void renderRow(int distance, int height, glm::mat3 Matrix) {
			for (int i = 1; i < 4; i++) {
				modelMatrix = Matrix * transform2D::Translate(i * distance, height);
			}
		}
	}


