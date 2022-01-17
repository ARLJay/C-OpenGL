#include <obj.h>

struct objects obj;

struct objects* ReturnObjects()
{
	return &obj;
}

void CreateObject(float x, float y, float width, float height, float mass)
{
	//bottom left, bottom right, top right, top left
	obj.Positions[8*obj.Count]   = x - (width/2);
	obj.Positions[8*obj.Count+1] = y - (height/2);

	obj.Positions[8*obj.Count+2] = x + (width/2);
	obj.Positions[8*obj.Count+3] = y - (height/2);

	obj.Positions[8*obj.Count+4] = x + (width/2);
	obj.Positions[8*obj.Count+5] = y + (height/2);

	obj.Positions[8*obj.Count+6] = x - (width/2);
	obj.Positions[8*obj.Count+7] = y + (height/2);

	obj.Masses[obj.Count] = mass;
	obj.Count++;
}

void ApplyGravity(float g)
{
	for(int i = 0; i < obj.Count; i++)
	{
		if(obj.Positions[8*i + 1] < 0.0f)
		{
			for(int j = 1; j < 8; j+= 2)
			{
				obj.Positions[8*i + j] += g;
			}
		}
	}
}
