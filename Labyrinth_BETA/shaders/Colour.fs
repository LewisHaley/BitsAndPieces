#version 150
// The final output colour
out vec4 outColour;

// The colour passed in from the program
uniform vec4 Colour;

void main ()
{
    // Set the output colour to the object colour
    outColour = Colour;
}
