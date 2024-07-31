#version 330 core
// This is the shader responsible for the coloring of the vertices we send it. We use a value called colorToPaint obtained from the vertex shader to paint the vertex with that color

flat in int colorToPaint;

out vec4 color;

void main()
{

	if(colorToPaint == 0) // Color for the grid line
	{
		color = vec4(1.0, 1.0, 1.0, 1.0); // White
	}

	// These are colors for the ADD option


	if(colorToPaint == 3) // Color for the house
	{
		color = vec4(0.5, 0.5, 0.5, 1.0); // Gray
	}

	if(colorToPaint == 1) // Color for the tree
	{
		color = vec4(0.0, 1.0, 0.0, 1.0); // Green
	}

	if(colorToPaint == 2) // Color for the vehicle
	{
		color = vec4(0.0, 1.0, 1.0, 1.0); // Cyan
	}

	//These are colors for the MOVE option


	if(colorToPaint == 30) // Color for the house but dim.
	{
		color = vec4(0.5, 0.5, 0.5, 0.1); // Gray
	}

	if(colorToPaint == 10) // Color for the tree but dim.
	{
		color = vec4(0.0, 1.0, 0.0, 0.0); // Green
	}

	if(colorToPaint == 20) // Color for the vehicle but dim.
	{
		color = vec4(0.0, 1.0, 1.0, 0.1); // Cyan
	}


}

