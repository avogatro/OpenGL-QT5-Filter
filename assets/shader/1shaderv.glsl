#version 120
uniform mat4 matrix;


attribute vec4 vertex;
attribute vec4 texCoord;

varying vec4 texc;
varying vec3 normal;
varying vec3 eyeVec;

const int  MAX_LIGHTS = 8;
const int   NUM_LIGHTS = 3;

varying vec3 lightDir[MAX_LIGHTS];

void main()
{
  gl_Position = matrix*vertex;
  texc = texCoord;
  normal = gl_NormalMatrix * gl_Normal;
  vec4 vVertex = matrix * vertex;
  eyeVec = -vVertex.xyz;
  int i;
  for (i=0; i<NUM_LIGHTS; ++i)
    lightDir[i] =
      vec3(gl_LightSource[i].position.xyz - vVertex.xyz);
}
