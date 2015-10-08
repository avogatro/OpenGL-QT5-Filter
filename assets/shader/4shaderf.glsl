#version 120

uniform sampler2D texture;
varying vec4 texc;

uniform float time;
uniform vec2 resolution;



float orgy(vec2 p) {
	float pl=0., expsmo=0.;
	float t=sin(time*7.);
	float a=-.35+t*.02;
	p*=mat2(cos(a/5.0),sin(a),-sin(a),cos(a));
	p=p*.1+vec2(.726,-.557)+t*.017+vec2(0.,t*.014);
	for (int i=0; i<12; i++) {
		p.x=abs(p.x);
		p=p*2.+vec2(-2.,.84)-t*.04;
		p/=min(dot(p,p),1.06);  
		float l=length(p*p);
		expsmo+=exp(-1.0/abs(l-pl*1.0));
		pl=l;
	}
	return expsmo;
}


void main( void )
{
    vec3 texel = texture2D(texture, texc.xy).rgb;
    gl_FragColor = vec4(texel.x,texel.y,texel.z, 1.0);

    gl_FragColor.r = dot(texel, vec3(.393, .769, .189));
    gl_FragColor.g = dot(texel, vec3(.349, .686, .168));
    gl_FragColor.b = dot(texel, vec3(.272, .534, .131));

}
