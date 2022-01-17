#include <glad/glad.h>
#include <view.h>


void setViewMatrix(unsigned int shaderProgram, float x, float y)
{
	float view[4][4] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	view[3][0] = x;
	view[3][1] = y;

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "View"), 1, GL_FALSE, &view[0][0]);
}
