#include <glad/glad.h>
#include <ortho.h>

//void setOrthoMatrix(unsigned int shaderProgram, float left, float right, float top, float bottom, float near, float far)
//{
//	float xx = 2/(right - left);
//	float yy = 2/(top - bottom);
//	float zz = (-2)/(far - near);
//
//	float tx = -1 * ((right + left)/(right - left));
//	float ty = -1 * ((top + bottom)/(top - bottom));
//	float tz = -1 * ((far + near)/(far - near));
//
//	float ortho[16] = {xx, 0.0, 0.0, tx, 
//										 0.0, yy, 0.0, ty,
//										 0.0, 0.0, zz, tz,
//										 0.0, 0.0, 0.0, 1.0};
//
//	glUniform4fv(glGetUniformLocation(shaderProgram, "ViewProjection"), 1, GL_FALSE, &ortho[0]);
//}

void setOrthoMatrix(unsigned int shaderProgram, float left, float right, float top, float bottom, float near, float far)
{
	float xx = 2/(right - left);
	float yy = 2/(top - bottom);
	float zz = (-2)/(far - near);

	float tx = -1 * ((right + left)/(right - left));
	float ty = -1 * ((top + bottom)/(top - bottom));
	float tz = -1 * ((far + near)/(far - near));

	float ortho[4][4] = {
		{xx, 0.0, 0.0, tx},
		{0.0, yy, 0.0, ty},
		{0.0, 0.0, zz, tz},
		{0.0, 0.0, 0.0, 1.0}
	};

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "Projection"), 1, GL_FALSE, &ortho[0][0]);
}
