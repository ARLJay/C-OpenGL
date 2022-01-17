#pragma once

struct objects
{
	float Positions[200]; //2 * 4 positions per mass
	float Masses[25];
	unsigned int Count;
};

struct objects* ReturnObjects();
void CreateObject(float x, float y, float width, float height, float mass);
void ApplyGravity(float g);
