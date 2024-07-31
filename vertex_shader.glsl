#version 330 core
layout(location = 0) in vec3 position;

// We take this variable from the CPU to decide the color to paint
uniform int typeToPaint;
flat out int colorToPaint;

// These are the three matrices we use to do Linear Algebra stuffs
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    colorToPaint = typeToPaint;
    gl_Position = projection * view * model * vec4(position, 1.0);
}

