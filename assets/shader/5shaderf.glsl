#version 150
uniform sampler2D texture;
uniform sampler2D texture1;

varying vec4 texc;

uniform float time;
uniform vec2 resolution;

const float PI = 3.1415926535897932384626433832795;

vec3 gauss(sampler2D tex, float sampleOffset){
    vec3 sum = vec3(0,0,0);
    sum += texture2D( tex, texc.xy + -10.0 * sampleOffset ).rgb * 0.009167927656011385;
    sum += texture2D( tex, texc.xy +  -9.0 * sampleOffset ).rgb * 0.014053461291849008;
    sum += texture2D( tex, texc.xy +  -8.0 * sampleOffset ).rgb * 0.020595286319257878;
    sum += texture2D( tex, texc.xy +  -7.0 * sampleOffset ).rgb * 0.028855245532226279;
    sum += texture2D( tex, texc.xy +  -6.0 * sampleOffset ).rgb * 0.038650411513543079;
    sum += texture2D( tex, texc.xy +  -5.0 * sampleOffset ).rgb * 0.049494378859311142;
    sum += texture2D( tex, texc.xy +  -4.0 * sampleOffset ).rgb * 0.060594058578763078;
    sum += texture2D( tex, texc.xy +  -3.0 * sampleOffset ).rgb * 0.070921288047096992;
    sum += texture2D( tex, texc.xy +  -2.0 * sampleOffset ).rgb * 0.079358891804948081;
    sum += texture2D( tex, texc.xy +  -1.0 * sampleOffset ).rgb * 0.084895951965930902;
    sum += texture2D( tex, texc.xy +   0.0 * sampleOffset ).rgb * 0.086826196862124602;
    sum += texture2D( tex, texc.xy +  +1.0 * sampleOffset ).rgb * 0.084895951965930902;
    sum += texture2D( tex, texc.xy +  +2.0 * sampleOffset ).rgb * 0.079358891804948081;
    sum += texture2D( tex, texc.xy +  +3.0 * sampleOffset ).rgb * 0.070921288047096992;
    sum += texture2D( tex, texc.xy +  +4.0 * sampleOffset ).rgb * 0.060594058578763078;
    sum += texture2D( tex, texc.xy +  +5.0 * sampleOffset ).rgb * 0.049494378859311142;
    sum += texture2D( tex, texc.xy +  +6.0 * sampleOffset ).rgb * 0.038650411513543079;
    sum += texture2D( tex, texc.xy +  +7.0 * sampleOffset ).rgb * 0.028855245532226279;
    sum += texture2D( tex, texc.xy +  +8.0 * sampleOffset ).rgb * 0.020595286319257878;
    sum += texture2D( tex, texc.xy +  +9.0 * sampleOffset ).rgb * 0.014053461291849008;
    sum += texture2D( tex, texc.xy + +10.0 * sampleOffset ).rgb * 0.009167927656011385;
    return sum;
}

void main() {

    float sampleOffset = (cos(time/2.0))*5.0/resolution.x;

    gl_FragColor = vec4( mix(gauss(texture,sampleOffset),gauss(texture1,5.0/resolution.x-sampleOffset),(cos(time/2.0)+1.0)/2.0),1.0) ;

}
