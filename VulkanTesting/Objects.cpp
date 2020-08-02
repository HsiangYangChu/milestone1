#include "Objects.h"



Objects::Objects() {
}


Objects::~Objects() {
}


std::vector<VertexData> Objects::generateBoxData(glm::vec3 size,
	glm::vec3 translation, glm::vec4 rotation, 
	glm::vec4 color) {

	std::vector<glm::vec3> positions;
	float half_x = size.x * 0.5f;
	float half_y = size.y * 0.5f;
	float half_z = size.z * 0.5f;

	/*    y 
	 *    2 ---- 3
	 *   /|     /|
	 *  6 ---- 7 |
	 *  | 0 ---- 1 --> x
	 *  |/     |/
	 *  4 ---- 5
	 */
	positions.push_back(glm::vec3(-half_x, -half_y, -half_z));
	positions.push_back(glm::vec3(half_x, -half_y, -half_z));
	positions.push_back(glm::vec3(-half_x, half_y, -half_z));
	positions.push_back(glm::vec3(half_x, half_y, -half_z));
	positions.push_back(glm::vec3(-half_x, -half_y, half_z));
	positions.push_back(glm::vec3(half_x, -half_y, half_z));
	positions.push_back(glm::vec3(-half_x, half_y, half_z));
	positions.push_back(glm::vec3(half_x, half_y, half_z));
	glm::mat4 tMatrix = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 rMatrix = glm::rotate(glm::mat4(1.0f), rotation.a, glm::vec3(rotation));
	glm::mat4 trMatrix = tMatrix * rMatrix;
	for (int i = 0; i < positions.size(); i++) {
		glm::vec4 pos = trMatrix * glm::vec4(positions[i], 1.0f);
		positions[i] = glm::vec3(pos);
	}

	std::vector<VertexData> data;
	int positionIndex[24]{
		0,1,2,3,  // back
		5,4,7,6,  // front
		1,5,3,7,  // right
		4,0,6,2,  // left
		7,6,3,2,  // top
		1,0,5,4,  // bottom
	};
	glm::vec3 norms[6]{
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f)
	};
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			data.push_back({ positions[positionIndex[i * 4 + j]], norms[i], color });
		}
	}
	return data;
}


std::vector<VertexData> Objects::generateSceneData() {

	std::vector<glm::vec3> positions;
	float y = 548.8f;
	float z = 559.2f;

	/*    y
	 *    7 ---- 4
	 *   /|     /|
	 *  6 ---- 5 |
	 *  | 1 ---- 0 --> x
	 *  |/     |/
	 *  2 ---- 3
	 */
	positions.push_back(glm::vec3(552.8f, 0.0f, 0.0f));
	positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	positions.push_back(glm::vec3(0.0f, 0.0f, z));
	positions.push_back(glm::vec3(549.6f, 0.0f, z));
	positions.push_back(glm::vec3(556.0f, y, 0.0f));
	positions.push_back(glm::vec3(556.0f, y, z));
	positions.push_back(glm::vec3(0.0f, y, z));
	positions.push_back(glm::vec3(0.0f, y, 0.0f));

	std::vector<VertexData> data;
	int positionIndex[20]{
		0,1,2,3,  // bottom
		4,5,6,7,  // top
		6,5,3,2,  // front
		7,6,2,1,  // left
		0,3,5,4,  // right
	};
	glm::vec3 norms[5]{
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f)
	};
	glm::vec4 colors[5]{
		glm::vec4(0.4f, 0.4f, 0.4f, 1.0f),
		glm::vec4(0.4f, 0.4f, 0.4f, 1.0f),
		glm::vec4(0.4f, 0.4f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)
	};
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			data.push_back({ positions[positionIndex[i * 4 + j]], norms[i], colors[i] });
		}
	}
	return data;
}


std::vector<uint16_t> Objects::generateIndex(uint16_t startIndex, bool isScene) {
	std::vector<uint16_t> indexData;

	if (isScene) {
		for (int i = 0; i < 5; i++) {
			// left up triangle
			indexData.push_back(startIndex + 4 * i);
			indexData.push_back(startIndex + 4 * i + 1);
			indexData.push_back(startIndex + 4 * i + 2);
			// right down triangle
			indexData.push_back(startIndex + 4 * i);
			indexData.push_back(startIndex + 4 * i + 2);
			indexData.push_back(startIndex + 4 * i + 3);
		}
		return indexData;
	}
	else {
		for (int i = 0; i < 6; i++) {
			// right up triangle
			indexData.push_back(startIndex + 4 * i);
			indexData.push_back(startIndex + 4 * i + 2);
			indexData.push_back(startIndex + 4 * i + 3);
			// left down triangle
			indexData.push_back(startIndex + 4 * i);
			indexData.push_back(startIndex + 4 * i + 3);
			indexData.push_back(startIndex + 4 * i + 1);
		}
		return indexData;
	}
}
