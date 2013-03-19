#version 150
/// \brief the vertex passed in
in vec3 inVert;
/// \brief the normal passed in
in vec3 inNormal;
/// \brief the in uv
in vec2 inUV;

//uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix;

struct Lights
{
    vec4 pos;
};

uniform Lights light;

out vec4 lightPos;

out vec4 vert_in_MV_pos;

out vec3 fragmentNormal;

/// \brief The uvs of the object
out vec2 vertUV;

void main()
{
    // calculate the fragments surface normal
    fragmentNormal = normalMatrix*inNormal;

    // calculate the vertex position
    gl_Position = MVP * vec4(inVert,1.0);

    vert_in_MV_pos = MV * vec4(inVert, 1.0);

    vertUV = inUV;

    lightPos = light.pos;
}
