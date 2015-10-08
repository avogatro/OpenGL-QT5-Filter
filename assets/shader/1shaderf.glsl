#version 120

uniform sampler2D texture;
uniform vec4  lightSource;
varying vec4 texc;

varying vec3 normal;
varying vec3 eyeVec;

uniform vec3 lightPos;
 

 
 



const int  MAX_LIGHTS = 8;
const int   NUM_LIGHTS = 3;

varying vec3 lightDir[MAX_LIGHTS];
void main (void)
{

  vec4 final_color =
       texture2D(texture, texc.xy)/2.0;
  vec3 N = normalize(normal);
  int i;
  for (i=0; i<NUM_LIGHTS; ++i)
  {
    vec3 L = normalize(lightDir[i]);
    float lambertTerm = dot(N,L);
    if (lambertTerm > 0.0)
    {
      final_color +=
        gl_LightSource[i].diffuse *
        gl_FrontMaterial.diffuse *
        lambertTerm;
      vec3 E = normalize(eyeVec);
      vec3 R = reflect(-L, N);
      float specular = pow(max(dot(R, E), 0.001),
                           gl_FrontMaterial.shininess);
      final_color += gl_LightSource[i].specular * gl_FrontMaterial.specular * specular;
    }
  }
  gl_FragColor = final_color;
}
