#version 150

uniform vec4 Colour;

// this is a pointer to the current 2D texture object
uniform sampler2D tex;
// the vertex UV
in vec2 vertUV;

in vec4 lightPos;

in vec4 vert_in_MV_pos;

in vec3 fragmentNormal;

/// \brief[out] output fragment colour
out vec4 fragColour;

void main ()
{
    vec3 vert_to_light = vec3(lightPos - vert_in_MV_pos);

    normalize(vert_to_light);
    normalize(fragmentNormal);

    float diffuse = clamp(dot(fragmentNormal,vert_to_light),0.0,1.0);

    fragColour = (texture2D(tex,vertUV)*Colour ) * (diffuse + vec4(0.8,0.8,0.8,1) );
}
