#version 150

out vec4 fragColour;

in vec4 particleCol;

uniform vec4 Colour;

void main ()
{
  fragColour =  particleCol;
}
