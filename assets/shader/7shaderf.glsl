uniform float time;
uniform vec2 resolution;
uniform sampler2D texture;

void main(void) {

vec2 temp =  gl_FragCoord.xy/ vec2(1280*0.7,720*0.7);
vec2 cPos = -1.0 + 2.0 * temp;
float cLength = length(cPos);

vec2 uv = temp+(cPos/cLength)*cos(cLength*12.0-time*4.0)*0.03;
vec3 col = texture2D(texture,uv).xyz;

gl_FragColor = vec4(col,1.0);
}
