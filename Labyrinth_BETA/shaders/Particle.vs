#version 150
uniform mat4 MVP;

uniform sampler2D Particle;
/// @brief the vertex passed in
in vec4 inVert;

in vec4 inCol;

uniform float Scale;

out vec4 particleCol;

void main(void)
{
  gl_PointSize = clamp(inVert.w*Scale,1,20);
  vec4 pos=vec4(inVert.xyz,1);
  gl_Position = MVP*pos;

  particleCol = inCol;
}
