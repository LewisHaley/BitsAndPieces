#version 150
// this is a pointer to the current 2D texture object
uniform sampler2D tex;
// the vertex UV
in vec2 vertUV;
// the final fragment colour
out vec4 outColour;

uniform vec4 Colour;

void main ()
{
    // set the fragment colour to the current texture
    outColour = texture2D(tex,vertUV);
    outColour = outColour*Colour;
}
